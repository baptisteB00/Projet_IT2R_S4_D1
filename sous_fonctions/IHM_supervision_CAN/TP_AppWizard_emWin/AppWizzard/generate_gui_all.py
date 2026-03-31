import os
import sys
import xml.etree.ElementTree as ET
import hashlib

# -----------------------------
# Paths
# -----------------------------
appwizard_dir = os.path.dirname(os.path.abspath(__file__))
appwizard_name = os.path.basename(appwizard_dir)
filelist_txt = os.path.join(appwizard_dir, "FileList.txt")
config_dir = os.path.join(appwizard_dir, "Config")
gui_config_file = os.path.join(config_dir, "gui_config.h")

# -----------------------------
# Find .uvprojx
# -----------------------------
def find_uvprojx_upwards(start_path):
    current = start_path
    while True:
        for f in os.listdir(current):
            if f.endswith(".uvprojx"):
                return os.path.join(current, f)
        parent = os.path.dirname(current)
        if parent == current:
            return None
        current = parent

uvprojx_file = find_uvprojx_upwards(appwizard_dir)
if uvprojx_file is None:
    print("ERROR: No .uvprojx found!")
    sys.exit(1)
print(f"Using Keil project: {uvprojx_file}")

# -----------------------------
# Generate gui_config.h if missing
# -----------------------------
if not os.path.exists(config_dir):
    os.makedirs(config_dir)

if not os.path.exists(gui_config_file):
    with open(gui_config_file, "w") as f:
        f.write("// gui_config.h - align GUI_CONST_STORAGE on 4 bytes\n")
        f.write("#ifndef GUI_CONFIG_H\n#define GUI_CONFIG_H\n\n")
        f.write("#undef GUI_CONST_STORAGE\n")
        f.write("#define GUI_CONST_STORAGE const __attribute__((aligned(4)))\n\n")
        f.write("#endif // GUI_CONFIG_H\n")
    print(f"Created {gui_config_file}")
else:
    print(f"{gui_config_file} already exists")

# -----------------------------
# Load project XML
# -----------------------------
tree = ET.parse(uvprojx_file)
root = tree.getroot()

# -----------------------------
# Update MiscControls to include gui_config.h
# -----------------------------
def ensure_misc_include(header_path):
    changed = False
    for target in root.iter("TargetOptions"):
        misc = target.find("MiscControls")
        if misc is None:
            misc = ET.SubElement(target, "MiscControls")
            misc.text = ""
        if misc.text is None:
            misc.text = ""
        # chemin relatif
        rel_path = os.path.relpath(header_path, start=os.path.dirname(uvprojx_file)).replace("\\", "/")
        inc_str = f'-include "{rel_path}"'
        if inc_str not in misc.text:
            if misc.text.strip():
                misc.text += " "
            misc.text += inc_str
            changed = True
            print(f"Added to MiscControls: {inc_str}")
    return changed

misc_changed = ensure_misc_include(gui_config_file)

# -----------------------------
# Read FileList.txt
# -----------------------------
if not os.path.exists(filelist_txt):
    print(f"ERROR: {filelist_txt} not found!")
    sys.exit(1)

with open(filelist_txt, "r") as f:
    files = [l.strip() for l in f if l.strip()]

# -----------------------------
# Helper functions for groups
# -----------------------------
def file_list_hash(files_node):
    paths = sorted([f.find("FilePath").text.replace("\\","/") for f in files_node.findall("File")])
    return hashlib.md5("".join(paths).encode("utf-8")).hexdigest()

def find_or_create_group(group_name):
    for group in root.iter("Group"):
        name = group.find("GroupName")
        if name is not None and name.text == group_name:
            files_node = group.find("Files")
            if files_node is None:
                files_node = ET.SubElement(group, "Files")
            return group
    groups = root.find(".//Groups")
    new_group = ET.SubElement(groups, "Group")
    ET.SubElement(new_group, "GroupName").text = group_name
    ET.SubElement(new_group, "Files")
    return new_group

def update_group(file_list, group_name, c_type="1"):
    group = find_or_create_group(group_name)
    files_node = group.find("Files")

    existing_files = {}
    for f in files_node.findall("File"):
        path_node = f.find("FilePath")
        if path_node is not None:
            existing_files[path_node.text.replace("\\", "/")] = f

    parent_dir = os.path.dirname(appwizard_dir)
    rel_paths_new = set()
    added = 0
    for fpath in file_list:
        rel_path = os.path.relpath(fpath, start=parent_dir).replace("\\", "/")
        rel_paths_new.add(rel_path)
        if rel_path not in existing_files:
            file_elem = ET.SubElement(files_node, "File")
            ET.SubElement(file_elem, "FileName").text = os.path.basename(rel_path)
            ET.SubElement(file_elem, "FileType").text = c_type
            ET.SubElement(file_elem, "FilePath").text = rel_path
            added += 1

    for path, fnode in list(existing_files.items()):
        if path not in rel_paths_new:
            files_node.remove(fnode)

    return added, group

def ensure_appw_x_fs(group_name="AppWizard Config"):
    fs_file = os.path.join(appwizard_dir, "APPW_X_FS.c")
    if not os.path.exists(fs_file):
        with open(fs_file, "w") as f:
            f.write("// Override AppWizard FS init - filesystem not used\n")
            f.write("void APPW_X_FS_Init(void) { }\n")
        print(f"Created: {fs_file}")

    parent_dir = os.path.dirname(appwizard_dir)
    rel_path = os.path.relpath(fs_file, start=parent_dir).replace("\\", "/")

    group = find_or_create_group(group_name)
    files_node = group.find("Files")
    for f in files_node.findall("File"):
        path_node = f.find("FilePath")
        if path_node is not None and path_node.text.replace("\\","/") == rel_path:
            return False

    file_elem = ET.SubElement(files_node, "File")
    ET.SubElement(file_elem, "FileName").text = "APPW_X_FS.c"
    ET.SubElement(file_elem, "FileType").text = "1"
    ET.SubElement(file_elem, "FilePath").text = rel_path
    print(f"Added to project group '{group_name}': {rel_path}")
    return True

# -----------------------------
# Separate Source / Resource files
# -----------------------------
def get_appwizard_root_folder(fpath):
    parts = os.path.normpath(fpath).split(os.sep)
    try:
        idx = parts.index(appwizard_name)
        return parts[idx + 1]
    except (ValueError, IndexError):
        return None

source_files = [f for f in files
                if get_appwizard_root_folder(f) == "Source"
                and os.path.splitext(f)[1].lower() == ".c"]

resource_files = [f for f in files
                  if get_appwizard_root_folder(f) == "Resource"
                  and os.path.splitext(f)[1].lower() == ".c"]

# -----------------------------
# Update groups
# -----------------------------
added_src, group_src = update_group(source_files, "Source AppWizard", c_type="1")
added_res, group_res = update_group(resource_files, "Resource AppWizard", c_type="1")
added_fs = ensure_appw_x_fs("AppWizard Config")

hash_before_src = file_list_hash(group_src)
hash_before_res = file_list_hash(group_res)

hash_after_src = file_list_hash(group_src)
hash_after_res = file_list_hash(group_res)

# -----------------------------
# Save project only if needed
# -----------------------------
if (added_src or added_res or added_fs or misc_changed or
    hash_before_src != hash_after_src or
    hash_before_res != hash_after_res):
    tree.write(uvprojx_file, encoding="utf-8", xml_declaration=True)
    print(f"{added_src} source files added/updated in 'Source AppWizard'")
    print(f"{added_res} resource files added/updated in 'Resource AppWizard'")
    print("Project updated successfully!")
else:
    print("No changes to project, .uvprojx not modified.")
import os
import sys

# Détecter dossier du script (ou de l'exécutable si PyInstaller était utilisé)
base_path = os.path.dirname(os.path.abspath(__file__))

# Fichier d'entrée et sortie
input_file = os.path.join(base_path, "FileList.txt")
output_file = os.path.join(base_path, "GUI_All.c")

# Vérifier que FileList.txt existe
if not os.path.exists(input_file):
    print(f"ERROR: {input_file} not found!")
    sys.exit(1)

# Lecture et génération de GUI_All.c
with open(input_file, "r") as f:
    lines = f.readlines()

with open(output_file, "w") as f:
    f.write("// Auto-generated file to include all AppWizard sources/resources\n\n")

    # Désactiver APPW_X_FS_Init proprement
    f.write("// Disable APPW_X_FS_Init()\n")
    f.write("static inline void APPW_X_FS_Init(void) { }\n\n")

    for line in lines:
        line = line.strip()
        if line.endswith(".c"):
            # utiliser chemin relatif si possible
            rel_path = os.path.relpath(line, base_path).replace("\\", "/")
            f.write(f'#include "{rel_path}"\n')

print(f"{output_file} generated with {len(lines)} includes.")
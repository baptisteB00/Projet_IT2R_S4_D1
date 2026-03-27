@echo off
REM Appelle le script Python pour générer GUI_All.c
python "%~dp0generate_gui_all.py"
IF %ERRORLEVEL% NEQ 0 (
    echo Failed to generate GUI_All.c
    exit /b 1
)
echo GUI_All.c generated successfully.
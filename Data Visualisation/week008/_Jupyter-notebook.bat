@echo off
cls

echo.
echo This bat will open Juypter Notebooks in the following directory.
echo.
echo     G:\Python
echo.

if not exist "G:\Python" mkdir G:\Python

REM >G:\Python\_Jupyter-notebook-output.txt (
REM Silent install of required packages not included by default
REM conda install -y basemap hvplot panel

REM Silent install packages requiring PIP installing
c:\Institutions\Gre\Apps\Python-Anaconda-3-2019.07\Scripts\pip.exe install sklearn hvplot "panel==0.8.0" "bokeh==1.4.0"

REM Run Jupyter-notebook-script pointing at G:\Python
c:\Institutions\Gre\Apps\Python-Anaconda-3-2019.07\python.exe c:\Institutions\Gre\Apps\Python-Anaconda-3-2019.07\Scripts\jupyter-notebook-script.py G:\Python
REM )

exit

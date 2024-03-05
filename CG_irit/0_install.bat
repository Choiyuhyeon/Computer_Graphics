@echo off

setx IRIT_BIN_IPC "1" -m
setx IRIT_DISPLAY "wntgdrvs64 -s-" -m
setx IRIT_PATH "C:/CG_irit/" -m
setx IRIT_PARALLEL "4" -m

mkdir "c:\Users\%USERNAME%\AppData\guirit"
copy "c:\CG_irit\Guirit64.cfg" "c:\Users\%USERNAME%\AppData\guirit"
copy "c:\CG_irit\GuiritGui64.cfg" "c:\Users\%USERNAME%\AppData\guirit"
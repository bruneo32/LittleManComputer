@echo off

echo Building  "lmc.c"
tcc lmc.c	-o bin\lmc.exe		-m32
if %ERRORLEVEL% NEQ 0 goto :err

echo Building  "lma.c"
tcc lma.c	-o bin\lma.exe		-m32
if %ERRORLEVEL% NEQ 0 goto :err


echo Creating lmc.zip
7za a -tzip lmc.zip examples >nul
move lmc.zip bin\lmc.zip >nul
cd bin
7za a -tzip lmc.zip lmc.exe lma.exe >nul
cd ..


goto end
:err
pause

:end

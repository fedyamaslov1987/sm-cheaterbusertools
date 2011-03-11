@SET SEVENZ="c:\Program Files\7-Zip\7z.exe"
@SET MYPATH=%~dp0
@cd /d %MYPATH%\cheatbustertools
del /F %MYPATH%cheatbustertools.zip
@%SEVENZ% a %MYPATH%cheatbustertools.zip @%MYPATH%packagefiles.txt
@cd /d %MYPATH%
pause
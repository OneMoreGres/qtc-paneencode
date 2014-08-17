@echo off
set VERSION=3.1.2
set PLUGIN_NAME=QtcPaneEncode
set BUILD_DIR=c:\Projects\qt-creator\3.1.2\qtcreator-5.3.0-vc10-release
del %PLUGIN_NAME%-%VERSION%-win.zip

rd /Q /S dist
mkdir dist\lib\qtcreator\plugins\Gres
mkdir dist\share\qtcreator\translations
copy /Y %BUILD_DIR%\lib\qtcreator\plugins\Gres\%PLUGIN_NAME%.dll        dist\lib\qtcreator\plugins\Gres
copy /Y %BUILD_DIR%\lib\qtcreator\plugins\Gres\%PLUGIN_NAME%.pluginspec dist\lib\qtcreator\plugins\Gres
copy /Y ..\translation\*.qm                                             dist\share\qtcreator\translations

cd dist
zip -q -r ../%PLUGIN_NAME%-%VERSION%-win.zip *
cd ..

rd /Q /S dist

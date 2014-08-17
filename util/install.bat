@echo off
set PLUGIN_NAME=QtcPaneEncode
set BUILD_DIR=c:\Projects\qt-creator\3.1.2\qtcreator-5.3.0-vc10-release
set INSTALL_DIR=c:\Qt\Qt5\Tools\QtCreator\
mkdir %INSTALL_DIR%\lib\qtcreator\plugins\Gres
@echo on

copy /Y %BUILD_DIR%\lib\qtcreator\plugins\Gres\%PLUGIN_NAME%.dll        %INSTALL_DIR%\lib\qtcreator\plugins\Gres
copy /Y %BUILD_DIR%\lib\qtcreator\plugins\Gres\%PLUGIN_NAME%.pluginspec %INSTALL_DIR%\lib\qtcreator\plugins\Gres
copy /Y ..\translation\*.qm                                             %INSTALL_DIR%\share\qtcreator\translations

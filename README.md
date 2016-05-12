#Qt Creator panes encoding change

##Introduction
Allows to change encoding of application and compiler ouput panes.
Useful in cases when application generates output not in local encoding and it cannot be changed.
Plugin automatically detects line encoding and converts it to unicode (QString).
However 100% match can not be guaranteed

Charset detection provided by [third-party library](https://github.com/batterseapower/libcharsetdetect).

##Distribution
Prebuilt binaries (win) can be found [here](https://sourceforge.net/projects/qtc-paneencode/files/bin)

##Installation
IMPORTANT: plugin's version must match Qt Creator's version (difference in last digit is acceptable)

###From source
1. Change paths.pri:

 - set `QTCREATOR_SOURCES` = path to Qt Creator source dir (with qtcreator.pro)
 - set `IDE_BUILD_TREE` = path to compiled Qt Creator dir (with bin,lib,libexec,...)

2. Compile plugin.

###From binaries
1. Extract/copy files from archive into Qt Creator's dir (archive already contains proper paths).
2. Enable plugin in Help->Modules menu.

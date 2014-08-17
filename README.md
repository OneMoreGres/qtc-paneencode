#Qt Creator panes encoding change

##Introduction
Allows to change encoding of application and compiler ouput panes.
Useful in cases when application generates output not in local encoding and it cannot be changed.
Plugin automatically detects line encoding and converts it to unicode (QString).
However 100% match can not be guaranteed

Charset detection provided by [third-party library](https://github.com/batterseapower/libcharsetdetect).

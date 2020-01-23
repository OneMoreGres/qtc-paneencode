DEFINES += QTCPANEENCODE_LIBRARY

include(paths.pri)

# QtcPaneEncode files

SOURCES += \
    src/QtcPaneEncodePlugin.cpp \
    src/Utils.cpp \
    src/OptionsWidget.cpp \
    src/OptionsPage.cpp

HEADERS += \
    src/Constants.h \
    src/PluginGlobal.h \
    src/QtcPaneEncodePlugin.h \
    src/Utils.h \
    src/OptionsWidget.h \
    src/OptionsPage.h

FORMS += \
    src/OptionsWidget.ui

TRANSLATIONS += \
    translation/QtcPaneEncode_ru.ts

OTHER_FILES += \
    LICENSE.md \
    README.md \
    util/README.md \
    uncrustify.cfg

LIBS += -L$$PWD/third-party/charsetdetect-build/build \
        -L$$PWD/third-party/charsetdetect-build/build/Debug \
        -L$$PWD/third-party/charsetdetect-build/build/Release \
        -lcharsetdetect
INCLUDEPATH += $$PWD/third-party/charsetdetect

PROVIDER = Gres

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = QtcPaneEncode
QTC_LIB_DEPENDS += \

QTC_PLUGIN_DEPENDS += \
    coreplugin\
    projectexplorer

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)

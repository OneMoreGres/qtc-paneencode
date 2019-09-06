#ifndef QTCPANEENCODECONSTANTS_H
#define QTCPANEENCODECONSTANTS_H

#include <QString>

namespace QtcPaneEncode {
  namespace Constants {
    const char OPTIONS_PAGE_ID[] = "QtcPaneEncode.OptionsPage";
    const char OPTIONS_CATEGORY_ICON[] = ":/core/images/category_buildrun.png"; // same as ProjectExplorer::Constants::PROJECTEXPLORER_SETTINGS_CATEGORY_ICON;

    const QString SETTINGS_GROUP = QLatin1String ("QtcPaneEncode");
    const QString SETTINGS_BUILD_ENABLED = QLatin1String ("buildEnabled");
    const QString SETTINGS_BUILD_ENCODING = QLatin1String ("buildEncoding");
    const QString SETTINGS_APP_ENABLED = QLatin1String ("appEnabled");
    const QString SETTINGS_APP_ENCODING = QLatin1String ("appEncoding");

    const QString AUTO_ENCODING = QLatin1String ("Auto");
  } // namespace QtcPaneEncode
} // namespace Constants

#endif // QTCPANEENCODECONSTANTS_H


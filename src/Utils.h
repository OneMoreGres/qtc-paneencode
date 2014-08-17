#ifndef UTILS_H
#define UTILS_H

#include <QTextCodec>

namespace QtcPaneEncode {
  namespace Internal {
    //! Change encoding of source string if needed.
    QString reencode(const QString &source);

  } // namespace Internal
} // namespace QtcPaneEncode

#endif // UTILS_H

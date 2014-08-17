#ifndef UTILS_H
#define UTILS_H

#include <QTextCodec>

namespace QtcPaneEncode {
  namespace Internal {
    //!
    /*!
     * \brief Change encoding of source string if needed.
     * \param source [in] Text to change encoding.
     * \param codec [in] Codec of resulting text. If NULL then it
     * will be detected automatically.
     * \return Reencoded string.
     */
    QString reencode(const QString &source, const QTextCodec *codec = NULL);

  } // namespace Internal
} // namespace QtcPaneEncode

#endif // UTILS_H

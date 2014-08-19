#include <QDebug>

#include "Utils.h"

#ifdef USE_ICU
#include "unicode/ucsdet.h"
QTextCodec *detectCodec(const QByteArray &source) {
  // Using ICU lib.
  Q_ASSERT(!source.isEmpty());
  UErrorCode error = U_ZERO_ERROR;
  UCharsetDetector *detector = ucsdet_open(&error);
  if(detector == NULL) {
    qCritical() << "codec detector open failed" << error << u_errorName(error);
    return NULL;
  }
  ucsdet_setText(detector, source.data(), source.size(), &error);
  const UCharsetMatch *match = ucsdet_detect(detector, &error);
  if(match == NULL) {
    qCritical() << "codec match failed" << error << u_errorName(error);
    return NULL;
  }

  QByteArray name = ucsdet_getName(match, &error);
  Q_ASSERT(!name.isEmpty());
  ucsdet_close(detector);

  QTextCodec *codec = QTextCodec::codecForName(name);
  return codec;
}
#else
#include "charsetdetect.h"
QTextCodec *detectCodec(const QByteArray &source) {
  csd_t detector = csd_open();
  if(detector <= 0) {
    qCritical() << "codec detector open failed";
    return NULL;
  }
  csd_consider(detector, source.data(), source.size());
  QByteArray name = csd_close(detector);
  QTextCodec *codec = QTextCodec::codecForName(name);
  return codec;
}
#endif

namespace {
  const QChar separator = QLatin1Char(' ');
  const int minLength = 3; // To avoid of too short strings detection
}

QString QtcPaneEncode::Internal::reencode(const QString &source, const QTextCodec *codec) {
  if (codec != NULL) {
    return codec->toUnicode (source.toLocal8Bit ());
  }
  // Detectors use only part of string to detect encoding.
  // So function splits source string into some parts.
  QString detectBuffer;
  QString result;
  for(int i = 0, end = source.size(); i <= end; ++i) {
    QChar curChar;
    if(i < end) {
      curChar = source.at(i);
      if(curChar != separator || detectBuffer.length() < minLength) {
        detectBuffer += curChar;
        continue;
      }
    }

    if(!detectBuffer.isEmpty()) {
      QByteArray rawSource = detectBuffer.toLocal8Bit();
      QTextCodec *codec = detectCodec(rawSource);
      result +=(codec != NULL) ? codec->toUnicode(rawSource)
                                : detectBuffer;
      detectBuffer.clear();
    }

    if(!curChar.isNull()) { // ignore last one(i == end)
      result += curChar;
    }
  }
  return result;
}

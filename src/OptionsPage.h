#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include <QPointer>

#include <coreplugin/dialogs/ioptionspage.h>

namespace QtcPaneEncode {
  namespace Internal {

    class Settings;
    class OptionsWidget;

    /*!
     * \brief Options page.
     * Creates edition widget. Emits settingsChanged().
     */
    class OptionsPage : public Core::IOptionsPage
    {
        Q_OBJECT
      public:
        explicit OptionsPage(QObject *parent = 0);
        ~OptionsPage ();

        bool matches(const QString &searchKeyWord) const;
        QWidget *widget();
        QWidget *createPage(QWidget *parent);
        void apply();
        void finish();

      signals:
        void settingsChanged ();

      private:
        QPointer<OptionsWidget> widget_;
        QStringList keyWords_;
    };

  } // namespace Internal
} // namespace QtcPaneEncode


#endif // OPTIONSPAGE_H

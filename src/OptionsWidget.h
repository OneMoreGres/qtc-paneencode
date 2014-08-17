#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>

namespace Ui {
  class OptionsWidget;
}

namespace QtcPaneEncode {
  namespace Internal {

    class OptionsWidget : public QWidget
    {
        Q_OBJECT

      public:
        explicit OptionsWidget(QWidget *parent = 0);
        ~OptionsWidget();

        void load();
        void apply();

      private:
        void init();

      private:
        Ui::OptionsWidget *ui;
    };
  } // namespace Internal
} // namespace QtcPaneEncode

#endif // OPTIONSWIDGET_H

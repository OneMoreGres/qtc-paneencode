#include <QSettings>
#include <QTextCodec>

#include <coreplugin/icore.h>

#include "OptionsWidget.h"
#include "ui_OptionsWidget.h"
#include "Constants.h"

using namespace QtcPaneEncode::Internal;
using namespace QtcPaneEncode::Constants;

OptionsWidget::OptionsWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::OptionsWidget)
{
  ui->setupUi(this);
  init();
  load();
}

void OptionsWidget::init(){
  QList<QByteArray> codecs = QTextCodec::availableCodecs();
  ui->buildEncodeCombo->addItem(AUTO_ENCODING);
  ui->appEncodeCombo->addItem(AUTO_ENCODING);
  foreach(const QByteArray &codec, codecs) {
    QString name = QString::fromUtf8(codec);
    ui->buildEncodeCombo->addItem(name);
    ui->appEncodeCombo->addItem(name);
  }
}

OptionsWidget::~OptionsWidget() {
  delete ui;
}

void OptionsWidget::load() {
  Q_ASSERT(Core::ICore::settings() != NULL);
  QSettings& settings = *(Core::ICore::settings());
  settings.beginGroup(SETTINGS_GROUP);

  ui->buildGroup->setChecked(settings.value(SETTINGS_BUILD_ENABLED, false).toBool());
  ui->buildEncodeCombo->setCurrentText(settings.value(SETTINGS_BUILD_ENCODING, AUTO_ENCODING).toString());

  ui->appGroup->setChecked(settings.value(SETTINGS_APP_ENABLED, false).toBool());
  ui->appEncodeCombo->setCurrentText(settings.value(SETTINGS_APP_ENCODING, AUTO_ENCODING).toString());

  settings.endGroup();
}

void OptionsWidget::apply(){
  Q_ASSERT(Core::ICore::settings() != NULL);
  QSettings& settings = *(Core::ICore::settings());
  settings.beginGroup(SETTINGS_GROUP);

  settings.setValue(SETTINGS_BUILD_ENABLED, ui->buildGroup->isChecked());
  settings.setValue(SETTINGS_BUILD_ENCODING, ui->buildEncodeCombo->currentText());

  settings.setValue(SETTINGS_APP_ENABLED, ui->appGroup->isChecked());
  settings.setValue(SETTINGS_APP_ENCODING, ui->appEncodeCombo->currentText());

  settings.endGroup();
}

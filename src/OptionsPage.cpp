#include "OptionsPage.h"
#include "OptionsWidget.h"
#include "Constants.h"
#include <projectexplorer/projectexplorerconstants.h>

using namespace QtcPaneEncode::Internal;
using namespace QtcPaneEncode::Constants;

OptionsPage::OptionsPage (QObject *parent) :
  IOptionsPage (parent) {
  setId (OPTIONS_PAGE_ID);
  setDisplayName (tr ("Pane encoding"));
  setCategory (ProjectExplorer::Constants::BUILD_AND_RUN_SETTINGS_CATEGORY);
  setCategoryIcon (Utils::Icon (OPTIONS_CATEGORY_ICON));

  keyWords_ << QLatin1String ("encoding") << QLatin1String ("build") <<
    QLatin1String ("output");
}

OptionsPage::~OptionsPage () {
}

bool OptionsPage::matches (const QString &searchKeyWord) const {
  return keyWords_.contains (searchKeyWord);
}

QWidget *OptionsPage::widget () {
  return createPage (NULL);
}

QWidget *OptionsPage::createPage (QWidget *parent) {
  widget_ = new OptionsWidget (parent);
  return widget_.data ();
}

void OptionsPage::apply () {
  Q_ASSERT (!widget_.isNull ());
  widget_->apply ();
  emit settingsChanged ();
}

void OptionsPage::finish () {
}

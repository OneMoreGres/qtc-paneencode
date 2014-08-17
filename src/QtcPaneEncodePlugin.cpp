#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/project.h>
#include <projectexplorer/target.h>
#include <projectexplorer/task.h>
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/buildsteplist.h>
#include <extensionsystem/pluginmanager.h>
#include <projectexplorer/buildmanager.h>

#include "QtcPaneEncodePlugin.h"
#include "Utils.h"
#include "Constants.h"

using namespace QtcPaneEncode::Internal;

using namespace Core;
using namespace ProjectExplorer;
using namespace ExtensionSystem;

namespace {
  const QString appOutputPaneClassName =
      QLatin1String("ProjectExplorer::Internal::AppOutputPane");
}

QtcPaneEncodePlugin::QtcPaneEncodePlugin():
  IPlugin ()
{
  // Create your members
}

QtcPaneEncodePlugin::~QtcPaneEncodePlugin() {
  // Unregister objects from the plugin manager's object pool
  // Delete members
}

bool QtcPaneEncodePlugin::initialize(const QStringList &arguments, QString *errorString) {
  // Register objects in the plugin manager's object pool
  // Load settings
  // Add actions to menus
  // Connect to other plugins' signals
  // In the initialize function, a plugin can be sure that the plugins it
  // depends on have initialized their members.

  Q_UNUSED(arguments)
  Q_UNUSED(errorString)
  return true;
}

void QtcPaneEncodePlugin::extensionsInitialized() {
  // Retrieve objects from the plugin manager's object pool
  // In the extensionsInitialized function, a plugin can be sure that all
  // plugins that depend on it are completely initialized.


  // Compiler output
  connect(BuildManager::instance (), SIGNAL(buildStateChanged(ProjectExplorer::Project*)),
          this, SLOT(handleBuild(ProjectExplorer::Project*)));
  connect(this, SIGNAL(newOutput(QString,ProjectExplorer::BuildStep::OutputFormat,ProjectExplorer::BuildStep::OutputNewlineSetting)),
          BuildManager::instance (), SLOT(addToOutputWindow(QString,ProjectExplorer::BuildStep::OutputFormat,ProjectExplorer::BuildStep::OutputNewlineSetting)));
  connect(this, SIGNAL(newTask(ProjectExplorer::Task)),
          BuildManager::instance (), SLOT(addToTaskWindow(ProjectExplorer::Task)));

  // Run control output
  QObject *appOutputPane = PluginManager::getObjectByClassName(appOutputPaneClassName);
  if (appOutputPane != NULL) {
    connect (ProjectExplorerPlugin::instance (), SIGNAL (runControlStarted(ProjectExplorer::RunControl *)),
             this, SLOT (handleRunStart (ProjectExplorer::RunControl *)));
    connect(this, SIGNAL(newMessage(ProjectExplorer::RunControl*,QString,Utils::OutputFormat)),
            appOutputPane, SLOT(appendMessage(ProjectExplorer::RunControl*,QString,Utils::OutputFormat)));
  }
  else {
    qCritical () << "Failed to find appOutputPane";
  }
}

ExtensionSystem::IPlugin::ShutdownFlag QtcPaneEncodePlugin::aboutToShutdown() {
  // Save settings
  // Disconnect from signals that are not needed during shutdown
  // Hide UI (if you add UI that is not in the main window directly)
  this->disconnect ();
  return SynchronousShutdown;
}

void QtcPaneEncodePlugin::handleBuild(ProjectExplorer::Project *project) {
  if (!BuildManager::isBuilding ()) {
    return;
  }
  Target* target = project->activeTarget ();
  if (target == NULL) {
    return;
  }
  BuildConfiguration* buildCOnfiguration = target->activeBuildConfiguration ();
  if (buildCOnfiguration == NULL) {
    return;
  }
  QList<Core::Id> stepsIds = buildCOnfiguration->knownStepLists ();
  foreach (const Core::Id& id, stepsIds) {
    BuildStepList* steps = buildCOnfiguration->stepList (id);
    if (steps == NULL) {
      continue;
    }
    for(int i = 0, end = steps->count (); i < end; ++i) {
      BuildStep *step = steps->at (i);
      connect(step, SIGNAL(addOutput(QString,ProjectExplorer::BuildStep::OutputFormat,ProjectExplorer::BuildStep::OutputNewlineSetting)),
              this, SLOT(addOutput(QString,ProjectExplorer::BuildStep::OutputFormat,ProjectExplorer::BuildStep::OutputNewlineSetting)),
              Qt::UniqueConnection);
      disconnect(step, SIGNAL(addOutput(QString,ProjectExplorer::BuildStep::OutputFormat,ProjectExplorer::BuildStep::OutputNewlineSetting)),
                 BuildManager::instance (), SLOT(addToOutputWindow(QString,ProjectExplorer::BuildStep::OutputFormat,ProjectExplorer::BuildStep::OutputNewlineSetting)));

      connect(step, SIGNAL(addTask(ProjectExplorer::Task)),
              this, SLOT(addTask(ProjectExplorer::Task)),
              Qt::UniqueConnection);
      disconnect(step, SIGNAL(addTask(ProjectExplorer::Task)),
                 BuildManager::instance (), SLOT(addToTaskWindow(ProjectExplorer::Task)));
    }
  }
}

void QtcPaneEncodePlugin::addTask(const Task &task) {
  Task convertedTask = task;
  convertedTask.description = reencode (task.description);
  emit newTask(convertedTask);
}

void QtcPaneEncodePlugin::addOutput(const QString &string, BuildStep::OutputFormat format, BuildStep::OutputNewlineSetting newlineSetting) {
  QString convertedString = reencode (string);
  emit newOutput (convertedString, format, newlineSetting);
}

void QtcPaneEncodePlugin::handleRunStart(RunControl *runControl) {
  QObject *appOutputPane = PluginManager::getObjectByClassName (appOutputPaneClassName);
  if (appOutputPane != NULL) {
    connect(runControl, SIGNAL(appendMessage(ProjectExplorer::RunControl*,QString,Utils::OutputFormat)),
            this, SLOT(appendMessage(ProjectExplorer::RunControl*,QString,Utils::OutputFormat)),
            Qt::UniqueConnection);
    disconnect (runControl, SIGNAL(appendMessage(ProjectExplorer::RunControl*,QString,Utils::OutputFormat)),
                appOutputPane, SLOT(appendMessage(ProjectExplorer::RunControl*,QString,Utils::OutputFormat)));
  }
}

void QtcPaneEncodePlugin::appendMessage(RunControl *rc, const QString &out, Utils::OutputFormat format) {
  QString convertedOut = reencode (out);
  emit newMessage (rc, convertedOut, format);
}

Q_EXPORT_PLUGIN2(QtcPaneEncode, QtcPaneEncodePlugin)


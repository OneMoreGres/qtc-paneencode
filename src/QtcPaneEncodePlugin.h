#ifndef QTCPANEENCODE_H
#define QTCPANEENCODE_H

#include "PluginGlobal.h"

#include <extensionsystem/iplugin.h>

#include <projectexplorer/runconfiguration.h>
#include <projectexplorer/buildstep.h>
#include <projectexplorer/runcontrol.h>

namespace QtcPaneEncode {
  namespace Internal {

    class QtcPaneEncodePlugin : public ExtensionSystem::IPlugin {
      Q_OBJECT
      Q_PLUGIN_METADATA (IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QtcPaneEncode.json")

      public:
        QtcPaneEncodePlugin ();
        ~QtcPaneEncodePlugin ();

        bool initialize (const QStringList &arguments, QString *errorString);
        void extensionsInitialized ();
        ShutdownFlag aboutToShutdown ();

      private slots:
        void updateSettings ();

        // Compiler output

      private slots:
        //! Set self as proxy for build messages.
        void handleBuild (ProjectExplorer::Project *project);
        void addTask (const ProjectExplorer::Task &task, int linkedOutputLines, int skipLines);
        void addOutput (const QString &string, ProjectExplorer::BuildStep::OutputFormat format, ProjectExplorer::BuildStep::OutputNewlineSetting newlineSetting);

      signals:
        void newTask (const ProjectExplorer::Task &task, int linkedOutputLines, int skipLines);
        void newOutput (const QString &string, ProjectExplorer::BuildStep::OutputFormat format, ProjectExplorer::BuildStep::OutputNewlineSetting newlineSetting);

        // Run control output

      private slots:
        //! Set self as proxy for application messages.
        void handleRunStart (ProjectExplorer::RunControl *runControl);
        void appendMessage (const QString &out, Utils::OutputFormat format);

      signals:
        void newMessage (ProjectExplorer::RunControl *rc, const QString &out, Utils::OutputFormat format);

      private:
        void initLanguage ();

      private:
        //! Encoding for build output. Empty if not enabled.
        QByteArray buildEncoding_;
        //! Encoding for application output. Empty if not enabled.
        QByteArray appEncoding_;
    };

  } // namespace Internal
} // namespace QtcPaneEncode

#endif // QTCPANEENCODE_H


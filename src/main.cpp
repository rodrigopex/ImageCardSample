#include <bb/cascades/Application>

#include <QLocale>
#include <QTranslator>
#include "applicationui.hpp"

#include <QObject>
#include <Qt/qdeclarativedebug.h>
#include <bb/system/InvokeManager>

using namespace bb::cascades;
using namespace bb::system;

void myMessageOutput(QtMsgType type, const char* msg) {
	fprintf(stdout, "%s\n", msg);
	fflush(stdout);
	Q_UNUSED(type)
}

Q_DECL_EXPORT int main(int argc, char **argv) {
	Application app(argc, argv);
	qInstallMsgHandler(myMessageOutput);
	// Create the Application UI object, this is where the main.qml file
	// is loaded and the application scene is set.

	ApplicationUI * preShare = new ApplicationUI(&app);
	InvokeManager invokeManager;

	bool connectResult;
	Q_UNUSED(connectResult);
	connectResult = QObject::connect(&invokeManager,
			SIGNAL(invoked(bb::system::InvokeRequest)), preShare,
			SLOT(invoked(bb::system::InvokeRequest)));
	Q_ASSERT(connectResult);

	switch (invokeManager.startupMode()) {
	case ApplicationStartupMode::LaunchApplication:
		// If the application was launched from the home screen, it can initialize
		break;
	case ApplicationStartupMode::InvokeCard:
		// If the application is invoked,
		//it must wait until it receives an invoked(..) signal
		// so that it can determine the UI that it needs to initialize
		qDebug() << "Vai que vai!!!";
		break;
	default:
		// Who am I and how did I get here?
		break;
	}
	// Enter the application main event loop.
	return Application::exec();
}

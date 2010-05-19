#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include "../mpCommon/mpCommon.h"

using namespace mpCommon;
using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	consoleOut("mprun 0.2");

	QStringList arguments = a.arguments();

	if (arguments.count() < 2){
		consoleOut("Insufficient arguments. Need at least 1.");
	} else {
		// do work.
		QProcess process;
		arguments.takeFirst(); // removes arg 0
		QString pid = arguments.takeFirst(); // takes the PID
		arguments.prepend("/C");
		consoleOut(arguments.join("|"));
		process.start("cmd.exe",arguments);
		while(process.state() == QProcess::Running)
		{
			if (process.waitForReadyRead())
			{
				cout << QString(process.readAllStandardOutput().data()).toStdString();
			}
		}
		// delete pid
		QString appPath = a.applicationDirPath();
		QString fileName = appPath + QString("/") + pid + QString(".pid");

		QFile file(fileName);
		file.remove();
	}
	a.quit();
	return 0;
}

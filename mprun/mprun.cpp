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
	consoleOut("mprun 0.1");

	QStringList arguments = a.arguments();

	if (arguments.count() < 2){
		consoleOut("Insufficient arguments. Need at least 1.");
	} else {
		// Get process ID and write it out
		QString appPath = a.applicationDirPath();
		QString fileName = appPath + QString("/%1.pid").arg(a.applicationPid());
		writeText(fileName,"");
		// do work.
		QProcess process;
		arguments.takeFirst();
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
		QFile file(fileName);
		file.remove();
	}
	a.quit();
	return 0;
}

#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <QTest>
#include <QThread>
#include <iostream>
#include "../mpCommon/mpCommon.h"

using namespace mpCommon;
using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	consoleOut("mpstart 0.1");

	QStringList arguments = a.arguments();

	if (arguments.count() < 2){
		consoleOut("Insufficient arguments. Need at least 1.");
	} else {
		// Check how many there are running
		QString appPath = a.applicationDirPath();
		QDir dir(appPath);
		QStringList infoList = dir.entryList(QStringList()<<"*pid");
		consoleOut(infoList.join("|"));
		// Pause if there are number of processor * 2
		int numthreads = QThread::idealThreadCount() * 2;
		while(infoList.count() >= numthreads){
			QTest::qSleep(8);
			infoList = dir.entryList(QStringList()<<"*pid");
		}
		// launch mprun
		QProcess process;
		arguments.takeFirst();
		process.startDetached("mprun.exe",arguments,QDir().absolutePath());
	}
	a.quit();
	return 0;
}

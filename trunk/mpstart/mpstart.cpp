#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <QTest>
#include <QThread>
#include <QUuid>
#include <iostream>
#include "../mpCommon/mpCommon.h"

using namespace mpCommon;
using namespace std;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	consoleOut("mpstart 0.2");

	QStringList arguments = a.arguments();

	if (arguments.count() < 2){
		consoleOut("Insufficient arguments. Need at least 1.");
	} else {
		// Check how many there are running
		QString appPath = a.applicationDirPath();
		QDir dir(appPath);
		QStringList infoList = dir.entryList(QStringList()<<"*pid");
		//consoleOut(infoList.join("|"));
		// Pause if there are number of processor
		int numthreads = QThread::idealThreadCount();
		while(infoList.count() >= numthreads){
			QTest::qSleep(8);
			infoList = dir.entryList(QStringList()<<"*pid");
		}
		// launch mprun
		QProcess process;
		arguments.takeFirst();
		QString id = QUuid::createUuid().toString();
		arguments.prepend( QString("%1").arg(id) );
		
		// Get process ID and write it out
		
		QString fileName = appPath + QString("/%1.pid").arg(id);
		writeText(fileName,"");

		process.startDetached("mprun.exe",arguments,QDir().absolutePath());
	}
	a.quit();
	return 0;
}

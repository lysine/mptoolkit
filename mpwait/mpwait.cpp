#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include <QTest>
#include <iostream>
#include "../mpCommon/mpCommon.h"

using namespace mpCommon;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	consoleOut("mpwait 0.2");

	// wait until all pid's disappear
	QString appPath = a.applicationDirPath();
	QDir dir(appPath);
	QStringList infoList = dir.entryList(QStringList()<<"*pid");
	consoleDebug(infoList.join("|"));
	// wait until there are no more pid's
	while(infoList.count() > 1){
		QTest::qSleep(8);
		infoList = dir.entryList(QStringList()<<"*pid");
	}
	a.quit();
	return 0;
}

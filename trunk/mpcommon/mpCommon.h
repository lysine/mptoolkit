#pragma once

#include <QtCore/QCoreApplication>
#include <QDir>
#include <QTextStream>
#include <iostream>
#include <QProcess>
#include <QTextCodec>

namespace mpCommon{
	void consoleDebug(QString string);
	void consoleOut(QString string);
	int writeText(QString filePath, QString string);
}

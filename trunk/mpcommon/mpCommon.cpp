#include "mpCommon.h"

namespace mpCommon {

/* 
	Utility Function to output to Console.
	Only works when DEBUG is defined.
	Use for verbose debugging. Will not output in Release mode for speed.
*/
void consoleDebug(QString string){
#ifdef DEBUG
	QTextStream out(stdout);
	out << string << endl;
#endif
}

/* 
	Utility Function to output to Console.
	Use for all regular output.
*/
void consoleOut(QString string){
	QTextStream out(stdout);
	out << string << endl;
}

int writeText(QString filePath, QString string){
	QFile fileout(filePath);
	if (!fileout.open(QIODevice::WriteOnly | QIODevice::Text)){
		consoleOut("Error Cannot Open : " + fileout.fileName());
		return 1;
	}
	QTextStream out(&fileout);
	out << string;
	fileout.close();
	return 0;
}

} //namespace mpCommon
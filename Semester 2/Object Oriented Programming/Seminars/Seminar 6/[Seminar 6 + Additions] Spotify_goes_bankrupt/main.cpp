#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_DBG_MALLOC

#include <QtWidgets/QApplication>
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <iostream>
#include <crtdbg.h>
#include "ui.h"
#include "MainPage.h"


using std::cout;
using std::endl;


void runApp(int argc, char* argv[])
	{
	    QApplication a{ argc, argv };

		Repository repo;
		Service srv{ repo };
		//Console console{ srv };
		MainPage gui{srv };
		gui.show();
		a.exec();
		//console.run();
	}

int main(int argc, char* argv[]) {
	
	runApp(argc, argv);

	// does not always work correctly with Qt applications

	//_CrtDumpMemoryLeaks();
		
	
}
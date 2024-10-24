#define _CRT_SECURE_NO_WARNINGS
#define _CRT_DBG_MALLOC
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <iostream>
#include <crtdbg.h>
#include "ui.h"


using std::cout;
using std::endl;


void runApp() 
	{
		Repository repo;
		Service srv{ repo };
		Console console{ srv };
		console.run();
	}

int main() {
	runApp();

	_CrtDumpMemoryLeaks();
		
	
}
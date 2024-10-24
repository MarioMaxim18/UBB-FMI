#define _CRT_DBG_MALLOC
#include <assert.h>
#include <stdio.h>
#include <crtdbg.h>
#include "tests.h"

void testAll() {
	testCreateDestroyArray();
	testAddArray();
	testSetGetElemPosArray();
	testRemoveFromArray();
	testSearchInArray();
}
int main() {
	testAll();
	_CrtDumpMemoryLeaks();
}
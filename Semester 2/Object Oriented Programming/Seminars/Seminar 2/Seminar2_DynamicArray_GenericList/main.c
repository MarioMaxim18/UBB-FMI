#define _CRT_DBG_MALLOC
#include <assert.h>
#include <stdio.h>
#include <crtdbg.h>
#include "tests_int.h"
#include "tests_moviess.h"
#include "tests_moviesd.h"

void testInts() {
	testCreateDestroyArray();
	testAddArray();
	testSetGetElemPosArray();
	testRemoveFromArray();
	testSearchInArray();
	printf("Finished tests for TElem = ints.\n");
}
void testMovieS() {
	testCreateDestroyArrayMovieS();
	testAddArrayMovieS();
	testSetGetElemPosArrayMovieS();
	testRemoveFromArrayMovieS();
	testSearchInArrayMovieS();
	printf("Finished tests for movies with static allocation.\n");
}
void testMovieD() {
	testCreateDestroyArrayMovieD();
	testAddArrayMovieD();
	testRemoveFromArrayMovieD();
	testSearchInArrayMovieD();
	printf("Finished tests for movies with dynamic allocation.\n");

}
void testAll() {
	//now we can run them all at once
	testInts();
	testMovieS();
	testMovieD();

	
}
int main() {
	testAll();
	_CrtDumpMemoryLeaks();
}
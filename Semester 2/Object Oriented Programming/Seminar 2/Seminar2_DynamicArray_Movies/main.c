#define _CRT_DBG_MALLOC
#include <assert.h>
#include <stdio.h>
#include <crtdbg.h>
//#include "tests_movies.h"
#include "tests_moviesd.h"
//void testMovieS() {
//	testCreateDestroyArrayMovieS();
//	printf("testCreateDestroy finished\n");
//	testAddArrayMovieS();
//	printf("testAdd finished\n");
//	testSetGetElemPosArrayMovieS();
//	printf("testGetSet finished\n");
//	testRemoveFromArrayMovieS();
//	printf("testRemove finished\n");
//	testSearchInArrayMovieS();
//	printf("testSearch finished\n");
//
//}
void testMovieD() {
	testCreateDestroyArrayMovieD();
	printf("testCreateDestroy finished\n");
	testAddArrayMovieD();
	printf("testAdd finished\n");

	testSetGetElemPosArray();
	printf("testGetSet finished\n");

	testRemoveFromArrayMovieD();
	printf("testRemove finished\n");

	testSearchInArrayMovieD();
	printf("testSearch finished\n");

}
void testAll() {
	//testMovieS();
	testMovieD();

	
}
int main() {
	//whenever we want to run with a type of movie
	//we have to comment out the tests corresponding to the other
	//and exclude from project (Right click on file -> Exclude from 
	//project) the test files for the other
	//even though we change TElem to be MovieS/MovieD (and make the additional
	//changes for element comparison and destruction), our dynamic array
	//is still limited to storing just one type of element 
	//i.e. if TElem = MovieS, I cannot have dynamic arrays of MovieD 
	//in the same program
	testAll();
	_CrtDumpMemoryLeaks();
}
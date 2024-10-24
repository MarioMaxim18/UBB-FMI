#include "MediaItem.h"
#include"Repository.h"
#include <iostream>
#include <crtdbg.h>
using std::cout;
int main() {

	{
		/*
		MediaItem* m = new MediaItem("Cardigan", "Taylor Swift", " ");
		MediaItem* m1[10];// this is not dynamic, its just a static array of pointers
		m1[0] = m;
		MediaItem** heapArray = new MediaItem * [10];
		heapArray[0] = m;
		VideoItem* v = new VideoItem{ "aa", "hh", " ", "444" };
		m1[1] = v;
		heapArray[1] = v;
		for (int i = 0; i < 2; i++)
			cout << *heapArray[i] << '\n';
		cout << *m;
		delete m;
		delete[] heapArray;
		delete v;
		*/
		RepoTester::testAll();
	}
	_CrtDumpMemoryLeaks();
}
#include "tests_moviesd.h"



void testCreateDestroyArrayMovieD()
{
	DynamicArray arr = createArray(equalMovieD, destroyMovieD);
	assert(size(&arr) == 0);
	destroyArray(&arr);
}

void testAddArrayMovieD()
{
	DynamicArray arr = createArray(equalMovieD, destroyMovieD);
	MovieD* m1 = createMovieD("Movie1", "Director1", 1999, 2.33);
	addToEnd(&arr, m1);
	assert(size(&arr) == 1);

	MovieD* elem1 = getElem(&arr, 0);
	assert(strcmp(elem1->title, "Movie1") == 0);
	assert(strcmp(elem1->director, "Director1") == 0);
	assert(elem1->year == 1999);
	assert(elem1->rating == 2.33);

	addToEnd(&arr, createMovieD("Movie2", "Director2", 2024, 4.12));
	assert(size(&arr) == 2);

	MovieD* elem2 = getElem(&arr, 1);
	assert(strcmp(elem2->title, "Movie2") == 0);
	assert(strcmp(elem2->director, "Director2") == 0);
	assert(elem2->year == 2024);
	assert(elem2->rating == 4.12);

	addToEnd(&arr, createMovieD("Movie3", "Director3", 2020, 3.01));
	assert(size(&arr) == 3);

	MovieD* lastElement = getElem(&arr, arr.length - 1);
	assert(strcmp(lastElement->title, "Movie3") == 0);
	assert(strcmp(lastElement->director, "Director3") == 0);
	assert(lastElement->year == 2020);
	assert(lastElement->rating == 3.01);

	MovieD* elem1a = getElem(&arr, 0);
	assert(strcmp(elem1a->title, "Movie1") == 0);
	assert(strcmp(elem1a->director, "Director1") == 0);
	assert(elem1a->year == 1999);
	assert(elem1a->rating == 2.33);


	destroyArray(&arr);
}


void testRemoveFromArrayMovieD() {
	DynamicArray arr = createArray(equalMovieD, destroyMovieD);
	addToEnd(&arr, createMovieD("Movie1", "Director1", 1999, 2.33));
	addToEnd(&arr, createMovieD("Movie2", "Director2", 2021, 4.21));
	addToEnd(&arr, createMovieD("Movie3", "Director3", 1976, 4.56));
	addToEnd(&arr, createMovieD("Movie4", "Director4", 2000, 3.32));
	addToEnd(&arr, createMovieD("Movie5", "Director5", 2022, 4.8));


	assert(size(&arr) == 5);
	MovieD* deletedElement = removeLast(&arr);
	assert(size(&arr) == 4);
	assert(!search(&arr, deletedElement));
	assert(deletedElement->year == 2022);
	destroyMovieD(deletedElement);


	deletedElement = removeFromPosition(&arr, 0);
	assert(deletedElement->year == 1999);
	assert(size(&arr) == 3);
	destroyMovieD(deletedElement);

	deletedElement = removeFromPosition(&arr, 0);
	assert(deletedElement->year == 2021);
	assert(size(&arr) == 2);
	destroyMovieD(deletedElement);


	deletedElement = removeFromPosition(&arr, 1);
	assert(deletedElement->year == 2000);
	assert(size(&arr) == 1);
	destroyMovieD(deletedElement);


	destroyArray(&arr);


}

void testSearchInArrayMovieD() {
	DynamicArray arr = createArray(equalMovieD, destroyMovieD);

	MovieD* m1 = createMovieD("Movie1", "Director1", 1999, 2.33);
	addToEnd(&arr, m1);

	MovieD* m2 = createMovieD("Movie2", "Director2", 2021, 4.21);
	addToEnd(&arr, m2);

	MovieD* m3 = createMovieD("Movie3", "Director3", 1976, 4.56);
	addToEnd(&arr, m3);
	MovieD* m4 = createMovieD("Movie4", "Director4", 2000, 3.32);

	addToEnd(&arr, m4);

	MovieD* m5 = createMovieD("Movie5", "Director5", 2022, 4.8);
	addToEnd(&arr, m5);

	MovieD* m6 = createMovieD("Movie6", "Director6", 2022, 4.8);
	MovieD* m7 = createMovieD("Movie5", "Director8", 2022, 4.8);

	
	assert(!search(&arr, m6));
	assert(!search(&arr, m7));
	assert(search(&arr, m1));
	assert(search(&arr, m2));
	assert(search(&arr, m4));

	destroyMovieD(m6);
	destroyMovieD(m7);
	destroyArray(&arr);




}

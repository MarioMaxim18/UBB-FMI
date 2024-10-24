#include "tests_movies.h"

void testCreateDestroyArrayMovieS()
{
	DynamicArray arr = createArray(equalMovieS, destroyMovieS);
	assert(size(&arr) == 0);
	destroyArray(&arr);
}

void testAddArrayMovieS()
{
	DynamicArray arr = createArray(equalMovieS, destroyMovieS);
	MovieS m1 = createMovieS("Movie1", "Director1", 1999, 2.33);
	addToEnd(&arr, m1);
	assert(size(&arr) == 1);
	TElem elem1 = getElem(&arr, 0);
	assert(strcmp(elem1.title,"Movie1")==0);
	assert(strcmp(elem1.director, "Director1") == 0);
	assert(elem1.year==1999);
	assert(elem1.rating==2.33);

	addToEnd(&arr, createMovieS("Movie2","Director2", 2024, 4.12));
	assert(size(&arr) == 2);

	TElem elem2 = getElem(&arr, 1);
	assert(strcmp(elem2.title, "Movie2") == 0);
	assert(strcmp(elem2.director, "Director2") == 0);
	assert(elem2.year == 2024);
	assert(elem2.rating == 4.12);

	addToEnd(&arr, createMovieS("Movie3", "Director3", 2020, 3.01));
	assert(size(&arr) == 3);

	TElem lastElement = getElem(&arr, arr.length-1);
	assert(strcmp(lastElement.title, "Movie3") == 0);
	assert(strcmp(lastElement.director, "Director3") == 0);
	assert(lastElement.year == 2020);
	assert(lastElement.rating == 3.01);

	TElem elem1a = getElem(&arr, 0);
	assert(strcmp(elem1a.title, "Movie1") == 0);
	assert(strcmp(elem1a.director, "Director1") == 0);
	assert(elem1a.year == 1999);
	assert(elem1a.rating == 2.33);


	destroyArray(&arr);
}

void testSetGetElemPosArrayMovieS() {
	DynamicArray arr = createArray(equalMovieS, destroyMovieS);
	MovieS m1 = createMovieS("Movie1", "Director1", 1999, 2.33);
	addToEnd(&arr, m1);
	MovieS m2 = createMovieS("Movie2", "Director2", 2021, 4.21);
	addToEnd(&arr, m2);
	MovieS m3 = createMovieS("Movie3", "Director3", 1976, 4.56);
	addToEnd(&arr, m3);

	TElem element = getElem(&arr, 0);
	assert(equalMovieS(&element, &m1));

	element = getElem(&arr, 1);
	assert(equalMovieS(&element, &m2));

	element = getElem(&arr, 2);
	assert(equalMovieS(&element, &m3));



	MovieS m4 = createMovieS("Movie4", "Director4", 1997, 3.01);
	TElem replacedElement = setElem(&arr, m4, 0);
	assert(equalMovieS(&replacedElement, &m1));
	element = getElem(&arr, 0);
	assert(equalMovieS(&element, &m4));

	destroyMovieS(&replacedElement);
	destroyArray(&arr);

}



void testRemoveFromArrayMovieS(){
	DynamicArray arr = createArray(equalMovieS, destroyMovieS);
	addToEnd(&arr, createMovieS("Movie1", "Director1", 1999, 2.33));
	addToEnd(&arr, createMovieS("Movie2", "Director2", 2021, 4.21));
	addToEnd(&arr, createMovieS("Movie3", "Director3", 1976, 4.56));
	addToEnd(&arr, createMovieS("Movie4", "Director4", 2000, 3.32));
	addToEnd(&arr, createMovieS("Movie5", "Director5", 2022, 4.8));

	
	assert(size(&arr) == 5);
	TElem deletedElement = removeLast(&arr);
	assert(size(&arr) == 4);
	assert(!search(&arr, deletedElement));
	assert(deletedElement.year == 2022);

	assert(getElem(&arr, 0).year == 1999);
	assert(getElem(&arr, 1).year == 2021);
	assert(getElem(&arr, 2).year == 1976);
	assert(getElem(&arr, 3).year == 2000);

	deletedElement = removeFromPosition(&arr, 0);
	assert(deletedElement.year==1999);
	assert(size(&arr) == 3);

	deletedElement = removeFromPosition(&arr, 0);
	assert(deletedElement.year==2021);
	assert(size(&arr) == 2);


	deletedElement = removeFromPosition(&arr, 1);
	assert(deletedElement.year == 2000);
	assert(size(&arr) == 1);

	destroyArray(&arr);

	
}

void testSearchInArrayMovieS() {
	DynamicArray arr = createArray(equalMovieS, destroyMovieS);

	MovieS m1 = createMovieS("Movie1", "Director1", 1999, 2.33);
	addToEnd(&arr, m1);

	MovieS m2 = createMovieS("Movie2", "Director2", 2021, 4.21);
	addToEnd(&arr,m2);

	MovieS m3 = createMovieS("Movie3", "Director3", 1976, 4.56);
	addToEnd(&arr, m3 );
	MovieS m4 = createMovieS("Movie4", "Director4", 2000, 3.32);

	addToEnd(&arr,m4);

	MovieS m5 = createMovieS("Movie5", "Director5", 2022, 4.8);
	addToEnd(&arr,m5);
	MovieS m6 = createMovieS("Movie6", "Director6", 2022, 4.8);
	MovieS m7 = createMovieS("Movie5", "Director8", 2022, 4.8);


	assert(!search(&arr, m6));
	assert(!search(&arr, m7));
	assert(search(&arr, m1));
	assert(search(&arr, m2));
	assert(search(&arr,m4));

	destroyArray(&arr);




}

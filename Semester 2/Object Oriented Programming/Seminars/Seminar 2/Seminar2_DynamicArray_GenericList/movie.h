#pragma once
#include <string.h>
#include <stdbool.h>
typedef struct {
	char title[30];
	char director[30];
	int year;
	double rating;
} MovieS;

typedef struct {
	char* title;
	char* director;
	int year;
	double rating;
} MovieD;

//Modification from last version - these methods now return pointers
MovieS* createMovieS(char* title, char* director, int year, double rating);
MovieD* createMovieD(char* title, char* director, int year, double rating);

void destroyMovieS(MovieS* m);
void destroyMovieD(MovieD* m);

bool equalMovieS(MovieS* m1, MovieS* m2);

bool equalMovieD(MovieD* m1, MovieD* m2);



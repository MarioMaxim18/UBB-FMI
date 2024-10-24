#include "movie.h"
#include <stdlib.h>
MovieS createMovieS(char* title, char* director, int year, double rating)
{
    MovieS movie;
    strcpy_s(movie.title, 30, title);
    strcpy_s(movie.director, 30, director);
    movie.year = year;
    movie.rating = rating;
    return movie;

}

MovieD createMovieD(char* title, char* director, int year, double rating)
{
    MovieD m;
    size_t nrCTitle = strlen(title) + 1;
    m.title = malloc(nrCTitle * sizeof(char));

    size_t nrCDirector = strlen(director) + 1;
    m.director = malloc(nrCDirector * sizeof(char));

    strcpy_s(m.title, nrCTitle, title);
    strcpy_s(m.director, nrCDirector, director);
    m.year = year;
    m.rating = rating;
    return m;

}

void destroyMovieS(MovieS* m)
{
    m->title[0] = '\0';
    m->director[0] = '\0';
    m->year = -1;
    m->rating = -1;
}

void destroyMovieD(MovieD* m)
{
    free(m->title);
    free(m->director);
    m->title = NULL;
    m->director = NULL;
    m->year = -1;
    m->rating = -1;
}

bool equalMovieS(MovieS* m1, MovieS* m2) {
    return strcmp(m1->director, m2->director) == 0 && strcmp(m1->title, m2->title) == 0;
}

bool equalMovieD(MovieD* m1, MovieD* m2) {
    return strcmp(m1->director, m2->director) == 0 && strcmp(m1->title, m2->title) == 0;
}


//TO DO: add tests for movie functions
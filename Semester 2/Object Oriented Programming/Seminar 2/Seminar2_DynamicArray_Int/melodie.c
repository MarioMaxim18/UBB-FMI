#include "melodie.h"

MelodieS createMelodieS(char* artist, char* titlu, double durata)
{
    MelodieS melodie;
    strcpy_s(melodie.artist, 30, artist);
    strcpy_s(melodie.titlu, 30, titlu);
    melodie.durata = durata;
    return melodie;

}

MelodieD createMelodieD(char* artist, char* titlu, double durata)
{
    MelodieD melodie;
    size_t nrCaractereArtist = strlen(artist) + 1;
    melodie.artist = malloc(nrCaractereArtist * sizeof(char));

    size_t nrCaractereTitlu = strlen(artist) + 1;
    melodie.titlu = malloc(nrCaractereTitlu * sizeof(char));

    strcpy_s(melodie.artist, nrCaractereArtist, artist);
    strcpy_s(melodie.titlu, nrCaractereTitlu, titlu);
    melodie.durata = durata;
    return melodie;

}

void destroyMelodieS(MelodieS* m)
{
    m->artist[0] = '\0';
    m->titlu[0] = '\0';
    m->durata = -1;
}

void destroyMelodieD(MelodieD* m)
{
    free(m->titlu);
    free(m->artist);
    m->titlu = NULL;
    m->artist = NULL;
    m->durata = -1;
}
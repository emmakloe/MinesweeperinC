#ifndef TOPLISTA_H_INCLUDED
#define TOPLISTA_H_INCLUDED
#include "adatszerkezetek.h"

void beolvas(char* const fajlnev, Toplist *elso);
void fajlba_ir(char* fajlnev, Toplist *elso);
void torol(Toplist* elso, int j);
bool toplistara_ir(Jatekos** jatekos, Toplist* elso, Palya* palya);
void toplista_ir(SDL_Renderer *renderer, TTF_Font *font1, Toplist* elso, enum Toplista tplst);
void toplista_free(Toplist* elso);

#endif // TOPLISTA_H_INCLUDED

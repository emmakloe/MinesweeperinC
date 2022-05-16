#ifndef GRAFIKA_H_INCLUDED
#define GRAFIKA_H_INCLUDED
#include "adatszerkezetek.h"

void beturajzol (SDL_Renderer *renderer, SDL_Color szin, TTF_Font *font, char* szoveg, int x, int y);
void gomb(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int r, int g, int b);
void menurajzol(SDL_Renderer *renderer,SDL_Window* window,SDL_Color fekete, TTF_Font *font, SDL_Texture* egy);
void toplistarajzol(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *font1, Toplist *elso, char* gomb1, SDL_Color gomb1szin, char* gomb2, SDL_Color gomb2szin, char* szint, enum Toplista tplst);
void beallitasrajzol(SDL_Renderer *renderer, SDL_Window* window,SDL_Color fekete, TTF_Font *font, enum Settings stt, SDL_Texture* zaszlo);
void egyenirajzol(SDL_Renderer *renderer, SDL_Window* window, TTF_Font *font, TTF_Font *font1, SDL_Texture* egy);
void fejlecrajzol(SDL_Renderer* renderer, TTF_Font *font, Palya* palya, SDL_Texture* ujjatek, SDL_Texture* menu);
void palyaseged(SDL_Renderer* renderer, Palya* palya, SDL_Texture* fedett);
void jatekrajzol(SDL_Renderer *renderer, SDL_Window* window, TTF_Font *font,Palya* palya, SDL_Texture* fedett, SDL_Texture* ujjatek, SDL_Texture* menu);
void gyoztesrajzol(SDL_Renderer *renderer, SDL_Window* window, TTF_Font *font1, TTF_Font* font2);
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);
void kep(SDL_Renderer *renderer, SDL_Texture* texture, int meret, int x, int y);

#endif // GRAFIKA_H_INCLUDED

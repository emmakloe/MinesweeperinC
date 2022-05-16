#ifndef INGAME_H_INCLUDED
#define INGAME_H_INCLUDED

void aknamellett(Palya* palya, int y, int x, SDL_Renderer* renderer, TTF_Font* fontkep, SDL_Texture* egy, SDL_Texture* ketto, SDL_Texture* harom, SDL_Texture* negy, SDL_Texture* ot, SDL_Texture* hat, SDL_Texture* het, SDL_Texture* nyolc);
void felfed(Palya* palya, int y, int x, SDL_Renderer* renderer, TTF_Font *font2, int* p, char* jelolt, SDL_Texture* akna, SDL_Texture* jatekospirosakna, SDL_Texture* jeloltbomba, SDL_Texture* egy, SDL_Texture* ketto, SDL_Texture* harom, SDL_Texture* negy, SDL_Texture* ot, SDL_Texture* hat, SDL_Texture* het, SDL_Texture* nyolc, SDL_Texture* jeloltakna, SDL_Texture* ures);
void jatekBAL(SDL_Renderer *renderer, TTF_Font *font2, Koordinata koord, Palya* palya, int* p, char* jelolt, SDL_Texture* akna, SDL_Texture* jatekospirosakna, SDL_Texture* jeloltbomba, SDL_Texture* egy, SDL_Texture* ketto, SDL_Texture* harom, SDL_Texture* negy, SDL_Texture* ot, SDL_Texture* hat, SDL_Texture* het, SDL_Texture* nyolc, SDL_Texture* jeloltakna, SDL_Texture* ures);
bool nyer(Palya* palya);
bool veszit(Palya* palya);
void jatekJOBB(SDL_Renderer *renderer, Koordinata koord, Palya* palya, SDL_Texture* jeloltakna);
Uint32 idozit(Uint32 ms, void *param);

#endif // INGAME_H_INCLUDED

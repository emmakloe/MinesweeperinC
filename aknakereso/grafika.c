#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "grafika.h"
#include "adatszerkezetek.h"
#include "debugmalloc.h"
#include "toplista.h"

SDL_Color fekete3 = {0, 0, 0, 255};
SDL_Color piros3 = {255, 0, 0, 255};
SDL_Color feher3 = {255, 255, 255, 255};

void beturajzol (SDL_Renderer *renderer, SDL_Color szin, TTF_Font *font, char* szoveg, int x, int y){ /*Kiírás*/
    SDL_Rect hova = { x, y, 0, 0 };

    SDL_Surface* felirat = TTF_RenderUTF8_Solid(font, szoveg, szin);
    SDL_Texture* felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.w=felirat->w;
    hova.h=felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
    SDL_RenderPresent(renderer);
}

void gomb(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int r, int g, int b){ /*Gombok rajzolása*/
    boxRGBA(renderer, x1, y1, x2, y2, r, g, b, 255);
    thickLineRGBA(renderer, x1+5, y1+5, x2-5, y1+5, 2, 0, 0, 0, 255);
    thickLineRGBA(renderer, x1+5, y2-5, x2-5, y2-5, 2, 0, 0, 0, 255);
    thickLineRGBA(renderer, x1+5, y1+5, x1+5, y2-5, 2, 0, 0, 0, 255);
    thickLineRGBA(renderer, x2-5, y1+5, x2-5, y2-5, 2, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void menurajzol(SDL_Renderer *renderer,SDL_Window* window, SDL_Color fekete, TTF_Font *font, SDL_Texture* egy) /*Menüt kirajzol*/
{
    SDL_SetWindowSize(window,880,720);
    SDL_RenderClear(renderer);
    boxRGBA(renderer, 0, 0, 880, 720, 0, 0, 0, 255);
    int x;
    int y=0;
    int bla=0;
    int rand1=1, rand2=0;
    for(int i=0; i<30;i++){
        while(bla!=6 && y<=720){
            x=(rand()%(200+rand1))+(rand1+rand2);
            kep(renderer,egy,60,x,y);
            bla++;
            rand1+=100;
            rand2+=200;
        }
        rand1=1;
        rand2=1;
        y+=80;
        bla=0;
    }

    gomb(renderer, 150, 100, 730, 200, 255, 255, 255);
    gomb(renderer, 150, 300, 730, 400, 255, 255, 255);
    gomb(renderer, 150, 500, 730, 600, 255, 255, 255);
    SDL_RenderPresent(renderer);
    beturajzol(renderer, fekete3, font, "Új Játék", 335, 120);
    beturajzol(renderer, fekete3, font, "Beállítások", 305 , 320);
    beturajzol(renderer, fekete3, font, "Toplista", 340, 520);

    SDL_RenderPresent(renderer);
}

void toplistarajzol(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *font1, Toplist *elso, char* gomb1, SDL_Color gomb1szin, char* gomb2, SDL_Color gomb2szin, char* szint, enum Toplista tplst){
    SDL_RenderClear(renderer);
    boxRGBA(renderer, 0, 0, 880, 720, 0, 0, 0, 255);

    gomb(renderer, 390, 680, 490, 720, 255, 255, 255); ///visszagomb
    gomb(renderer, 0, 680, 100, 720, gomb1szin.r, gomb1szin.g, gomb1szin.b); ///elsõ gomb
    gomb(renderer, 780, 680, 880, 720, gomb2szin.r, gomb2szin.g, gomb2szin.b); ///második gomb

    SDL_RenderPresent(renderer);

    beturajzol(renderer, fekete3, font1, "Vissza", 398, 682);
    beturajzol(renderer, piros3, font, szint, 360, 30);
    beturajzol(renderer, piros3, font, "Név", 100, 100);
    beturajzol(renderer, piros3, font, "Idõ", 650, 100);
    beturajzol(renderer, fekete3, font1, gomb1, 8, 682);
    beturajzol(renderer, fekete3, font1, gomb2, 788, 682);

    toplista_ir(renderer, font1, elso, tplst);
}

void beallitasrajzol(SDL_Renderer *renderer, SDL_Window* window, SDL_Color fekete, TTF_Font *font, enum Settings stt, SDL_Texture* zaszlo) /*Beállítást rajzol*/
{
    SDL_RenderClear(renderer);
    SDL_SetWindowSize(window,550,720);
    boxRGBA(renderer, 0, 0, 880, 720, 0, 0, 0, 255);

        int x;
    int y=0;
    int bla=0;
    int rand1=1, rand2=0;
    for(int i=0; i<30;i++){
        while(bla!=3 && y<=720){
            x=(rand()%(70+rand1))+(rand1+rand2);
            kep(renderer,zaszlo,70,x,y);
            bla++;
            rand1+=100;
            rand2+=70;
        }
        rand1=1;
        rand2=1;
        y+=130;
        bla=0;
    }

    gomb(renderer, 0, 680, 100, 720, 255, 255, 255); ///visszagomb
    gomb(renderer, 200, 150, 350, 200, 255, 255, 255); ///kezdõ
    gomb(renderer, 200, 250, 350, 300, 255, 255, 255); ///haladó
    gomb(renderer, 200, 350, 350, 400, 255, 255, 255); ///mester
    gomb(renderer, 200, 450, 350, 500, 255, 255, 255); ///egyéni
    switch (stt) { /* kattintásra a gomb színe megváltozik,ez jelzi a felhasználó számára, hogy melyikre ment rá*/
    case beginner:
        gomb(renderer, 200, 150, 350, 200, 255, 0, 0);
        break;
    case intermediate:
        gomb(renderer, 200, 250, 350, 300, 255, 0, 0);
        break;
    case master:
        gomb(renderer, 200, 350, 350, 400, 255, 0, 0);
        break;
    case custom:
        gomb(renderer, 200, 450, 350, 500, 255, 0, 0);
        break;
    }
    SDL_RenderPresent(renderer);
    beturajzol(renderer, fekete3, font, "Kezdõ", 230, 160);
    beturajzol(renderer, fekete3, font, "Haladó", 230, 260);
    beturajzol(renderer, fekete3, font, "Mester", 230, 360);
    beturajzol(renderer, fekete3, font, "Egyéni", 230, 460);
    beturajzol(renderer, fekete3, font, "Vissza", 10, 683);

    SDL_RenderPresent(renderer);
}

void egyenirajzol(SDL_Renderer *renderer, SDL_Window* window,TTF_Font *font, TTF_Font *font1, SDL_Texture* egy) /*Egyénit rajzol*/
{
    SDL_SetWindowSize(window,880,720);
     SDL_RenderClear(renderer);
     boxRGBA(renderer, 0, 0, 880, 720, 0, 0, 0, 255);
    int x;
    int y=0;
    int bla=0;
    int rand1=1, rand2=0;
    for(int i=0; i<30;i++){
        while(bla!=6 && y<=720){
            x=(rand()%(200+rand1))+(rand1+rand2);
            kep(renderer,egy,60,x,y);
            bla++;
            rand1+=100;
            rand2+=200;
        }
        rand1=1;
        rand2=1;
        y+=80;
        bla=0;
    }
     boxRGBA(renderer, 0, 680, 100, 720, 255, 255, 255, 255); ///vissza gomb
     boxRGBA(renderer, 390, 680, 490, 720, 255, 255, 255, 255); ///mentés gomb
     SDL_RenderPresent(renderer);
     gomb(renderer, 0, 680, 100, 720, 255, 255, 255); ///vissza gomb
     gomb(renderer, 390, 680, 490, 720, 255, 255, 255); ///mentés gomb
     beturajzol(renderer, fekete3, font1, "Vissza", 10, 683);
     beturajzol(renderer, fekete3, font1, "Mentés", 396, 683);
     boxRGBA(renderer, 350, 60, 540, 140, 0, 0, 0, 255);
     beturajzol(renderer, feher3, font, "Egyéni", 360, 50);
     boxRGBA(renderer, 100, 140, 360, 240, 0, 0, 0, 255);
     beturajzol(renderer, feher3, font, "Magasság:", 100, 150);
     boxRGBA(renderer, 100, 290, 360, 390, 0, 0, 0, 255);
     beturajzol(renderer, feher3, font, "Szélesség:", 100, 300);
     boxRGBA(renderer, 100, 440, 300, 540, 0, 0, 0, 255);
     beturajzol(renderer, feher3, font, "Aknák:", 100, 450);
     SDL_RenderPresent(renderer);
}

void fejlecrajzol(SDL_Renderer* renderer, TTF_Font *font, Palya* palya, SDL_Texture* ujjatek, SDL_Texture* menu){ /*Játéktér fejléc*/
    int j=palya->x;
    int k=palya->y;
   // boxRGBA(renderer, 0, 0, j*25, 100+k*25, 135, 133, 130, 255); ///Szürke alapszín szükségtelen a képek miatt
    boxRGBA(renderer, 0, 0, j*25, 100, 0, 0, 0, 255); ///Fekete fejléc
    kep(renderer,ujjatek,30,(j*25/2)-43,35); ///Új játék gomb - emoji
   // boxRGBA(renderer,(j*25/2)+43,35,(j*25/2)+13, 65, 255, 0, 0, 255); ///Menü
   // beturajzol(renderer,fekete3,font,"M",(j*25/2)+19,38);
    kep(renderer, menu, 30, (j*25/2)+13, 35);
    SDL_RenderPresent(renderer);
}

void palyaseged(SDL_Renderer* renderer, Palya* palya, SDL_Texture* fedett) { /*Játéktér pálya*/
    int j=palya->x;
    int k=palya->y;
   /* for(int i=0;i<(j+1)*25; i=i+25){ ///Régi vonalak kirajzolása
        lineRGBA(renderer,0+i,100,0+i,100+k*25,0,0,0,255);
    }
    for(int i=0;i<(k+1)*25; i=i+25) { ///Régi vonalak kirajzolása
        lineRGBA(renderer,0,100+i ,j*25,100+i,0,0,0,255);
    }*/
    for(int i=0; i<(palya->x)*25; i+=25){
        for(int z=100; z<(palya->y)*25+100;z+=25){
          kep(renderer,fedett,25,i,z); ///Fedett mezők betöltése
        }
    }

}

void jatekrajzol(SDL_Renderer *renderer, SDL_Window* window, TTF_Font *font, Palya* palya, SDL_Texture* fedett, SDL_Texture* ujjatek, SDL_Texture* menu){ /*Játéktér kirajzolása*/
    SDL_SetWindowSize(window,palya->x*25,palya->y*25+100);
    SDL_RenderClear(renderer);
    fejlecrajzol(renderer, font, palya, ujjatek, menu);
    palyaseged(renderer, palya, fedett);
    SDL_RenderPresent(renderer);
}

void gyoztesrajzol(SDL_Renderer *renderer, SDL_Window* window, TTF_Font *font1, TTF_Font* font2){ /*Győztes üzenet*/
     SDL_SetWindowSize(window,600,300);
     beturajzol(renderer,feher3,font1,"Gratulálok! Kérlek írd be a neved!",100,100);
     gomb(renderer,200,250,275,300,255,255,255); ///Új játék
     gomb(renderer,325,250,400,300,255,255,255); ///Menü
     beturajzol(renderer,fekete3,font2,"Új játék",207,263);
     beturajzol(renderer,fekete3,font2,"Menü",340,263);
     SDL_RenderPresent(renderer);
}

bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer)
{
    /* Ez tartalmazza az aktualis szerkesztest */
    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';
    /* Ezt a kirajzolas kozben hasznaljuk */
    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    /* Max hasznalhato szelesseg */
    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter)
    {
        /* doboz kirajzolasa */
        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);
        /* szoveg kirajzolasa */
        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0')
        {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        }
        else
        {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw)
        {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }
        /* megjeleniti a képernyon az eddig rajzoltakat */
        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        /* Kulonleges karakter */
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_BACKSPACE)
            {
                int textlen = strlen(dest);
                do
                {
                    if (textlen == 0)
                    {
                        break;
                    }
                    if ((dest[textlen-1] & 0x80) == 0x00)
                    {
                        /* Egy bajt */
                        dest[textlen-1] = 0x00;
                        break;
                    }
                    if ((dest[textlen-1] & 0xC0) == 0x80)
                    {
                        /* Bajt, egy tobb-bajtos szekvenciabol */
                        dest[textlen-1] = 0x00;
                        textlen--;
                    }
                    if ((dest[textlen-1] & 0xC0) == 0xC0)
                    {
                        /* Egy tobb-bajtos szekvencia elso bajtja */
                        dest[textlen-1] = 0x00;
                        break;
                    }
                }
                while(true);
            }
            if (event.key.keysym.sym == SDLK_RETURN)
            {
                enter = true;
            }
            break;

        /* A feldolgozott szoveg bemenete */
        case SDL_TEXTINPUT:
            if (strlen(dest) + strlen(event.text.text) < hossz)
            {
                strcat(dest, event.text.text);
            }

            /* Az eddigi szerkesztes torolheto */
            composition[0] = '\0';
            break;

        /* Szoveg szerkesztese */
        case SDL_TEXTEDITING:
            strcpy(composition, event.edit.text);
            break;

        case SDL_QUIT:
            /* visszatesszuk a sorba ezt az eventet, mert
             * sok mindent nem tudunk vele kezdeni */
            SDL_PushEvent(&event);
            kilep = true;
            break;
        }
    }

    /* igaz jelzi a helyes beolvasast; = ha enter miatt allt meg a ciklus */
    SDL_StopTextInput();
    return enter;
}

void kep(SDL_Renderer *renderer, SDL_Texture* texture, int meret, int x, int y) {
    SDL_Rect *src=NULL;
    SDL_Rect dst={x, y, meret, meret};
    SDL_RenderCopy(renderer,texture,src,&dst);
    SDL_RenderPresent(renderer);
}


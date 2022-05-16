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
#include "debugmalloc.h"
#include "adatszerkezetek.h"
#include "ingame.h"
#include "grafika.h"

SDL_Color fekete1 = {0, 0, 0, 255};
SDL_Color feher33 = {255, 255, 255, 255};

void aknamellett(Palya* palya, int y, int x, SDL_Renderer* renderer, TTF_Font* font2, SDL_Texture* egy, SDL_Texture* ketto, SDL_Texture* harom, SDL_Texture* negy, SDL_Texture* ot, SDL_Texture* hat, SDL_Texture* het, SDL_Texture* nyolc) /*Akna melletti mezők megjelenítése*/
{
            if(palya->ertek[y][x]==1){
               //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,51,255,18,255);
                //beturajzol(renderer,fekete1,font2,"1",x*25+8,100+y*25+2);
                kep(renderer,egy,25,x*25,y*25+100);
            }
            if(palya->ertek[y][x]==2){
               //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,87,255,59,255);
                //beturajzol(renderer,fekete1,font2,"2",x*25+8,100+y*25+2);
                kep(renderer,ketto,25,x*25,y*25+100);
            }
            if(palya->ertek[y][x]==3){
               //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,121,255,99,255);
                //beturajzol(renderer,fekete1,font2,"3",x*25+8,100+y*25+2);
                kep(renderer,harom,25,x*25,y*25+100);
            }
            if(palya->ertek[y][x]==4){
               //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,151,255,134,255);
                //beturajzol(renderer,fekete1,font2,"4",x*25+8,100+y*25+2);
                kep(renderer,negy,25,x*25,y*25+100);
            }
            if(palya->ertek[y][x]==5){
               //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,179,255,166,255);
                //beturajzol(renderer,fekete1,font2,"5",x*25+8,100+y*25+2);
                kep(renderer,ot,25,x*25,y*25+100);
            }
            if(palya->ertek[y][x]==6){
               //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,202,254,193,255);
                //beturajzol(renderer,fekete1,font2,"6",x*25+8,100+y*25+2);
                kep(renderer,hat,25,x*25,y*25+100);
            }
            if(palya->ertek[y][x]==7){
               //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,191,247,180,255);
                //beturajzol(renderer,fekete1,font2,"7",x*25+8,100+y*25+2);
                kep(renderer,het,25,x*25,y*25+100);
            }
             if(palya->ertek[y][x]==8){
               //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,217,254,209,255);
                //beturajzol(renderer,fekete1,font2,"8",x*25+8,100+y*25+2);
                kep(renderer,nyolc,25,x*25,y*25+100);
            }
        SDL_RenderPresent(renderer);
}

void felfed(Palya* palya, int y, int x, SDL_Renderer* renderer, TTF_Font *font2, int* p, char* jelolt, SDL_Texture* akna, SDL_Texture* jatekospirosakna, SDL_Texture* jeloltbomba, SDL_Texture* egy, SDL_Texture* ketto, SDL_Texture* harom, SDL_Texture* negy, SDL_Texture* ot, SDL_Texture* hat, SDL_Texture* het, SDL_Texture* nyolc, SDL_Texture* jeloltakna, SDL_Texture* ures){ /*Mezõk felfedése*/
    if(x<0 || y<0 || x>=(palya->x) || y>=(palya->y)){ ///Ne legyen túlindexelés
        return;
    }
    if(palya->ertek[y][x] < 10){ ///Már fel van fedve
        return;
    }
    if(palya->ertek[y][x]==10) { ///Üressziget
            palya->ertek[y][x]-=10;
           // boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,200,200,200,255);
            kep(renderer,ures,25,x*25,y*25+100);

            felfed(palya,y,x+1,renderer,font2,p,jelolt, akna, jatekospirosakna, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);
            felfed(palya,y+1,x+1,renderer,font2,p,jelolt, akna, jatekospirosakna, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);
            felfed(palya,y+1,x,renderer,font2,p,jelolt, akna, jatekospirosakna, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);
            felfed(palya,y+1,x-1,renderer,font2,p,jelolt, akna, jatekospirosakna, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);
            felfed(palya,y,x-1,renderer,font2,p,jelolt, akna, jatekospirosakna, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);
            felfed(palya,y-1,x-1,renderer,font2,p,jelolt, akna, jatekospirosakna, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);
            felfed(palya,y-1,x,renderer,font2,p,jelolt, akna, jatekospirosakna, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);
            felfed(palya,y-1,x+1,renderer,font2,p,jelolt, akna, jatekospirosakna, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);
    }
    if(palya->ertek[y][x] >10 && palya->ertek[y][x] <19) { ///Akna melletti mezõk
        palya->ertek[y][x]-=10;
        aknamellett(palya,y,x,renderer,font2, egy, ketto, harom, negy, ot, hat, het, nyolc);
        return;
    }
    if(palya->ertek[y][x]==19){ ///Akna
        palya->ertek[y][x]=9;
        for(int s=0;s<palya->y;s++){
            for(int t=0;t<palya->x;t++){
                if(palya->ertek[s][t] ==19) {
                    palya->ertek[s][t]-=10;
                    /*boxRGBA(renderer,t*25,100+s*25,t*25+25,100+s*25+25,0,0,0,255); ///A megjelenõ aknák feketék piros X-el
                    lineRGBA(renderer,t*25,100+s*25,t*25+25,100+s*25+25, 255, 0, 0, 255);
                    lineRGBA(renderer,t*25,100+s*25+25,t*25+25,100+s*25, 255, 0, 0, 255);*/
                    kep(renderer,akna,25,t*25,100+s*25);
                }
                if(palya->ertek[s][t] == 119){
                   /* boxRGBA(renderer,t*25+1,100+s*25+1,t*25+25-1,100+s*25+25-1,0,0,0,255); ///A zászlóval korábban megjelölt aknák fehér X-el jelennek meg
                    lineRGBA(renderer,t*25,100+s*25,t*25+25,100+s*25+25, 255, 255, 255, 255);
                    lineRGBA(renderer,t*25,100+s*25+25,t*25+25,100+s*25, 255, 255, 255, 255);*/
                    kep(renderer,jeloltbomba,25,t*25,100+s*25);
                }
            }
        }
     //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,255,0,0,255); ///Az akna amire kattintott piros
     kep(renderer,jatekospirosakna,25,x*25,100+y*25);
        return;
    }
    if(palya->ertek[y][x] > 100){ ///Zászló visszavétele
        palya->ertek[y][x] -= 100;
        //boxRGBA(renderer,x*25+1,100+y*25+1,x*25+25-1,100+y*25+25-1,135,133,130,255);
        kep(renderer,jeloltakna,25,x*25,y*25+100);
        *p+=1; ///Azért kell, hogy utána újra rakhasson
        sprintf(jelolt,"%d",*p);
        //boxRGBA(renderer,8,35,38,65,255,255,255,255);
        kep(renderer,jeloltakna,38,8,31);
        if(*p < 10)
            beturajzol(renderer, fekete1, font2, jelolt, 22, 40); ///Nem értem mi a fasz történik
        if(*p > 9)
            beturajzol(renderer, fekete1, font2, jelolt, 17, 40);
        return;
    }
}

void jatekBAL(SDL_Renderer *renderer, TTF_Font *font2, Koordinata koord,Palya* palya, int* p, char* jelolt, SDL_Texture* akna, SDL_Texture* jatekospirosakna, SDL_Texture* jeloltbomba, SDL_Texture* egy, SDL_Texture* ketto, SDL_Texture* harom, SDL_Texture* negy, SDL_Texture* ot, SDL_Texture* hat, SDL_Texture* het, SDL_Texture* nyolc, SDL_Texture* jeloltakna, SDL_Texture* ures) { /*Bal egér-játéktér*/
    int ujy1,ujx1;
    int i,j;
    for(i=0;i<palya->y;i++) ///y koord keresése
        if((koord.y-i*25)>=100 && (koord.y-i*25)<=125)
            ujy1=i;

    for(j=0;j<palya->x;j++) ///x koord keresése
        if((koord.x-j*25)>=0 && (koord.x-j*25)<=25)
        ujx1=j;

    felfed(palya,ujy1,ujx1,renderer,font2,p,jelolt,akna,jatekospirosakna,jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, jeloltakna, ures);

    SDL_RenderPresent(renderer);
}

bool nyer(Palya* palya)
{
    bool temp = false;
    for(int i=0;i<palya->y;i++){
        for(int j=0;j<palya->x;j++){
                if(palya->ertek[i][j] < 9 || (palya->ertek[i][j] ==119 || palya->ertek[i][j] == 19)){
                    temp=true;
                    }
                else
                    return false;
        }
    }
    return temp;
}

bool veszit(Palya* palya)
{
    bool temp=false;
    for(int i=0;i<palya->y;i++){
        for(int j=0;j<palya->x;j++){
                if(palya->ertek[i][j] == 9)
                temp=true;
        }
    }
    return temp;
}

void jatekJOBB(SDL_Renderer *renderer, Koordinata koord, Palya* palya, SDL_Texture* jeloltakna) /*Jobb egér-játéktér (zászló)*/
{
    int ujy1,ujx1;
    int i,j;
    for(i=0;i<palya->y;i++) ///y koord keresése
        if((koord.y-i*25)>=100 && (koord.y-i*25)<=125)
            ujy1=i;

    for(j=0;j<palya->x;j++) ///x koord keresése
        if((koord.x-j*25)>=0 && (koord.x-j*25)<=25)
            ujx1=j;

    palya->ertek[ujy1][ujx1] +=100; ///100 feletti érték a zászló
   // boxRGBA(renderer,ujx1*25+1,100+ujy1*25+1,ujx1*25+25-1,100+ujy1*25+25-1,255,255,255,255); ///Zászló-fehér mezõ
    kep(renderer,jeloltakna,25,ujx1*25,ujy1*25+100);
    SDL_RenderPresent(renderer);
}

Uint32 idozit(Uint32 ms, void *param) /*A játékos idejéhez*/
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}


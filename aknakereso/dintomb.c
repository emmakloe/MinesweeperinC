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
#include "dintomb.h"

void foglal(Palya* palya)   /*2D-s tömb foglalása*/
{
    palya->ertek=(int**) malloc(palya->y * sizeof(int*));
    for(int y=0; y <palya->y; y++){
        palya->ertek[y]=(int*) malloc(palya->x * sizeof(int));
    }
}

void palyatolt(Palya* palya,int aknax, int aknay)   /*Értéktöltés*/
{
    int x=palya->x;
    int y=palya->y;
    int aknak=palya->akna;
    int c, d;
    int db=0;
    for (int a=0; a<y; a++){
        for (int b=0; b<x; b++)
            palya->ertek[a][b]=10; ///Kezdõ értékként  legyen mindegyik 10 (10 és annál nagyobbak a fedettek)
    }
    while (db != aknak) ///Addig amíg el nem éri az aknák számát
    {
        c=rand()%x;
        d=rand()%y;
        if(palya->ertek[d][c] != 19 && (c!=aknax || d!=aknay))  ///Azért kell, hogy ne sorsolja ugyanarra a helyre kétszer és az elsõ kattintás ne legyen akna
        {
            palya->ertek[d][c]=19;
            db++;
        }
    }
    for (int i=1; i<y-1; i++)  ///A tömb belsejében lévõ aknák keresése
    {
        for (int j=1; j<x-1; j++)
        {
            if (palya->ertek[i][j]==19)
            {
                if(palya->ertek[i+1][j+1] != 19){palya->ertek[i+1][j+1]+=1;}   ///Akna melletti mezõk értékének növelése
                if(palya->ertek[i][j+1] != 19){palya->ertek[i][j+1]+=1;}
                if(palya->ertek[i-1][j+1] != 19){palya->ertek[i-1][j+1]+=1;}
                if(palya->ertek[i-1][j] != 19){palya->ertek[i-1][j]+=1;}
                if(palya->ertek[i-1][j-1] != 19){palya->ertek[i-1][j-1]+=1;}
                if(palya->ertek[i][j-1] != 19){palya->ertek[i][j-1]+=1;}
                if(palya->ertek[i+1][j-1] != 19){palya->ertek[i+1][j-1]+=1;}
                if(palya->ertek[i+1][j] != 19){palya->ertek[i+1][j]+=1;}
            }
        }
    }
    for(int i=1; i<(y-1); i++) ///A szélsõ oszlopokat másként kell kezelni
    {
        if(palya->ertek[i][x-1] ==19){
            if(palya->ertek[i+1][x-1] !=19){palya->ertek[i+1][x-1]+=1;}
            if(palya->ertek[i+1][x-2]!=19){palya->ertek[i+1][x-2]+=1;}
            if(palya->ertek[i][x-2] != 19){palya->ertek[i][x-2]+=1;}
            if(palya->ertek[i-1][x-2] != 19){palya->ertek[i-1][x-2]+=1;}
            if(palya->ertek[i-1][x-1] != 19){palya->ertek[i-1][x-1]+=1;}
        }
        if(palya->ertek[i][0]==19){
            if(palya->ertek[i-1][0] !=19){palya->ertek[i-1][0]+=1;}
            if(palya->ertek[i-1][1] !=19){palya->ertek[i-1][1]+=1;}
            if(palya->ertek[i][1]!=19){palya->ertek[i][1]+=1;}
            if(palya->ertek[i+1][1]!=19){palya->ertek[i+1][1]+=1;}
            if(palya->ertek[i+1][0]!=19){palya->ertek[i+1][0]+=1;}
        }

    }
    for(int i=1; i<(x-1); i++) ///Az elsõ és utolsó sort másként kell kezelni
    {
        if(palya->ertek[0][i]==19){
            if(palya->ertek[0][i-1] != 19){palya->ertek[0][i-1]+=1;}
            if(palya->ertek[1][i-1] !=19){palya->ertek[1][i-1]+=1;}
            if(palya->ertek[1][i] !=19){palya->ertek[1][i]+=1;}
            if(palya->ertek[1][i+1]!=19){palya->ertek[1][i+1]+=1;}
            if(palya->ertek[0][i+1]!=19){palya->ertek[0][i+1]+=1;}
        }
        if(palya->ertek[y-1][i]==19){
            if(palya->ertek[y-1][i-1] !=19){palya->ertek[y-1][i-1]+=1;}
            if(palya->ertek[y-2][i-1] !=19){palya->ertek[y-2][i-1]+=1;}
            if(palya->ertek[y-2][i]!=19){palya->ertek[y-2][i]+=1;}
            if(palya->ertek[y-2][i+1]!=19){palya->ertek[y-2][i+1]+=1;}
            if(palya->ertek[y-1][i+1] !=19){palya->ertek[y-1][i+1]+=1;}
        }
    }
    if(palya->ertek[0][0]==19){  ///Bal felsõ sarok
        if(palya->ertek[0][1]!=19){palya->ertek[0][1]+=1;}
        if(palya->ertek[1][1]!=19){palya->ertek[1][1]+=1;}
        if(palya->ertek[1][0]!=19){palya->ertek[1][0]+=1;}
    }
    if(palya->ertek[y-1][0]==19){ ///Bal alsó sarok
        if(palya->ertek[y-2][0]!=19){palya->ertek[y-2][0]+=1;}
        if(palya->ertek[y-2][1]!=19){palya->ertek[y-2][1]+=1;}
        if(palya->ertek[y-1][1]!=19){palya->ertek[y-1][1]+=1;}
    }
    if(palya->ertek[0][x-1]==19){  ///Jobb felsõ sarok
        if(palya->ertek[0][x-2]!=19){palya->ertek[0][x-2]+=1;}
        if(palya->ertek[1][x-2]!=19){palya->ertek[1][x-2]+=1;}
        if(palya->ertek[1][x-1]!=19){palya->ertek[1][x-1]+=1;}
    }
    if(palya->ertek[y-1][x-1]==19){  ///Jobb alsó sarok
        if(palya->ertek[y-1][x-2]!=19){palya->ertek[y-1][x-2]+=1;}
        if(palya->ertek[y-2][x-2]!=19){palya->ertek[y-2][x-2]+=1;}
        if(palya->ertek[y-2][x-1]!=19){palya->ertek[y-2][x-1]+=1;}
    }
}

void palyafelszabadit(Palya* palya)  /*2D-s tömb felszabadítása*/
{

    for(int j=0; j<palya->y; j++)
        free(palya->ertek[j]);
    free(palya->ertek);
}

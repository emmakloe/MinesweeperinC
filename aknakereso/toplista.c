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
#include "toplista.h"
#include "grafika.h"

SDL_Color piros4 = {255, 0, 0, 255};

void beolvas(char* const fajlnev, Toplist *elso)  /*Toplistát beolvas*/
{
    FILE *fp;
    fp = fopen(fajlnev, "rt");
    char sor[50+1];
    if (fp != NULL)
    {
        fgets(sor, 50+1, fp);
        int szamol = 0;
        while(sor[szamol]!= '\0')
        {
            szamol++;
        }
        elso->nev=(char*) malloc(szamol*sizeof(char));
        for(int i=0; i<szamol-1; i++)
        {
            elso->nev[i]=sor[i];
        }
        elso->nev[szamol-1]='\0';
        fgets(sor, 50+1, fp);
        elso->ido=atoi(sor);
        Toplist *mozgo;
        mozgo=elso;
        bool eznev = true;
        while(fgets(sor, 50+1, fp)!=NULL)
        {
            if(eznev)
            {
                Toplist *uj = (Toplist*) malloc(sizeof(Toplist));
                szamol = 0;
                while(sor[szamol]!='\0')
                {
                    szamol++;
                }
                uj->nev=(char*) malloc(szamol*sizeof(char));
                for(int i=0; i<szamol-1; i++)
                {
                    uj->nev[i]=sor[i];
                }
                uj->nev[szamol-1]='\0';
                mozgo->kov=uj;
                uj->kov=NULL;
                mozgo=uj;
                eznev=false;
            }
            else
            {
                mozgo->ido = atoi(sor);
                eznev=true;
            }
        }

        fclose(fp);
    }
    else
    {
        perror("Nem sikerult megnyitni a fajlt!");
    }
    return;
}

void fajlba_ir(char* fajlnev, Toplist *elso) /*Fájlba írja a toplistát*/
{
    FILE *fp;
    fp = fopen(fajlnev, "w");
    Toplist* mozgo;
    for(mozgo=elso; mozgo!=NULL; mozgo=mozgo->kov)
        fprintf(fp, "%s\n%d", mozgo->nev, mozgo->ido);
    fclose(fp);
}

void torol(Toplist* elso, int j){ /*Láncolt lista elemet töröl*/
    Toplist *lemarado = NULL;
    Toplist* mozgo = elso;
    int i=0;
    while (mozgo != NULL && i!=j+10) {
        lemarado = mozgo;
        mozgo = mozgo->kov;
        i++;
    }
    lemarado->kov = mozgo->kov; /* törlendő = ahol megállt */
    free(mozgo);
}

bool toplistara_ir(Jatekos** jatekos, Toplist* elso, Palya* palya) /*Vizsgálja felkerül-e a játékos*/
{
    Toplist *mozgo, *lemarado=NULL;
    Toplist *uj=(Toplist*) malloc(sizeof(Toplist)); /*Új elem létrehozása*/
    strcpy(uj->nev, (*jatekos)->nev);
    uj->ido=(*jatekos)->ido;
    uj->kov=NULL;
    int i,j;
    int db=1;
    mozgo=elso;
    if(palya->x==8 && palya->y==8 && palya->akna==10) /*Megnézi milyen szinten játszott a játékos*/
    {                                                 /*Kezdő*/
        j=1;
    }
    if(palya->x==16 && palya->y==16 && palya->akna==40) /*Haladó*/
    {
        j=11;

    }
    if(palya->x==30 && palya->y==16 && palya->akna==99) /*Mester*/
    {
        j=21;
    }
    while(db!=j)
    {
        mozgo = mozgo->kov;
        db++;
    }
    for(mozgo, i=0; mozgo->kov!=NULL && i!=10; lemarado=mozgo, mozgo=mozgo->kov, i++)
    {
        if(uj->ido<mozgo->ido) /*Ha jobb az ideje, akkor toplistára kerül*/
        {
            lemarado->kov=uj;
            uj->kov=mozgo;
            torol(elso, j); /*Törölni kell a legrosszabb eredményt*/
            }
        return true;
    }
}




void toplista_ir(SDL_Renderer *renderer, TTF_Font *font1, Toplist* elso, enum Toplista tplst)  /*Toplistát kiír*/
{
    Toplist* mozgo;
    int z= 190;
    int i=1;
    switch(tplst)
    {
    case kezdo: ///A kezdõ toplista az 1. elemtõl kezdõdik
        for (mozgo=elso, i; mozgo != NULL, i!=10 ; mozgo = mozgo->kov, i++)
        {
            beturajzol(renderer, piros4, font1, mozgo->nev, 110, z);
            char tmp[10];
            int mp = mozgo->ido%60;
            int perc = (mozgo->ido-mp)/60;
            sprintf(tmp,"%d", perc);
            strcat(tmp,":");
            char tmp2[10];
            sprintf(tmp2,"%d", mp);
            strcat(tmp,tmp2);
            beturajzol(renderer, piros4, font1, tmp, 665, z);
            z+=50;
        }
        break;
    case halado:
        mozgo = elso;
        int db=0;
        while (db!=10)   /*A haladó toplista a 11. elemtõl kezdõdik*/
        {
            mozgo = mozgo->kov;
            db++;
        }
        for (mozgo, i; mozgo != NULL, i!=10 ; mozgo = mozgo->kov, i++)
        {
            beturajzol(renderer, piros4, font1, mozgo->nev, 110, z);
            char tmp[10];
            int mp = mozgo->ido%60;
            int perc = (mozgo->ido-mp)/60;
            sprintf(tmp,"%d", perc);
            strcat(tmp,":");
            char tmp2[10];
            sprintf(tmp2,"%d", mp);
            strcat(tmp,tmp2);
            beturajzol(renderer, piros4, font1, tmp, 665, z);
            z+=50;
        }
        break;
    case mester:
        mozgo = elso;
        int db1=0;
        while (db1!=20)   /*A mester toplista a 21.elemtõl kezdõdik*/
        {
            mozgo = mozgo->kov;
            db1++;
        }
        for (mozgo, i; mozgo != NULL, i!=10 ; mozgo = mozgo->kov, i++)
        {
            beturajzol(renderer, piros4, font1, mozgo->nev, 110, z);
            char tmp[10];
            int mp = mozgo->ido%60;
            int perc = (mozgo->ido-mp)/60;
            sprintf(tmp,"%d", perc);
            strcat(tmp,":");
            char tmp2[10];
            sprintf(tmp2,"%d", mp);
            strcat(tmp,tmp2);
            beturajzol(renderer, piros4, font1, tmp, 665, z);
            z+=50;
        }
        break;
    }
}

void toplista_free(Toplist* elso)  /*Láncolt listát felszabadít*/
{
    Toplist* p=elso;
    while(p!=NULL)
    {
        Toplist* tmp=p->kov;
        free(p->nev);
        free(p);
        p=tmp;
    }

}

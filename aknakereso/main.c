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
#include "grafika.h"
#include "adatszerkezetek.h"
#include "ingame.h"
#include "toplista.h"
#include "dintomb.h"

SDL_Color sarga = {255, 255, 0, 255};
SDL_Color fekete2 = {0, 0, 0, 255};
SDL_Color fekete = {0, 0, 0, 255};
SDL_Color feher = {255, 255, 255, 255};
SDL_Color piros = {255, 0, 0, 255};

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    /* ablak létrehozása */
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("Minesweeper", 880, 720, &window, &renderer);
    Koordinata koord;
    enum Field fld=inmenu;
    enum Toplista tpls = kezdo;
    enum Settings stt= beginner;
    Toplist *elso = (Toplist*) malloc(sizeof(Toplist)); ///Láncolt lista első eleme
    Jatekos *jatekos = (Jatekos*) malloc(sizeof(Jatekos));
    jatekos->ido=0;
    beolvas("toplista.txt", elso);

    Palya palya;
    palya.akna=10; ///Ha nem választ a játékos nehézségi szintet, akkor legyen kezdő
    palya.x=8;
    palya.y=8;

    SDL_TimerID id = SDL_AddTimer(1000, idozit, NULL);
    bool iras=false;
    char szoveg[51]; ///Beolvasásokhoz
    char szoveg1[51];
    char szoveg2[51];
    char szoveg3[51];
    char ido[5];
    char jelolt[5];
    bool elsokatt=true; ///Első kattintás ne legyen akna
    int aknay,aknax; ///Első kattintás koordinátái
    int db_jobb=palya.akna; ///Csak annyi zászló lehet ahány akna
    int* p=&db_jobb; ///Lehetőség van visszaszedni a zászlót

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("LiberationSerif-Regular.ttf", 60);
    if (!font)
    {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    TTF_Init();
    TTF_Font *font1 = TTF_OpenFont("LiberationSerif-Regular.ttf", 30);
    if (!font1)
    {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    TTF_Init();
    TTF_Font *font2 = TTF_OpenFont("LiberationSerif-Regular.ttf", 20);
    if (!font2)
    {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Surface *felirat;
    SDL_Texture *pirosakna = IMG_LoadTexture(renderer, "pirosakna.jpg");
    SDL_Texture *zaszlo = IMG_LoadTexture(renderer, "zaszlo.jpg");
    SDL_Texture *jeloltakna = IMG_LoadTexture(renderer, "jeloltakna.jpg");
    SDL_Texture *ures = IMG_LoadTexture(renderer, "ures.jpg");
    SDL_Texture *egy = IMG_LoadTexture(renderer, "egy.jpg");
    SDL_Texture *ketto = IMG_LoadTexture(renderer, "ketto.jpg");
    SDL_Texture *harom = IMG_LoadTexture(renderer, "harom.jpg");
    SDL_Texture *negy = IMG_LoadTexture(renderer, "negy.jpg");
    SDL_Texture *ot = IMG_LoadTexture(renderer, "ot.jpg");
    SDL_Texture *hat = IMG_LoadTexture(renderer, "hat.jpg");
    SDL_Texture *het = IMG_LoadTexture(renderer, "het.jpg");
    SDL_Texture *nyolc = IMG_LoadTexture(renderer, "nyolc.jpg");
    SDL_Texture *simaakna = IMG_LoadTexture(renderer, "akna.jpg");
    SDL_Texture *bomba = IMG_LoadTexture(renderer, "jatekpirosakna.jpg");
    SDL_Texture *fedett = IMG_LoadTexture(renderer, "fedettmezo.jpg");
    SDL_Texture *jeloltbomba = IMG_LoadTexture(renderer, "jeloltbomba.jpg");
    SDL_Texture *ujjatek = IMG_LoadTexture(renderer, "ujjatek.png");
    SDL_Texture *menu = IMG_LoadTexture(renderer, "menu.png");

    SDL_Rect hely; ///Beolvasásokhoz
    SDL_Rect r= { 500, 180, 300, 30 };
    SDL_Rect r1= { 500, 330, 300, 30 };
    SDL_Rect r2= { 500, 480, 300, 30 };
    SDL_Rect r3= { 250, 200, 100, 30 };
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    /* varunk a kilepesre */
    SDL_Event ev;
    menurajzol(renderer,window, fekete2, font, pirosakna); /*Menü*/
    bool szabad=false;
    bool szabadits=false;

    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT)
    {
        if(!iras)
        {
            switch(ev.type)
            {
            case SDL_MOUSEMOTION:
                koord.x=ev.motion.x;
                koord.y=ev.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch(ev.button.button)
                {
                case SDL_BUTTON_LEFT: //Bal egérggomb
                    switch (fld)
                    {
                    case inmenu:
                        db_jobb=palya.akna; //megjelölhető aknák
                        jatekos->ido=0; //idő nullázás
                        elsokatt=true;
                        tpls=kezdo;
                        if(koord.x>=150 && koord.x<=730 && koord.y>=100 && koord.y<=200)  ///Új játék gomb
                        {
                            fld=ingame;
                            szabadits=true;
                            if(szabad){
                            palyafelszabadit(&palya);}
                            jatekrajzol(renderer, window, font2, &palya, fedett, ujjatek, menu);
                            foglal(&palya); //2D tömb foglalás
                        }
                        if(koord.x>=150 && koord.x<=730 && koord.y>=300 && koord.y<=400) ///Beállítások gomb
                        {
                            fld=inoptions;
                            beallitasrajzol(renderer, window, fekete2, font1, stt, zaszlo);
                        }
                        if(koord.x>=150 && koord.x<=730 && koord.y>=500 && koord.y<=600) ///Toplista gomb
                        {
                            fld = inleaderboard;
                            toplistarajzol(renderer, font, font1, elso, " ", fekete2, "Haladó", feher, "Kezdő", kezdo);
                        }
                        break;
                    case inoptions:
                        szabad=false;
                        //szabadits=true;
                        if(koord.x>=200 && koord.x<=350 && koord.y>=150 && koord.y<=200)  ///Kezdő gomb
                        {
                            stt = beginner;
                            palya.x = 8;
                            palya.y = 8;
                            palya.akna = 10;
                            beallitasrajzol(renderer, window, fekete2, font1, stt, zaszlo); /*Ha kezdőre kattint az legyen piros*/
                        }
                        if(koord.x>=200 && koord.x<=350 && koord.y>=250 && koord.y<=300)  ///Haladó gomb
                        {
                            stt = intermediate;
                            palya.x = 16;
                            palya.y= 16;
                            palya.akna = 40;
                            beallitasrajzol(renderer, window, fekete2, font1, stt, zaszlo); /*Ha haladóra kattint az legyen piros*/
                        }
                        if(koord.x>=200 && koord.x<=350 && koord.y>=350 && koord.y<=400)  ///Mester gomb
                        {
                            stt = master;
                            palya.x = 30;
                            palya.y = 16;
                            palya.akna = 99;
                            beallitasrajzol(renderer, window, fekete2, font1, stt, zaszlo); /*Ha mesterre kattint az legyen piros*/
                        }
                        if(koord.x>=200 && koord.x<=350 && koord.y>=450 && koord.y<=500)  ///Egyéni gomb
                        {
                            stt = custom; /*Ha egyénire kattint az legyen piros*/
                            iras=true;
                            fld=incustom;
                            egyenirajzol(renderer, window, font, font1, pirosakna); /*Egyéni kirajzolása*/
                        }
                        if(koord.x>=0 && koord.x<=100 && koord.y>=680 && koord.y<=720)
                        {
                            fld=inmenu;
                            menurajzol(renderer, window, fekete2, font, pirosakna); /*Visszagombra kattintva vissza a Menübe*/
                        }
                        break;
                    case inleaderboard:
                        switch (tpls)
                        {
                        case kezdo: /*Kezdőben két gomb: vissza és haladó*/
                            if(koord.x>=780 && koord.x<=880 && koord.y>=620 && koord.y<=720)
                            {
                                toplistarajzol(renderer, font, font1, elso, "Kezdő",feher, "Mester", feher, "Haladó", halado);
                                tpls = halado;  /*Haladóra kattintva átlép a haladóba*/
                            }
                            break;
                        case halado: /*Haladóban három gomb: kezdő, vissza és mester*/
                            if(koord.x>=0 && koord.x<=100 && koord.y>=620 && koord.y<=720)
                            {
                                toplistarajzol(renderer, font, font1, elso, " ",fekete2, "Haladó", feher, "Kezdő", kezdo);
                                tpls = kezdo; /*Kezdőre kattintva*/
                            }
                            if(koord.x>=780 && koord.x<=880 && koord.y>=620 && koord.y<=720)
                            {
                                toplistarajzol(renderer, font, font1, elso, "Haladó", feher, " ", fekete2, "Mester", mester);
                                tpls = mester; /*Mesterre kattintva*/
                            }
                            break;
                        case mester: /*Mesterben két gomb: haladó és vissza*/
                            if(koord.x>=0 && koord.x<=100 && koord.y>=620 && koord.y<=720)
                            {
                                toplistarajzol(renderer, font, font1, elso, "Kezdő", feher, "Mester", feher, "Haladó", halado);
                                tpls = halado; /*Haladóra kattintva*/
                            }
                            break;
                        }
                        if(koord.x>=390 && koord.x<=490 && koord.y>=680 && koord.y<=720)
                        {
                            fld=inmenu;
                            menurajzol(renderer, window, fekete2, font, pirosakna); /*Bármelyik toplistában a Vissza gombra kattintva a Menü jelenik meg*/
                        }
                        break;
                    case incustom:
                        if(koord.x>=390 && koord.x<=490 && koord.y>=680 && koord.y<=720)
                        {
                            fld=inmenu; /*Mentés gombra kattintva visszalép a Menübe*/
                            menurajzol(renderer, window, fekete2, font, pirosakna);
                        }
                        if(koord.x>=0 && koord.x<=100 && koord.y>=680 && koord.y<=720)
                        {
                            fld=inoptions; /*Vissza gombra kattintva Beállításokba lép*/
                            beallitasrajzol(renderer, window, fekete2, font1, stt, zaszlo);
                        }
                        break;
                    case ingame:
                        szabad=false;
                       // szabadits=false;
                        sprintf(jelolt,"%d",db_jobb); ///Megjelölhető aknák
                        kep(renderer, fedett, 38, 8, 31);
                        beturajzol(renderer, fekete2, font2, jelolt, 17, 40);

                        if(koord.x>=0 && koord.x<=palya.x*25 && koord.y>=100 && koord.y<=palya.y*25+100)
                        {
                            while(elsokatt)  /*Első kattintás ne legyen akna*/
                            {
                                for(int i=0; i<palya.y; i++) ///y koord keresése
                                {
                                    if((koord.y-(i*25))>=100 && (koord.y-(i*25))<=125)
                                        aknay=i;
                                }

                                for(int j=0; j<palya.x; j++) ///x koord keresése
                                {
                                    if((koord.x-(j*25))>=0 && (koord.x-(j*25))<=25)
                                        aknax=j;
                                }
                                palyatolt(&palya, aknax, aknay);
                                elsokatt=false;
                            }
                            jatekBAL(renderer, font2, koord, &palya, p, jelolt, simaakna, bomba, jeloltbomba, egy, ketto, harom, negy, ot, hat, het, nyolc, fedett, ures);
                        }
                        if(koord.y >= 35 && koord.y <=65)
                        {
                            if(koord.x>=((palya.x*25/2)-43) && koord.x<=((palya.x*25/2)-13) && koord.y>=35 && koord.y<=65)   ///J gombra kattintva új játék indul
                            {
                                elsokatt=true;
                                db_jobb=palya.akna;
                                fld=ingame;
                                jatekos->ido=0;
                                jatekrajzol(renderer, window, font2, &palya, fedett, ujjatek, menu);
                            }
                            if(koord.x<=((palya.x*25/2)+43) && koord.x>=((palya.x*25/2)+13) && koord.y>=35 && koord.y<=65)  ///M gombra kattintva visszalép a menübe
                            {
                                fld=inmenu;
                                elsokatt=true;
                                szabad=true; ///fel kell szabadítani
                                szabadits=true;

                                menurajzol(renderer, window, fekete2, font, pirosakna);
                            }
                        }
                        if(nyer(&palya))
                        {
                            fld=ifwin;
                            gyoztesrajzol(renderer, window, font1, font2);
                            iras=true; //név beolvasása-írás aktiválása
                        }
                        if(veszit(&palya))
                            fld=iflose;
                        break;
                    case ifwin:
                        szabadits=true;
                        if(koord.x>=200 && koord.x<=275 && koord.y>=250 && koord.y<=300)  ///Új játék gomb
                        {
                            elsokatt=true;
                            db_jobb=palya.akna;
                            fld=ingame;
                            jatekos->ido=0;
                            jatekrajzol(renderer, window, font2, &palya, fedett, ujjatek, menu);
                        }
                        if(koord.x>=325 && koord.x<=400 && koord.y>=250 && koord.y<=300)  ///Menü gomb
                        {
                            fld=inmenu;
                            elsokatt=true;
                            szabad=true; ///fel kell szabadítani
                            menurajzol(renderer, window, fekete2, font, pirosakna);
                        }
                        break;
                    case iflose:
                        szabadits=true;
                        if(koord.x>=((palya.x*25/2)-43) && koord.x<=((palya.x*25/2)-13) && koord.y>=35 && koord.y<=65)   ///J gomb
                        {
                            elsokatt=true;
                            fld=ingame;
                            jatekos->ido=0; ///idő nullázása
                            db_jobb=palya.akna; ///megjelölhetők visszaállítása
                            jatekrajzol(renderer, window, font2, &palya, fedett, ujjatek, menu);
                        }
                        if(koord.x<=((palya.x*25/2)+43) && koord.x>=((palya.x*25/2)+13) && koord.y>=35 && koord.y<=65)  ///M gomb
                        {
                            fld=inmenu;
                            szabad=true; ///fel kell szabadítani
                            menurajzol(renderer, window, fekete2, font, pirosakna);
                        }
                        break;
                    }
                    break;
                case SDL_BUTTON_RIGHT: //Jobb egérgomb
                    if(db_jobb != 0)  ///Az aknák számánál többet nem lehet megjelölni
                    {
                        if(fld==ingame)
                        {
                            jatekJOBB(renderer, koord, &palya, jeloltakna);
                            db_jobb--;
                            sprintf(jelolt,"%d",db_jobb);
                            kep(renderer,fedett,38, 8, 31);
                            if(db_jobb < 10)
                                beturajzol(renderer, fekete, font2, jelolt, 22, 40); ///Nem értem mi a fasz történik
                            if(db_jobb > 9)
                                beturajzol(renderer, fekete, font2, jelolt, 17, 40);
                        }
                    }

                    break;
                }
                break;
            case SDL_USEREVENT:
                if(fld==ingame && elsokatt==false){
                    jatekos->ido++;

                    sprintf(ido,"%d",jatekos->ido);
                    kep(renderer, fedett, 38, palya.x*25-40, 31);
                    if(jatekos->ido < 10)
                        beturajzol(renderer, fekete, font2, ido, palya.x*25-25, 40);
                    if(jatekos->ido < 100 && jatekos->ido > 9)
                         beturajzol(renderer, fekete, font2, ido, palya.x*25-30, 40);
                    if(jatekos->ido > 99)
                        beturajzol(renderer, fekete, font2, ido, palya.x*25-36, 40);
                }
                break;
            }
        }
        if(iras)
        {
            switch(fld)
            {
            case incustom:
                input_text(szoveg, 100, r, fekete2, feher, font, renderer); ///Pálya magasságának bekérése
                palya.y = atoi(szoveg);

                /* szoveg kirajzolasa */
                if (szoveg[0] != 0x0000){
                    egyenirajzol(renderer, window, font, font1, pirosakna);
                    boxRGBA(renderer,645,150,690,220,0,0,0,255);

                    felirat = TTF_RenderUTF8_Blended(font, szoveg, feher);
                    hely.x = 650;
                    hely.y = 150;
                    SDL_BlitSurface(felirat, NULL, screen, &hely);
                    SDL_FreeSurface(felirat);
                    SDL_RenderPresent(renderer);
                }

                input_text(szoveg1, 100, r1, fekete2, feher, font, renderer); ///Pálya szélességének bekérése
                palya.x=atoi(szoveg1);

                if (szoveg[0] != 0x0000){
                    egyenirajzol(renderer, window, font, font1, pirosakna);
                    boxRGBA(renderer,645,150,690,220,0,0,0,255);
                    boxRGBA(renderer,645,300,690,370,0,0,0,255);
                    beturajzol(renderer,feher,font,szoveg,650,150);

                    felirat = TTF_RenderUTF8_Blended(font, szoveg1, feher);
                    hely.x = 650;
                    hely.y = 300;
                    SDL_BlitSurface(felirat, NULL, screen, &hely);
                    SDL_FreeSurface(felirat);
                    SDL_RenderPresent(renderer);
                }
                input_text(szoveg2, 100, r2, fekete2, feher, font, renderer); ///Aknák számának bekérése
                palya.akna=atoi(szoveg2);

                if (szoveg[0] != 0x0000){
                    egyenirajzol(renderer, window, font, font1, pirosakna);
                    boxRGBA(renderer,645,150,690,220,0,0,0,255);
                    boxRGBA(renderer,645,300,690,370,0,0,0,255);
                    boxRGBA(renderer,645,450,690,520,0,0,0,255);
                    beturajzol(renderer,feher,font,szoveg,650,150);
                    beturajzol(renderer,feher,font,szoveg1,650,300);

                    felirat = TTF_RenderUTF8_Blended(font, szoveg2, feher);
                    hely.x = 650;
                    hely.y = 450;
                    SDL_BlitSurface(felirat, NULL, screen, &hely);
                    SDL_FreeSurface(felirat);
                    SDL_RenderPresent(renderer);
                }
                break;
            case ifwin: ///Győztes játék után a játékos nevének bekérése
                input_text(szoveg3, 100, r3, fekete2, feher, font, renderer);
                strcpy(jatekos->nev,szoveg3);

                if (szoveg[0] != 0x0000){
                    gyoztesrajzol(renderer,window,font1,font2);

                    felirat = TTF_RenderUTF8_Blended(font1, szoveg3, feher);
                    hely.x = 265;
                    hely.y = 170;
                    SDL_BlitSurface(felirat, NULL, screen, &hely);
                    SDL_FreeSurface(felirat);
                    SDL_RenderPresent(renderer);
                }
                break;
                default: break;
            }
            iras=false;
        }
    }
    toplista_free(elso);
    free(jatekos);
    if(szabadits){
    palyafelszabadit(&palya);}
    SDL_DestroyTexture(pirosakna);
    SDL_DestroyTexture(zaszlo);
    /* ablak bezarasa */
    TTF_CloseFont(font);
    SDL_RemoveTimer(id);
    debugmalloc_dump();
    debugmalloc_log_file("debugmalloc.txt");
    SDL_Quit();
    return 0;
}


#ifndef ADATSZERKEZETEK_H_INCLUDED
#define ADATSZERKEZETEK_H_INCLUDED

typedef struct Jatekos{
    char nev[50+1]; /*a játékos neve*/
    int ido; /*a játékos ideje*/
} Jatekos;

typedef struct Toplist{
    char* nev;
    int ido; /*a toplistás ideje*/
    struct Toplist* kov; /*a lista következõ elemére mutat*/
} Toplist;

typedef struct Koordinata{
    int x,y; /*egér koordinátái*/
} Koordinata;

typedef struct Palya{
    int x,y,akna; /*pálya szélessége, magassága, aknáinak száma*/
    int** ertek; /*mező értékei--2D tömb*/
} Palya;

typedef enum Field {inmenu, ingame, inleaderboard, inoptions, incustom, ifwin, iflose} Field; /*a program területegységei*/
typedef enum Toplista {kezdo, halado, mester} Toplista; /*3 toplista*/
typedef enum Settings {beginner, intermediate, master, custom} Settings; /*beállítások menüpontjai*/

#endif // ADATSZERKEZETEK_H_INCLUDED

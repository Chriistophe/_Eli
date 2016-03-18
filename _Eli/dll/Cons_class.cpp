
/*
    +------------------------------------------------------------------------+
    +     Prog/prj: BolosR    tokens lexer, compil, decompil for ti langage   +
    +    File Name: Cons_class.cpp declaration classe gestion console        +
    +------------------------------------------------------------------------+

*/


#include "lCons_class.h"

#include <io.h>
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <cstring>
#include <string>
#include <vector>
#include <windows.h>


class iCol : public ConsoleP
{

   void wtR();

    void attConWrit(int);
    void attRest();

    void attEcr_Auto(int );
    void attFon_Auto(int );
    bool Printf(HANDLE , PCHAR );
    int OdemoConInfo(HANDLE );
    void lavierge();
    void ourson();

    int carRead();
    int bckRead();
    void attCalc();
    HANDLE hConOut;



private:

    int a_reps;
    int a_aide;
    int a_fond;
    int a_coer;
    int a_text;
    int fpause;

    int attConD;
    int carConD;
    int bckConD;
    int bckConCH;

};

void iCol::attRest()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),this->attConD);
}

void iCol::wtR()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),this->attConD);
}

void iCol::attCalc() //juste une fois cpt test
{
  static int ban_ve=0;
  {
    // printf(" hello static flag count ....nb-> %d \n",ban_ve);

  }
    attConD = OdemoConInfo(GetStdHandle(STD_OUTPUT_HANDLE)) ;
    carConD = attConD % 16;
    bckConD = attConD - carConD;
    bckConCH = bckConD / 16;
    ban_ve++;
}

int iCol::bckRead() {
    return (bckConD);
}
int iCol::carRead() {
    return (carConD);
}



int iCol::OdemoConInfo(HANDLE hConOut)
{
    bool bSuccess;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    bSuccess = GetConsoleScreenBufferInfo(hConOut, &csbi);
    return ((csbi.wAttributes));
}


bool iCol::Printf(HANDLE hConsole, PCHAR s)
{
    bool bSuccess;
    DWORD cCharsWritten;
    const PCHAR crlf = "\n";
    bool retflag = TRUE;

    bSuccess = WriteConsole(hConsole, s, strlen(s), &cCharsWritten, NULL);
    retflag = bSuccess;
    bSuccess = WriteConsole(hConsole, crlf, strlen(crlf), &cCharsWritten, NULL);
    if (!bSuccess)
        retflag = FALSE;
    return(retflag);
}


void iCol::attEcr_Auto(int hexacolor)
{
    hexacolor=hexacolor % 0x0F;
    int tmp=0;
    tmp=hexacolor;
    while((hexacolor >(this->bckConD/16)-5)  && (hexacolor <(this->bckConD/16)+5)) hexacolor=(hexacolor+89) %16;
    hexacolor = hexacolor+ this->bckConD;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),hexacolor);
}


void iCol::attFon_Auto(int hexacolor)
{
    hexacolor=hexacolor % 0xF;
    int tmp=0;
    tmp=hexacolor;
    hexacolor=hexacolor * 16;
    hexacolor = hexacolor+ this->carRead();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),hexacolor);
}


void iCol::attConWrit(int dcol)
{
    dcol=dcol+ this->bckRead();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),dcol);
}


void iCol::lavierge()
{
    printf("\n");
    attEcr_Auto(12);
    printf("    + ------------------------------------------------------------------- +\n");
    printf("    +   Natural console mode:                                             +\n");
    printf("    + ti83->pc  BolosR file.83p create file.tib you can edit and modifie  +\n");
    printf("    +           the source code and recompil it.                          +\n");
    printf("    + pc->ti83  BolosR file.tib create file.83p transferable on your      +\n");
    printf("    +           texas instrument school computer.                         +\n");
    printf("    +   Forcing operation on console:                                     +\n");
    printf("    + ti83->pc  BolosR file -d create file.tib to modifie like .txt       +\n");
    printf("    + pc->ti83  BolosR file -c create file.83p to transfere on ti83       +\n");
    printf("    +   Drag & Drop over Windows:                                         +\n");
    printf("    + Select .tib or .83p, with themouse and put on 83 icone (exe file)   +\n");
    printf("    + BolosR  .exe (83p) will run on automatic mode.                       +\n");
    printf("    +                                                                     +\n");
    printf("    +   (c) Christophe Gousset  Oct/2015           ccgousset@gmail.com    +\n");
    printf("    +---------------------------------------------------------------------+\n");
     printf("\n");
    attEcr_Auto(11);
    printf("    + ------------------------------------------------------------------- +\n");
    printf("    +   Mode naturel sous console:                                        +\n");
    printf("    + ti83->pc  BolosR fichier.83p cree fichier.tib editable en .txt      +\n");
    printf("    + pc->ti83  BolosR fichier.tib cree fichier.83p transferable sur ti8x +\n");
    printf("    +   Modes forces sous console:                                        +\n");
    printf("    + ti83->pc  BolosR fichier -d cree fichier.tib a editer en .txt       +\n");
    printf("    + pc->ti83  BolosR fichier -c cree fichier.83p tranfere sur ti8       +\n");
    printf("    +   Drag & Drop sous Windows:                                         +\n");
    printf("    + Avec souris selectionnez un .tib ou .83p, deposez le sur l icone    +\n");
    printf("    + de BolosR  .exe (83p)qui fera la selection d action automatique.     +\n");
    printf("    +                                                                     +\n");
    attEcr_Auto(10);
    printf("    + Utilisateurs de calculatrice TexasInstrument ti83,ti82stat et .fr   +\n");
    printf("    + vous pouvez charger sur la calco les sources .83p compiles ou les   +\n");
    printf("    + transferer de la calco au pc ou mac avec un cable link (ti link).   +\n");
    printf("    + Mais vous qui voulez echanger modifier le contenu de ces programmes +\n");
    printf("    + source vous ne pouvez pas. Naturellement c est un impossible ....   +\n");
    printf("    + Grace a ce programme apres avoir transfere votre programme depuis   +\n");
    printf("    + votre TI , vous le transformez en code lisible (ti basic) pour      +\n");
    printf("    + le modifier ou l echanger avec vos potes. (plus besoin de le taper  +\n");
    printf("    + dans la machine. Vous le faites dans un notepad ou word en mode txt +\n");
    printf("    +  Une fois modifie, vous le recompilez avec BolosR et le repassez    +\n");
    printf("    + sur la ti avec le cable de transfert. A noter au passage que la     +\n");
    printf("    + decompilation BolosR retire la protection des programmes (chut ...) +\n");
    printf("    + donc a ne pas utiliser avec les programmes commerciaux.             +\n");
    printf("    + Memo par lot ms/dos:    c:> for %%f in (*.83p) do BolosR %%f         +\n");
    printf("    +---------------------------------------------------------------------+\n");
}


ConsoleP   *Get_ConsoleP()
{
    ConsoleP *p;
    p = new (iCol);
    return  p;
}



void iCol::ourson()
{
    attEcr_Auto(7);
    printf("       ___\n");
    attEcr_Auto(7);
    printf("    __|___|__    ");
    attEcr_Auto(6);
    printf("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n");
    attEcr_Auto(7);
    printf("    c/ .-. \\g    ");
    attEcr_Auto(6);
    printf("³  ");
    attEcr_Auto(17);
    printf("BolosR");
    attEcr_Auto(5);
    printf(" (Compil & Reverse) for Ti83/stat/.fr             ");
    attEcr_Auto(6);
    printf("  ³\n");
    attEcr_Auto(7);
    printf("   __\\( c )/__   ");
    attEcr_Auto(6);
    printf("³");
    attEcr_Auto(7);
    printf("                                                            ");
    attEcr_Auto(6);
    printf("³\n");
    attEcr_Auto(7);
    printf(" (_.-/     \\-._) ");
    attEcr_Auto(6);
    printf("³  ");
    attEcr_Auto(7);
    printf("BolosR [.83p]->.tib   or   BolosR [.tib ,.txt]->.83p      ");
    attEcr_Auto(6);
    printf("³\n");
    attEcr_Auto(7);
    printf("     \\  ");
    printf("\ ");
    printf("  /     ");
    attEcr_Auto(6);
    printf("³  ");
    attEcr_Auto(7);
    printf("BolosR [help,h,?]  for help                               ");
    attEcr_Auto(6);
    printf("³\n");
    attEcr_Auto(7);
    printf("   _.' ___ '._   ");
    attEcr_Auto(6);
    printf("³  ");
    attEcr_Auto(5);
    printf("typVer::publiee_10/03/17 chSum::ok Elise nRev::100        ");
    attEcr_Auto(6);
    printf("³\n");
    attEcr_Auto(7);
    printf("  (.-./   |.-.)  ");
    attEcr_Auto(6);
    printf("³  ");
    attEcr_Auto(7);
    printf("                           ");
    attEcr_Auto(13);
    printf("(c) ccgousset@gmail.com 2016   ");
    attEcr_Auto(6);
    printf("³\n");
    attEcr_Auto(7);
    printf("   `-'     `-'   ");
    attEcr_Auto(6);
    printf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n");
}


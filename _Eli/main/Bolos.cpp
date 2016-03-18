
/*
    +------------------------------------------------------------------------+
    +    Compil et decompil de .tib -> .83p a texas instrument calto system
    +    Debloquage de l octet de protection sur les codes decompiles. Chut!
    +     Prog/prj: BolosR    tokens lexer, compil, decompil for ti langage  +
    +    File Name: Main program. Corps du programme                         +
      ___
   __|___|__    ┌────────────────────────────────────────────────────────────┐
   c/ .-. \g    │  BolosR (Compil & Reverse) for Ti83/stat/.fr               │
  __\( c )/__   │  Version publiee sur CS le 18 mars 2016                    │
(_.-/     \-._) │  Version publiee sur gitHub le 18 mars 2016                │
    \     /     │                                                            │
  _.' ___ '._   │  .                                                         │
 (.-./   |.-.)  │                             (c) ccgousset@gmail.com 2015   │
  `-'     `-'   └────────────────────────────────────────────────────────────┘

    +                                                                        +
    +------------------------------------------------------------------------+
*/

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

#include "mCons_class.h"  //  aux Libannais, red made.
#include "mLexer_class.h"  //  aux Libannais, red made.

#define var_sigM_OB  17		  //  17 bytes for the variable header
#define error(x) {printf(x);return(0);}

//extern "C" void __declspec(dllimport) testInternDll(const LPCSTR sometext);
// alors les pros fini de rire ... ccg
using namespace std;

int stripBad(char *hoc);
int test( char *hic );
int min(int a, int b);
int xx=0;

void stripExtension(const char *gul,char *gol,char *ette);
void stripAslash(const char *iver,char *iat) ;
ConsoleP  *ioCon = ::Get_ConsoleP();

int main(int argc, char *argv[])
{
    // testInternDll(" dll_test ver 8 oct 2015"); test dll externe
    char fth[200]="";
    char src[200]="";
    char dst[200]="";
    char nomV[100]="";
    char ext[21]="";
    int modCol=0;
    int att=0;
    int bck=0;
    int car=0;
    int bckB=0;

    //ConsoleP  *ioCon = ::Get_ConsoleP();
    LexerP  *ioLex = ::Get_LexerP();

    ioLex->initialiseTokens();
    ioCon->attCalc();  // _getch();
    //   param retour de test
    //  2 pas de permission d ecriture. Tchao 2
    //  1 permission d ecriture. Atchoum 1 ..... \n",fil);       return 1;
    //  3 inexistant dans le chemin . Tchao 3  return 3;
    //  4 erreur inconnue, flux non detetcte. Inconnu  4 ..... \n",fil);    return 4;
    //  double test ligneCo vide et test
    // 1/ pas de fichier ou fichier absent -> cadre ourson

    if ( argv[1]==NULL || (test(argv[1])==3) )
    {
        if (stricmp(argv[1],"-h")==0 ||stricmp(argv[1],"help")==0\
            ||stricmp(argv[1],"?")==0)goto panzani;
        ioCon->ourson();
        ioCon->wtR();
        return 0;   // pas de param, aff.ourson, p.aide, ret.attribut, sortie
    }

    // 2/ argument 1 present > cadre ourson
    strcpy(src,argv[1]);
    strcpy(fth,src);  //  fth pour traitement tel kel
    stripExtension(argv[1],dst,ext);  //  ok aiguillage le 11 juillet 2015

    //  1 decompil   2 compil  3 aide
panzani:

    int opt=0;
    if ( stricmp(argv[2],"-d")==0 || stricmp(ext,"83p")==0  ) opt=1;
    if ( stricmp(argv[2],"-c")==0 || stricmp(ext,"tib")==0  ) opt=2;
    if ( stricmp(argv[1],"-h")==0 || stricmp(argv[1],"help")==0 ||\
         stricmp(argv[1],"?")==0   ) opt=3;

    if (opt==3)   //help
    {
        ioCon->lavierge();
        ioCon->wtR();
        return 0; // pas de param, g.aide, ret.attribut, sortie
    }

    if (opt==1)  //  decompil
    {
        strcat(dst,".tib");
        printf(" \n > --- decompilation  -- en couleur -------\n\n");
        printf(" > source entree %s \n", src);
        printf(" > modife sortie %s \n", dst);

		ioLex->h();
        ioLex->decompile(src,dst); //appel func decompil fichiers entree sortie
         _getch();
        ioCon->wtR();
        return 0; // param -d ,.83p,decompil ,ret.attribut, sortie
    }

    if (opt == 2 )  //  compil
    {
        stripAslash(dst,nomV);
        stripBad(nomV);
        strcat(dst,".83P");
        printf(" \n > ----- compilation -- quel b");
        ioCon->attConWrit(13);
        printf("%s","\5");
        ioCon->wtR();
        printf("nheur ! ---\n\n","\5");
        printf(" > source entree %s \n", src);
        printf(" > modife sortie %s \n", dst);
        printf(" > nom variable ti8X %s \n",nomV);

        char buff[0xFFFF];
        FILE *plouc;
        if ((int)(plouc = fopen(src, "rb"))==EOF)	  error(" > on open file .... ");
        fseek(plouc, 0, SEEK_END);  //  Calculate source fileSize.
        int t;

        t = ftell(plouc);

        fseek(plouc, 0, SEEK_SET);
        if (t > 0xFFEC)	  error(" > file is oversized ( < 64ko ) ");
        fread(buff,1,t,plouc);  //  Check if file was closed correctly.
        if (fclose(plouc)==EOF)  error(" > on closing file .... ");

        ioLex->h();
        ioLex->compile(src,dst);
        ioLex->Wcompile(src,dst,nomV);
        ioCon->wtR();
        return 0; // param -c,.tib,compil ,ret.attribut, sortie
    }
}

void stripAslash(const char *in,char *outP)  //  burger
{
    int i=0;
    int j=0;
    if (strrchr(in, '\\')!=NULL)
    {
        for (i=strrchr(in, '\\')-in+1; i<strlen(in); i++)  //  && i>(strlen(in)-4);i++)
        {
            outP[j++] = in[i];
        }
        strcat(outP,"\0");
        printf(" > avec AS ds r Asl %s\n",outP);
    }
    else
        strcpy(outP, in);
    printf(" > sans AS ds r Asl %s\n",outP);
}


void stripExtension(const char *in,char *outP,char *ext)  //  burger
{
    int i=0;
    int j=0;
    if (strrchr(in, '.')!=NULL)
    {
        strncpy(outP, in, strrchr(in, '.')-in);
        for (i=0; i<strlen(in); i++)
        {
            if(i> strlen(in)-4)ext[j++] = in[i];
        }
        strcat(ext,"\0");
    }

    else
        strcpy(outP, in);
}

int stripBad(char *chn)
{
    int u=0;
    int uu=0;
    int flid=0;
    char tempo[20]="";

    uu=strlen(chn);
    for (u=0; u<uu; u++)
    {
        if (  isalpha(chn[u]) )  //  si lettre
        {
            tempo[u]=toupper( chn[u] );
            flid=1;
            //  // _getch();;
            goto fin;
        }
        if ( isdigit(chn[u]) )
        {
            if (u==0)
            {
                tempo[u]='X';
                flid==1;        //  a voir warning de niveau etonnant !!!!!!!!!!!! tof
                goto fin;
            }
            if (u!=0)
            {
                tempo[u]=chn[u];
                goto fin;
            }
        }
        tempo[u]='X';
        flid==1;
fin:
        ;
    }
    strncpy(chn,tempo,strlen(tempo));
}

int test( char *fil )
{
    /* Check for existence */
    if( (_access( fil, 0 )) != -1 )
    {
        printf("\n > lecture source ... Ok \n",fil);
        /* Check for write permission */
        if( (_access( fil, 2 )) == -1 )
        {
            return 2;
        }
        return 1;
    }
    if( (_access( fil, 0 )) == -1 )
    {
        return 3;
    }
    printf(" > %s erreur inconnue, flux non detetcte. Inconnu  4 ..... \n",fil);
    return 4;
}


int min(int a, int b)
{
    if (a>b)return b;
    else return a;
}


inline void dparam()
{
    printf (" chez %s\n ---------------------------------------- \n",__FILE__);
    printf (" date %s\n",__DATE__);
    printf (" time %s\n",__TIME__);
    printf (" line %d\n",__LINE__);
    printf (" tstp %s\n",__TIMESTAMP__);
    //printf (" et le h ... ");
}

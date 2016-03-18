/*
    +------------------------------------------------------------------------+
    +     Prog/prj: BolosR    tokens lexer, compil, decompil for ti langage   +
    +    File Name: mLexer_class.h  librairie declarartions for main import   +
    +     Fonction:                                                          +
    +  Factor date: October 27 2015 15:34                                    +
    +	  Copyrights: ccgousset@gmail.com 2015                                 +
    +	      Auteur: Christophe GOUSSET , tokens list licence GNU             +
    +	    Remarque: mLexer_class.h declaration import of main                 +
    +------------------------------------------------------------------------+

*/


#include <io.h>
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <windows.h>

#include "..\Dll\Decl_Struct.h"

using namespace std;

struct LexerP
{
    virtual void h()=0;
    virtual void initialiseTokens()=0;
    virtual int Wcompile(string sr,string ds,char *nam)=0;
    virtual size_t getLongestToken()=0;// g_TokenLookup[string i] a &ret
    virtual bool CT_lookupToken(string in, token_t &ret)=0;//  g_ReverseLookup[short in] a &out
    virtual bool IS_lookupToken(unsigned short in, string &out)=0;
    virtual bool compile(string inFile, string outFile)=0;
    virtual bool decompile(string inFile, string outFile)=0;
 //   virtual void zza()=0;
};

extern "C" __declspec(dllimport) LexerP* Get_LexerP();


/*
    +--------------------------------------------------------------------------------------+
    +  Prog/prj:  mLexer_class.h   EXE IMPORT
    +  Historiq:  dimanche 6  sept
    +
    +  Fonction:  h de declaration structure (class ) base compilo pour l EXE IMPORT
    +  Techniqu:
    +  Auteur  : (c) ccgousset@gmail.com 2015 .Toute repro, utilisation, copie ou/et       +
    +           publication du prog, source, obj ou dll est soumise a droit d auteur.
    +--------------------------------------------------------------------------------------+
    +  mLexer_class.h dll commun a dll et corp sauf que la en importation
    +  (cdecl import) on importe de l exterieur alors quon exporte lamem class
    +  dans le dll (cdecl export) . mais ATTENTION cette .h appel la decl
    +  de structure dans Decl_Struct.h (autre rep celui de la dll).
    +  Au cas ou je perde une deuxieme fois la tete . toute donnee sensible
    +  dans .dlls . classe heritee style COM microsoft a constructeur masque
    +  Afin de livrer le projet sans les compilo decompilo gestion console
    +  Voila. double classe masquee pour ma version. Le reve du programmeur
    +  (c) ccgousset@gmail.com 2015 .Toute repro, utilisation, copie ou/et       +
    +  publication du prog, source, obj ou dll est soumise a droit d auteur.
    +------------------------------------------------------------------------+

*/



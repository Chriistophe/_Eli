/*
    +------------------------------------------------------------------------+
    +     Prog/prj: BolosRD  tokens lexer, compil, decompil for ti langage   +
    +    File Name: mCons_class.h  librairie declarartions for main import   +
    +     Fonction:                                                          +
    +  Factor date: October 27 2015 15:34                                    +
    +      Version: PerroK                                                   +
    +	  Copyrights: ccgousset@gmail.com 2015                                 +
    +   Compil Sys: CodeBlocks project but STL                               +
    +	      Auteur: Christophe GOUSSET , tokens list licence GNU             +
    +	    Remarque: mCons_class.h declaration import of main                 +
    +------------------------------------------------------------------------+

*/


#include <io.h>
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <windows.h>

struct ConsoleP
{
   virtual  void wtR()=0;

    virtual void attConWrit(int )=0;
    virtual void attRest()=0;
    virtual void attEcr_Auto(int )=0;
    virtual void attFon_Auto(int )=0;
    virtual bool Printf(HANDLE , PCHAR )=0;
    virtual int OdemoConInfo(HANDLE )=0;
    virtual void lavierge()=0;
    virtual void ourson()=0;

    virtual int carRead()=0;
    virtual int bckRead()=0;

    virtual void attCalc()=0;
};
//  Factory function that creates instances of the fils_object.
extern "C" __declspec(dllimport) ConsoleP* Get_ConsoleP();


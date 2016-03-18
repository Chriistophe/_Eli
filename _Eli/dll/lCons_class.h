
/*
    +------------------------------------------------------------------------+
    +     Prog/prj: BolosRD  tokens lexer, compil, decompil for ti langage   +
    +    File Name: lCons_class.h  librairie declarartions                   +
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
    virtual void attEcr_Auto(int )=0;
    virtual void attFon_Auto(int )=0;
    virtual void attRest()=0;
    virtual bool Printf(HANDLE , PCHAR )=0;
    virtual int OdemoConInfo(HANDLE )=0;
    virtual void lavierge()=0;
    virtual void ourson()=0;

  //  virtual int attRead()=0;
    virtual int carRead()=0;
    virtual int bckRead()=0;

    virtual void attCalc()=0;
};

extern "C" __declspec(dllexport) ConsoleP* Get_ConsoleP(void);

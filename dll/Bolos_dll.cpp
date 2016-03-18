/*+--------------------------------------------------------------------------------------+
    +  Prog/prj:  BolR_Dll.cpp rBolos.exe
    +  Historiq:  25 aout 23:11
    +
    +  Fonction:  corps de la dll
    +  Techniqu:
    +  Auteur  : (c) ccgousset@gmail.com 2015 .Toute repro, utilisation, copie ou/et       +
    +           publication du prog, source, obj ou dll est soumise a droit d auteur.      +
    +--------------------------------------------------------------------------------------+      */


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


extern "C" void __declspec(dllexport) testInternDll(const LPCSTR sometext)
{
    MessageBoxA(0,"test dll       (c) <ccgousset@gmail.com> \n\
restriction : dll code compilateur,console \n\
connection : aucune connection masquee\n",sometext,MB_OK | MB_ICONINFORMATION);
};


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  const char* sometext="Message from dll testInternDll";
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(0, sometext, "DLL_PROCESS_ATTACH ccgousset@gmail.com",MB_OK | MB_ICONINFORMATION);
               break;
    case DLL_PROCESS_DETACH:    break;
    case DLL_THREAD_ATTACH:
        MessageBoxA(0, sometext, "DLL_THREAD_ATTACH ccgousset@gmail.com",MB_OK | MB_ICONINFORMATION);
        break;
    case DLL_THREAD_DETACH: break;
    }
    return TRUE;  //  succesful
}

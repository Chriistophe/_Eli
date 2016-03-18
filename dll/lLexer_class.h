/*
    +------------------------------------------------------------------------+
    +     Prog/prj: BolosRD  tokens lexer, compil, decompil for ti langage   +
    +    File Name: lLexer_class.h  librairie declarartions                   +
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


using namespace std;


struct LexerP
{
  virtual  void h()=0;
  virtual  void initialiseTokens()=0;
  virtual  int Wcompile(string sr,string ds,char *nam)=0;
  virtual  size_t getLongestToken()=0;
  virtual  bool CT_lookupToken(string in, token_t &ret)=0;  //  assigne g_TokenLookup[string i] a &ret
  virtual  bool IS_lookupToken(unsigned short in, string &out)=0;  //  assigne g_ReverseLookup[short in] a &out
  virtual  bool compile(string inFile, string outFile)=0;
  virtual  bool decompile(string inFile, string outFile)=0;

  /*  virtual FILE *Getfp()=0;
    virtual void Setfp(FILE *val)=0;

    virtual unsigned int GetfileSize()=0;
    virtual void SetfileSize(unsigned int val)=0;

    virtual char *Getbuff()=0;
    virtual void Setbuff(char *val)=0;*/

   //virtual void zza()=0;
};


extern "C" __declspec(dllexport) LexerP* Get_LexerP(void);





/*
    +------------------------------------------------------------------------+
    +     Prog/prj: BolosR    tokens lexer, compil, decompil for ti langage   +
    +    File Name: Lexer_class.cpp. declaration classe lexer (compilo )     +
    +     Fonction:                                                          +
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

#define var_sigM 55
#define varHeaderSize 17

#define error(x) {printf(x);return(0);}

using namespace std;

#include "decl_Struct.h"
#include "lLexer_class.h"
#include "decl_Dico83.h"
#include "lCons_class.h"


ConsoleP  *coCon = ::Get_ConsoleP();

class iLexer:public LexerP
{

public:
    string Sout,Ssrc;
    int g;
    int ldata;
    size_t g_LongestInput;
    unsigned int fileSize;
    unsigned int sum ;

    unsigned char buff[0xFFFF];
    unsigned char buf[0xFFFF];
    unsigned char checksum[2];
    unsigned char header[var_sigM];
    unsigned char varheader[varHeaderSize];

    FILE *fp;

    map<string, token_t> g_TokenLookup;
    map<string, token_t>::const_iterator iter;
    map<unsigned short, string> g_ReverseLookup;

   // void zza();
    void h();
    void initialiseTokens();
    size_t getLongestToken();

    bool CT_lookupToken(string in, token_t &ret);
    bool IS_lookupToken(unsigned short in, string &out);
    bool compile(string inFile, string outFile);
    bool decompile(string inFile, string outFile);
    int Wcompile(string sr,string ds,char *nam);
};


void iLexer::initialiseTokens() //  Initialises the token map
{
    size_t i;       // long arraylen(standardToken 199]
    for(i = 0; i < 199; i++)     // Debut increment tablo token
    {
        token_t value;           // init structure auto nom value
        value.token = StandardTokens[i].data;
        value.sz = sizeof(StandardTokens[i].data);
        size_t len = strlen(StandardTokens[i].text);
        if(len > g_LongestInput)  g_LongestInput = len;

        string s = string(StandardTokens[i].text);

        g_TokenLookup[s] = value;

        g_ReverseLookup[value.token] = s;
    }

    for(i = 0; i < (sizeof(CalcVars) / sizeof(Token)); i++)
    {
        token_t value;
        value.token = CalcVars[i].data;
        value.sz = sizeof(CalcVars[i].data);

        size_t len = strlen(CalcVars[i].text);
        if(len > g_LongestInput)
            g_LongestInput = len;

        string s = string(CalcVars[i].text);

        g_TokenLookup[s] = value;

        g_ReverseLookup[value.token] = s;
    }


    for(i = 0; i < (sizeof(Replacements) / sizeof(ConvertRule)); i++)
    {
        token_t value;
        value.token = Replacements[i].tok;
        value.sz = sizeof(Replacements[i].tok);

        char c[] = {Replacements[i].c, 0};
        string s = c;


        g_TokenLookup[s] = value;

        g_ReverseLookup[value.token] = s;
    }
    //debug  _getch();
}

// start ++++++++++++++++++ spec tof ontrace +++++++++++++++++++++++++++++++++++++++++ debug

bool iLexer::compile(string inFile, string outFile)
{
    ifstream f(inFile.c_str(), ifstream::in);
    string tmpLine;	//	printf("inFile %s\n",inFile.c_str());
    vector<token_t> output;
    unsigned short outputSize = 0;
    int r=0;


    while(!f.eof())
    {
        getline(f, tmpLine, '\n');//papa ici samedi
        if(!tmpLine.length())continue;
        token_t st170; //var struc indefini ushort tokne, size_t sz

        while(tmpLine.length()) //tan que la ligne non nulle
        {
            string s = tmpLine.substr(0, getLongestToken()); //Grab the longest possible st170 .
            bool validToken = false;

            while(!validToken && s.length())
            {
                validToken = CT_lookupToken(s, st170);
                if(!validToken) s = s.substr(0, s.length() - 1);
            }
            if(!s.length() && isalpha(tmpLine[0]))
            {
                st170.token = toupper(tmpLine[0]);
                st170.sz = 1;
                s = tmpLine.substr(0, 1);
            }

            if(!s.length())
            {
                error(" > token non invalide ");
                f.close();
                return false;
            }

            else
            {
                outputSize += st170.sz;
                output.push_back(st170);
                tmpLine = tmpLine.substr(s.length(), tmpLine.length());
            }
        }

        bool gotNewline = CT_lookupToken("\n", st170);
        if(gotNewline)
        {
            outputSize += st170.sz;
            output.push_back(st170);
        }
    }


    for(vector<token_t>::iterator it = output.begin(); it != output.end();  ++it)
    {
        r=r+1;
        if (it->sz==2)
        {
            buff[r]=it->token & 0xFF ; //170;
            r=r+1;

            if ((it->token>>8)==0)
                buff[r]=48;
            else
                buff[r]=it->token >> 8;

        }
        else
        {
            buff[r]=it->token;
        }
    }
    buff[1]=0x3E;
    buff[r++]='\0';

    int t=0;
    for (t=1; t<=r; t++)
        buf[t-1]=buff[t];
    for (t=0; t<r; t++)
    {
        buff[t]=buf[t];
        //printf("%c",buff[t]);
    }

    ldata=strlen((char*)buff);
    return true;
}

bool iLexer::decompile(string inFile, string outFile)
{
    int ok=0;
    FILE *fp = fopen(inFile.c_str(), "rb");
    if(!fp) {}   unsigned short temp;

    fseek (fp, 0, SEEK_END);  //  non-portable
    ok=ftell (fp);
    fseek (fp, 0, SEEK_SET);  //  non-portable

    //  bool bAsmProgram = false;  assembleur non imlemente ds cette version
    struct ProgramHeader phdr;
    struct VariableEntry ventry;

    string sOutput = "";
    string conv="";
    size_t nBytesRead = 0;

    fread(&phdr, sizeof(phdr), 1, fp);
    fread(&ventry, sizeof(ventry), 1, fp);

    //debug  cout<<ok<<endl;
    fseek(fp, -1, SEEK_CUR);
    int flag;
    int tmp;
    flag=tmp=0;

    while (ftell(fp)<= ok-3 )
    {
        fread(&temp, 1, 2, fp);
        string conv;
        bool bIsFound = IS_lookupToken(temp, conv);
        //debug  cout <<temp <<endl;
        if(!bIsFound)
            bIsFound = IS_lookupToken(temp & 0xFF, conv);

        if(!bIsFound)
        {
            coCon->attEcr_Auto(13);
            cout<<  static_cast<char>(temp); //  _getch();
            coCon->attEcr_Auto(11);
            sOutput += static_cast<char>(temp);
            fseek(fp, -1, SEEK_CUR);
            nBytesRead++;
        }
        else
        {
            sOutput += conv;
            coCon->attEcr_Auto(10);
            cout<<  conv;
            coCon->attEcr_Auto(15);
            token_t tokenInfo;
            CT_lookupToken(conv, tokenInfo);

            if(tokenInfo.sz < sizeof(unsigned short))
            {
                fseek(fp, -1, SEEK_CUR);
                nBytesRead++;
            }
            else
                nBytesRead += 2;
        }
    }
    fclose(fp);
    ofstream f(outFile.c_str());
    f << sOutput;
    f.close();
    printf("\n\n > fait par un super mutant \n");
    printf(" > mais d ou vient son pouvoir ?\n\n");
    printf("  (c) ccgousset@gmail.com 2015 \n");

    return true;
};


bool iLexer::CT_lookupToken(string in, token_t &ret)  //  assigne g_TokenLookup[string i] a &ret
{
    if(in.length() > g_LongestInput)
        return false;
    if(g_TokenLookup.find(in) == g_TokenLookup.end())
        return false;
    ret = g_TokenLookup[in];
    return true;
};

bool iLexer::IS_lookupToken(unsigned short in, string &out)  //  assigne g_ReverseLookup[short in] a &out
{
    if(g_ReverseLookup.find(in) == g_ReverseLookup.end())
        return false;
    out = g_ReverseLookup[in];
    return true;
};

int iLexer::Wcompile(string sr,string ds,char *nam)
{
    char *src,*dst;
    strcpy(src,sr.c_str());
    strcpy(dst,ds.c_str());
    int i=0;

    remove(dst);
    if ((int)(fp = fopen(dst, "a+b"))==EOF)	  error("_Target_Open_error");

    header[53] = ((ldata + varHeaderSize)) & 0xFF;		//Data Size + Var header size (L)
    header[54] = ((ldata + varHeaderSize)>>8) & 0xFF;	//Data Size + Var header size (H)
    fwrite(header,1,55,fp); //35 36h long fichier  - 55 (entete) soit h39

//Write variable header to target file.
    varheader[2] =  (ldata + 2) & 0xFF;				//Data Size (L)
    varheader[3] =  ((ldata + 2)>>8) & 0xFF;			//Data Size (H)


    for(i=0; i<8 ; i++)
    {
        if ((char*)nam[i]!="\0")
        {
            varheader[5+i] = nam[i];
        }
    }

    varheader[12] = (0) & 0xFF;
    varheader[13] = (ldata + 2) & 0xFF;				//Data Size (L)
    varheader[14] = ((ldata + 2)>>8) & 0xFF;			//Data Size (H)
    varheader[15] = ldata & 0xFF;						//Data Size (L)
    varheader[16] = (ldata>>8) & 0xFF;					//Data Size (H)

    fwrite(varheader,1,varHeaderSize,fp);
    fwrite(buff,1,ldata,fp);  //Write variable data to target file.

    for(i = 0; i<ldata; i++)  //Calculate and Write checksum to target file.
        sum += buff[i];

    for(i = 0; i<varHeaderSize; i++)
        sum += varheader[i];

  printf("\n > sigma bytes is %X \n",sum); // sigma porno

    checksum[0] = (sum) & 0xFF;		//Checksum (L)
    checksum[1] = (sum>>8) & 0xFF;	//Checksum (H)

    fwrite(checksum,1,2,fp);
    fclose(fp);
// if (fclose(fp)==EOF)  error("_Target_Close_error");

    printf("\n > %s is write \n",dst);
    printf(" > ti83 source name's %s \n",nam);
    printf(" > fait par un super mutant \n");
    printf(" > mais d ou vient son pouvoir ?\n\n");
    printf("  (c) ccgousset@gmail.com 2015 \n");

    return 0;

};

size_t iLexer::getLongestToken()
{
    return g_LongestInput;
};

void iLexer::h()
{
    coCon->attCalc();

    int i=0;
    int j=0;

    char sigM[55]=
    {
        0x2A, 0x2A, 0x54, 0x49, 0x38, 0x33, 0x2A, 0x2A,		//**TI83**   //8   header 0 7
        0x1A, 0x0A,	0x00,									//signature 26 10 00         //11   8 9 a

        0x43, 0x6F, 0x6D, 0x70, 0x69, 0x6C, 0x65, 0x20, // reco ti calculatrice hash texas
        0x70, 0x61, 0x72, 0x20, 0x42, 0x6F, 0x6C, 0x6F,  // en octal ti Basic
        0x73, 0x20, 0x28, 0x63, 0x29, 0x63, 0x63, 0x67,  // commentaire 39 car
        0x6F, 0x75, 0x73, 0x73, 0x65, 0x74, 0x20, 0x32,
        0x30, 0x31, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00,
        0x00, 0x00,
    };
    char heaM[17] =
    {
        0x0B,0x00,			//0 1								//start of variable header    37 38   //0b 00
        0x0C,0x00,			//2 3								//length of variable in bytes  of data 39 3a
        0x05,												//variable type ID. 0x15 is for appvar     3b char 06 hidden 05 libre
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//variable nam (max 8 characters)  3c 43 prog nam000
        0x00, 0x00,//44 45 length of variable in bytes (copy)44 45 dat  15 16
        0x00, 0x00,	 //46
        // 0x0B,0x00,			  //  0  //  start of variable header    37 38  //  0b 00
        // 0x0C,0x00,			  //  2 3	  //  length of variable in bytes  of data 39 3a
    };
    cout <<" > information h_1:  ";
    for (i=0; i<55; i++)
    {
        this->header[i]=sigM[i];
    }
   // cout <<endl;
    for (i=0; i<17; i++)
    {
        this->varheader[i]=heaM[i];
    }

};


LexerP   *Get_LexerP()
{
    LexerP *p;
    p = new (iLexer);   // malloc(sizeof(iLexer));
    return  p;
}

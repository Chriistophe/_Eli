
/*
    +------------------------------------------------------------------------+
    +     Prog/prj: BolosRD  tokens lexer, compil, decompil for ti langage   +
    +    File Name: decl_struct.h  declarations ,and abstracts structures    +
    +------------------------------------------------------------------------+
*/


struct Token  //  Describes a potential token to be read by the compiler
{
    unsigned char data;  //  The compiled byte for the token
    const char *text;  //  The actual text to be converted by the interpreter
};


struct TwoByte {  //  A two byte token (0xBB, 0x7E and SysVar)
    unsigned short data;
    const char *text;
};

struct ConvertRule {  //  Direct ASCII character to token conversion.
    char c;				  //  the character
    unsigned char tok;	  //  the equivalent token
};

typedef struct
{
    unsigned short token;
    size_t sz;
} token_t;

struct ProgramHeader
{
    char sig[8];  //
    char extsig[3];  //
    char comment[42];  //  faux ne peu pas marcher
    char head[2] ;  //  trop court
} as;

struct VariableEntry
{
    unsigned short start;  //  valeur 0x0C
    unsigned short length1;  //  prog apparement
    unsigned char type;  //  11
    char name[8];  //  led

    //  char ver;  //  oui a remettre
    //  char flags;  //  areuh maitre
    unsigned short le;  //  lof data
    unsigned short length2;  //  lof program
} sas;



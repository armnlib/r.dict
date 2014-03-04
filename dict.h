/*
* dict_to_stdout.c 
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <libxml/xmlmemory.h>
#include <libxml/encoding.h>
#include <libxml/parser.h>

#define DEBUG(x) printf(x)
#define NCARMAX 256

#define NOMVAR 0
#define TYPVAR 1

#define SHORT 0
#define LONG  1

#define INTEGER 0
#define REAL    1
#define LOGICAL 2
#define CODE    3

#define FRANCAIS 0
#define ENGLISH  1

  typedef struct 
    {
    int tokenkind;
    char nomvar[8];
    char typvar[4];
    char short_description[128];
    char long_description[128];
    int code_nature;
    char nature[128];
    char magnitude[32];
    char mesure[32];
    char units[32];
    char min[32];
    char max[32];
    char logical_codes[2][16];
    char logical_meanings[2][64];
    char codes[64][16];
    char meanings[64][64];
    int ncodes;
    } _metvar;


/*
*  Forward declaration of fucntions
*/

void parsMetvar(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur, char *var_name, char *desc_type, char *language);
void parsTypvar(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur, char *var_type, char *desc_type, char *language);
int  parseDictionary(char *filename, char *var_name, char *var_type, char *desc_type, char *language);
extern void c_ccard(char **argv,int argc,char **cle,char val[][NCARMAX], char **def,int n,int *npos);
int changeEncoding(char *string, int encoding);

/* 
  External variable for validating DTD */
  extern int xmlDoValidityCheckingDefaultValue;

/*
* Globals var.
*/

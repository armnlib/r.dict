#include "dict.h"

int verbose_mode = 0;
int code_encoding = XML_CHAR_ENCODING_ASCII;



/* -------------------------------------------------------------------------- */


int main(int argc, char **argv) 
  {
  char *ptr_char = NULL;
  char dictionaryPath[256];
  char *liste[6], lcl_liste[6][256], *def[6], lcl_def[6][16], val[6][256];
  char name[8], type[4], desc[8], language[12], verbose[12], encoding[12]; 
  int i, npos;

  strcpy(lcl_liste[0], "n.");
  strcpy(lcl_liste[1], "t.");
  strcpy(lcl_liste[2], "desc.");
  strcpy(lcl_liste[3], "lang.");
  strcpy(lcl_liste[4], "v.");
  strcpy(lcl_liste[5], "encoding.");

  liste[0] = (char *) lcl_liste[0];
  liste[1] = (char *) lcl_liste[1];
  liste[2] = (char *) lcl_liste[2];
  liste[3] = (char *) lcl_liste[3];
  liste[4] = (char *) lcl_liste[4];
  liste[5] = (char *) lcl_liste[5];

  strcpy(val[0],"");
  strcpy(val[1],"");
  strcpy(val[2],"short");
  strcpy(val[3],"undefined");
  strcpy(val[4],"no");
  strcpy(val[5],"ascii");

  strcpy(lcl_def[0],".");
  strcpy(lcl_def[1],".");
  strcpy(lcl_def[2],"long");
  strcpy(lcl_def[3],"undefined");
  strcpy(lcl_def[4],"yes");
  strcpy(lcl_def[5], "ascii");

  def[0] = (char *) lcl_def[0];
  def[1] = (char *) lcl_def[1];
  def[2] = (char *) lcl_def[2];
  def[3] = (char *) lcl_def[3];
  def[4] = (char *) lcl_def[4];
  def[5] = (char *) lcl_def[5];

 
  npos = 0;
  c_ccard(argv,argc,(char **) liste,val, (char **) def,6,&npos);
  
  strcpy(name, val[0]);
  strcpy(type, val[1]);
  strcpy(desc, val[2]);
  strcpy(language, val[3]);
  strcpy(verbose, val[4]);
  strcpy(encoding, val[5]);
  
  if (0 != strcmp(name, ".") && 0 == strlen(type))
    {
    strcpy(type, "");
    }
  
  if (0 == strcmp(name, ".") && 0 == strlen(type))
    {
    strcpy(type, ".");
    }
  
  if (0 == strlen(name) && 0 == strlen(type))
    {
    strcpy(name, ".");
    strcpy(type, ".");
    }
  
  if (0 == strcmp(verbose, "yes"))
    {
    verbose_mode = 1;
    }
    
  code_encoding = XML_CHAR_ENCODING_ASCII;
    if (0 == strcmp(encoding, "iso8859-1"))
      {
      code_encoding = XML_CHAR_ENCODING_8859_1;
      }
     
     if (0 == strcmp(encoding, "utf8"))
      {
      code_encoding = XML_CHAR_ENCODING_UTF8;
      }
     
 
  /*  Get env. variable to set the language  */
  if (0 == strcmp(language, "undefined"))
    {  
    if ((ptr_char = getenv("CMCLNG")) == NULL ) 
      {
      if (verbose_mode)
        {
        fprintf(stderr,"Cannot get ENVIRONMENT var: CMCLNG. setting to english\n");
        }
      strcpy(language,"english");         
      }
    else
      {
      strcpy(language,ptr_char);
      }
    }

  xmlDoValidityCheckingDefaultValue = 1;

  /* COMPAT: Do not generate nodes for formatting spaces */

  LIBXML_TEST_VERSION
  xmlKeepBlanksDefault(0);

  if ((ptr_char = getenv("AFSISIO")) == NULL ) 
    {
    fprintf(stderr,"Cannot get env var: AFSISIO. cannot  load the dictionary\n");
    exit(13);         
    }
  
  sprintf(dictionaryPath, "%s%s", getenv("AFSISIO"), "/datafiles/constants/stdf.variable_dictionary.xml");
  if (parseDictionary(dictionaryPath, name, type, desc, language)) 
    {
    printf("Failure\n");
    return(1);
    }

  return(0);
  }

   
  



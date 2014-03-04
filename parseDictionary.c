#include "dict.h"

extern int code_encoding;
extern int verbose_mode;

/* -------------------------------------------
* 
* Function parseJobFile : parse an xml file
*
* -------------------------------------------
*/
int  parseDictionary(char *filename, char *var_name, char *var_type, char *desc_type, char *language) 
  {
  xmlDocPtr    doc;
  xmlNsPtr     ns;
  xmlNodePtr   cur;
  xmlDtdPtr    dtd ;
  xmlValidCtxt ctxt;
  char dtdfile[256];
  
  static int once = 1;

  /*
  * build an XML tree from the file;
  */
  doc = xmlParseFile(filename);
  if (doc == NULL) return(1);

    /* -----------------------------------------  */
    /*  Check the document is of the right kind   */
    /* ------------------------------------------ */
  cur = xmlDocGetRootElement(doc);
  if (cur == NULL ) 
    {
    fprintf(stderr,"empty document\n");
    xmlFreeDoc(doc);
    return(1);
    }

  if (verbose_mode)
    {
    printf("%s -- %s -- %s\n",cur->name,xmlGetProp(cur,"date") , xmlGetProp(cur,"version_number"));
    }

    /* ---------------------- */
    /*  Parse the DTD!   */
    /* ---------------------- */
    strcpy(dtdfile, "");
    strcat(dtdfile, getenv("AFSISIO"));
    strcat(dtdfile, "/datafiles/constants/dict.dtd");
/*    printf(stderr, "%s\n", dtdfile); */
    dtd = xmlParseDTD(NULL,dtdfile);
    if (! dtd ) 
    {
    printf("Error Parsing DTD\n");
    return (1);
    }

    /* ----------------------------------------------------------- */
    /*   Set up xmlValidCtxt for error reporting when validating   */
    /* ----------------------------------------------------------- */

    ctxt.userData = stderr; 
    ctxt.error    = (xmlValidityErrorFunc) fprintf;   /* register error function */ 
    ctxt.warning  = (xmlValidityWarningFunc) fprintf; /* register warning function */ 


    if (xmlValidateDtd(&ctxt,doc,dtd))
      {
      if (verbose_mode)
        {
        printf("Validation (DTD) Ok!\n");
        }
      }        
    else 
      {
      printf("Validation error!<br>\n");
      return (1);
      }


    /*
    * Now, walk the tree.
    */


    cur = cur->children; 
    while (cur != NULL) 
      { 
      if (0 == strcmp(cur->name, "metvar") && 0 < strlen(var_name))
        {
        parsMetvar(doc, ns, cur, var_name, desc_type, language);  
        } 
        
      if (0 == strcmp(cur->name, "typvar") && 0 < strlen(var_type))
        {
        if (once)
          {
          once = 0;
          printf("---TYPVAR-----------------------------------------------------------------------\n");
          }
        parsTypvar(doc, ns, cur, var_type, desc_type, language);  
        } 
 
      cur = cur->next;
      }


    /* Free all */

    xmlFreeDtd(dtd);
    xmlFreeDoc(doc);
    return(0);
  }

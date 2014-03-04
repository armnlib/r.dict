#include "dict.h"

extern int code_encoding;

void  parsTypvar(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur,  char *var_type, char *desc_type, char *language) 
  {

  xmlNodePtr Trotteur ,Trotteur1;
  char buf_usage[40]="";
  int check_var_type = 0;
  int code_desc = 0;
  _metvar metvar;
  xmlChar *nomvar, *short_description, *long_description, *mesure, *units;
  xmlChar *magnitude, *min, *max, *natureVariable;
  
  memset(&metvar, NULL, sizeof(_metvar));


  /* COMPAT xmlChildrenNode is a macro unifying libxml1 and libxml2 names */

  /* grab the usage , cause we will loose this we we go down the tree */
  strcpy(buf_usage,(char *)xmlGetProp(cur,"usage"));

  if (0 != strcmp(var_type,".")) check_var_type = 1;
  if (0 != strcmp(desc_type, "short")) code_desc = 1;
  
  cur = cur->children;  
  while (cur != NULL) 
    {
    if (!strcmp((char *)cur->name, "nomtype")) 
      {
      strcpy(metvar.typvar, xmlNodeListGetString(doc, cur->children, 1));
      }

      if (check_var_type)
        {
        if (0 == strmatch(metvar.typvar, var_type))
          {
          return;
          }
        }
      /* --- DESCRIPTION --- */


    if (!strcmp((char *)cur->name, "description")) 
      {
      Trotteur1 = cur->children;
      while (Trotteur1 ) 
        {
        if (!strcmp((char *)Trotteur1->name, "short")) 
          {
          if (!strcmp((char *)xmlGetProp(Trotteur1,"lang"),"en") && !strncmp(language,"english",2))  
            {
            strcpy(metvar.short_description, xmlNodeListGetString(doc, Trotteur1->children, 1));
            changeEncoding(metvar.short_description, code_encoding);
            }
          else
            {
            if (!strcmp((char *)xmlGetProp(Trotteur1,"lang"),"fr") && !strncmp(language,"francais",2))             
              {
              strcpy(metvar.short_description, xmlNodeListGetString(doc, Trotteur1->children, 1));
              changeEncoding(metvar.short_description, code_encoding);
              }           
            }          
          }

        if (!strcmp((char *)Trotteur1->name, "long") && xmlNodeListGetString(doc, Trotteur1->children, 1)) 
          {
          strcpy(metvar.long_description, xmlNodeListGetString(doc, Trotteur1->children, 1));
          changeEncoding(metvar.long_description, code_encoding);
          }

        Trotteur1 = Trotteur1->next;
        }
      }
    cur = cur->next;
    } 
    
    printf("%s  %-60s\n", metvar.typvar, metvar.short_description);

  }

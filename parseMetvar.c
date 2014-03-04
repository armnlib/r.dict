#include "dict.h"

extern int code_encoding;

/* -------------------------------------------------------------
*
* Function parsMetvar : Do the actual parsing
*
* -------------------------------------------------------------
*/

void  parsMetvar(xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur,  char *var_name, char *desc_type, char *language) 
  {
  xmlNodePtr Trotteur ,Trotteur1;
  char buf_usage[40]="";
  int check_var_name = 0;
  int check_type_name = 0;
  int code_desc = 0;
  int i, lan;
    
  _metvar metvar;
  xmlChar *nomvar, *short_description, *long_description, *mesure, *units;
  xmlChar *magnitude, *min, *max, *natureVariable;
  
  static char *short_desc[] = {"Description courte :", "Short Description : "};
  static char *long_desc[]  = {"Description longue :", "Long  Description : "};
  static char *unites[]     = {"Unites : ", "Units : "};
  static char *mag[]     = {"Ordre de grandeur : ", "Magnitude : "};
  
  memset(&metvar, NULL, sizeof(_metvar));

  /* COMPAT xmlChildrenNode is a macro unifying libxml1 and libxml2 names */
  /* grab the usage , cause we will loose this we we go down the tree */
  strcpy(buf_usage,(char *)xmlGetProp(cur,"usage"));

  if (0 != strcmp(var_name,".")) check_var_name = 1;
  if (0 != strcmp(desc_type, "short")) code_desc = 1;
  
  cur = cur->children;  
  while (cur != NULL) 
    {
    /* --- NOMVAR --- */ 
    
    if (!strcmp((char *)cur->name, "nomvar")) 
      {
      strcpy(metvar.nomvar, xmlNodeListGetString(doc, cur->children, 1));
      }

    if (check_var_name)
      {
      if (0 == strmatch(metvar.nomvar, var_name))
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

        /* --- MESURE --- */
      
      if (!strcmp((char *) cur->name, "measure")) 
        {
        Trotteur = cur->children;
      /*
            -------------
                integer
            -------------
      */

      if (!strcmp((char *)Trotteur->name,"integer")) 
        {
        metvar.code_nature = INTEGER;
        if (strncmp(language,"english",2))
          {
          strcpy(metvar.nature, "Integer Variable");
          }
        else
          {
          strcpy(metvar.nature, "Variable entiere");
          }


        Trotteur1 = Trotteur->children;

        while (Trotteur1 ) 
          {
          if ( 0 == strcmp((char *)Trotteur1->name,"units")) 
            {
            strcpy(metvar.mesure, xmlNodeListGetString(doc, Trotteur1->children, 1));   
            }            

          if ( 0 == strcmp((char *)Trotteur1->name,"magnitude")) 
            { 
            magnitude = xmlNodeListGetString(doc, Trotteur1->children, 1);            
            if (magnitude)
              {
              strcpy(metvar.magnitude, magnitude);
              } 
            }

          if ( 0 == strcmp((char *)Trotteur1->name,"min")) 
            { 
            min = xmlNodeListGetString(doc, Trotteur1->children, 1);            
            if (min)
              {
              strcpy(metvar.min, min);
              }
            } 

          if ( 0 == strcmp((char *)Trotteur1->name,"max")) 
            { 
            max = xmlNodeListGetString(doc, Trotteur1->children, 1);            
            if (max)
              {
              strcpy(metvar.max, max);
              } 
            }

          Trotteur1 = Trotteur1->next;
          }
        }
            /*
            -------------
                real
            -------------
      */
      if (!strcmp((char *)Trotteur->name,"real")) 
        {
        metvar.code_nature = REAL;
        if ( !strncmp(language,"english",2))
          {
          strcpy(metvar.nature, "Real Variable");
          }
        else
          {
          strcpy(metvar.nature, "Variable reelle");
          }

        Trotteur1 = Trotteur->children;
        while (Trotteur1 ) 
          {
          if ( !strcmp((char *)Trotteur1->name,"units")) 
            {
            units = xmlNodeListGetString(doc, Trotteur1->children, 1);	 
            if (units)
              {           
              strcpy(metvar.units, units);
              }
            }

          if ( 0 == strcmp((char *)Trotteur1->name,"magnitude")) 
            { 
            magnitude = xmlNodeListGetString(doc, Trotteur1->children, 1);            
            if (magnitude)
              {
              strcpy(metvar.magnitude, magnitude);
              } 
            }

          if ( 0 == strcmp((char *)Trotteur1->name,"min")) 
            { 
            min = xmlNodeListGetString(doc, Trotteur1->children, 1);            
            if (min)
              {
              strcpy(metvar.min, min);
              }
            } 

          if ( 0 == strcmp((char *)Trotteur1->name,"max")) 
            { 
            max = xmlNodeListGetString(doc, Trotteur1->children, 1);            
            if (max)
              {
              strcpy(metvar.max, max);
              } 
            }

            Trotteur1 = Trotteur1->next;
          }
        }

      /*
            -------------
                logical
            -------------
      */
      if (0 == strcmp((char *)Trotteur->name,"logical")) 
        {
        metvar.code_nature = LOGICAL;
        if (0 == strncmp(language,"english",2))
          {
          strcpy(metvar.nature, "Logical variable");
          }
        else
          {
          strcpy(metvar.nature, "Variable logique");
          }
        

        Trotteur1 = Trotteur->children;                               
        i = 0;
        while (Trotteur1 ) 
          {
          if (!strcmp((char *)Trotteur1->name,"value"))
            {
            strcpy(metvar.logical_codes[i],xmlNodeListGetString(doc, Trotteur1->children, 1));  
            }                    
          
          if (!strcmp((char *)Trotteur1->name,"meaning"))
            {
            strcpy(metvar.logical_meanings[i],xmlNodeListGetString(doc, Trotteur1->children, 1));      
            i++; 
            }
          metvar.ncodes = i;
          Trotteur1 = Trotteur1->next;
          }
        }
        

      /*
            -------------
                code
            -------------
      */
      if (!strcmp((char *)Trotteur->name,"code")) 
        {
        metvar.code_nature = CODE;
        if (0 != strncmp(language,"english",2))
          {
          strcpy(metvar.nature, "Variable codee\n");
          }
        else
          {
          strcpy(metvar.nature, "Coded Variable\n");
          }
          

        Trotteur1 = Trotteur->children;
        i = 0;
        while (Trotteur1 ) 
          {
          if (!strcmp((char *)Trotteur1->name,"value"))
              strcpy(metvar.codes[i], (xmlChar *) xmlNodeListGetString(doc, Trotteur1->children, 1));                      
          if (!strcmp((char *)Trotteur1->name,"meaning"))
            {
            strcpy(metvar.meanings[i], (xmlChar *) xmlNodeListGetString(doc, Trotteur1->children, 1));                      
            changeEncoding(metvar.meanings[i], code_encoding);
            i++;
            }
          Trotteur1 = Trotteur1->next;
         }
        metvar.ncodes = i;
        }

      }/* end if mesure */

        /*
          ---------------
          DESCRIPTORUSAGE
          ---------------
        */

        if (!strcmp((char *)cur->name,"descriptorUsage")) 
          {
  /*       
          Trotteur1 = cur->children;  

          if (Trotteur1 != NULL ) 
            {
            if (!strcmp(lang,"francais"))
                printf("\nUsage des Descripteurs");
            else
                printf("\nDescriptorUsage");

          while (Trotteur1 )
            {
            if (!strcmp((char *)Trotteur1->name,"Typvar")) 
              {
              (! xmlNodeListGetString(doc, Trotteur1->children, 1)) ? printf("") : printf("\nTypeVar : %s",xmlNodeListGetString(doc, Trotteur1->children, 1)) ;

              Trotteur1 = Trotteur1->next;
              continue;
              }

            if (!strcmp((char *) Trotteur1->name,"IP1")) 
              {
              if (xmlGetProp(Trotteur1, "value"))
                    printf("\nIP1 : %s",xmlGetProp(Trotteur1,"value"));
              Trotteur1 = Trotteur1->next;
              continue;
              }

            if (!strcmp((char *) Trotteur1->name,"IP2")) 
              {
              if (xmlGetProp(Trotteur1,"value")) 
                    printf("\nIP2 : %s",xmlGetProp(Trotteur1,"value"));
              Trotteur1 = Trotteur1->next;
              continue;
              }

            if (!strcmp((char *) Trotteur1->name,"IP3")) 
              {
              if (xmlGetProp(Trotteur1,"value")) 
                    printf("\nIP3 : %s",xmlGetProp(Trotteur1,"value"));                 
              Trotteur1 = Trotteur1->next;
              continue;
              }

            }
          } 
          } */
      } /* end if descriptorUsage */
  
    
    cur = cur->next;
    } 
    
  lan = 0;
  if (0 == strcmp(language, "english"))
    {
    lan = 1;
    }
    

  switch(code_desc)
    {
    case SHORT:
      printf("%s  %-60s %-s\n", metvar.nomvar, metvar.short_description, metvar.units);
    break;

    case LONG:
      printf("--------------------------------------------------------------------------------\n");
      printf("Nomvar : %-s\n", metvar.nomvar);
      printf("%-s %-s\n",  short_desc[lan], metvar.short_description);
      printf("%-s %-s\n",  long_desc[lan], metvar.long_description);
      printf("Representation: %-s\n", metvar.nature);
      
      switch (metvar.code_nature)
        {
        case INTEGER:
        case REAL:
          printf("%-s %s\t%-s\t%-s\tMin: %-s\tMax: %-s\n", unites[lan], metvar.units, mag[lan], metvar.magnitude, metvar.min, metvar.max);
          break;
          
        case LOGICAL:
          printf("\tCode\t\tVal.\n");
          printf("\t----\t\t----------------\n");
          for (i=0; i < metvar.ncodes; i++)
            {
            printf("\t%-s\t\t%-s\n", metvar.logical_codes[i], metvar.logical_meanings[i]);
            }
          break;
          
        case CODE:
          printf("\tCode\t\tVal.\n");
          printf("\t----\t\t----------------\n");
          for (i=0; i < metvar.ncodes; i++)
            {
            printf("\t%-s\t\t%-s\n", metvar.codes[i], metvar.meanings[i]);
            }
          break;
        }
    break;
    }    

 }
 

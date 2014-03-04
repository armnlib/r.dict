#include "dict.h"

/* -------------------------------------------------------------------------- */
int changeEncoding(char *string, int encoding)
{
  char tmpString[256];
  int tmplenout, tmplenin;
  int i, i2;
  
  tmplenin = strlen(string);
  tmplenout = tmplenin;
  memset(tmpString, NULL, 256);
  switch (encoding)
    {
    case XML_CHAR_ENCODING_ASCII:
    i = 0;
    i2 = 0;
    while (i < tmplenout && i2 < 255)
      {
      switch ((unsigned char)string[i])
        {        
        case 0xC3:
        i++;
        switch ((unsigned char) string[i])
          {
          case 0x82:
          tmpString[i2] = 'A';
          break;
          
          case 0x89:
          tmpString[i2] = 'E';
          break;
          
          case 0xA0:
          case 0xA1:
          case 0xA2:
          tmpString[i2] = 'a';
          break;
          
          case 0xA7:
          tmpString[i2] = 'c';
          break;
          
          case 0xA8:
          case 0xA9:
          case 0xAA:
          case 0xAB:
          tmpString[i2] = 'e';
          break;
          
          case 0xEE:
          tmpString[i2] = 'i';
          break;
          
          case 0xB4:
          tmpString[i2] = 'o';
          break;
          
          case 0xF9:
          case 0xFB:
          tmpString[i2] = 'u';
          break;
          
          default:
          break;
          }
        break;
               
        default:
        tmpString[i2] = string[i];
        break;
        }
        i++;
        i2++;
      }
    strcpy(string, tmpString);
    break;
    
    case XML_CHAR_ENCODING_8859_1:
    tmplenout = tmplenin;
    UTF8Toisolat1(tmpString, &tmplenout, string, &tmplenin);
    strcpy(string, tmpString);
    break;
    
    case XML_CHAR_ENCODING_UTF8:
    break;
    }
}

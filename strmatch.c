#include "dict.h"

/* -------------------------------------------------------------------------- */
/*
 * Match string against the extended regular expression in
 * pattern, treating errors as no match.
 *
 * Return 1 for match, 0 for no match.
 */


int strmatch(const char *string, char *pattern)
  {
  int    status;
  regex_t    re;
  
  if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB|REG_ICASE) != 0) 
    {
    return(0);      /* Report error. */
    }
  status = regexec(&re, string, (size_t) 0, NULL, 0);
  regfree(&re);
  if (status != 0) 
    {
    return(0);      /* Report error. */
    }
  return(1);
  }


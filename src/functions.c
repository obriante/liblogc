
/*
 * liblogc - C Library for video and file log
 *
 * Copyright (C) 2012 - 2013, Orazio Briante, <orazio.briante@hotmail.it>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */  
  
#include "functions.h"
  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
  
#ifdef __cplusplus
extern "C"  {
  
#endif  /*  */
  
#ifdef _WIN32
  int asprintf(char **ret, const char *format, ...)  {
    va_list ap;
    *ret = NULL;                     /* Ensure value can be passed to free() */
    va_start(ap, format);
    int count = vsnprintf(NULL, 0, format, ap);
     va_end(ap);
     if (count >= 0)
        {
      char *buffer = malloc(count + 1);
       if (buffer == NULL)
        return -1;
       va_start(ap, format);
       count = vsnprintf(buffer, count + 1, format, ap);
       va_end(ap);
       if (count < 0)
          {
        free(buffer);
        return count;
        }
       *ret = buffer;
      }
     return count;
  }
   
#endif  /*  */
     

/*
 * ALLOC_STRING
 */ 
  char *alloc_string(const char *string)  {
    char *output = NULL;
     if (string)
      asprintf(&output, "%s", string);
     return output;
  }
   

/*
 *  INTERNAL_FUNCTION
 */ 
  char *time2String(const char *template)  {
    time_t now;
    struct tm *tmNow;
    int timeString_size = 26 * sizeof(char) * 8;
    char *timeString = (char *)malloc(timeString_size);
     time(&now);
    tmNow = localtime(&now);
     strftime(timeString, 80, template, tmNow);
    return (timeString);
  }
   
#ifdef __cplusplus
}


#endif  /*  */

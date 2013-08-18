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

#ifdef __cplusplus
extern "C"
  {
#endif

/*
 * ALLOC_STRING
 */

char *
alloc_string(const char* string)
{
  char *output = NULL;

  if (string)
    asprintf(&output, "%s", string);

  return output;
}

/*
 *  INTERNAL_FUNCTION
 */

char* time2String(){
time_t now;
struct tm tmNow;
int timeString_size=26*sizeof(char)*8;
char* timeString=(char*)malloc(timeString_size);
now = time(NULL );
localtime_r(&now, &tmNow);
strftime(timeString, timeString_size, "%Y-%m-%d %H:%M:%S", &tmNow);
return timeString;
}

#ifdef __cplusplus
}
#endif

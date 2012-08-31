/*
 * libtwitc - C Support Library for Twitter
 * Copyright (C) 2012 Orazio Briante orazio.briante@hotmail.it
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
#ifndef _LOGC_H_
#define _LOGC_H_

#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define debug(template, ...)    _debug(__FILE__, __FUNCTION__, __LINE__, template, ## __VA_ARGS__)
#else
#define debug(template, ...)
#endif

#define info(template, ...) _info(__FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)
#define warning(template, ...) _warning( __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)
#define error(template, ...) _error( __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)

static FILE *logFile = NULL;

extern void
removeFile(const char *);

extern long
checkFileSize(const char *);


extern void
initLog(const char *, const long);

extern void
_debug(const char *, const char *, int, const char *, ...);

extern void
_info(const char *, const char *, int, const char *, ...);

extern void
_warning(const char *, const char *, int, const char *, ...);

extern void
_error(const char *, const char *, int, const char *, ...);

extern void
uninitLog();

#endif /* _LOGC_H_ */

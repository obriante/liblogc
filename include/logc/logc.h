/*
 * liblogc - C Library for video and file log
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

#define DEFAULT_FILE_LOG	NULL
#define DEFAULT_VIDEO_LOG	stderr

#define DEFAULT_LOG_MODE	DISABLED_LOG
#define DEFAULT_DEBUG_MODE	DISABLED_LOG


#define debug(template, ...)	_debug(__FILE__, __FUNCTION__, __LINE__, template, ## __VA_ARGS__)
#define log(logType, template, ...) _log(logType, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)


typedef enum{
	DISABLED_LOG,
	VIDEO_LOG,
	FILE_LOG,
	FILE_VIDEO_LOG
}LogMode;


typedef enum
{
  ERROR,
  WARNING,
  INFO
}LogType;

extern void
removeFile(const char *);

extern long
checkFileSize(const char *);

extern void
initLog(LogMode, LogMode);

extern void
openLogFile(const char *, const long);


extern void openVideoLog(FILE *);

extern void
_debug(const char *, const char *, int, const char *, ...);

extern void
_log(const LogType, const char *, const char *, int, const char *, ...);


extern void
uninitLog();

#endif /* _LOGC_H_ */

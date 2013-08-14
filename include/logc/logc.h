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


/** \mainpage liblogc Documentation
 *
 * \section liblogc_functions Library Functions
 *
 * see logc.h and logc.c documentation.
 *
 * <H2>README</H2>
 *
 * @verbinclude README
 *
 */

/**
 * @page liblogc_readme README
 * @verbinclude README
 */

/**
 * @page liblogc_install INSTALL
 * @verbinclude INSTALL
 */

/**
 * @page liblogc_license COPYING
 * @verbinclude COPYING
 */

/**
 * @page liblogc_changelog ChangeLog
 * @verbinclude ChangeLog
 */

/**
 * \file logc.h
 * \brief The logc header
 *
**/


#ifndef _LOGC_H_
#define _LOGC_H_

#include <stdio.h>
#include <string.h>

#define DEFAULT_FILE_LOG	NULL /**< Default Log File Value */
#define DEFAULT_VIDEO_LOG	stderr /**< Default Video Log Value */

#define DEFAULT_LOG_MODE	DISABLED_LOG /**< Default Log Mode*/
#define DEFAULT_DEBUG_MODE	DISABLED_LOG /**< Default Debug Mode */

#define log(logType, template, ...) _log(logType, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)/**< To print a log output*/
#define debug(template, ...)	_log(DEBUG, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)/**< To print a log output*/

/** Define How to log information*/
typedef enum{
	DISABLED_LOG, /**< Log Disabled*/
	VIDEO_LOG, /**< Only Video Log */
	FILE_LOG, /**< Only File Log*/
	FILE_VIDEO_LOG /**< File and Video Log*/
}LogMode;

/** Is used into the log function to show the message relevance*/
typedef enum
{
  ERROR,
  WARNING,
  INFO,
  DEBUG
}LogType;

extern int
removeFile(const char *);

extern long
getFileSize(const char *);

extern int
checkFileSize(const char *, const long);

extern void
initLog(LogMode, LogMode);

extern int
openLogFile(const char *);

extern void openVideoLog(FILE *);

extern void
_log(const LogType, const char *, const char *, int, const char *, ...);


extern void
uninitLog();

#endif /* _LOGC_H_ */

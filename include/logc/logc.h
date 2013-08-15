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

#ifdef __GNUC__
	#ifndef attribute_deprecated
		#define attribute_deprecated __attribute__((deprecated))
	#endif
#endif

#define DEFAULT_FILE_LOG	NULL		 /**< Default Log File Value */
#define DEFAULT_VIDEO_LOG	stderr		 /**< Default Video Log Value */

#define DEFAULT_LOG_MODE	DISABLED_LOG /**< Default Log Mode*/
#define DEFAULT_DEBUG_MODE	DISABLED_LOG /**< Default Debug Mode */

#define DEFAULT_LOG_LEVEL	ALL_LEVEL	 /**< Default Log Mode*/

#define log(logType, template, ...) _log(logType, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)	/**< To print a generic log output*/

#define trace(template, ...)	_log(TRACE, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)	/**< To print a trace output*/
#define debug(template, ...)	_log(DEBUG, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)	/**< To print a debug output*/
#define info(template, ...)		_log(INFO, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)		/**< To print a info output*/
#define warning(template, ...)	_log(WARNING, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)	/**< To print a warning output*/
#define error(template, ...)	_log(ERROR, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)	/**< To print a error output*/
#define fatal(template, ...)	_log(FATAL, __FILE__,  __FUNCTION__, __LINE__, template, ## __VA_ARGS__)	/**< To print a fatal output*/

/** Define How to log information*/
typedef attribute_deprecated enum{
	DISABLED_LOG, /**< Log Disabled*/
	VIDEO_LOG, /**< Only Video Log */
	FILE_LOG, /**< Only File Log*/
	FILE_VIDEO_LOG /**< File and Video Log*/
}LogMode; // Deprecated

/** Is used into the log function to show the message relevance*/
typedef enum
{
	TRACE=1,
	DEBUG=2,
	INFO=3,
	WARNING=4,
	ERROR=5,
	FATAL=6
}LogType;

typedef enum
{
	OFF_LEVEL=0,
	ALL_LEVEL=1,
	DEBUG_LEVEL=2,
	INFO_LEVEL=3,
	WARNING_LEVEL=4,
	ERROR_LEVEL=5,
	FATAL_LEVEL=6
}LogLevel;

static FILE *file_stream=NULL;
static FILE *video_stream=NULL;

static LogLevel _video_log_level = DEFAULT_LOG_LEVEL;
static LogLevel _file_log_level = DEFAULT_LOG_LEVEL;


static LogMode _log_mode = DEFAULT_LOG_MODE;		// deprecated
static LogMode _debug_mode = DEFAULT_DEBUG_MODE;	// deprecated

extern int
removeFile(const char *);

extern long
getFileSize(const char *);

extern int
checkFileSize(const char *, const long);

extern void
initLog(LogMode, LogMode) attribute_deprecated;

extern void
initLogger(LogLevel, LogLevel);

extern int
openLogFile(const char *);

extern void openVideoLog(FILE *);

extern void
_log(const LogType, const char *, const char *, int, const char *, ...);


extern void
uninitLog();

#endif /* _LOGC_H_ */

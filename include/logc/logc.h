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

#include "logcver.h"
#include <logc/deprecated.h>

#include <stdio.h>

#define TRACE_TYPE_STRING		" TRACE   "
#define DEBUG_TYPE_STRING		" DEBUG   "
#define INFO_TYPE_STRING		" INFO    "
#define WARNING_TYPE_STRING 	" WARNING "
#define ERROR_TYPE_STRING		" ERROR   "
#define FATAL_TYPE_STRING		" FATAL   "


#ifdef __linux__

#define RESET   				"\033[0m"
#define BLACK   				"\033[30m"      /* Black */
#define RED     				"\033[31m"      /* Red */
#define GREEN   				"\033[32m"      /* Green */
#define YELLOW  				"\033[33m"      /* Yellow */
#define BLUE    				"\033[34m"      /* Blue */
#define MAGENTA 				"\033[35m"      /* Magenta */
#define CYAN    				"\033[36m"      /* Cyan */
#define WHITE   				"\033[37m"      /* White */

#define TRACE_TYPE_COLOR		CYAN
#define DEBUG_TYPE_COLOR		BLUE
#define INFO_TYPE_COLOR			GREEN
#define WARNING_TYPE_COLOR		YELLOW
#define ERROR_TYPE_COLOR		RED
#define FATAL_TYPE_COLOR		MAGENTA

#else

#define RESET   				""
#define BLACK   				""
#define RED     				""
#define GREEN   				""
#define YELLOW  				""
#define BLUE    				""
#define MAGENTA 				""
#define CYAN    				""
#define WHITE   				""

#define TRACE_TYPE_COLOR		CYAN
#define DEBUG_TYPE_COLOR		BLUE
#define INFO_TYPE_COLOR			GREEN
#define WARNING_TYPE_COLOR		YELLOW
#define ERROR_TYPE_COLOR		RED
#define FATAL_TYPE_COLOR		MAGENTA

#endif


#define DEFAULT_FILE_LOG		NULL					/**< Default Log File Value */
#define DEFAULT_VIDEO_LOG		stderr					/**< Default Video Log Value */

#define DEFAULT_VIDEO_LOG_LEVEL	ALL_LEVEL	 			/**< Default Log Mode */
#define DEFAULT_FILE_LOG_LEVEL	ALL_LEVEL	 			/**< Default Log Mode */

#define DEFAULT_TIME_FORMAT		"%Y-%m-%d %H:%M:%S" 	/**< Default Time Format */
#define DEFAULT_LOG_TEMPLATE	"%s %s [%s] %s:%i - %s"	/**< Default LOG Template */

#define log(logc, logType, message)	_log(logc, logType, __FILE__,  __FUNCTION__, __LINE__, message)	/**< To print a generic log output */

#define trace(logc, message)		_log(logc, TRACE, __FILE__,  __FUNCTION__, __LINE__, message)	/**< To print a trace output */
#define debug(logc, message)		_log(logc, DEBUG, __FILE__,  __FUNCTION__, __LINE__, message)	/**< To print a debug output */
#define info(logc, message)			_log(logc, INFO, __FILE__,  __FUNCTION__, __LINE__, message)		/**< To print a info output */
#define warning(logc, message)		_log(logc, WARNING, __FILE__,  __FUNCTION__, __LINE__, message)	/**< To print a warning output */
#define error(logc, message)		_log(logc, ERROR, __FILE__,  __FUNCTION__, __LINE__, message)	/**< To print a error output */
#define fatal(logc, message)		_log(logc, FATAL, __FILE__,  __FUNCTION__, __LINE__, message)	/**< To print a fatal output */

/** Is used into the log function to show the message relevance*/
typedef enum
{
	TRACE=0,
	DEBUG=5,
	INFO=10,
	WARNING=15,
	ERROR=20,
	FATAL=25
}LogType;

typedef enum
{
	OFF_LEVEL=0,
	ALL_LEVEL=5,
	DEBUG_LEVEL=10,
	INFO_LEVEL=15,
	WARNING_LEVEL=20,
	ERROR_LEVEL=25,
	FATAL_LEVEL=30
}LogLevel;

typedef struct{

	char * logger_name;
	char * log_filename;
	char * time_format_template;
	char * log_template;

	FILE *file_stream;
	FILE *video_stream;
	LogLevel video_log_level;
	LogLevel file_log_level;

	int colored;
}Logc_t;

extern Logc_t * init_logger(LogLevel, FILE *, LogLevel, const char *);
extern const int uninit_log(Logc_t *);

extern int set_logger_name(Logc_t *, const char *);
extern int set_log_file(Logc_t *, const char *);
extern int set_time_format_template(Logc_t *, const char *);
extern int set_log_template(Logc_t*, const char *);
extern void set_video_log_level(Logc_t*, const LogLevel);
extern void set_file_log_level(Logc_t*, const LogLevel);
extern void set_log_videostream(Logc_t*, FILE *);
extern void set_log_colored(Logc_t*, int);

extern const char * get_logger_name(Logc_t*);
extern const char * get_log_filename(Logc_t*);
extern const char* get_time_format_template(Logc_t*);
extern const char * get_log_template(Logc_t*);
extern const LogLevel get_video_log_level(Logc_t*);
extern const LogLevel get_file_log_level(Logc_t*);
extern FILE * get_log_videosteam(Logc_t*);
extern FILE * get_log_filestream(Logc_t*);
extern const int get_log_colored(Logc_t*);

extern int open_log_filestream(Logc_t *);
extern int close_log_filestream(Logc_t *);
extern int remove_log_file(Logc_t *);

#endif /* _LOGC_H_ */

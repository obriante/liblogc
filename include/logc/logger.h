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

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdio.h>

#define TRACE_TYPE_STRING		" TRACE   "
#define DEBUG_TYPE_STRING		" DEBUG   "
#define INFO_TYPE_STRING		" INFO    "
#define WARNING_TYPE_STRING      	" WARNING "
#define ERROR_TYPE_STRING		" ERROR   "
#define FATAL_TYPE_STRING		" FATAL   "

#ifdef __linux__

#define RESET   			"\033[0m"
#define BLACK   			"\033[30m"      /* Black */
#define RED     			"\033[31m"      /* Red */
#define GREEN   			"\033[32m"      /* Green */
#define YELLOW  			"\033[33m"      /* Yellow */
#define BLUE    			"\033[34m"      /* Blue */
#define MAGENTA 			"\033[35m"      /* Magenta */
#define CYAN    			"\033[36m"      /* Cyan */
#define WHITE   			"\033[37m"      /* White */

#define TRACE_TYPE_COLOR		CYAN
#define DEBUG_TYPE_COLOR		BLUE
#define INFO_TYPE_COLOR			GREEN
#define WARNING_TYPE_COLOR		YELLOW
#define ERROR_TYPE_COLOR		RED
#define FATAL_TYPE_COLOR		MAGENTA

#else

#define RESET   			""
#define BLACK   			""
#define RED     			""
#define GREEN   			""
#define YELLOW  			""
#define BLUE    			""
#define MAGENTA 			""
#define CYAN    			""
#define WHITE   			""

#define TRACE_TYPE_COLOR		CYAN
#define DEBUG_TYPE_COLOR		BLUE
#define INFO_TYPE_COLOR			GREEN
#define WARNING_TYPE_COLOR		YELLOW
#define ERROR_TYPE_COLOR		RED
#define FATAL_TYPE_COLOR		MAGENTA

#endif

#define DEFAULT_FILE_LOG		NULL					/**< Default Log File Value */
#define DEFAULT_VIDEO_LOG		stderr					/**< Default Video Log Value */

#define DEFAULT_VIDEO_LOG_LEVEL	        ALL_LEVEL	 			/**< Default Log Mode */
#define DEFAULT_FILE_LOG_LEVEL	        ALL_LEVEL	 			/**< Default Log Mode */

#define DEFAULT_TIME_FORMAT	        "%Y-%m-%d %H:%M:%S"

/** < Default Time Format
Code    Meaning

----    -------

%a      abbreviated weekday name

%A      full weekday name

%b      abbreviated month name

%B      full month name

%c      the standard date and time string

%d      day of the month, as a number (1-31)

%H      hour, 24 hour format (0-23)

%I      hour, 12 hour format (1-12)

%j      day of the year, as a number (1-366)

%m      month as a number (1-12). Note: some versions of Microsoft Visual C++ may use values that range from 0-11.

%M      minute as a number (0-59)

%p      locale's equivalent of AM or PM

%S      second as a number (0-59)

%U      week of the year, sunday as the first day

%w      weekday as a decimal (0-6, sunday=0)

%W      week of the year, monday as the first day

%x      standard date string

%X      standard time string

%y      year in decimal, without the century (0-99)

%Y      year in decimal, with the century

%Z      time zone name

%%      a percent sign*/

#define DEFAULT_LOG_TEMPLATE	        "%s %s [%s] %s:%i - %s"	/**< Default LOG Template */

#define logger_print(logger, logType, message) print(logger, logType, message, __FILE__,  __FUNCTION__, __LINE__) /**< To print a generic log output */

/** Is used into the log function to show the message relevance*/
typedef enum
{
  TRACE = 0, DEBUG = 5, INFO = 10, WARNING = 15, ERROR = 20, FATAL = 25
} log_type_t;

typedef enum
{
  OFF_LEVEL = 0,
  ALL_LEVEL = 5,
  DEBUG_LEVEL = 10,
  INFO_LEVEL = 15,
  WARNING_LEVEL = 20,
  ERROR_LEVEL = 25,
  FATAL_LEVEL = 30
} log_level_t;

typedef struct
{

  char * log_filename;
  char * log_template;
  char * time_format;

  FILE *file_stream;
  FILE *video_stream;
  log_level_t video_logger_level;
  log_level_t file_logger_level;

  int colored;
} logger_t;

extern logger_t *
init_logger(log_level_t, FILE *, log_level_t, const char *);

extern const int
uninit_logger(logger_t *);

extern int
set_logger_file(logger_t *, const char *);

extern int
set_logger_template(logger_t*, const char *);

extern int
set_time_format(logger_t *, const char *);

extern void
set_video_logger_level(logger_t*, const log_level_t);

extern void
set_file_logger_level(logger_t*, const log_level_t);

extern void
set_logger_videostream(logger_t*, FILE *);

extern void
set_logger_colored(logger_t*, int);

extern void
set_logger_filename(logger_t*, const char *);

extern const char *
get_logger_filename(logger_t*);

extern const char *
get_logger_template(logger_t*);

extern const char*
get_time_format(logger_t *);

extern const log_level_t
get_video_logger_level(logger_t*);

extern const log_level_t
get_file_logger_level(logger_t*);

extern FILE *
get_logger_videosteam(logger_t*);

extern FILE *
get_logger_filestream(logger_t*);

extern const int
get_logger_colored(logger_t*);

extern int
open_logger_filestream(logger_t *);

extern int
close_logger_filestream(logger_t *);

extern int
remove_logger_file(logger_t *);

extern void
print(logger_t *, const log_type_t, const char *, const char *, const char *,
    int);

#endif /* _LOGGER_H_ */

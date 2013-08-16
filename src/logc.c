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

/**
 * \file logc.c
 * \brief The logc functions
 *
 **/


#include <logc/logc.h>

#include <stdlib.h>
#include <stdarg.h>
#include <time.h>


#ifdef __cplusplus
extern "C"
{
#endif

char* _time2String(){
	time_t now;
	struct tm tmNow;
	int timeString_size=26*sizeof(char)*8;
	char* timeString=(char*)malloc(timeString_size);
	now = time(NULL );
	localtime_r(&now, &tmNow);
	strftime(timeString, timeString_size, "%Y-%m-%d %H:%M:%S", &tmNow);
	return timeString;
}

void _printMessage(FILE *stream, const char *template, va_list argp, const char *string)
{
	fprintf(stream, "%s",string);
	vfprintf(stream, template, argp);
	fprintf(stream, "\n");
	fflush(stream);
}

void
_log(Logc_t *logc, const LogType logType, const char *file, const char *function, int line,
		const char *template, ...)
{

	va_list argp;
	va_start(argp, template);

	char *file_string=NULL;
	char *video_string=NULL;
	char *string_format="%s %s [%s] %s:%i - ";

	char *timeString=_time2String();

	char*  _template=NULL;
	asprintf(&_template, "%s", template);

	char* type=NULL;
	char* color=RESET;

	switch (logType)
	{
	case TRACE:
		type=TRACE_TYPE_STRING;
		break;

	case DEBUG:
		type=DEBUG_TYPE_STRING;
		break;

	case INFO:
		type=INFO_TYPE_STRING;
		break;

	case WARNING:
		type=WARNING_TYPE_STRING;
		break;

	case ERROR:
		type=ERROR_TYPE_STRING;
		break;

	case FATAL:
		type=FATAL_TYPE_STRING;
		break;

	default:
		type=TRACE_TYPE_STRING;
		break;
	}

#ifdef __linux__

	switch (logType)
	{
	case TRACE:
		color=TRACE_TYPE_COLOR;
		break;

	case DEBUG:
		color=DEBUG_TYPE_COLOR;
		break;

	case INFO:
		color=INFO_TYPE_COLOR;
		break;

	case WARNING:
		color=WARNING_TYPE_COLOR;
		break;

	case ERROR:
		color=ERROR_TYPE_COLOR;
		break;

	case FATAL:
		color=FATAL_TYPE_COLOR;
		break;

	default:
		color=TRACE_TYPE_COLOR;
		break;
	}

	char* typeColor=NULL;
	asprintf(&typeColor, "%s%s%s",color,type,RESET);
	asprintf(&video_string, string_format, timeString, typeColor, function, file, line);
	asprintf(&file_string,  string_format, timeString, type, function, file, line);
#else
	asprintf(&video_string, string_format, timeString, type, function, file, line);
	asprintf(&file_string,  string_format, timeString, type, function, file, line);
#endif

	if (logc->video_stream!=NULL)
		switch (logc->video_log_level)
		{
		case OFF_LEVEL:
			break;

		case ALL_LEVEL:
			_printMessage(logc->video_stream,template, argp, video_string);
			break;

		case DEBUG_LEVEL:
			if(logType!=TRACE )
			{
				_printMessage(logc->video_stream,template, argp, video_string);
			}
			break;

		case INFO_LEVEL:
			if(logType!=TRACE && logType!=DEBUG)
			{
				_printMessage(logc->video_stream,template, argp, video_string);
			}
			break;

		case WARNING_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO)
			{
				_printMessage(logc->video_stream,template, argp, video_string);
			}
			break;

		case ERROR_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO && logType!=WARNING)
			{
				_printMessage(logc->video_stream,template, argp, video_string);
			}
			break;

		case FATAL_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO && logType!=WARNING && logType!=ERROR)
			{
				_printMessage(logc->video_stream,template, argp, video_string);
			}
			break;

		default:
			_printMessage(logc->video_stream,template, argp, video_string);
			break;
		}

	if (logc->file_stream!=NULL)
		switch (logc->file_log_level)
		{
		case OFF_LEVEL:
			break;

		case ALL_LEVEL:
			_printMessage(logc->file_stream,template, argp, file_string);
			break;

		case DEBUG_LEVEL:
			if(logType!=TRACE )
			{
				_printMessage(logc->file_stream,template, argp, file_string);
			}
			break;

		case INFO_LEVEL:
			if(logType!=TRACE && logType!=DEBUG)
			{
				_printMessage(logc->file_stream,template, argp, file_string);
			}
			break;

		case WARNING_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO)
			{
				_printMessage(logc->file_stream,template, argp, file_string);
			}
			break;

		case ERROR_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO && logType!=WARNING)
			{
				_printMessage(logc->file_stream,template, argp, file_string);
			}
			break;

		case FATAL_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO && logType!=WARNING && logType!=ERROR)
			{
				_printMessage(logc->file_stream,template, argp, file_string);
			}
			break;

		default:
			_printMessage(logc->file_stream,template, argp, file_string);
			break;
		}

	va_end(argp);
}


/**
 * Delete a File
 * @param fileName The name of the file to delete
 *
 * @return 0 for operation success, 1 for operation failure
 * */
int
remove_log_file(Logc_t *logc)
{
	if (remove(logc->log_file_name))
	{
		log(logc, ERROR,"Can't delete: %s", logc->log_file_name);
	}
	else
	{
		log(logc, TRACE,"%s successfully deleted.", logc->log_file_name);
		logc->file_stream=NULL;
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;

}

/**
 * Check File Dimension
 *
 * @param fileName The name of the file to check
 * @return The dimension of the file (long value)
 */

long
get_file_size(Logc_t *logc)
{
	if (logc->log_file_name)
	{

		FILE *fp = fopen(logc->log_file_name, "r");

		if (fp)
		{
			fseek(fp, 0L, SEEK_END);
			long sz = ftell(fp);
			rewind(fp);

			fclose(fp);

			log(logc, TRACE,"%s dimension: %d", logc->log_file_name, sz);

			return sz;
		}

	}

	return -1;
}

Logc_t* init_logger(LogLevel video_log_level, LogLevel file_log_level, const char *log_file_name)
{

	Logc_t *logc=(Logc_t *)malloc(sizeof(Logc_t)*8);

	logc->video_stream = DEFAULT_VIDEO_LOG;
	logc->file_stream = DEFAULT_FILE_LOG;

	if(log_file_name)
		asprintf(&logc->log_file_name,"%s",log_file_name);

	logc->video_log_level=video_log_level;
	logc->file_log_level=file_log_level;


	return logc;
}


/**
 * Open a Log File called by name.
 *
 * @param fileName The name of the Log file to open.
 *
 * @return 0 for operation success, 1 for operation failure
 */
int
open_log_file(Logc_t *logc, const long size)
{

	if (logc->log_file_name)
	{

		long real_size=get_file_size(logc);
		if (real_size<size || size==-1)
		{

			trace(logc, "Try Opening %s in append mode", logc->log_file_name);
			logc->file_stream = fopen(logc->log_file_name, "a");

		}
		else
		{
			trace(logc, "Try Opening %s in write mode", logc->log_file_name);
			logc->file_stream = fopen(logc->log_file_name, "w+");

		}

		if (logc->file_stream){

			return EXIT_SUCCESS;
		}

	}

	trace(logc, "Failure Opening\t%s", logc->log_file_name);
	return EXIT_FAILURE;
}

/**
 * Change the Video stream
 *
 * @param video the new stream
 */
void set_log_video(Logc_t *logc, FILE *video)
{
	logc-> video_stream=video;
}

/**
 * Uninitialize the Logging Process
 */
int
uninitLog(Logc_t *logc)
{

	if (logc->file_stream)
	{
		if(fclose(logc->file_stream)==EOF)
			return EXIT_FAILURE;

		logc->file_stream = NULL;

	}

	if(logc->log_file_name)
	{
		trace (logc, "%s successfully closed", logc->log_file_name);
		free(logc->log_file_name);
		logc->log_file_name=NULL;
	}

	logc->video_stream = NULL;

	free(logc);
	logc=NULL;


	return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif

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


#define TRACE_TYPE_STRING		" TRACE   "
#define DEBUG_TYPE_STRING		" DEBUG   "
#define INFO_TYPE_STRING		" INFO    "
#define WARNING_TYPE_STRING 	" WARNING "
#define ERROR_TYPE_STRING		" ERROR   "
#define FATAL_TYPE_STRING		" FATAL   "


#ifdef __linux__

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#define TRACE_TYPE_COLOR		CYAN
#define DEBUG_TYPE_COLOR		BLUE
#define INFO_TYPE_COLOR			GREEN
#define WARNING_TYPE_COLOR		YELLOW
#define ERROR_TYPE_COLOR		RED
#define FATAL_TYPE_COLOR		MAGENTA

#endif

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * Delete a File
 * @param fileName The name of the file to delete
 *
 * @return 0 for operation success, 1 for operation failure
 * */
int
removeFile(const char *fileName)
{
	if (remove(fileName)){
		log(ERROR,"Can't delete: %s", fileName);
		return EXIT_SUCCESS;
	}
	else
		log(TRACE,"%s successfully deleted.", fileName);


	return EXIT_FAILURE;

}

/**
 * Check File Dimension
 *
 * @param fileName The name of the file to check
 * @return The dimension of the file (long value)
 */
long
getFileSize(const char * fileName)
{

	if (fileName)
	{

		FILE *fp = fopen(fileName, "r");

		if (fp)
		{
			fseek(fp, 0L, SEEK_END);
			long sz = ftell(fp);
			rewind(fp);

			fclose(fp);

			log(TRACE,"File: \"%s\", Dimension: %d", fileName, sz);

			return sz;
		}

	}

	log(ERROR,"File: \"%s\", Dimension Unknown",fileName);

	return -1;
}

/**
 * Erase the File (indicated  through fileName) if the file dimension are more or equal of the declared max size .
 *
 * @param fileName The name of the file that must be checked
 * @param maxSize The max size of file
 *
 * @return 0 for operation success, 1 for operation failure
 */
int
checkFileSize(const char * fileName, const long maxSize)
{
	if (fileName)
	{
		long size = getFileSize(fileName);

		trace ("fileName: %s, size:\t%d", fileName, size);

		if (size >= maxSize)
			return removeFile(fileName);

	}

	return EXIT_FAILURE;
}

/**
 * Initialize the Logging process. The video stream and the file stream are set to the default value.
 *
 * @param log_mode the LogMode to use for log message
 * @param debug_mode the LogMode to use for debug message
 */
void initLog(LogMode log_mode, LogMode debug_mode)
{
	video_stream = DEFAULT_VIDEO_LOG;
	file_stream = DEFAULT_FILE_LOG;

	_log_mode=log_mode;
	_debug_mode=debug_mode;

	_video_log_level=OFF_LEVEL;
	_file_log_level=OFF_LEVEL;


}

void initLogger(LogLevel video_log_level, LogLevel file_log_level)
{
	video_stream = DEFAULT_VIDEO_LOG;
	file_stream = DEFAULT_FILE_LOG;

	_video_log_level=video_log_level;
	_file_log_level=file_log_level;

}

/**
 * Open a Log File called by name.
 *
 * @param fileName The name of the Log file to open.
 *
 * @return 0 for operation success, 1 for operation failure
 */
int
openLogFile(const char * fileName)
{

	if (fileName)
	{
		trace("Opening\t%s", fileName);

		file_stream = fopen(fileName, "a");

		if (file_stream){

			return EXIT_SUCCESS;
		}

	}

	trace("Failure Opening\t%s", fileName);
	return EXIT_FAILURE;
}

/**
 * Change the Video stream
 *
 * @param video the new stream
 */
void openVideoLog(FILE *video)
{
	video_stream=video;
}

/**
 * Uninitialize the Logging Process
 */
void
uninitLog()
{
	if (file_stream)
	{
		trace ("Closing Log File");
		fclose(file_stream);
	}

	video_stream = DEFAULT_VIDEO_LOG;
	file_stream = DEFAULT_FILE_LOG;

	_log_mode=DISABLED_LOG;
	_debug_mode=DISABLED_LOG;

}

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

void _printMessage(FILE *stream, const char *template, const va_list argp, const char *string)
{
	fprintf(stream, "%s",string);
	vfprintf(stream, template, argp);
	fprintf(stream, "\n");
	fflush(stream);
}



void
_log(const LogType logType, const char *file, const char *function, int line,
		const char *template, ...)
{

	char *file_string=NULL;
	char *video_string=NULL;
	char *string_format="%s %s [%s] %s:%i - ";

	char *timeString=_time2String();

	char*  _template=NULL;
	asprintf(&_template, "%s", template);

	char* type=NULL;
	char* color=RESET;

	va_list argp;
	va_start(argp, template);

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

	if (video_stream!=NULL)
		switch (_video_log_level)
		{
		case OFF_LEVEL:
			break;

		case ALL_LEVEL:
			_printMessage(video_stream,template, argp, video_string);
			break;

		case DEBUG_LEVEL:
			if(logType!=TRACE )
			{
				_printMessage(video_stream,template, argp, video_string);
			}
			break;

		case INFO_LEVEL:
			if(logType!=TRACE && logType!=DEBUG)
			{
				_printMessage(video_stream,template, argp, video_string);
			}
			break;

		case WARNING_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO)
			{
				_printMessage(video_stream,template, argp, video_string);
			}
			break;

		case ERROR_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO && logType!=WARNING)
			{
				_printMessage(video_stream,template, argp, video_string);
			}
			break;

		case FATAL_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO && logType!=WARNING && logType!=ERROR)
			{
				_printMessage(video_stream,template, argp, video_string);
			}
			break;

		default:
			_printMessage(video_stream,template, argp, video_string);
			break;
		}

	if (file_stream!=NULL)
		switch (_file_log_level)
		{
		case OFF_LEVEL:
			break;

		case ALL_LEVEL:
			_printMessage(file_stream,template, argp, file_string);
			break;

		case DEBUG_LEVEL:
			if(logType!=TRACE )
			{
				_printMessage(file_stream,template, argp, file_string);
			}
			break;

		case INFO_LEVEL:
			if(logType!=TRACE && logType!=DEBUG)
			{
				_printMessage(file_stream,template, argp, file_string);
			}
			break;

		case WARNING_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO)
			{
				_printMessage(file_stream,template, argp, file_string);
			}
			break;

		case ERROR_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO && logType!=WARNING)
			{
				_printMessage(file_stream,template, argp, file_string);
			}
			break;

		case FATAL_LEVEL:
			if(logType!=TRACE && logType!=DEBUG && logType!=INFO && logType!=WARNING && logType!=ERROR)
			{
				_printMessage(file_stream,template, argp, file_string);
			}
			break;

		default:
			_printMessage(file_stream,template, argp, file_string);
			break;
		}


	/*	Deprecated Section*/
	if(_log_mode!= DISABLED_LOG)
	{

		if(video_stream && _log_mode!=FILE_LOG)
		{

			fprintf(video_stream, "%s",video_string);
			vfprintf(video_stream, template, argp);
			fprintf(video_stream, "\n");
			fflush(video_stream);
		}

		if (file_stream && _log_mode!=VIDEO_LOG)
		{

			fprintf(file_stream, "%s", file_string);
			vfprintf(file_stream, template, argp);
			fprintf(file_stream, "\n");
			fflush(file_stream);
		}
	}
	/*	Deprecated Section*/

	va_end(argp);
}

#ifdef __cplusplus
}
#endif

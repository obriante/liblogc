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

#endif


static FILE *file_stream=NULL;
static FILE *video_stream=NULL;
static LogMode logMode = DEFAULT_LOG_MODE;
static LogMode debugMode = DEFAULT_DEBUG_MODE;

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
		log(INFO,"Can't delete: %s", fileName);
		return EXIT_SUCCESS;
	}
	else
		log(ERROR,"%s successfully deleted.", fileName);


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

			log(INFO,"File: \"%s\", Dimension: %d", fileName, sz);

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

		debug ("fileName: %s, size:\t%d", fileName, size);

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

	logMode=log_mode;
	debugMode=debug_mode;
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
		debug ("fileName:\t%s", fileName);

		file_stream = fopen(fileName, "a");

		if (file_stream){

			// debug ("Opened \"%s\" in Append Mode", fileName);
			return EXIT_SUCCESS;
		}

	}

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
		debug ("Closing Log File");
		fclose(file_stream);
	}

	video_stream = DEFAULT_VIDEO_LOG;
	file_stream = DEFAULT_FILE_LOG;

	logMode=DISABLED_LOG;
	debugMode=DISABLED_LOG;

}

void
_logWrite(FILE * output, const char *type, const char *file,
		const char *function, int line, const char *template, va_list argp)
{
	time_t now;
	struct tm tmNow;
	char timeString[26];

	now = time(NULL );
	localtime_r(&now, &tmNow);
	strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &tmNow);

	fprintf(output, "%s - %s - (%s - %s:%i): ", type, timeString, function, file,
				line);
	vfprintf(output, template, argp);
	fprintf(output, "\n");
	fflush(output);
}

void
_logWriteColor(FILE * output, const char *type, const char* color, const char *file,
		const char *function, int line, const char *template, va_list argp)
{
	time_t now;
	struct tm tmNow;
	char timeString[26];

	now = time(NULL );
	localtime_r(&now, &tmNow);
	strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &tmNow);

	fprintf(output, "%s %s"RESET" - %s - (%s - %s:%i): ", color, type, timeString, function, file,
			line);

	vfprintf(output, template, argp);
	fprintf(output, "\n");
	fflush(output);
}

void
_log(const LogType logType, const char *file, const char *function, int line,
		const char *template, ...)
{

	char*  _template=NULL;
	asprintf(&_template, "%s", template);

	char* type=NULL;
	char* color=RESET;

	va_list argp;
	va_start(argp, template);

	if (logType == ERROR)
	{
		type="[ERROR  ]";
		color=RED;
	}
	else if (logType == WARNING)
	{
		type="[WARNING]";
		color=YELLOW;
	}
	else if (logType == INFO)
	{
		type="[INFO   ]";
		color=GREEN;
	}
	else
	{
		type="[DEBUG  ]";
		color=CYAN;
	}

	if(logMode!= DISABLED_LOG)
	{
		if(video_stream && logMode!=FILE_LOG)
#ifdef __linux__
		_logWriteColor(video_stream, type, color, file, function, line, _template, argp);
#else
		_logWrite(video_stream, type, file, function, line, _template, argp);
#endif


		if (file_stream && logMode!=VIDEO_LOG)
			_logWrite(file_stream, type, file, function, line, _template, argp);
	}

	va_end(argp);
}

#ifdef __cplusplus
}
#endif

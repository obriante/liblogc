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
#include <logc/logc.h>

#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

static FILE *file_stream=NULL;
static FILE *video_stream=NULL;
static LogMode logMode = DEFAULT_LOG_MODE;
static LogMode debugMode = DEFAULT_DEBUG_MODE;

#ifdef __cplusplus
extern "C"
{
#endif

void
removeFile(const char * fileName)
{
	if (remove(fileName))
		log(INFO,"Can't delete: %s", fileName);
	else
		log(ERROR,"%s successfully deleted.", fileName);
}

long
checkFileSize(const char * fileName)
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


void
checkLogFileDimension(const char * fileName, const long maxSize)
{
	if (fileName)
	{
		long size = checkFileSize(fileName);

		debug ("fileName: %s, size:\t%d", fileName, size);

		if (size >= maxSize)
			removeFile(fileName);

	}
}

void initLog(LogMode log_mode, LogMode debug_mode)
{
	video_stream = DEFAULT_VIDEO_LOG;
	file_stream = DEFAULT_FILE_LOG;

	logMode=log_mode;
	debugMode=debug_mode;
}

void
openLogFile(const char * fileName, const long maxbyteSize)
{

	if (fileName)
	{

		if(maxbyteSize>=0)
			checkLogFileDimension(fileName, maxbyteSize);

		debug ("fileName:\t%s", fileName);

		file_stream = fopen(fileName, "a");

		if (file_stream)
			debug ("Opened \"%s\" in Append Mode", fileName);

	}
}

void openVideoLog(FILE *video)
{
video_stream=video;
}

void
uninitLog()
{
	if (file_stream)
	{
		debug ("Closing logFile");
		fclose(file_stream);
		file_stream = NULL;
	}

	logMode=DISABLED_LOG;
	debugMode=DISABLED_LOG;

}

static void
_logWrite(FILE * output, const char *type, const char *file,
		const char *function, int line, const char *template, va_list argp)
{
	time_t now;
	struct tm tmNow;
	char timeString[26];

	now = time(NULL );
	localtime_r(&now, &tmNow);
	strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &tmNow);

	fprintf(output, "%s %s (%s - %s:%i): ", timeString, type, function, file,
			line);
	vfprintf(output, template, argp);
	fprintf(output, "\n");
	fflush(output);
}

void
_log(const LogType logType, const char *file, const char *function, int line,
		const char *template, ...)
{


	char* type=NULL;

	va_list argp;
	va_start(argp, template);

	if (logType == ERROR)
		type="ERROR  ";
	else if (logType == WARNING)
		type="WARNING";
	else
		type="INFO   ";


	if(video_stream && logMode!=DISABLED_LOG)
		_logWrite(video_stream, type, file, function, line, template, argp);

	if (file_stream && (logMode==FILE_LOG || logMode==FILE_VIDEO_LOG))
		_logWrite(file_stream, type, file, function, line, template, argp);

	va_end(argp);
}

void
_debug(const char *file, const char *function, int line, const char *template,
		...)
{
	va_list argp;
	va_start(argp, template);

	if(video_stream && debugMode!=DISABLED_LOG)
		_logWrite(video_stream, "DEBUG  ", file, function, line, template, argp);

	if (file_stream && (debugMode==FILE_LOG || debugMode==FILE_VIDEO_LOG))
		_logWrite(file_stream, "DEBUG  ", file, function, line, template, argp);


	va_end(argp);
}


#ifdef __cplusplus
}
#endif

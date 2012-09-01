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


static FILE *logFile = NULL;
static LogMode logMode=LOG_NONE;
static LogMode debugMode=LOG_NONE;

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

			log(INFO,"File: \"%s\", Dimension: %l", fileName, sz);

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
		debug ("fileName:\t%s", fileName);

		long size = checkFileSize(fileName);
		debug ("size:\t%s", fileName);

		if (size >= maxSize)
			removeFile(fileName);

	}
}

void initLog(LogMode log_mode, LogMode debug_mode){

	logMode=log_mode;
	debugMode=debug_mode;
}

void
initLogFile(const char * fileName, const long maxbyteSize)
{

	if (fileName)
	{

		if(maxbyteSize)
			checkLogFileDimension(fileName, maxbyteSize);

		debug ("fileName:\t%s", fileName);

		logFile = fopen(fileName, "a");

		if (logFile)
			debug ("Opened \"%s\" in Append Mode", fileName);

	}
}

void
uninitLog()
{
	if (logFile)
	{
		debug ("Closing logFile");
		fclose(logFile);
		logFile = NULL;
	}

	logMode=LOG_NONE;
		debugMode=LOG_NONE;

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


	if(logMode!=LOG_NONE)
		_logWrite(stderr, type, file, function, line, template, argp);

	if (logFile && (logMode==LOG_FILE || logMode==LOG_FILE_VIDEO))
		_logWrite(stderr, type, file, function, line, template, argp);

	va_end(argp);
}

void
_debug(const char *file, const char *function, int line, const char *template,
		...)
{
	va_list argp;
	va_start(argp, template);

	if(logMode!=LOG_NONE)
		_logWrite(stderr, "DEBUG  ", file, function, line, template, argp);

	if (logFile && (logMode==LOG_FILE || logMode==LOG_FILE_VIDEO))
		_logWrite(stderr, "DEBUG  ", file, function, line, template, argp);


	va_end(argp);
}


#ifdef __cplusplus
}
#endif

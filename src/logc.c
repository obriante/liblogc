/* 
 * liblogger - C Library for video and file log
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
 * \file logger.c
 * \brief The logger functions
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

/*
 * 	FREE
 */

/*void free_logger_name(Logc_t *logger) {

	if (logger->logger_name) {
		free(logger->logger_name);
		logger->logger_name = NULL;
	}
}

void free_log_filename(Logc_t *logger) {

	if (logger->log_filename) {
		free(logger->log_filename);
		logger->log_filename = NULL;
	}
}

void free_time_format_template(Logc_t *logger) {
	if (logger->time_format_template) {
		free(logger->time_format_template);
		logger->time_format_template = NULL;
	}
}

void free_log_template(Logc_t *logger) {
	if (logger->log_template) {
		free(logger->log_template);
		logger->log_template = NULL;
	}
}*/

/*
 * ALLOC_STRING
 */

char *
alloc_string(const char* string) {
	char *output = NULL;

	if (string)
		asprintf(&output, "%s", string);

	return output;
}

/*
 *  INTERNAL_FUNCTION
 */

char* _time2String(Logc_t *logger) {
	time_t now;
	struct tm tmNow;
	int timeString_size = 26 * sizeof(char) * 8;
	char* timeString = (char*) malloc(timeString_size);
	now = time(NULL);
	localtime_r(&now, &tmNow);
	strftime(timeString, timeString_size, "%Y-%m-%d %H:%M:%S", &tmNow);
	return timeString;
}

void _printMessage(Logc_t *logger, LogType logType, const char *string) {

	if (!logger->colored)
	{
		char* color = RESET;


		switch (logType)
		{
		case TRACE:
			color	= TRACE_TYPE_COLOR;
			break;

		case DEBUG:
			color 	= DEBUG_TYPE_COLOR;
			break;

		case INFO:
			color	= INFO_TYPE_COLOR;
			break;

		case WARNING:
			color	= WARNING_TYPE_COLOR;
			break;

		case ERROR:
			color	= ERROR_TYPE_COLOR;
			break;

		case FATAL:
			color	= FATAL_TYPE_COLOR;
			break;

		default:
			color	= TRACE_TYPE_COLOR;
			break;
		}
		fprintf(logger->video_stream, "%s%s%s\n", color, string, RESET);
	}
	else
		fprintf(logger->video_stream, "%s\n", string);

	fprintf(logger->file_stream, "%s\n", string);

}

void _log(Logc_t *logger, const LogType logType, const char *file, const char *function, int line, const char *message)
{
	char *output_string = NULL;

	char *string_format = DEFAULT_LOG_TEMPLATE;

	char *timeString = _time2String(logger);

	char* type = NULL;


	switch (logType) {
	case TRACE:
		type = TRACE_TYPE_STRING;
		break;

	case DEBUG:
		type = DEBUG_TYPE_STRING;
		break;

	case INFO:
		type = INFO_TYPE_STRING;
		break;

	case WARNING:
		type = WARNING_TYPE_STRING;
		break;

	case ERROR:
		type = ERROR_TYPE_STRING;
		break;

	case FATAL:
		type = FATAL_TYPE_STRING;
		break;

	default:
		type = TRACE_TYPE_STRING;
		break;
	}

	asprintf(&output_string, string_format, timeString, type, function, file, line, message);

	if (logger->file_stream != NULL)
		switch (logger->file_log_level) {
		case OFF_LEVEL:
			break;

		case ALL_LEVEL:
			_printMessage(logger, logType, output_string);
			break;

		case DEBUG_LEVEL:
			if (logType != TRACE) {
				_printMessage(logger, logType, output_string);
			}
			break;

		case INFO_LEVEL:
			if (logType != TRACE && logType != DEBUG) {
				_printMessage(logger, logType, output_string);
			}
			break;

		case WARNING_LEVEL:
			if (logType != TRACE && logType != DEBUG && logType != INFO) {
				_printMessage(logger, logType, output_string);
			}
			break;

		case ERROR_LEVEL:
			if (logType != TRACE && logType != DEBUG && logType != INFO
					&& logType != WARNING) {
				_printMessage(logger, logType, output_string);
			}
			break;

		case FATAL_LEVEL:
			if (logType != TRACE && logType != DEBUG && logType != INFO
					&& logType != WARNING && logType != ERROR) {
				_printMessage(logger, logType, output_string);
			}
			break;

		default:
			_printMessage(logger, logType, output_string);
			break;
		}
}

/*
 * GETTERS
 */

const char *
get_logger_name(Logc_t *logger)
{
	return logger->logger_name;
}


const char *
get_log_filename(Logc_t *logger) {
	return logger->log_filename;
}

const char*
get_time_format_template(Logc_t *logger) {
	return logger->time_format_template;
}

const char *
get_log_template(Logc_t *logger) {
	return logger->log_template;
}

const LogLevel get_video_log_level(Logc_t *logger) {
	return logger->video_log_level;
}

const LogLevel get_file_log_level(Logc_t *logger) {
	return logger->file_log_level;
}

FILE *
get_log_videosteam(Logc_t *logger) {
	return logger->file_stream;
}

FILE *
get_log_filestream(Logc_t *logger) {
	return logger->file_stream;
}

const int get_log_colored(Logc_t *logger){
	return logger->colored;
}


/*
 *  SETTERS
 */
int set_logger_name(Logc_t *logger, const char *name)
{
	if(logger)
	{
		if (logger->logger_name)
		{
			free(logger->logger_name);
			logger->logger_name = NULL;
		}
		logger->logger_name=alloc_string(name);

		if(logger->logger_name)
			return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int set_log_file(Logc_t *logger, const char *filename) {

	if (logger && filename)
		if (!close_log_filestream(logger)) {
			if (logger->log_filename)
			{
				free(logger->log_filename);
				logger->log_filename = NULL;
			}
			logger->log_filename = alloc_string(filename);
			if (logger->log_filename)
				return open_log_filestream(logger);

		}

	return EXIT_FAILURE;
}

int set_time_format_template(Logc_t *logger, const char *template) {
	if (logger && template) {
		if (logger->time_format_template)
		{
			free(logger->time_format_template);
			logger->time_format_template = NULL;
		}
		logger->time_format_template = alloc_string(template);

		if (logger->time_format_template)
			return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int set_log_template(Logc_t *logger, const char *template) {

	if (logger && template) {
		if (logger->log_template)
		{
			free(logger->log_template);
			logger->log_template = NULL;
		}
		logger->log_template = alloc_string(template);

		if (logger->log_template)
			return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

void set_video_log_level(Logc_t *logger, const LogLevel log_level) {
	if (logger)
		logger->video_log_level = log_level;
}

void set_file_log_level(Logc_t *logger, const LogLevel log_level) {
	if (logger)
		logger->file_log_level = log_level;
}

void set_log_videostream(Logc_t *logger, FILE *video_stream) {
	if (logger)
		logger->video_stream = video_stream;
}

void set_log_colored(Logc_t *logger, int color)
{
	if (color<1)
		logger->colored=0;
	else
		logger->colored=1;
}

/**
 * Open a Log File called by name.
 *
 * @param fileName The name of the Log file to open.
 *
 * @return 0 for operation success, 1 for operation failure
 */

int open_log_filestream(Logc_t *logger) {
	if (logger)
		if (logger->log_filename) {

			char *message=NULL;

			asprintf(&message,"Try Opening %s in append mode", logger->log_filename);
			trace(logger, message);
			free(message);
			message=NULL;

			logger->file_stream = fopen(logger->log_filename, "a+");

			if (logger->file_stream) {

				return EXIT_SUCCESS;
			}

			asprintf(&message,"Failure Opening\t%s", logger->log_filename);
			trace(logger, message);
			free(message);
			message=NULL;

		}

	return EXIT_FAILURE;
}

int close_log_filestream(Logc_t *logger) {

	if (logger->file_stream)
	{
		if (fclose(logger->file_stream) == EOF)
			return EXIT_FAILURE;

		logger->file_stream = NULL;
	}

	if (logger->log_filename){

		char *message=NULL;
		asprintf(&message,"%s successfully closed", logger->log_filename);
		trace(logger, message);
		free(message);
		message=NULL;
	}

	if (logger->log_filename)
	{
		free(logger->log_filename);
		logger->log_filename = NULL;
	}

	if (logger->log_filename == NULL)
		return EXIT_SUCCESS;

	return EXIT_FAILURE;
}

/**
 * Delete a File
 * @param fileName The name of the file to delete
 *
 * @return 0 for operation success, 1 for operation failure
 * */
int remove_log_file(Logc_t *logger) {
	char *message=NULL;

	if (remove(logger->log_filename)) {


		asprintf(&message,"Can't delete: %s", logger->log_filename);
		error(logger, message);
		free(message);
		message=NULL;

	} else {

		asprintf(&message,"%s successfully deleted.", logger->log_filename);
		error(logger, message);
		free(message);
		message=NULL;

		logger->file_stream = NULL;
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;

}

Logc_t *
init_logger(LogLevel video_level, FILE *video_stream, LogLevel file_level, const char *log_filename)
{

	Logc_t *logger = (Logc_t *) malloc(sizeof(Logc_t) * 8);

	if (logger) {

		char *random_name=NULL;

		struct timeval timestamp;

		gettimeofday(&timestamp, NULL );
		asprintf(&random_name,"logger-%i.%i", timestamp.tv_sec, timestamp.tv_usec);
		logger->logger_name=random_name;

		set_video_log_level(logger, video_level);
		set_log_videostream(logger, video_stream);

		set_file_log_level(logger, file_level);
		set_log_file(logger, log_filename);

		set_time_format_template(logger, DEFAULT_TIME_FORMAT);
		set_log_template(logger, DEFAULT_LOG_TEMPLATE);
		set_log_colored(logger, 1);
	}

	return logger;

}

/**
 * Uninitialize the Logging Process
 */
const int uninit_logger(Logc_t *logger) {

	if(logger->file_stream)
		if (close_log_filestream(logger))
			return EXIT_FAILURE;

	if (logger->log_filename)
	{
		free(logger->log_filename);
		logger->log_filename = NULL;
	}

	if (logger->time_format_template)
	{
		free(logger->time_format_template);
		logger->time_format_template = NULL;
	}

	if (logger->log_template)
	{
		free(logger->log_template);
		logger->log_template = NULL;
	}

	logger->video_stream = NULL;


	free(logger);
	logger = NULL;

	return EXIT_SUCCESS;

}

#ifdef __cplusplus
}
#endif

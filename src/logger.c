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

/**
 * \file logger.c
 * \brief The logger functions
 *
 **/

#include <logc/logger.h>
#include "functions.h"

#include <stdlib.h>
#include <stdarg.h>

#ifdef _WIN32

#include <stdarg.h>

#ifdef __cplusplus
extern "C"
  {
#endif

int asprintf(char **ret, const char *format, ...)
{
    va_list ap;

    *ret = NULL;  /* Ensure value can be passed to free() */

    va_start(ap, format);
    int count = vsnprintf(NULL, 0, format, ap);
    va_end(ap);

    if (count >= 0)
    {
        char* buffer = malloc(count + 1);
        if (buffer == NULL)
            return -1;

        va_start(ap, format);
        count = vsnprintf(buffer, count + 1, format, ap);
        va_end(ap);

        if (count < 0)
        {
            free(buffer);
            return count;
        }
        *ret = buffer;
    }

    return count;
}

#endif

int
check_print(log_level_t log_level, log_type_t logType)
{
  int status = EXIT_FAILURE;
  switch (log_level)
    {
  case OFF_LEVEL:
    break;

  case ALL_LEVEL:
    status = EXIT_SUCCESS;
    break;

  case DEBUG_LEVEL:
    if (logType != TRACE)
      {
        status = EXIT_SUCCESS;
      }
    break;

  case INFO_LEVEL:
    if (logType != TRACE && logType != DEBUG)
      {
        status = EXIT_SUCCESS;
      }
    break;

  case WARNING_LEVEL:
    if (logType != TRACE && logType != DEBUG && logType != INFO)
      {
        status = EXIT_SUCCESS;
      }
    break;

  case ERROR_LEVEL:
    if (logType != TRACE && logType != DEBUG && logType != INFO
        && logType != WARNING)
      {
        status = EXIT_SUCCESS;
      }
    break;

  case FATAL_LEVEL:
    if (logType != TRACE && logType != DEBUG && logType != INFO
        && logType != WARNING && logType != ERROR)
      {
        status = EXIT_SUCCESS;
      }
    break;

  default:
    break;
    }

  return status;

}

void
print_msg(FILE *stream, int colored, log_type_t logType, const char *string)
{
  if (stream)
    {

      char* output = NULL;

      if (!colored)
        {
          char* color = RESET;

          switch (logType)
            {
          case TRACE:
            color = TRACE_TYPE_COLOR;
            break;

          case DEBUG:
            color = DEBUG_TYPE_COLOR;
            break;

          case INFO:
            color = INFO_TYPE_COLOR;
            break;

          case WARNING:
            color = WARNING_TYPE_COLOR;
            break;

          case ERROR:
            color = ERROR_TYPE_COLOR;
            break;

          case FATAL:
            color = FATAL_TYPE_COLOR;
            break;

          default:
            color = TRACE_TYPE_COLOR;
            break;
            }

          asprintf(&output, "%s%s%s\n", color, string, RESET);
        }
      else
        asprintf(&output, "%s\n", string);

      if (output)
        {
          fprintf(stream, "%s\n", output);
          free(output);
          output = NULL;
        }
    }
}

void
print(logger_t *logger, const log_type_t logType, const char *message,
    const char *file, const char *function, int line)
{
  if (!logger)
    return;

  char *output_string = NULL;

  char *string_format = DEFAULT_LOG_TEMPLATE;

  char *timeString = time2String();

  char* type = NULL;

  switch (logType)
    {
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

  asprintf(&output_string, string_format, timeString, type, function, file,
      line, message);

  if (!check_print(logger->video_logger_level, logType))
    print_msg(logger->video_stream, logger->colored, logType, output_string);

  if (!check_print(logger->file_logger_level, logType))
    print_msg(logger->file_stream, 1, logType, output_string);

  free(output_string);
  output_string = NULL;
}

/*
 * GETTERS
 */

const char *
get_logger_filename(logger_t *logger)
{
  return logger->log_filename;
}

const char *
get_logger_template(logger_t *logger)
{
  return logger->log_template;
}

const log_level_t
get_video_logger_level(logger_t *logger)
{
  return logger->video_logger_level;
}

const log_level_t
get_file_logger_level(logger_t *logger)
{
  return logger->file_logger_level;
}

FILE *
get_logger_videosteam(logger_t *logger)
{
  return logger->file_stream;
}

FILE *
get_logger_filestream(logger_t *logger)
{
  return logger->file_stream;
}

const int
get_logger_colored(logger_t *logger)
{
  return logger->colored;
}

/*
 *  SETTERS
 */

void
set_logger_filename(logger_t* logger, const char *filename)
{

  if (logger)
    if (filename)
      {

        if (logger->file_stream)
          close_logger_filestream(logger);

        if (logger->log_filename)
          {
            free(logger->log_filename);
            logger->log_filename = NULL;
          }

        logger->log_filename = alloc_string(filename);
      }

}

int
set_logger_file(logger_t *logger, const char *filename)
{

  if (logger)
    {

      set_logger_filename(logger, filename);

      if (logger->log_filename)
        return open_logger_filestream(logger);

    }
  return EXIT_FAILURE;
}

int
set_logger_template(logger_t *logger, const char *template)
{

  if (logger && template)
    {
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

void
set_video_logger_level(logger_t *logger, const log_level_t log_level)
{
  if (logger)
    logger->video_logger_level = log_level;
}

void
set_file_logger_level(logger_t *logger, const log_level_t log_level)
{
  if (logger)
    logger->file_logger_level = log_level;
}

void
set_logger_videostream(logger_t *logger, FILE *video_stream)
{
  if (logger)
    logger->video_stream = video_stream;
}

void
set_logger_colored(logger_t *logger, int color)
{
  if (color < 1)
    logger->colored = 0;
  else
    logger->colored = 1;
}

/**
 * Open a Log File called by name.
 *
 * @param fileName The name of the Log file to open.
 *
 * @return 0 for operation success, 1 for operation failure
 */

int
open_logger_filestream(logger_t *logger)
{
  if (logger)
    if (logger->log_filename)
      {

        char *message = NULL;
        const char *file_name = get_logger_filename(logger);
        asprintf(&message, "Try Opening %s in append mode", file_name);
        logger_print(logger, TRACE, message);
        free(message);
        message = NULL;

        logger->file_stream = fopen(logger->log_filename, "a+");

        if (logger->file_stream)
          return EXIT_SUCCESS;

        asprintf(&message, "Failure Opening\t%s", logger->log_filename);
        logger_print(logger, TRACE, message);
        free(message);
        message = NULL;

      }

  return EXIT_FAILURE;
}

int
close_logger_filestream(logger_t *logger)
{
  if (logger)
    {
      if (logger->file_stream)
        {
          if (fclose(logger->file_stream) == EOF)
            return EXIT_FAILURE;

          logger->file_stream = NULL;
        }

      if (logger->log_filename)
        {

          char *message = NULL;
          asprintf(&message, "%s successfully closed", logger->log_filename);
          logger_print(logger, TRACE, message);
          free(message);
          message = NULL;
        }

      if (logger->log_filename)
        {
          free(logger->log_filename);
          logger->log_filename = NULL;
        }

      if (logger->log_filename == NULL)
        return EXIT_SUCCESS;
    }
  return EXIT_FAILURE;
}

/**
 * Delete a File
 * @param fileName The name of the file to delete
 *
 * @return 0 for operation success, 1 for operation failure
 * */
int
remove_logger_file(logger_t *logger)
{
  char *message = NULL;
  if (logger)
    if (logger->log_filename)
      if (remove(logger->log_filename))
        {

          asprintf(&message, "Can't delete: %s", logger->log_filename);
          logger_print(logger, ERROR, message);
          free(message);
          message = NULL;

        }
      else
        {

          asprintf(&message, "%s successfully deleted.", logger->log_filename);
          logger_print(logger, ERROR, message);
          free(message);
          message = NULL;

          logger->file_stream = NULL;
          return EXIT_SUCCESS;
        }

  return EXIT_FAILURE;

}

logger_t *
init_logger(log_level_t video_level, FILE *video_stream, log_level_t file_level,
    const char *log_filename)
{

  logger_t *logger = (logger_t *) calloc(1, sizeof(logger_t));

  if (logger)
    {

      set_video_logger_level(logger, video_level);
      set_logger_videostream(logger, video_stream);

      set_file_logger_level(logger, file_level);

      if (file_level)
        set_logger_file(logger, log_filename);
      else
        {
          logger->file_stream = NULL;
          set_logger_filename(logger, log_filename);
        }

      set_logger_template(logger, DEFAULT_LOG_TEMPLATE);
      set_logger_colored(logger, 1);
    }

  return logger;

}

/**
 * Uninitialize the Logging Process
 */
const int
uninit_logger(logger_t *logger)
{

  if (logger->file_stream)
    if (close_logger_filestream(logger))
      return EXIT_FAILURE;

  if (logger->log_filename)
    {
      free(logger->log_filename);
      logger->log_filename = NULL;
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

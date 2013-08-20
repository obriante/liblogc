/*
 * Copyright © 2012 - Orazio Briante <orazio.briante@hotmail.it>
 *
 * Licensed under the GNU Lesser General Public License Version 3
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * or write to the Free Software Foundation, Inc., 51 Franklin St
 * Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <logc/logc.h>

#define LOG_FILE_NAME	"simplelog.log"

#define	OFF_LEVEL_STRING "OFF_LEVEL"
#define	ALL_LEVEL_STRING "ALL_LEVEL"
#define DEBUG_LEVEL_STRING "DEBUG_LEVEL"
#define INFO_LEVEL_STRING "INFO_LEVEL"
#define WARNING_LEVEL_STRING "WARNING_LEVEL"
#define ERROR_LEVEL_STRING "ERROR_LEVEL"
#define FATAL_LEVEL_STRING "FATAL_LEVEL"

void
print_messages(logger_t* logger, const char *log_level_video,
    const char *log_level_file)
{

  char* message = NULL;
  asprintf(&message, "Video Log Level: %s, File Log Level: %s", log_level_video,
      log_level_file, NULL, NULL);

  logger_print(logger, TRACE, message);
  logger_print(logger, DEBUG, message);
  logger_print(logger, INFO, message);
  logger_print(logger, WARNING, message);
  logger_print(logger, ERROR, message);
  logger_print(logger, FATAL, message);

  free(message);
  message = NULL;
}

int
main(int argc, char *argv[])
{

  logger_t *logger = init_logger(ALL_LEVEL, stderr, OFF_LEVEL, LOG_FILE_NAME, NULL, NULL);
  set_logger_time_format(logger, "%H:%M:%S %d-%m-%Y");
  set_logger_template(logger, "@t @T [@f] @F:@l - @m");
  remove_logger_file(logger);
  open_logger_filestream(logger);

  char* version = NULL;
  asprintf(&version, "liblogc v%s", logc_version());
  logger_print(logger, INFO, version);
  free(version);
  version = NULL;

  char *copyright = NULL;
  asprintf(&copyright, "Copyright (C) %s", logc_copyright());
  logger_print(logger, INFO, copyright);
  free(copyright);
  copyright = NULL;

  print_messages(logger, ALL_LEVEL_STRING, OFF_LEVEL_STRING);

  set_video_logger_level(logger, OFF_LEVEL);
  set_file_logger_level(logger, ALL_LEVEL);
  print_messages(logger, OFF_LEVEL_STRING, ALL_LEVEL_STRING);

  set_video_logger_level(logger, ALL_LEVEL);
  set_file_logger_level(logger, ALL_LEVEL);
  print_messages(logger, ALL_LEVEL_STRING, ALL_LEVEL_STRING);

  set_video_logger_level(logger, DEBUG_LEVEL);
  set_file_logger_level(logger, DEBUG_LEVEL);
  print_messages(logger, DEBUG_LEVEL_STRING, DEBUG_LEVEL_STRING);

  set_video_logger_level(logger, INFO_LEVEL);
  set_file_logger_level(logger, INFO_LEVEL);
  print_messages(logger, INFO_LEVEL_STRING, INFO_LEVEL_STRING);

  set_video_logger_level(logger, WARNING_LEVEL);
  set_file_logger_level(logger, WARNING_LEVEL);
  print_messages(logger, WARNING_LEVEL_STRING, WARNING_LEVEL_STRING);

  set_video_logger_level(logger, ERROR_LEVEL);
  set_file_logger_level(logger, ERROR_LEVEL);
  print_messages(logger, ERROR_LEVEL_STRING, ERROR_LEVEL_STRING);

  set_video_logger_level(logger, FATAL_LEVEL);
  set_file_logger_level(logger, FATAL_LEVEL);
  print_messages(logger, FATAL_LEVEL_STRING, FATAL_LEVEL_STRING);

  set_video_logger_level(logger, ALL_LEVEL);
  set_file_logger_level(logger, ALL_LEVEL);
  set_logger_videostream(logger, stdout);
  print_messages(logger, ALL_LEVEL_STRING, ALL_LEVEL_STRING);

  if (logger)
    uninit_logger(logger);

}

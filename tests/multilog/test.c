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

#include<stdlib.h>
#include<stdio.h>
#include <logc/logc.h>

#define	OFF_LEVEL_STRING "OFF_LEVEL"
#define	ALL_LEVEL_STRING "ALL_LEVEL"
#define DEBUG_LEVEL_STRING "DEBUG_LEVEL"
#define INFO_LEVEL_STRING "INFO_LEVEL"
#define WARNING_LEVEL_STRING "WARNING_LEVEL"
#define ERROR_LEVEL_STRING "ERROR_LEVEL"
#define FATAL_LEVEL_STRING "FATAL_LEVEL"

#define TRUE 0
#define FALSE 1

void
print_messages(logger_t* logger, const char *log_level_video,
    const char *log_level_file)
{

  char* message = NULL;
  asprintf(&message, "Video Log Level: %s, File Log Level: %s", log_level_video,
      log_level_file);

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
  logger_t *logger1 = init_logger(ALL_LEVEL, stdout, ALL_LEVEL,
      "multilog-1.log");
  logger_t *logger2 = init_logger(ALL_LEVEL, stdout, ALL_LEVEL,
      "multilog-2.log");

  remove_logger_file(logger1);
  open_logger_filestream(logger1);

  remove_logger_file(logger2);
  open_logger_filestream(logger2);
  set_logger_colored(logger2, TRUE);

  char* version = NULL;
  asprintf(&version, "liblogc v%s", logc_version());
  logger_print(logger1, INFO, version);
  logger_print(logger2, INFO, version);
  free(version);
  version = NULL;

  char *copyright = NULL;
  asprintf(&copyright, "Copyright (C) %s", logc_copyright());
  logger_print(logger1, INFO, copyright);
  logger_print(logger2, INFO, copyright);
  free(copyright);
  copyright = NULL;

  print_messages(logger1, ALL_LEVEL_STRING, ALL_LEVEL_STRING);
  print_messages(logger2, ALL_LEVEL_STRING, ALL_LEVEL_STRING);

  uninit_logger(logger1);
  uninit_logger(logger2);

  return 0;
}

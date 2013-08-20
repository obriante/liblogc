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
#include <logc/logc.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{

  int logger_ids[255];

  init_logc();

  char* version = NULL;
  asprintf(&version, "liblogc-v%s", logc_version());

  char *copyright = NULL;
  asprintf(&copyright, "Copyright (C) %s", logc_copyright());

  int i = 0;
  for (i = 0; i < 255; i++)
    {
      logger_ids[i] = add_logger(ALL_LEVEL, stdout, OFF_LEVEL, NULL, NULL, NULL);
    }

  for (i = 0; i < 255; i++)
    {

      logger_t *logger = get_logger(logger_ids[i]);

      char * output = NULL;
      asprintf(&output, "logger ID: %i", i + 1);
      logger_print(logger, INFO, output);
      free(output);
      output = NULL;

      info(logger_ids[i], version);
      info(logger_ids[i], copyright);
    }

  for (i = 0; i < 255; i++)
    {
      delete_logger(logger_ids[i]);
    }

  unit_logc();

  free(version);
  version = NULL;

  free(copyright);
  copyright = NULL;

  return EXIT_SUCCESS;
}


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


#define LOG_INDEX       255

int
main(int argc, char *argv[])
{

  int logger_ids[LOG_INDEX];

  init_logc();

  int i = 0;
  for (i = 0; i < LOG_INDEX; i++) {
    logger_ids[i] = add_logger(ALL_LEVEL, stdout, OFF_LEVEL, NULL, NULL, NULL);
  }

  for (i = 0; i < LOG_INDEX; i++) {

    logger_t *logger = get_logger(logger_ids[i]);

    char *output = NULL;
    asprintf(&output, "logger ID: %i", i + 1);
    logger_print(logger, INFO, output);
    free(output);
    output = NULL;

    info(logger_ids[i], "liblogc-v%s", logc_version());
    info(logger_ids[i], "Copyright (C) %s", logc_copyright());
  }

  for (i = 0; i < LOG_INDEX; i++) {
    delete_logger(logger_ids[i]);
  }

  unit_logc();

  return EXIT_SUCCESS;
}

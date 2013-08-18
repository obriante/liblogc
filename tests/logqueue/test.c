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

  init_logc();

  const char *data_content = "Simple data content";

  queue_t *queue = init_queue();

  int num_elem = get_queue_nelem(queue);

  int id1 = queue_item_add(queue, (void *) data_content);

  num_elem = get_queue_nelem(queue);

  int id2 = queue_item_add(queue, (void *) data_content);

  num_elem = get_queue_nelem(queue);

  queue_item_t *begin = get_queue_begin(queue);
  queue_item_t *item = get_queue_item_by_id(queue, id2);
  queue_item_t *end = get_queue_end(queue);

  int status = queue_delete_item(queue, id1);

  num_elem = get_queue_nelem(queue);

  uninit_queue(queue);

  char* version = NULL;
  asprintf(&version, "liblogc v%s", logc_version());


  logger_t *logger1=init_logger(ALL_LEVEL, stdout, OFF_LEVEL, NULL);
  logger_print(logger1, INFO, version);

  int id_logger1=add_logger(ALL_LEVEL, stdout, OFF_LEVEL, NULL); // BUG without file!!
  int id_logger2=add_logger(ALL_LEVEL, stdout, OFF_LEVEL, NULL); // BUG without file!!


  info(id_logger1,  version);
  info(id_logger2,  version);

  logger_t *logger2=get_logger(id_logger2);

  logger_print(logger1, INFO, version);
  logger_print(logger2, INFO, version);

  free(version);
  version = NULL;

  delete_logger(id_logger1);
  delete_logger(id_logger2);

  unit_logc();

  return EXIT_SUCCESS;
}

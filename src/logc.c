
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
#include <stdarg.h>
  
#ifdef __cplusplus
extern "C"  {
  
#endif  /*  */
  void init_logc()  {
    logger_queue = init_queue();
  } void unit_logc()  {
    queue_item_t * item;
     if (logger_queue)
       {
      for (item = logger_queue->head; item; item = item->next)
         uninit_logger(item->data);
      }
     uninit_queue(logger_queue);
  }
   int add_logger(log_level_t video_level, FILE * video_stream, log_level_t file_level, const char *log_filename,
                     const char *time_format, const char *template)  {
    logger_t * logger = init_logger(video_level, video_stream, file_level, log_filename, time_format, template);
     return queue_item_add(logger_queue, (void *)logger);
  }  int delete_logger(int id)  {
    queue_item_t * item = get_queue_item_by_id(logger_queue, id);
     if (!uninit_logger(item->data))
      return queue_delete_item(logger_queue, id);
     return EXIT_FAILURE;
  }
   logger_t * get_logger(int id) {
    queue_item_t * item = get_queue_item_by_id(logger_queue, id);
     return item->data;
  }
   void print_message(int id, const log_type_t logType, const char *file, const char *function, int line, const char *template,
                         ...)  {
     char message[4096];
     va_list argList;
     va_start(argList, template);
    vsnprintf(message, 4096, template, argList);
    va_end(argList);
     queue_item_t * item = get_queue_item_by_id(logger_queue, id);
    logger_t * logger = (logger_t *) item->data;
    print(logger, logType, message, file, function, line);
   }  
#ifdef __cplusplus
} 
#endif  /*  */

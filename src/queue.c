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

#include <logc/queue.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
  {
#endif

/*
 * ITEMS QUEUE FUNCTIONS
 */

int
queue_item_add(queue_t *queue, void *data)
{
  if (!queue)
    return -1;

  queue_item_t *item = calloc(1, sizeof(*item));

  if (!item)
    return -1;

  item->id = get_queue_nelem(queue)+1;
  item->data = data;
  item->queue = queue;
  item->next = queue->head;
  item->prev = NULL;
  queue->head = item;

  if (item->next)
    item->next->prev = item;
  if (!queue->tail)
    queue->tail = item;

  queue->num_elem++;

  return item->id;
}

void
queue_item_delete(queue_item_t *queue_item)
{
  if (queue_item)
    {

      if (queue_item->next)
        queue_item->next->prev = queue_item->prev;
      else
        queue_item->queue->tail = queue_item->prev;

      if (queue_item->prev)
        queue_item->prev->next = queue_item->next;
      else
        queue_item->queue->head = queue_item->next;

      queue_item->queue->num_elem--;

      free(queue_item);
      queue_item = NULL;
    }
}

queue_item_t *
queue_item_next(queue_item_t * item)
{
  return (item ? item->next : 0);
}

queue_item_t *
queue_item_prev(queue_item_t *item)
{
  return (item ? item->prev : 0);
}

/*
 *  LIST FUNCTIONS
 */

queue_t *
init_queue()
{
  queue_t *this = calloc(1, sizeof(queue_t));
  this->head = 0;
  this->tail = 0;
  this->num_elem = 0;

  return this;
}

int
get_queue_nelem(queue_t *queue)
{
  return (queue ? queue->num_elem : 0);
}

queue_item_t *
get_queue_begin(queue_t *queue)
{
  return (queue ? queue->head : 0);
}

queue_item_t *
get_queue_end(queue_t *queue)
{
  return (queue ? queue->tail : 0);
}

queue_item_t *
get_queue_item_by_id(queue_t *queue, int id)
{
  queue_item_t *item;

  if (queue)
    {
      for (item = queue->head; item; item = item->next)
        if (id == item->id)
          return item;
    }
  return NULL;
}

queue_item_t *
get_queue_item_by_data(queue_t *queue, void *data)
{
  queue_item_t *item;

  if (queue)
    {
      for (item = queue->head; item; item = item->next)
        if (data == item->data)
          return item;
    }

  return NULL;
}

void
uninit_queue(queue_t *queue)
{
  queue_item_t *next;
  queue_item_t *current;

  if (queue)
    {

      if (queue->num_elem > 0)
        {
          current = queue->head;
          while (current)
            {
              next = current->next;
              queue_item_delete(current);
              current = next;
            }
        }

      free(queue);
      queue = NULL;
    }
}

void
clear_queue(queue_t *queue)
{
  queue->head = NULL;
  queue->tail = NULL;
  queue->num_elem = 0;
}

int
queue_delete_item(queue_t *queue, int id)
{
  if (!queue)
    return EXIT_FAILURE;

  queue_item_t *item = get_queue_item_by_id(queue, id);

  if (!item)
    return EXIT_FAILURE;

  queue_item_delete(item);
  return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif

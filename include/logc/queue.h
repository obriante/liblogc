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

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct queue_item
{
  int id;
  void *data;
  struct queue *queue;
  struct queue_item *next;
  struct queue_item *prev;
} queue_item_t;

typedef struct queue
{
  queue_item_t *head;
  queue_item_t *tail;
  int num_elem;
} queue_t;

extern int
queue_item_add(queue_t *queue, void *data);

extern void
queue_item_delete(queue_item_t *queue_item);

extern queue_item_t
*
queue_item_next(queue_item_t * item);

extern queue_item_t
*
queue_item_prev(queue_item_t *item);

extern queue_t *
init_queue();

extern void
uninit_queue(queue_t *);

extern void
clear_queue(queue_t *);

extern int
queue_delete_item(queue_t *, int id);

extern int
get_queue_nelem(queue_t *queue);

extern queue_item_t *
get_queue_begin(queue_t *queue);

extern queue_item_t *
get_queue_end(queue_t *queue);

extern queue_item_t *
get_queue_item_by_id(queue_t *queue, int id);

extern queue_item_t *
get_queue_item_by_data(queue_t *queue, void *data);

#endif /* QUEUE_H_ */

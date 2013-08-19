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

/** \mainpage liblogc Documentation
 *
 * \section liblogc_functions Library Functions
 *
 * see logc.h and logc.c documentation.
 *
 * <H2>README</H2>
 *
 * @verbinclude README
 *
 */

/**
 * @page liblogc_readme README
 * @verbinclude README
 */

/**
 * @page liblogc_install INSTALL
 * @verbinclude INSTALL
 */

/**
 * @page liblogc_license COPYING
 * @verbinclude COPYING
 */

/**
 * @page liblogc_changelog ChangeLog
 * @verbinclude ChangeLog
 */

/**
 * \file logc.h
 * \brief The logc header
 *
 **/

#ifndef LOGC_H_
#define LOGC_H_

#include "logcver.h"
#include <logc/deprecated.h>
#include <logc/logger.h>
#include <logc/queue.h>

#define log(id, logType, message)     print_message(id, logType, message, __FILE__,  __FUNCTION__, __LINE__) /**< To print a generic log output */

#define trace(id, message)            print_message(id, TRACE, message, __FILE__,  __FUNCTION__, __LINE__)   /**< To print a trace output */
#define debug(id, message)            print_message(id, DEBUG,  message, __FILE__,  __FUNCTION__, __LINE__)   /**< To print a debug output */
#define info(id, message)             print_message(id, INFO,  message, __FILE__,  __FUNCTION__, __LINE__)    /**< To print a info output */
#define warning(id, message)          print_message(id, WARNING,  message, __FILE__,  __FUNCTION__, __LINE__) /**< To print a warning output */
#define error(id, message)            print_message(id, ERROR,  message, __FILE__,  __FUNCTION__, __LINE__)   /**< To print a error output */
#define fatal(id, message)            print_message(id, FATAL,  message, __FILE__,  __FUNCTION__, __LINE__)   /**< To print a fatal output */

static queue_t *logger_queue;

extern void
init_logc();

extern void
unit_logc();

extern int
add_logger();

extern int
delete_logger(int id);

extern logger_t *
get_logger(int id);

void
print_message(int, const log_type_t, const char *, const char *, const char *,
    int);

#endif /* LOGC_H_ */

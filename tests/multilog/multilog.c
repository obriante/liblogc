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


void print_messages(Logc_t* logger, const char *log_level_video, const char *log_level_file)
{

	char* message=NULL;
	asprintf(&message, "Video Log Level: %s, File Log Level: %s", log_level_video, log_level_file);

	trace(logger, message);
	debug(logger, message);
	info(logger, message);
	warning(logger, message);
	error(logger, message);
	fatal(logger, message);

	free(message);
	message=NULL;
}


int main(int argc, char *argv[])
{
	Logc_t *logger1=init_logger(ALL_LEVEL, stdout, ALL_LEVEL, "/tmp/liblogc.multitest-1.log");
	Logc_t *logger2=init_logger(ALL_LEVEL, stdout, ALL_LEVEL, "/tmp/liblogc.multitest-2.log");

	set_logger_name(logger1, "logger1");
	set_logger_name(logger2, "logger2");

	remove_log_file(logger1);
	open_log_filestream(logger1);

	remove_log_file(logger2);
	open_log_filestream(logger2);
	set_log_colored(logger2, TRUE);

	char* message=NULL;
	asprintf(&message,"%s - liblogc - v%s", get_logger_name(logger1), logc_version());
	info(logger1, message);
	free(message);
	message=NULL;

	message=NULL;
	asprintf(&message,"%s - liblogc - v%s", get_logger_name(logger2), logc_version());
	info(logger2, message);
	free(message);
	message=NULL;

	print_messages(logger1, ALL_LEVEL_STRING, ALL_LEVEL_STRING );
	print_messages(logger2, ALL_LEVEL_STRING, ALL_LEVEL_STRING );

	uninit_logger(logger1);
	uninit_logger(logger2);

	return 0;
}

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

#include <logc/logc.h>

#define LOG_FILE_NAME	"/tmp/liblogc.test.log"

#define	OFF_LEVEL_STRING "OFF_LEVEL"
#define	ALL_LEVEL_STRING "ALL_LEVEL"
#define DEBUG_LEVEL_STRING "DEBUG_LEVEL"
#define INFO_LEVEL_STRING "INFO_LEVEL"
#define WARNING_LEVEL_STRING "WARNING_LEVEL"
#define ERROR_LEVEL_STRING "ERROR_LEVEL"
#define FATAL_LEVEL_STRING "FATAL_LEVEL"


void print_messages(Logc_t* logger, const char *log_level_video, const char *log_level_file)
{
	trace(logger, "Video Log Level: %s, File Log Level: %s", log_level_video,log_level_file);
	debug(logger, "Video Log Level: %s, File Log Level: %s", log_level_video,log_level_file);
	info(logger, "Video Log Level: %s, File Log Level: %s", log_level_video,log_level_file);
	warning(logger, "Video Log Level: %s, File Log Level: %s", log_level_video,log_level_file);
	error(logger, "Video Log Level: %s, File Log Level: %s", log_level_video,log_level_file);
	fatal(logger, "Video Log Level: %s, File Log Level: %s", log_level_video,log_level_file);
}


int main(int argc, char *argv[])
{
	Logc_t *logger=init_logger(ALL_LEVEL, OFF_LEVEL, NULL);
	//info(logger, "liblogc version:\t%s", logc_version());
	print_messages(logger, ALL_LEVEL_STRING, OFF_LEVEL_STRING );

	if(!uninitLog(logger)){
		logger=init_logger(OFF_LEVEL, ALL_LEVEL, LOG_FILE_NAME);
		open_log_file(logger,0);
		print_messages(logger, OFF_LEVEL_STRING, ALL_LEVEL_STRING);
	}

	if(!uninitLog(logger)){
		logger=init_logger(ALL_LEVEL, ALL_LEVEL, LOG_FILE_NAME);
		open_log_file(logger, -1);
		print_messages(logger,ALL_LEVEL_STRING, ALL_LEVEL_STRING);
	}

	if(!uninitLog(logger)){
		logger=init_logger(DEBUG_LEVEL, DEBUG_LEVEL, LOG_FILE_NAME);
		open_log_file(logger, -1);
		print_messages(logger, DEBUG_LEVEL_STRING, DEBUG_LEVEL_STRING);
	}

	if(!uninitLog(logger)){
		logger=init_logger(INFO_LEVEL, INFO_LEVEL, LOG_FILE_NAME);
		open_log_file(logger, -1);
		print_messages(logger, INFO_LEVEL_STRING, INFO_LEVEL_STRING);
	}

	if(!uninitLog(logger)){
		logger=init_logger(WARNING_LEVEL, WARNING_LEVEL, LOG_FILE_NAME);
		open_log_file(logger, -1);
		print_messages(logger, WARNING_LEVEL_STRING, WARNING_LEVEL_STRING);
	}

	if(!uninitLog(logger)){
		logger=init_logger(ERROR_LEVEL, ERROR_LEVEL, LOG_FILE_NAME);
		open_log_file(logger, -1);
		print_messages(logger, ERROR_LEVEL_STRING, ERROR_LEVEL_STRING);
	}

	if(!uninitLog(logger)){
		logger=init_logger(FATAL_LEVEL, FATAL_LEVEL, LOG_FILE_NAME);
		open_log_file(logger, -1);
		print_messages(logger, FATAL_LEVEL_STRING, FATAL_LEVEL_STRING);
	}

	if(!uninitLog(logger)){
		logger=init_logger(ALL_LEVEL, ALL_LEVEL, LOG_FILE_NAME);
		set_log_video(logger, stdout);
		open_log_file(logger, -1);
		print_messages(logger, ALL_LEVEL_STRING, ALL_LEVEL_STRING);
	}

	if(logger)
		uninitLog(logger);

}

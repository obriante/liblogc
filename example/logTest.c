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


void print_messages(const char *message)
{
	trace(message);
	debug(message);
	info(message);
	warning(message);
	error(message);
	fatal(message);
}


int main(int argc, char *argv[])
{
	print_messages("No Log initialization");

	/*
	initLog(VIDEO_LOG, VIDEO_LOG);
	print_messages("log mode: VIDEO_LOG, video mode: VIDEO_LOG");
	uninitLog();

	initLog(FILE_VIDEO_LOG, FILE_VIDEO_LOG);
	openVideoLog(stdout);
	print_messages("log mode: FILE_VIDEO_LOG, video mode: FILE_VIDEO_LOG");
	uninitLog();*/

	initLogger(ALL_LEVEL, OFF_LEVEL);
	print_messages("Video Log Level: ALL_LEVEL, File Log Level: OFF_LEVEL");
	uninitLog();

	initLogger(OFF_LEVEL, ALL_LEVEL);
	checkFileSize(LOG_FILE_NAME, 0);
	openLogFile(LOG_FILE_NAME);
	print_messages("Video Log Level: OFF_LEVEL, File Log Level: ALL_LEVEL");
	uninitLog();

	initLogger(ALL_LEVEL, ALL_LEVEL);
	openLogFile(LOG_FILE_NAME);
	print_messages("Video Log Level: ALL_LEVEL, File Log Level: ALL_LEVEL");
	uninitLog();

	initLogger(DEBUG_LEVEL, DEBUG_LEVEL);
	openLogFile(LOG_FILE_NAME);
	print_messages("Video Log Level: DEBUG_LEVEL, File Log Level: DEBUG_LEVEL");
	uninitLog();

	initLogger(INFO_LEVEL, INFO_LEVEL);
	openLogFile(LOG_FILE_NAME);
	print_messages("Video Log Level: INFO_LEVEL, File Log Level: INFO_LEVEL");
	uninitLog();

	initLogger(WARNING_LEVEL, WARNING_LEVEL);
	openLogFile(LOG_FILE_NAME);
	print_messages("Video Log Level: WARNING_LEVEL, File Log Level: WARNING_LEVEL");
	uninitLog();

	initLogger(ERROR_LEVEL, ERROR_LEVEL);
	openLogFile(LOG_FILE_NAME);
	print_messages("Video Log Level: ERROR_LEVEL, File Log Level: ERROR_LEVEL");
	uninitLog();

	initLogger(FATAL_LEVEL, FATAL_LEVEL);
	openLogFile(LOG_FILE_NAME);
	print_messages("Video Log Level: FATAL_LEVEL, File Log Level: FATAL_LEVEL");
	uninitLog();

	initLogger(ALL_LEVEL, ALL_LEVEL);
	openLogFile(LOG_FILE_NAME);
	openVideoLog(stdout);
	print_messages("Video Log Level: ALL_LEVEL, File Log Level: ALL_LEVEL");
	uninitLog();

	initLog(FILE_VIDEO_LOG, FILE_VIDEO_LOG);
	openLogFile(LOG_FILE_NAME);
	openVideoLog(stderr);
	print_messages("log mode: FILE_VIDEO_LOG [DEPRECATED], video mode: FILE_VIDEO_LOG [DEPRECATED]");
	uninitLog();

}

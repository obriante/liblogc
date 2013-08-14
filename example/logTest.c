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

void print_messages(const char *message)
{
	log(INFO,message);
	log(WARNING,message);
	log(ERROR,message);
	log(DEBUG,message);
	debug(message);

}


int main(int argc, char *argv[])
{
	print_messages("No Log initialization");

	initLog(VIDEO_LOG, VIDEO_LOG);
	print_messages("log mode: VIDEO_LOG, video mode: VIDEO_LOG");
	uninitLog();

	char *fileName="/tmp/liblogc.test.log";

	initLog(FILE_LOG, FILE_LOG);
	checkFileSize(fileName, 0);
	openLogFile(fileName);
	print_messages("log mode: FILE_LOG, video mode: FILE_LOG");
	uninitLog();

	initLog(FILE_VIDEO_LOG, FILE_VIDEO_LOG);
	openLogFile(fileName);
	print_messages("log mode: FILE_VIDEO_LOG, video mode: FILE_VIDEO_LOG");
	uninitLog();

	initLog(FILE_VIDEO_LOG, FILE_VIDEO_LOG);
	openLogFile(fileName);
	openVideoLog(stdout);
	print_messages("log mode: FILE_VIDEO_LOG, video mode: FILE_VIDEO_LOG");
	uninitLog();

}

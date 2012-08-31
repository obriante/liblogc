/* 
 * libtwitc - C Support Library for Twitter
 * Copyright (C) 2012 Orazio Briante orazio.briante@hotmail.it
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
#include <logc/debug.h>

#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif

int
createDirectory(const char * dirName)
{

  if (dirName)
    {
      if (mkdir(dirName, 0777))
        return EXIT_SUCCESS;

    }

  return EXIT_FAILURE;

}

void
removeFile(const char * fileName)
{
  if (remove(fileName))
    error("Can't delete: %s", fileName);
  else
    info("%s successfully deleted.", fileName);
}

long
checkFileSize(const char * fileName)
{

  if (fileName)
    {

      FILE *fp = fopen(fileName, "r");

      if (fp)
        {
          fseek(fp, 0L, SEEK_END);
          long sz = ftell(fp);
          rewind(fp);

          fclose(fp);

          return sz;
        }

    }

  return -1;
}


  void
  checkLogFileDimension(const char * fileName, const long maxSize)
  {
    if (fileName)
      {
        debug ("fileName:\t%s", fileName);

        long size = checkFileSize(fileName);
        debug ("size:\t%s", fileName);

        if (size >= maxSize)
          removeFile(fileName);

      }
  }
  void
  initLog(const char * fileName, const long maxbyteSize)
  {

    if (fileName)
      {

        checkLogFileDimension(fileName, maxbyteSize);

        debug ("fileName:\t%s", fileName);

        logFile = fopen(fileName, "a");

        if (logFile)
          debug ("Opened \"%s\" in Append Mode", fileName);

      }
  }

  void
  uninitLog()
  {
    if (logFile)
      {
        debug ("Closing logFile");
        fclose(logFile);
        logFile = NULL;
      }

  }

  static void
  _logWrite(FILE * output, const char *type, const char *file,
      const char *function, int line, const char *template, va_list argp)
  {
    time_t now;
    struct tm  tmNow;
    char timeString[26];

    now = time(NULL );
    localtime_r(&now, &tmNow);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &tmNow);

    fprintf(output, "%s %s (%s - %s:%i): ", timeString, type, function, file,
        line);
    vfprintf(output, template, argp);
    fprintf(output, "\n");
    fflush(output);
  }

  void
  _info(const char *file, const char *function, int line,
      const char *template, ...)
  {
    va_list argp;
    va_start(argp, template);

    _logWrite(stderr, "INFO   ", file, function, line, template, argp);

    if (logFile)
      _logWrite(logFile, "INFO   ", file, function, line, template, argp);

    va_end(argp);
  }

  void
  _warning(const char *file, const char *function, int line,
      const char *template, ...)
  {
    va_list argp;
    va_start(argp, template);

    _logWrite(stderr, "WARNING", file, function, line, template, argp);

    if (logFile)
      _logWrite(logFile, "WARNING", file, function, line, template, argp);

    va_end(argp);
  }

  void
  _error(const char *file, const char *function, int line,
      const char *template, ...)
  {
    va_list argp;
    va_start(argp, template);

    _logWrite(stderr, "ERROR  ", file, function, line, template, argp);

    if (logFile)
      _logWrite(logFile, "ERROR  ", file, function, line, template, argp);

    va_end(argp);
  }

  void
  _debug(const char *file, const char *function, int line, const char *template,
      ...)
  {
    va_list argp;
    va_start(argp, template);

    _logWrite(stderr, "DEBUG  ", file, function, line, template, argp);

    va_end(argp);
  }


#ifdef __cplusplus
}
#endif

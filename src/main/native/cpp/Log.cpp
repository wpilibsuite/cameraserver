/*----------------------------------------------------------------------------*/
/* Copyright (c) 2016-2017 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Log.h"

#ifdef __APPLE__
#include <libgen.h>
#endif

#ifdef __ANDROID__
#include <libgen.h>
#endif

#include <cstdio>

#ifdef _WIN32
#include <cstdlib>
#else
#include <cstring>
#endif

using namespace cs;

ATOMIC_STATIC_INIT(Logger)

static void def_log_func(unsigned int level, const char* file,
                         unsigned int line, const char* msg) {
  if (level == 20) {
    std::fprintf(stderr, "CS: %s\n", msg);
    return;
  }

  const char* levelmsg;
  if (level >= 50)
    levelmsg = "CRITICAL";
  else if (level >= 40)
    levelmsg = "ERROR";
  else if (level >= 30)
    levelmsg = "WARNING";
  else
    return;
#ifdef _WIN32
  char fname[60];
  char ext[10];
  _splitpath_s(file, nullptr, 0, nullptr, 0, fname, 60, ext, 10);
  std::fprintf(stderr, "CS: %s: %s (%s%s:%d)\n", levelmsg, msg, fname, ext,
               line);
#elif __APPLE__
  int len = std::strlen(msg) + 1;
  char* basestr = new char[len + 1];
  std::strncpy(basestr, file, len);
  std::fprintf(stderr, "CS: %s: %s (%s:%d)\n", levelmsg, msg, basename(basestr),
               line);
  delete[] basestr;
#else
  std::fprintf(stderr, "CS: %s: %s (%s:%d)\n", levelmsg, msg, basename(file),
               line);
#endif
}

Logger::Logger() { SetDefaultLogger(); }

Logger::~Logger() {}

void Logger::SetDefaultLogger() { SetLogger(def_log_func); }

// Adapted from instructional material provided by Oregon State University
// Date: 9/15/2024
// Utilization/Definition of gprint functionality for debug printing derived from material provided in coursework from CS344 - 2024


#include <cstdio>
#include <cerrno>
#include "../includes/gprintf.hpp"
// Write formatted error information using list of arguments passed in function call to standard error
void(vgprintf)(char const *prefix, char const *fmt, va_list ap)
{
  int e = errno;
  fputs(prefix, stderr);
  vfprintf(stderr, fmt, ap);
  putc('\n', stderr);
  errno = e;
}

// Write formatted error information following the filename and line at which the gprintf call was made 
void(gprintf)(char const *prefix, char const *fmt, ...)
{
  int e = errno;
  va_list ap;
  va_start(ap, fmt);
  (vgprintf)(prefix, fmt, ap);
  va_end(ap);
  errno = e;
}
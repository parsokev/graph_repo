// Adapted from instructional material provided by Oregon State University
// Date: 9/15/2024
// Utilization/Definition of gprint functionality for debug printing derived from material provided in coursework from CS344 - 2024

#pragma once
#include <cstdarg>

void vgprintf(char const *prefix, char const *fmt, va_list ap);
void gprintf(char const *prefix, char const *fmt, ...);

// In release configuration, gprintf function calls are effectively ignored and do not accept any passed arguments or formatted strings for writing to standard error
#ifdef NDEBUG
#define vgprintf(fmt, ap) ((void)(0))
#define gprintf(fmt, ...) ((void)(0))
#else

// In debug configuration, gprintf function calls integrate the line number and filename information of the call as a prefix for writing to standard error
#define GPRINTF_STRINGIFY_(x) #x
#define GPRINTF_STRINGIFY(x) GPRINTF_STRINGIFY_(x)

// Prints strings with formatted arguments and incorporated prefixes detailing function call location when gprintf is called in debug configuration
#define vgprintf(fmt, ap)                                                      \
  (vgprintf)("[DEBUG] " __FILE__ ":" GPRINTF_STRINGIFY(__LINE__) ": ", fmt, ap)
#define gprintf(fmt, ...)                                                      \
  (gprintf)("[DEBUG] " __FILE__ ":" GPRINTF_STRINGIFY(__LINE__) ": ",          \
            fmt,                                                               \
            ##__VA_ARGS__)
#endif
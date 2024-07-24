#pragma once
#include <stdarg.h>

/** print formatted debug logs */
void vgprintf(char const *prefix, char const *fmt, va_list ap);
void gprintf(char const *prefix, char const *fmt, ...);

#ifdef NDEBUG
#define vgprintf(fmt, ap) ((void)(0))
#define gprintf(fmt, ...) ((void)(0))
#else

#define GPRINTF_STRINGIFY_(x) #x
#define GPRINTF_STRINGIFY(x) GPRINTF_STRINGIFY_(x)

#define vgprintf(fmt, ap)                                                      \
  (vgprintf)("[DEBUG] " __FILE__ ":" GPRINTF_STRINGIFY(__LINE__) ": ", fmt, ap)
#define gprintf(fmt, ...)                                                      \
  (gprintf)("[DEBUG] " __FILE__ ":" GPRINTF_STRINGIFY(__LINE__) ": ",          \
            fmt,                                                               \
            ##__VA_ARGS__)
#endif
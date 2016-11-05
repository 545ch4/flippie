#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAXLN 200
#define ISSPACE " \t\n\r\f\v"

int sscanf (const char *buf, const char *fmt, ...);

#endif

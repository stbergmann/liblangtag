/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * lt-utils.c
 * Copyright (C) 2011-2012 Akira TAGOH
 * 
 * Authors:
 *   Akira TAGOH  <akira@tagoh.org>
 * 
 * You may distribute under the terms of either the GNU
 * Lesser General Public License or the Mozilla Public
 * License, as specified in the README file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "lt-messages.h"
#include "lt-utils.h"


/*< private >*/

/*< public >*/
int
lt_strcmp0(const char *v1,
	   const char *v2)
{
	if (!v1)
		return -(v1 != v2);
	if (!v2)
		return v1 != v2;
	return strcmp(v1, v2);
}

int
lt_strcasecmp(const char *s1,
	      const char *s2)
{
	char c1, c2;

	lt_return_val_if_fail (s1 != NULL, 0);
	lt_return_val_if_fail (s2 != NULL, 0);

	while (*s1 && *s2) {
		c1 = tolower(*s1);
		c2 = tolower(*s2);
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

int
lt_strncasecmp(const char *s1,
	       const char *s2,
	       size_t      len)
{
	char c1, c2;

	lt_return_val_if_fail (s1 != NULL, 0);
	lt_return_val_if_fail (s2 != NULL, 0);

	while (len && *s1 && *s2) {
		len--;
		c1 = tolower(*s1);
		c2 = tolower(*s2);
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}

	if (len)
		return (*s1 - *s2);
	else
		return 0;
}

char *
lt_strlower(char *string)
{
	size_t len;
	char *p = string;

	lt_return_val_if_fail (string != NULL, NULL);

	len = strlen(string);
	while (len) {
		*p = tolower(*p);
		p++;
		len--;
	}

	return string;
}

char *
lt_strdup_printf(const char *format,
		 ...)
{
	va_list ap;
	char *retval;

	va_start(ap, format);

	retval = lt_strdup_vprintf(format, ap);

	va_end(ap);

	return retval;
}

char *
lt_strdup_vprintf(const char *format,
		  va_list     args)
{
	char *retval, c;
	va_list ap;
	int size;

	lt_return_val_if_fail (format != NULL, NULL);

	va_copy(ap, args);

	size = vsnprintf(&c, 1, format, ap) + 1;

	va_end(ap);

	retval = malloc(sizeof (char) * size);
	if (retval) {
		vsprintf(retval, format, args);
	}

	return retval;
}

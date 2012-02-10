// memchar.c
// 
// This file incorporates material from Newlib and code
// from the FreeBSD project.
// 
// See COPYING.NEWLIB and COPYING.BSD for licence details.
//
// Copyright (c) 1990, 1993
//  The Regents of the University of California.  All rights reserved.
//
//  This code is derived from software contributed to Berkeley by
//  Chris Torek.
//

/*
FUNCTION
    <<memchr>>---find character in memory

INDEX
    memchr

ANSI_SYNOPSIS
    #include <string.h>
    void *memchr(const void *<[src]>, int <[c]>, size_t <[length]>);

TRAD_SYNOPSIS
    #include <string.h>
    void *memchr(<[src]>, <[c]>, <[length]>)
    void *<[src]>;
    void *<[c]>;
    size_t <[length]>;

DESCRIPTION
    This function searches memory starting at <<*<[src]>>> for the
    character <[c]>.  The search only ends with the first
    occurrence of <[c]>, or after <[length]> characters; in
    particular, <<NUL>> does not terminate the search.

RETURNS
    If the character <[c]> is found within <[length]> characters
    of <<*<[src]>>>, a pointer to the character is returned. If
    <[c]> is not found, then <<NULL>> is returned.

PORTABILITY
<<memchr>> is ANSI C.

<<memchr>> requires no supporting OS subroutines.

QUICKREF
    memchr ansi pure
*/

#include <string.h>

void *memchr(const void *s, int c, size_t n) {
	if (n != 0) {
	const unsigned char *p = s;

	do {
		if (*p++ == (unsigned char)c)
		return ((void *)(p - 1));
	} while (--n != 0);
	}
	return (NULL);
}

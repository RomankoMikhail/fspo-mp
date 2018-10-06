/*
 * Copyright (c) 2018, mikhail
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * File:   string.h
 * Author: mikhail
 *
 * Created on 27 апреля 2018 г., 22:58
 */



#ifndef STRING_H
#define STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *memcpy(void *dest, const void *src, size_t n);
extern void *memchr(const void *s, int c, size_t n);
extern int memcmp(const void *s1, const void *s2, size_t n);
extern void *memset(void *dest, int val, size_t n);

extern char *strcat(char *dest, const char *src);
extern char *strncat(char *dest, const char *src, size_t n);
extern char *strchr(const char *s, int c);
extern char *strrchr(const char *s, int c);
extern int strcmp(const char *str1, const char *str2);
extern int strncmp(const char *str1, const char *str2, size_t n);
extern char *strcpy(char *toHere, const char *fromHere);
extern char *strncpy(char *toHere, const char *fromHere, size_t n);
extern size_t strlen(const char *str);
extern size_t strspn(const char *s, const char *accept);
extern size_t strcspn(const char *s, const char *reject);
extern char *strpbrk(const char *s, const char *accept);
extern char *strstr(const char *haystack, const char *needle);

#ifdef __cplusplus
}
#endif

#endif /* STRING_H */


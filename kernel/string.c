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
#include <stddef.h>
#include <stdint.h>
#include "string.h"

int isinstr(const char sym, const char *str)
{
    while (*str)
    {
        if (*str == sym)
            return 1;
        str++;
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    void * r = dest;

    while (n > 0)
    {
        switch (n % 4)
        {
        case 0:
            *(uint32_t*) dest = *(uint32_t*) src;
            dest += 4;
            src += 4;
            n -= 4;
            break;
        case 3:
        case 2:
            *(uint16_t*) dest = *(uint16_t*) src;
            dest += 2;
            src += 2;
            n -= 2;
            break;
        default:
            *(uint8_t*) dest = *(uint8_t*) src;
            dest++;
            src++;
            n--;
            break;
        }
    }
    return r;
}

void *memchr(const void *s, int c, size_t n)
{
    while (n > 0)
    {
        if (*(const char*) s == c)
            return (void*) s;
        s++;
        n--;
    }
    return NULL;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    while (n > 0)
    {
        int d = *(char*) s1 - *(char*) s2;
        if (d > 0)
            return 1;
        else if (d < 0)
            return -1;
        s1++;
        s2++;
        n--;
    }
    return 0;
}

void *memset(void *dest, int val, size_t n)
{
    void *r = dest;
    register uint16_t v16 = val | ((uint16_t) val << 8);
    register uint32_t v32 = v16 | ((uint32_t) v16 << 16);

    while (n > 0)
    {
        switch (n % 4)
        {
        case 0:
            *(uint32_t*) dest = v32;
            dest += 4;
            n -= 4;
            break;
        case 3:
        case 2:
            *(uint16_t*) dest = v16;
            dest += 2;
            n -= 2;
            break;
        default:
            *(uint8_t*) dest = (uint8_t) val;
            dest++;
            n--;
            break;
        }
    }
    return r;
}

char *strcat(char *dest, const char *src)
{
    char *d = dest;
    while (*dest) dest++;
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = 0;
    return d;
}

char *strncat(char *dest, const char *src, size_t n)
{
    char *d = dest;
    while (*dest) dest++;
    while (*src && n)
    {
        *dest = *src;
        dest++;
        src++;
        n--;
    }
    *dest = 0;
    return d;
}

char *strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return (char*) s;
        s++;
    }
    return NULL;
}

char *strrchr(const char *s, int c)
{
    char *last = NULL;
    while (*s)
    {
        if (*s == c)
            last = (char*) s;
        s++;
    }
    return last;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 > *str2)
            return 1;
        else if (*str1 < *str2)
            return -1;
        str1++;
        str2++;
    }
    return 0;
}

int strncmp(const char *str1, const char *str2, size_t n)
{
    while (*str1 && *str2 && n > 0)
    {
        if (*str1 > *str2)
            return 1;
        else if (*str1 < *str2)
            return -1;
        str1++;
        str2++;
        n--;
    }
    return 0;
}

char *strcpy(char *toHere, const char *fromHere)
{
    char *d = toHere;
    while (*fromHere)
    {
        *toHere = *fromHere;
        toHere++;
        fromHere++;
    }
    *toHere = 0;
    return d;
}

char *strncpy(char *toHere, const char *fromHere, size_t n)
{
    char *d = toHere;
    while (*fromHere && n > 0)
    {
        *toHere = *fromHere;
        toHere++;
        fromHere++;
        n--;
    }
    *toHere = 0;
    return d;
}

size_t strlen(const char *str)
{
    const char *s = str;
    while (*str)
        str++;
    return str - s;
}

size_t strspn(const char *s, const char *accept)
{
    size_t r = 0;
    while (*s)
    {
        if (!isinstr(*s, accept))
            break;
        r++;
        s++;
    }
    return r;
}

size_t strcspn(const char *s, const char *reject)
{
    size_t r = 0;
    while (*s)
    {
        if (isinstr(*s, reject))
            break;
        r++;
        s++;
    }

    return r;
}

char *strpbrk(const char *s, const char *accept)
{
    while (*s)
    {
        if (isinstr(*s, accept))
            return (char*) s;
        s++;
    }
    return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
    if (haystack == NULL || needle == NULL)
        return NULL;

    for (; *haystack; haystack++)
    {
        // Is the needle at this point in the haystack?
        const char *h, *n;
        for (h = haystack, n = needle; *h && *n && (*h == *n); ++h, ++n);
        if (*n == '\0')
            return (char*) haystack;
    }
    return NULL;
}

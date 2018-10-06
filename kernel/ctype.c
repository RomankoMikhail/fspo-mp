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

#include "ctype.h"

int isalnum(int c)
{
    return (isalpha(c) || isdigit(c));
}

int isalpha(int c)
{
    if (islower(c) || isupper(c))
        return 1;
    return 0;
}

int iscntrl(int c)
{
    if (c <= 0x8 || c == 0x7f)
        return 1;
    return 0;
}

int isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

int isgraph(int c)
{
    if (c >= 0x21 && c <= 0x7e)
        return 1;
    return 0;
}

int islower(int c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    return 0;
}

int isupper(int c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;
}

int isprint(int c)
{
    if (c >= 0x20 && c <= 0x7e)
        return 1;
    return 0;
}

int ispunct(int c)
{
    if ((c >= 0x21 && c <= 0x2f) || (c >= 0x3a && c <= 0x40) ||
            (c >= 0x5b && c <= 0x60) || (c >= 0x7b && c <= 0x7e))
        return 1;
    return 0;
}

int isspace(int c)
{
    if (c == '\t' || (c >= 0xa && c <= 0xd) || c == ' ')
        return 1;
    return 0;
}

int isxdigit(int c)
{
    if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || isdigit(c))
        return 1;
    return 0;
}

int tolower(int c)
{
    if(isupper(c))
        return c | (0x20);
    return c;
}

int toupper(int c)
{
    if(islower(c))
        return c & (0xdf);
    return c;
}

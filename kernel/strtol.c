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
#include "stdlib.h"
#include "ctype.h"

long int strtol(const char *str, char **endptr, int base)
{
    long int rvalue = 0;
    int sign = 1;
    char *ptr = (char*) str;

    // Skip space
    while (isspace(*ptr))
        ptr++;

    if (*ptr == '-')
    {
        sign = -1;
        ptr++;
    }

    while (isalnum(*ptr))
    {
        int digit = 0;

        if (isalpha(*ptr))
            digit = tolower(*ptr) - 'a' + 10;
        else
            digit = *ptr - '0';

        if (base == 0 && digit == 0)
        {
            if (*(ptr + 1) == 'x')
            {
                base = 16;
                ptr += 2;
                continue;
            }
            else
            {
                base = 8;
                ptr++;
                continue;
            }
        }
        else if (base == 0)
            base = 10;

        if (digit >= base)
            break;

        rvalue = rvalue * base + digit;
        ptr++;
    }
    if (endptr != NULL)
        *endptr = ptr;
    return rvalue * sign;
}
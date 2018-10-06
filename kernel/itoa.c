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
#include "string.h"

char alphabet[] = "0123456789abcdefghijklmnopqrstuwxyz";

void reverse(char *str, int n)
{
    int i;
    for (i = 0; i < n / 2; i++)
    {
        char c = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = c;
    }
}

void itoa(unsigned input, char *buffer, int radix)
{
    char *p = buffer;
    size_t s = 0;
    while (input)
    {
        *buffer = alphabet[input % radix];
        buffer++;
        s++;
        input /= radix;
    }
    reverse(p, s);
    *buffer = 0;
}

void apply_padding(char *buf, int padding, char pad)
{
	int i, j;
	for(i = strlen(buf); i < padding; i++)
	{
		for(j = i; j >= 0; j--)
		{
			buf[j + 1] = buf[j];
		}
		buf[0] = pad;
	}
}

void itoa_p(unsigned input, char *buffer, int radix, int padding)
{
    itoa(input, buffer, radix);
    apply_padding(buffer, padding, '0');
}

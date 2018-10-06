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
 * File:   abs.h
 * Author: mikhail
 *
 * Created on 28 апреля 2018 г., 13:38
 */

#ifndef ABS_H
#define ABS_H

#include <stdint.h>


#define absi8(val) _absi8((int8_t) val)
#define absi16(val) _absi16((int16_t) val)
#define absi32(val) _absi32((int32_t) val)
#define absi64(val) _absi64((int64_t) val)
#define abs(val) abslf(val)

#ifdef __cplusplus
extern "C" {
#endif

int8_t _absi8(int8_t val);
int16_t _absi16(int16_t val);
int32_t _absi32(int32_t val);
int64_t _absi64(int64_t val);
    
void _absf(uint8_t* ptr);

float absf(float val);
double abslf(double val);
//long double absllf(long double val);

#ifdef __cplusplus
}
#endif

#endif /* ABS_H */


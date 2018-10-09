#include <system.h>

void * memset(void *dest, int val, size_t n)
{
    val &= 0xFF;
    void *r = dest;
    uint32_t v32 = val << 24 | val << 16 | val << 8 | val;
    
    while(n >= 4)
    {
        *(uint32_t*) dest = v32;
        dest += 4;
        n -= 4;
    }

    while(n > 0)
    {
        *(uint8_t*) dest = val;
        dest++;
        n--;
    }
    return r;
}

int32_t _absi32(int32_t val)
{
    register int32_t t = val >> 31;
    return (val ^ t) - t;
}
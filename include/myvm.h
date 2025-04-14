#ifndef INC__MY_VM__H
#define INC__MY_VM__H

#include <device/cpu.h>
#include <stdio.h>

namespace lc3
{
    void read_image(memory __restrict__ __memory, FILE* __restrict__ __stream)
    {
        u16 org;
        fread(&org, 2, 1, __stream);
        org = little_endian_16(org);

        u16* ptr = __memory + org;
        u16 size = fread(ptr, 2, UINT16_MAX-org, __stream);
        while (size--)
        {
            *ptr = little_endian_16(*ptr);
            ++ptr;
        }
    }

    bool read_image(memory __restrict__ __memory, const char * const __path)
    {
        FILE* file = fopen(__path, "rb");
        if (!file) return false;
        read_image(__memory, file);
        fclose(file);
        return true;
    }
} // namespace lc3


#endif
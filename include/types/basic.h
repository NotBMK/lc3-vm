#ifndef INC__MYVM_TYPES__H
#define INC__MYVM_TYPES__H

#include <stdint.h>

namespace lc3
{
    using u08 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using s08 = int8_t;
    using s16 = int8_t;
    using s32 = int32_t;
    using s64 = int64_t;

    // @tparam __Bits will be extend to 16 bits
    template <u16 __Bits>
    u16 sign_extend(u16 __value)
    {
        if ((__value) & (1 << (__Bits-1)))
        {
            __value |= (0xFFFF << __Bits);
        }
        return __value;
    }

    u16 little_endian_16(u16 __big_endian)
    {
        return (__big_endian << 8) | (__big_endian >> 8);
    }
    
} // namespace lc3


#endif
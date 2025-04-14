#ifndef INC__MYVM_MEMORY__H
#define INC__MYVM_MEMORY__H

#include <types/basic.h>

namespace lc3
{
    // 64K * 2 byte = 128 KB
    using memory = u16[65536];

    enum
    {
        KBSR = 0xFE00,
        KBDR = 0xFE02,
    };
} // namespace lc3


#endif
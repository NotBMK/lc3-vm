#ifndef INC__MYVM_REGISTER__H
#define INC__MYVM_REGISTER__H

#include <types/basic.h>

namespace lc3
{
    enum RegisterID
    {
        // custom register
        R0, R1, R2, R3, R4, R5, R6, R7,
        PC, // program counter
        COND, // condition
        REGISTER_AMOUNT,
    };

    enum Flag
    {
        POS = 1,
        ZERO = 2,
        NEG = 4
    };

    using register_list = u16[REGISTER_AMOUNT];
} // namespace lc3

#endif // INC__MYVM_REGISTER__H
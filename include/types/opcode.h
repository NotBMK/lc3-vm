#ifndef INC__MYVM_OP_CODE__H
#define INC__MYVM_OP_CODE__H

#include <types/basic.h>

namespace lc3
{
    enum OpCode
    {
        // branch
        BR,
        // add
        ADD,
        // load
        LD,
        // store
        ST,
        // jump subroutine
        JSR,
        // and
        AND,
        // load register
        LDR,
        // store register
        STR,
        // unused
        RTI,
        // not
        NOT,
        // load indirect
        LDI,
        // store indirect
        STI,
        // jump
        JMP,
        // reserved
        RES,
        // load effective address
        LEA,
        // execute trap
        TRAP,

        OPCODE_AMOUNT,
    };

    enum TrapVector
    {
        GETC = 0x20,
        OUT = 0x21,
        PUTS = 0x22,
        IN = 0x23,
        PUTSP = 0x24,
        HALT = 0x25,
    };

    template <OpCode __Inst = OPCODE_AMOUNT>
    union opcode;

    template <>
    union opcode<BR>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 9;
            u16 CD  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<ADD>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 SR2 : 5;
            u16 IMM : 1;
            u16 SR1 : 3;
            u16 DR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<LD>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 9;
            u16 DR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<ST>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 9;
            u16 SR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<JSR>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 11;
            u16 MD  :  1;
            u16 OP  :  4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<AND>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 SR2 : 5;
            u16 IMM : 1;
            u16 SR1 : 3;
            u16 DR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<LDR>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 6;
            u16 BS  : 3;
            u16 DR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<STR>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 6;
            u16 BS  : 3;
            u16 SR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<NOT>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 UD  : 6; // unused
            u16 SR  : 3;
            u16 DR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<LDI>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 9;
            u16 DR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<STI>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 9;
            u16 SR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<JMP>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 UD2 : 6; // unused
            u16 BS  : 3;
            u16 UD1 : 3; // unused
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<LEA>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 OF  : 9;
            u16 DR  : 3;
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

    template <>
    union opcode<TRAP>
    {
        opcode(u16 __value)
        : value(__value)
        { }

    public:

        struct
        {
            u16 TV  : 8; // trap vector
            u16 UD  : 4; // unused
            u16 OP  : 4;
        };

    private:

        u16 value;
    };

} // namespace lc3

#endif
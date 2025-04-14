#ifndef INC__MYVM_CPU__H
#define INC__MYVM_CPU__H

#include <device/memory.h>
#include <types/opcode.h>
#include <types/register.h>
#include <conio.h>

namespace lc3
{
    
class CPU
{
public:

    void debug()
    {
        fprintf(stderr,
            "R0 %04X, R1 %04X, R2 %04X, R3 %04X, "
            "R4 %04X, R5 %04X, R6 %04X, R7 %04X\n"
            "PC %04X\n",
            regs[R0], regs[R1], regs[R2], regs[R3],
            regs[R4], regs[R5], regs[R6], regs[R7],
            regs[PC]);
    }
    
    // current context (registers)
    u16* context()
    {
        return regs;
    }

    void execute(u16 __cycles, memory __memory)
    {
        u16 cycles{0};
        while (cycles < __cycles)
        {
            u16 inst = _M_mem_get(__memory, regs[PC]++);
            ++cycles;
            switch (inst >> 12)
            {
            case BR:
            {
                opcode<BR>* op = reinterpret_cast<opcode<BR>*>(&inst);
                if (op->CD & regs[COND])
                {
                    regs[PC] += sign_extend<9>(op->OF);
                }
            } break;

            case ADD:
            {
                opcode<ADD>* op = reinterpret_cast<opcode<ADD>*>(&inst);
                regs[op->DR] = regs[op->SR1] + (op->IMM ? sign_extend<5>(op->SR2) : regs[op->SR2 & 0x7]);
                _M_update_flags(op->DR);
            } break;

            case LD:
            {
                opcode<LD>* op = reinterpret_cast<opcode<LD>*>(&inst);
                regs[op->DR] = _M_mem_get(__memory, regs[PC] + op->OF);
                _M_update_flags(op->DR);
            } break;

            case ST:
            {
                opcode<ST>* op = reinterpret_cast<opcode<ST>*>(&inst);
                _M_mem_set(__memory, regs[PC] + op->OF, regs[op->SR]);
            } break;

            case JSR:
            {
                opcode<JSR>* op = reinterpret_cast<opcode<JSR>*>(&inst);
                regs[R7] = regs[PC];
                if (op->MD)
                {
                    regs[PC] += op->OF; // JSR
                }
                else
                {
                    regs[PC] = regs[(op->OF>>6)&0x7]; // JSRR
                }
                
            } break;

            case AND:
            {
                opcode<AND>* op = reinterpret_cast<opcode<AND>*>(&inst);
                regs[op->DR] = regs[op->SR1] & (op->IMM ? sign_extend<5>(op->SR2) : regs[op->SR2 & 0x7]);
                _M_update_flags(op->DR);
            } break;

            case LDR:
            {
                opcode<LDR>* op = reinterpret_cast<opcode<LDR>*>(&inst);
                regs[op->DR] = _M_mem_get(__memory, regs[op->BS] + sign_extend<6>(op->OF));
                _M_update_flags(op->DR);
            } break;

            case STR:
            {
                opcode<STR>* op = reinterpret_cast<opcode<STR>*>(&inst);
                _M_mem_set(__memory, regs[op->BS] + sign_extend<6>(op->OF), regs[op->SR]);
            } break;

            case NOT:
            {
                opcode<NOT>* op = reinterpret_cast<opcode<NOT>*>(&inst);
                regs[op->DR] = ~regs[op->SR];
                _M_update_flags(op->DR);
            } break;

            case LDI:
            {
                opcode<LDI>* op = reinterpret_cast<opcode<LDI>*>(&inst);
                regs[op->DR] = _M_mem_get(__memory, _M_mem_get(__memory, regs[PC] + sign_extend<9>(op->OF)));
                _M_update_flags(op->DR);
            } break;

            case STI:
            {
                opcode<STI>* op = reinterpret_cast<opcode<STI>*>(&inst);
                _M_mem_set(__memory, _M_mem_get(__memory, regs[PC] + sign_extend<9>(op->OF)), regs[op->SR]);
            } break;

            case JMP:
            {
                opcode<JMP>* op = reinterpret_cast<opcode<JMP>*>(&inst);
                regs[PC] = regs[op->BS];
            } break;

            case LEA:
            {
                opcode<LEA>* op = reinterpret_cast<opcode<LEA>*>(&inst);
                regs[op->DR] = regs[PC] + sign_extend<9>(op->OF);
                _M_update_flags(op->DR);
            } break;

            case TRAP:
            {
                opcode<TRAP>* op = reinterpret_cast<opcode<TRAP>*>(&inst);
                switch (op->TV)
                {
                case GETC:
                {
                    u16 ch = getchar();
                    regs[R0] = ch;
                    _M_update_flags(R0);
                } break;

                case OUT:
                {
                    putc((char)regs[R0], stdout);
                    fflush(stdout);
                } break;

                case PUTS:
                {
                    u16* str = __memory + regs[R0];
                    while (*str)
                    {
                        putc((char)(*(str++)), stdout);
                    }
                    fflush(stdout);
                } break;

                case IN:
                {
                    printf("Enter a charactor: ");
                    char c = getchar();
                    putc(c, stdout);
                    regs[R0] = sign_extend<8>(c);
                    _M_update_flags(R0);
                } break;

                case PUTSP:
                {
                    char* str = reinterpret_cast<char*>(__memory + regs[R0]);
                    while (*str)
                    {
                        putc(*(str++), stdout);
                    }
                    fflush(stdout);
                } break;

                case HALT:
                {
                    puts("HALT");
                    fflush(stdout);
                    throw 0;
                } break;

                default:
                {
                    fprintf(stderr, "%s 0x%02X\n", "trap in", op->TV);
                    regs[R7] = regs[PC];
                    regs[PC] = op->TV;
                } break;
                }
            } break;

            default:
            {
                fprintf(stderr, "%s 0x%04X as [%02X:%02X]\n", "unhandled opcode", inst, (unsigned char)((regs[PC]-1)>>8), (unsigned char)((regs[PC]-1)));
            } break;

            }
        }
    }

protected:

    bool _M_check_key()
    {
        return _kbhit();
    }

    void _M_mem_set(memory __memory, u16 __address, u16 __value)
    {
        __memory[__address] = __value;
    }

    u16 _M_mem_get(memory __memory, u16 __address)
    {
        if (__address == KBSR)
        {
            if (_M_check_key())
            {
                __memory[KBSR] = (1 << 15);
                __memory[KBDR] = getchar();
            }
            else
            {
                __memory[KBSR] = 0;
            }
        }
        return __memory[__address];
    }

    void _M_update_flags(u16 __reg_id)
    {
        if (regs[__reg_id] == 0)
            regs[COND] = ZERO;
        else
        if (regs[__reg_id] & 0x8000)
            regs[COND] = NEG;
        else
            regs[COND] = POS;
    }

protected:

    register_list regs;
};

} // namespace lc3


#endif
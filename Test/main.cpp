#include <iostream>

#include <myvm.h>
#include <cstring>

int main(int argc, char const *argv[])
{
    std::cout << "execute from " << argv[0] << '\n';
    lc3::memory mem;
    lc3::CPU cpu;

    if (argc <= 1) return 0;

    memset(mem, 0, sizeof(mem));

    if (!lc3::read_image(mem, argv[1])) return 0;

    try
    {
        while (true)
        {
            cpu.execute(1, mem);
        }
    }
    catch(int exit_code)
    {
        fprintf(stderr, "exit with code %d\n", exit_code);
    }

    return 0;
}
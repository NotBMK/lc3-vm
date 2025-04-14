# lc3-vm (header-only)
简单的LC-3虚拟机实现

# Usage
```cpp
#include <myvm.h>

int main()
{
    lc3::memory mem;
    lc3::CPU cpu;

    // load image from disk
    if (lc3::read_image(mem, "your/path/to/image_file"))
    {
        lc3::u16 time_slice = 16;
        try
        {
            while (true)
            {
                // time slice = 16
                cpu.execute(time_slice, mem);
                // do something...
                // cpu.debug() or break_points ...
            }
        }
        catch (int exit_code) // exit from 'HALT'
        {
            printf("%s %d\n", "LC-3 VM exit with value", exit_code);
        }
    }

    return 0;
}
```


#pragma once

#if defined(__unix__) || defined(__APPLE__) || defined(__MACH__)
#define rand_ rand
#endif

#if defined(_WIN32)
int rand_()
{
    int x;
    x = (rand_() & 0xff);
    x |= ((rand_() & 0xff) << 8);
    x |= ((rand_() & 0xff) << 16);
    x |= ((rand_() & 0xff) << 24);
    return x;
}
#endif


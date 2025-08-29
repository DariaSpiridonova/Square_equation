#ifndef MY_ASSRT
#define MY_ASSRT

void my_assert(const char * str, const char * file, int line, const char * warning, ...);

#define MY_ASSERT(e, warning, ...) \
    if(!(e)) \
    { \
        my_assert(#e, __FILE__, __LINE__, warning, __VA_ARGS__); \
    }
#endif

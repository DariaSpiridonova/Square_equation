#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define d(e) #e

void my_assert(bool e)
{
    printf("%s %d", d(5 + 4), __LINE__);
}

int main()
{
    assert(0 > 5);
}
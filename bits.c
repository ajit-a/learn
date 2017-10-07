#include <stdio.h>
void main()
{
    struct abc
    {
        char a: 3;
        char b: 3;
        char c: 1;
    };
    struct abc s = {2, -6, 1};
    printf ("%d %d %d", s.a, s.b, s.c);
    return 0;
}

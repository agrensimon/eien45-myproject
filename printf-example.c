#include <stdio.h>

int main()
{
    int x = 17;
    int y = 428;
    int z = 1;
    double f = 13.37;
    double g = 1234.56789;
    char *s1 = " hej ";
    char *s2 = " hopp ";
    char b = 0b10100101;
    unsigned char ub = 0b10100101;
    printf("x == %d\n", x);
    printf("%x, %#X, %.4X, %d %u\n", x, x, x, x, x);
    printf("y == %d\n", y);
    printf("%x, %#X, %.4X, %d %u\n", y, y, y, y, y);
    printf("%#10x, %10.2x, %s\n", x, x, s1);
    printf("%#10x, %10.2x, %s\n", y, y, s2);
    printf("%#10x, %10.2x, %s\n", z, z, " literal ");
    printf("%f, %.2f, %2.2f\n", f, f, f);
    printf("%f, %.9f, %2.2f\n", g, g, g);
    // note the difference between signed and unsigned .
    printf("%x, %d, %u \n", b, b, b);
    printf("%x, %d, %u \n", ub, ub, ub);
    printf("%x, %d, %u \n", (unsigned char)b, (unsigned char)b, (unsigned char)b);
}
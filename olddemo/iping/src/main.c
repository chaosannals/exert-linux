#include <stdio.h>



int main()
{
    char ips[255][15];

    for (int i = 1; i < 255; ++i)
    {
        sprintf(ips[i], "192.168.0.%d", i);
        printf("ip: %s\n", ips[i]);
    }
    return 0;
}
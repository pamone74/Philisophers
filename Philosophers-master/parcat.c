#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
int main(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    printf("Seconds since Jan. 1, 1970: %ld\n", tv.tv_sec);

}
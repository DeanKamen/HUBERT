#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "HLS/math.h"
#include "expHBU.h"


component uint8_t executeexp(uint8_t exponent)
{
    return expHBU(exponent);
}
component uint8_t executeexp_basic(uint8_t exponent)
{
    return exp(exponent);
}

int main()
{   
    uint8_t exponent = 3;
    uint8_t result = executeexp(exponent);
    printf("result %d", result);
}

#include <stdint.h>
#include "HLS/math.h"

#ifdef __cplusplus
extern "C" {
#endif
	//int geluHBU(int input, int b, int c, int shift); //this is the correct version
	int geluHBU(int input);
	int int_erf(int input, int b, int c);
#ifdef __cplusplus
}
#endif

#include "filters.h"
short low_pass[NUM_COEFFS_1] = {
#include "lopass.h"
};

short band_pass[NUM_COEFFS_2] = {
#include "hipass.h"
};

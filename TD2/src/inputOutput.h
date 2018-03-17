#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include <mpfr.h>

#include "utils.h"

int readFromFile(const char* fileName, mpfr_t arrayToFill[], mpfr_t cond);

#endif /* INPUT_OUTPUT_H */

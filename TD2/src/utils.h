#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <mpfr.h>

char * buildFileName(int ordreGrandeur, int idFile);

void array_init(const size_t x, mpfr_t (**aptr)[x], const mpfr_prec_t precision);

void matrix_init(const size_t x, const size_t y, mpfr_t (**aptr)[x][y],
		const mpfr_prec_t precision);

void three_dimensions_array_init(const size_t x, const size_t y, const size_t z,
		mpfr_t (**aptr)[x][y][z], const mpfr_prec_t precision);

void freeMatrix(const size_t m, const size_t n, mpfr_t (*matrix)[m][n]);

void free3DArray(const size_t m, const size_t n, const size_t o,
		mpfr_t (*arrayToFree)[m][n][o]);

char** str_split(char* a_str, const char a_delim);

void cfree(void * ptr);

#endif // UTILS_H

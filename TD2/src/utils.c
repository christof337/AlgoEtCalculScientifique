#include "utils.h"

#include <stdio.h>
#include <mpfr.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// the fileName are in the format "TD2-File01-N100-C10e3.txt"
// so : "TD2-File≤idFile>-N100-C10e<ordreGrandeur>.txt"
const char * FULL_FILE_NAME_SAMPLE = "data2018/TD2-File01-N100-C10e3.txt";
const char * FOLDER = "data2018";
const char * PREFIX = "TD2-File";
const char * SUFFIX = "-N100-C10e";
const char * EXTENSION = ".txt";

/**
 * Build and returns the file name corresponding to the given magnitude and fileId.
 * The template is defined as const char *.
 * The resulting variable should be freed afterwards
 */
char * buildFileName(int ordreGrandeur, int idFile) {
	char * fileName;
	fileName = malloc(sizeof(char) * strlen(FULL_FILE_NAME_SAMPLE));
	if (idFile < 10) {
		sprintf(fileName, "%s/%s0%1d%s%1d%s", FOLDER, PREFIX, idFile, SUFFIX,
				ordreGrandeur, EXTENSION);
	} else {
		sprintf(fileName, "%s/%s%1d%s%1d%s", FOLDER, PREFIX, idFile, SUFFIX,
				ordreGrandeur, EXTENSION);
	}
	return fileName;
}

/**
 * Allocate then initialize at the given precision the given array
 */
void array_init(const size_t x, mpfr_t (**aptr)[x], const mpfr_prec_t precision) {
	*aptr = malloc(sizeof(mpfr_t[x])); // allocate a true array
	assert(*aptr != NULL);
	for (size_t i = 0; i < x; i++) {
		mpfr_init2((**aptr)[i], precision);
	}
}

/**
 * Allocate then initialize at the given precision the given matrix.
 */
void matrix_init(const size_t x, const size_t y, mpfr_t (**aptr)[x][y],
		const mpfr_prec_t precision) {
	*aptr = malloc(sizeof(mpfr_t[x][y])); // allocate a true 2D array
	assert(*aptr != NULL);
	for (size_t i = 0; i < x; ++i) {
		for (size_t j = 0; j < y; ++j) {
			mpfr_init2((**aptr)[i][j], precision);
		}
	}
}

/**
 * Allocate then initialize at the given precision the given 3Darray
 */
void three_dimensions_array_init(const size_t x, const size_t y, const size_t z,
		mpfr_t (**aptr)[x][y][z], const mpfr_prec_t precision) {
	*aptr = malloc(sizeof(mpfr_t[x][y][z])); // allocate a true 3D array
	assert(*aptr != NULL);
	for (size_t i = 0; i < x; ++i) {
		for (size_t j = 0; j < y; ++j) {
			for (size_t k = 0; k < z; ++k) {
				mpfr_init2((**aptr)[i][j][k], precision);
			}
		}
	}
}

/**
 * Free the matrix `matrix`
 *
 * @param      matrix  The matrix to free
 * @param[in]  m       number of rows
 * @param[in]  n       number of columns
 */
void freeMatrix(const size_t m, const size_t n, mpfr_t (*matrix)[m][n]) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			mpfr_clear((*matrix)[i][j]);
		}
	}
	cfree(matrix);
}

/**
 * Free the 3D array `arrayToFree`
 *
 * @param      arrayToFree  The 3d array to free
 * @param[in]  m       number of rows
 * @param[in]  n       number of columns
 * @param[in]  o       size of 3rd dimension
 */
void free3DArray(const size_t m, const size_t n, const size_t o,
		mpfr_t (*arrayToFree)[m][n][o]) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < o; ++k) {
				mpfr_clear((*arrayToFree)[i][j][k]);
			}
		}
	}
	cfree(arrayToFree);
}

/**
 * Split the string `a_str` with the given delimiter
 * @param a_str		The string to split
 * @param a_delim	The delimiter around which split
 * @return			An array of strings, splitted from a_str with a_delim
 */
char** str_split(char* a_str, const char a_delim) {
	char** result = 0;
	size_t count = 0;
	char* tmp = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp) {
		if (a_delim == *tmp) {
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
	 knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result) {
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token) {
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

/**
 * Unnecessary verification.
 */
void cfree(void * ptr) {
	if (ptr) {
		free(ptr);
	}
}

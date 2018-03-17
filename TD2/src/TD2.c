/*
 ============================================================================
 Name        : TD2.c
 Author      : Christophe Pont
 Version     : 1.1
 Copyright   : MIT License
 Description : TD2
 ============================================================================
 */

/*
 * Use `-lmpfr -lgmp` in the compilation
 * gcc src/TD2.c src/utils.h src/utils.c src/inputOutput.h src/inputOutput.c -o TD2.out -lmpfr -lgmp
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

#include "inputOutput.h"

#define PRECISION 53

/**
 * Get to know if MPFR is properly installed.
 */
void testMPFR(void) {
	// if this lines compile and prints well, then MPFR is properly installed ; plus you get to know which version you are using.
	printf("\nMPFR library: %-12s\nMPFR header:  %s (based on %d.%d.%d)\n",
			mpfr_get_version(), MPFR_VERSION_STRING, MPFR_VERSION_MAJOR,
			MPFR_VERSION_MINOR, MPFR_VERSION_PATCHLEVEL);
}

const int NB_OGC = 11;
const int NB_JDD_PER_OGC = 4;
const int ordreGrandeurCondLogArray[] = { 3, 6, 9, 12, 15, 16, 18, 20, 24, 28,
		32 };
const int EXPECTED_FLOATS_PER_FILE = 100;

void getArraysFromDataFiles(const size_t l, const size_t m, const size_t n,
		mpfr_t arrayFloats[l][m][n], mpfr_t arrayCond[l][m]) {
	char * currentFileName;

	// reading the files for each magnitude
	for (int i = 0; i < l; ++i) {
		// reading the files for each dataset
		for (int j = 1; j <= m; ++j) {
			int valOrdreGrandeur = ordreGrandeurCondLogArray[i];
			currentFileName = buildFileName(valOrdreGrandeur,
					j + i * NB_JDD_PER_OGC);

			readFromFile(currentFileName, arrayFloats[i][j - 1],
					arrayCond[i][j - 1]);

			cfree(currentFileName);
		}
	}
}

int main(void) {
	int out = EXIT_SUCCESS;
	printf("\nProgram start\n");
	mpfr_t (*arrayFloats)[NB_OGC][NB_JDD_PER_OGC][EXPECTED_FLOATS_PER_FILE];
	mpfr_t (*arrayCond)[NB_OGC][NB_JDD_PER_OGC];

	three_dimensions_array_init(NB_OGC, NB_JDD_PER_OGC,
			EXPECTED_FLOATS_PER_FILE, &arrayFloats, PRECISION);
	matrix_init(NB_OGC, NB_JDD_PER_OGC, &arrayCond, PRECISION);

	// begin
	getArraysFromDataFiles(NB_OGC, NB_JDD_PER_OGC, EXPECTED_FLOATS_PER_FILE,
			*arrayFloats, *arrayCond);

	// end
	free3DArray(NB_OGC, NB_JDD_PER_OGC, EXPECTED_FLOATS_PER_FILE, arrayFloats);
	freeMatrix(NB_OGC, NB_JDD_PER_OGC, arrayCond);

	printf("\nExiting\n");

	return out;
}

/*
 ============================================================================
 Name        : TD2.c
 Author      : Christophe Pont
 Version     : 1.2
 Copyright   : MIT License
 Description : TD2 : accuracy and sums
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
#define PRECISION_LARGE 200

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
	mpfr_t (*arraySum)[NB_OGC][NB_JDD_PER_OGC];
	mpfr_t cond;
	mpfr_init2(cond, PRECISION);

	three_dimensions_array_init(NB_OGC, NB_JDD_PER_OGC,
			EXPECTED_FLOATS_PER_FILE, &arrayFloats, PRECISION);
	matrix_init(NB_OGC, NB_JDD_PER_OGC, &arrayCond, PRECISION);
	matrix_init(NB_OGC, NB_JDD_PER_OGC, &arraySum, PRECISION);

	// begin
	getArraysFromDataFiles(NB_OGC, NB_JDD_PER_OGC, EXPECTED_FLOATS_PER_FILE,
			*arrayFloats, *arrayCond);

	for (int indOG = 0; indOG < NB_OGC; ++indOG) {
		for (int j = 0; j < NB_JDD_PER_OGC; ++j) {
			// the value of the magnitude is in valOrdreGrandeur (3,6...)
			int valOrdreGrandeur = ordreGrandeurCondLogArray[indOG];
			// indFile is the id of the file
			int indFile = indOG * NB_JDD_PER_OGC + (j + 1);
			// the content of the current file is in `array`, with EXPECTED_FLOATS_PER_FILE floats in it
			mpfr_t * array = (*arrayFloats)[indOG][j];
			mpfr_set(cond, (*arrayCond)[indOG][j], MPFR_RNDN);

			mpfr_t sum;
			mpfr_init2(sum, PRECISION_LARGE);
			mpfr_set_str(sum, "0", 10, MPFR_RNDN);
			for (int i = 0; i < EXPECTED_FLOATS_PER_FILE; ++i) {
				mpfr_add(sum, sum, array[i], MPFR_RNDN);
			}

			printf("\nThe file %s ", buildFileName(valOrdreGrandeur, indFile));
			printf("contains %d values in `array` ", EXPECTED_FLOATS_PER_FILE);
			mpfr_printf(", the conditionning is %Re", cond);
			mpfr_printf("and the sum might be %Re", sum);

			mpfr_clear(sum);
		}
	}

	// end
	free3DArray(NB_OGC, NB_JDD_PER_OGC, EXPECTED_FLOATS_PER_FILE, arrayFloats);
	freeMatrix(NB_OGC, NB_JDD_PER_OGC, arrayCond);
	mpfr_clear(cond);

	printf("\nExiting\n");

	return out;
}

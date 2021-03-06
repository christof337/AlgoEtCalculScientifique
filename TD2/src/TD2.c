/*
 ============================================================================
 Name        : TD2.c
 Author      : Christophe Pont
 Version     : 1.3
 Copyright   : MIT License
 Description : TD2 : accuracy and sums
 ============================================================================
 */

/*
 * Use `-lmpfr -lgmp` in the compilation
 * gcc src/TD2.c src/utils.h src/utils.c src/inputOutput.h src/inputOutput.c src/summations.c src/summations.h -o TD2.out -lmpfr -lgmp
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

#include "inputOutput.h"

#define PRECISION 53
#define PRECISION_LARGE 200

// number of magnitude treated
const int NB_OGC = 11;
// number of file per magnitude
const int NB_JDD_PER_OGC = 4;
const int ordreGrandeurCondLogArray[] = { 3, 6, 9, 12, 15, 16, 18, 20, 24, 28,
		32 };
// number of lines in files
const int EXPECTED_FLOATS_PER_FILE = 100;

/**
 * Put in arrayFloats and arrayCond all the lines (resp condition number) of the
 */
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
	// INITIALIZATIONS
	// on utilise des pointeurs sur tableaux, pensez à mettre `(*<arrayEnQuestion>)` lors de l'accès
	mpfr_t (*arrayFloats)[NB_OGC][NB_JDD_PER_OGC][EXPECTED_FLOATS_PER_FILE];
	mpfr_t (*arrayCond)[NB_OGC][NB_JDD_PER_OGC];
	mpfr_t (*arraySum)[NB_OGC][NB_JDD_PER_OGC];
	mpfr_t cond;
	mpfr_init2(cond, PRECISION);
	mpfr_t sum;
	mpfr_init2(sum, PRECISION_LARGE);

	// ALLOCATIONS + MPFR_INIT
	three_dimensions_array_init(NB_OGC, NB_JDD_PER_OGC,
			EXPECTED_FLOATS_PER_FILE, &arrayFloats, PRECISION);
	matrix_init(NB_OGC, NB_JDD_PER_OGC, &arrayCond, PRECISION);
	matrix_init(NB_OGC, NB_JDD_PER_OGC, &arraySum, PRECISION);

	// getting the arrays from the files
	getArraysFromDataFiles(NB_OGC, NB_JDD_PER_OGC, EXPECTED_FLOATS_PER_FILE,
			*arrayFloats, *arrayCond);

	// MAIN LOOP
	for (int indOG = 0; indOG < NB_OGC; ++indOG) {
		for (int j = 0; j < NB_JDD_PER_OGC; ++j) {
			// the value of the magnitude is in valOrdreGrandeur (3,6...)
			int valOrdreGrandeur = ordreGrandeurCondLogArray[indOG];
			// indFile is the id of the file
			int indFile = indOG * NB_JDD_PER_OGC + (j + 1);
			// the content of the current file is in `array`, with EXPECTED_FLOATS_PER_FILE floats in it
			mpfr_t * array = (*arrayFloats)[indOG][j];
			// the first value of `array` is `array[0]` (and not `(*array)[0]`)

			mpfr_set(cond, (*arrayCond)[indOG][j], MPFR_RNDN);
			// computing the sum here

			// ...

			// uncomment next line when the sum is computed
//			mpfr_set((*arraySum)[indOG][j], sum, MPFR_RNDN);

			printf("\nThe file %s ", buildFileName(valOrdreGrandeur, indFile));
			printf("contains %d values in `array`, ", EXPECTED_FLOATS_PER_FILE);
			mpfr_printf("its condition number is %Re ", cond);
			// uncomment next line when the sum is computed
//			mpfr_printf("and the sum is %Re", (*arraySum)[indOG][j]);
			// or
//			mpfr_out_str(stdout,10,0,(*arraySum)[indOG][j],MPFR_RNDN);
		}
	}

	// end
	// free arrays
	free3DArray(NB_OGC, NB_JDD_PER_OGC, EXPECTED_FLOATS_PER_FILE, arrayFloats);
	freeMatrix(NB_OGC, NB_JDD_PER_OGC, arrayCond);
	freeMatrix(NB_OGC, NB_JDD_PER_OGC, arraySum);
	mpfr_clear(cond);
	mpfr_clear(sum);

	printf("\nExiting\n");

	return out;
}

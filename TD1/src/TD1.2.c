/*
 ============================================================================
 Name        : TD1.2.c
 Author      : Christophe Pont
 Version     : 1.0
 Copyright   : MIT License
 Description : Exercise 2 of TD1 : Getting a grip on rounding modes with inverse factorial summations
 ============================================================================
 */

/*
 * Use `-lmpfr -lgmp` in the compilation
 * gcc src/TD1.2.c -o TD1.2 -lmpfr -lgmp
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

/** Even a float can't hold !35. **/
#define NB_FACT 35

#define PRECISION 200

/**
 * Get to know if MPFR is properly installed.
 */
void testMPFR(void) {
	// if this lines compile and prints well, then MPFR is properly installed ; plus you get to know which version you are using.
	printf("\nMPFR library: %-12s\nMPFR header:  %s (based on %d.%d.%d)\n",
			mpfr_get_version(), MPFR_VERSION_STRING, MPFR_VERSION_MAJOR,
			MPFR_VERSION_MINOR, MPFR_VERSION_PATCHLEVEL);
}

/**
 * Returns the factorial of a given double.
 */
double factD(double n) {
	if (n == 0)
		return 1;
	return n * factD(n - 1);
}

/**
 * Depending on the given rounding mode, computes the sum of the inverse of the factorial of the X first integers with MPFR, and print them.
 */
int computeSumInverseFact(mpfr_rnd_t roundingMode) {
	// declarations
	mpfr_t s, t, u;
	// initializations
	mpfr_inits2(PRECISION, t, s, u, (mpfr_ptr) NULL);
	mpfr_set_d(t, 1.0, roundingMode);
	mpfr_set_d(s, 1.0, roundingMode);

	for (unsigned int i = 1; i <= 200; ++i) {
		mpfr_mul_ui(t, t, i, roundingMode);
		mpfr_set_d(u, 1.0, roundingMode);
		mpfr_div(u, u, t, roundingMode);
		mpfr_add(s, s, u, roundingMode);
	}

	mpfr_out_str(stdout, 10, 0, s, roundingMode);
	putchar('\n');
	mpfr_clears(s, t, u, (mpfr_ptr) NULL);

	return EXIT_SUCCESS;
}

/**
 * Compute the sum of the inverse of the factorial of the X first integers in double precision.
 */
int computeSumInverseFactDouble(void) {
	double sumDouble = 1; 				// 171! is Inf

	for (unsigned int i = 1; i <= 200; ++i) {
		sumDouble += 1 / factD(i);
	}

	printf("\nDouble sum is : %f", sumDouble);

	return EXIT_SUCCESS;
}

/**
 * Computes the SumInverseFact for each rounding mode given by MPFR.
 */
int exercise2(void) {
	//	MPFR_RNDN=0,  /* round to nearest, with ties to even */
	//  MPFR_RNDZ,    /* round toward zero */
	//  MPFR_RNDU,    /* round toward +Inf */
	//  MPFR_RNDD,    /* round toward -Inf */
	//  MPFR_RNDA,    /* round away from zero */
	//  MPFR_RNDF,    /* faithful rounding (not implemented yet) */
	//  MPFR_RNDNA=-1 /* round to nearest, with ties away from zero (mpfr_round) */
	printf("Round to nearest, with ties to even\t");
	computeSumInverseFact(MPFR_RNDN);
	printf("Round toward zero\t\t\t");
	computeSumInverseFact(MPFR_RNDZ);
	printf("Round toward +Inf\t\t\t");
	computeSumInverseFact(MPFR_RNDU);
	printf("Round toward -Inf\t\t\t");
	computeSumInverseFact(MPFR_RNDD);
	printf("Round away from zero\t\t\t");
	computeSumInverseFact(MPFR_RNDA);

	return EXIT_SUCCESS;
}

int exercise4(void) {
	const long int size = 5000;

	printf("\nBefore init\n");

	mpfr_t (**tab)[size][size];
	tab = malloc(sizeof(mpfr_t*[size][size]));
	*tab = malloc(sizeof(mpfr_t[size][size]));

	// for information, a matrix of double can easily handle this process
	// until 50000 rows and columns (if you have enough RAM).
//	double (**tabD)[size][size];
//	tabD = malloc(sizeof(double*[size][size]));
//	*tabD = malloc(sizeof(double[size][size]));

	printf("After init\n");

	for (long int i = 0; i < size; ++i) {
		for (long int j = 0; j < size; ++j) {
//			(**tabD)[i][j] = i*j;

			mpfr_init2((**tab)[i][j], 20000);
			mpfr_set_si((**tab)[i][j], i * j, MPFR_RNDU);
		}
	}

	printf("After set\n");
	//	getchar();

	for (long int i = 0; i < size; ++i) {
		for (long int j = 0; j < size; ++j) {
			mpfr_clear((**tab)[i][j]);
		}
	}

	free(*tab);
	free(tab);
//	free(*tabD);
//	free(tabD);

	printf("\nAfter clear\n");

	return EXIT_SUCCESS;
}

int main(void) {
	int out = EXIT_FAILURE;

	// ex 2
	printf("\nExercise 2:\n");
	out += exercise2();

	// ex 4?
//	exercise4();

	return out;
}


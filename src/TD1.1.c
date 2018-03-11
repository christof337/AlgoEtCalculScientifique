/*
 ============================================================================
 Name        : TD1.1.c
 Author      : Christophe Pont
 Version     : 1.2
 Copyright   : MIT License
 Description : Exercise 1 of TD1 : Getting a grip on computer limits
 ============================================================================
 */

/*
 * Use `-lmpfr -lgmp` in the compilation
 * gcc src/TD1.1.c -o TD1.1 -lmpfr -lgmp
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
 * Returns the factorial of a given int.
 */
int factI(int n) {
	if (n == 0)
		return 1;
	return n * factI(n - 1);
}

/**
 * Returns the factorial of a given long int.
 */
long int factLI(long int n) {
	if (n == 0)
		return 1;
	return n * factLI(n - 1);
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
 * Returns the factorial of a given float.
 */
float factF(float n) {
	if (n == 0)
		return 1;
	return n * factF(n - 1);
}

/**
 * Print the factorial of the NB_FACT first integers, for int, long int, float and double values.
 */
int exercise1(void) {
	int factInt = 0; 					// 13! is wrong
	long int factLongInt = 0;			// 21! is wrong
	float factFloat = 0;				// 35! is Inf
	double factDouble = 0; 				// 171! is Inf

	// loop over the first integers
	for (int i = 1; i <= 35; ++i) {
		factInt = factI(i);
		factLongInt = factLI(i);
		factFloat = factF(i);
		factDouble = factD(i);
		printf(
				"Factorial of %2d is [int:]%13d\t[long int:]%20ld\t[float:] %13e\t[double:] %10e\n",
				i, factInt, factLongInt, factFloat, factDouble);
	}

	// showing the extreme values for double
	printf(
			"...\nFactorial of 170 is [double:] %e\nFactorial of 171 is [double:] %e\n",
			factD(170), factD(171));

	return EXIT_SUCCESS;
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
	float sumDouble = 1; 				// 171! is Inf

	for (unsigned int i = 1; i <= 200; ++i) {
		sumDouble += 1 / factF(i);
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

int main(void) {
	int out = EXIT_FAILURE;

	// ex 1
	printf("\nExercise 1:\n");
	out = exercise1();
	// ex 2
	printf("\nExercise 2:\n");
	out += exercise2();

	return out;
}

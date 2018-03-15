/*
 ============================================================================
 Name        : TD1.1.c
 Author      : Christophe Pont
 Version     : 1.3
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

int main(void) {
	int out = EXIT_FAILURE;

	// ex 1
	printf("\nExercise 1:\n");
	out = exercise1();

	return out;
}

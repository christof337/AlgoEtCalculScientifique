/*
 ============================================================================
 Name        : TD1.1.c
 Author      : Christophe Pont
 Version     : 1.1
 Copyright   : MIT License
 Description : Exercise 1 of TD1 : Getting a grip on computer limits
 ============================================================================
 */

/*
 * Use `-lmpfr -lgmp` in the compilation
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

int factI(int n) {
	if (n == 0)
		return 1;
	return n * factI(n - 1);
}

long int factLI(long int n) {
	if (n == 0)
		return 1;
	return n * factLI(n - 1);
}

double factD(double n) {
	if (n == 0)
		return 1;
	return n * factD(n - 1);
}

float factF(float n) {
	if (n == 0)
		return 1;
	return n * factF(n - 1);
}

int exercise1(void) {
	int factInt = 0; 					// 13! is wrong
	long int factLongInt = 0;			// 21! is wrong
	float factFloat = 0;				// 35! is Inf
	double factDouble = 0; 				// 171! is Inf

	for (int i = 1; i <= 35; ++i) {
		factInt = factI(i);
		factLongInt = factLI(i);
		factFloat = factF(i);
		factDouble = factD(i);
		printf(
				"Factorial of %2d is [int:]%13d\t[long int:]%20ld\t[float:] %13e\t[double:] %10e\n",
				i, factInt, factLongInt, factFloat, factDouble);
	}

	printf(
			"...\nFactorial of 170 is [double:] %e\nFactorial of 171 is [double:] %e\n",
			factD(170), factD(171));

	printf("\nMPFR library: %-12s\nMPFR header:  %s (based on %d.%d.%d)\n",
			mpfr_get_version(), MPFR_VERSION_STRING, MPFR_VERSION_MAJOR,
			MPFR_VERSION_MINOR, MPFR_VERSION_PATCHLEVEL);
	return EXIT_SUCCESS;
}

int exercise2_save(void) {
	float sumDouble = 1; 				// 171! is Inf
	mpfr_t s, t, u;
	mpfr_init2(t, 200);
	mpfr_set_d(t, 1.0, MPFR_RNDD);
	mpfr_init2(s, 200);
	mpfr_set_d(s, 1.0, MPFR_RNDD);
	mpfr_init2(u, 200);

	for (unsigned int i = 1; i <= 200; ++i) {
		mpfr_mul_ui(t, t, i, MPFR_RNDU);
		mpfr_set_d(u, 1.0, MPFR_RNDD);
		mpfr_div(u, u, t, MPFR_RNDD);
		mpfr_add(s, s, u, MPFR_RNDD);

		sumDouble+=1/factF(i);
	}

	printf("\nDouble sum is : %f",sumDouble);
	printf("\nMpfr sum is \t");
	mpfr_out_str(stdout, 10, 0, s, MPFR_RNDD);
	putchar('\n');
	mpfr_clear(s);
	mpfr_clear(t);
	mpfr_clear(u);

	return EXIT_SUCCESS;
}

int computeSumInverseFact(mpfr_rnd_t roundingMode) {
	float sumDouble = 1; 				// 171! is Inf
	mpfr_t s, t, u;
	mpfr_init2(t, 200);
	mpfr_set_d(t, 1.0, roundingMode);
	mpfr_init2(s, 200);
	mpfr_set_d(s, 1.0, roundingMode);
	mpfr_init2(u, 200);

	for (unsigned int i = 1; i <= 200; ++i) {
		mpfr_mul_ui(t, t, i, roundingMode);
		mpfr_set_d(u, 1.0, roundingMode);
		mpfr_div(u, u, t, roundingMode);
		mpfr_add(s, s, u, roundingMode);

		sumDouble+=1/factF(i);
	}

	printf("\nDouble sum is : %f",sumDouble);
	printf("\nMpfr sum is \t");
	mpfr_out_str(stdout, 10, 0, s, roundingMode);
	putchar('\n');
	mpfr_clear(s);
	mpfr_clear(t);
	mpfr_clear(u);

	return EXIT_SUCCESS;
}

int exercise2(void) {
	/*
	 *   MPFR_RNDN=0,  /* round to nearest, with ties to even */
//  MPFR_RNDZ,    /* round toward zero */
//  MPFR_RNDU,    /* round toward +Inf */
//  MPFR_RNDD,    /* round toward -Inf */
//  MPFR_RNDA,    /* round away from zero */
//  MPFR_RNDF,    /* faithful rounding (not implemented yet) */
//  MPFR_RNDNA=-1 /* round to nearest, with ties away from zero (mpfr_round) */
//	 */
	printf("\nround to nearest, with ties to even");
	computeSumInverseFact(MPFR_RNDN);
	printf("\nround toward zero");
	computeSumInverseFact(MPFR_RNDZ);
	printf("\nround toward +Inf");
	computeSumInverseFact(MPFR_RNDU);
	printf("\nround toward -Inf");
	computeSumInverseFact(MPFR_RNDD);
	printf("\nround away from zero");
	computeSumInverseFact(MPFR_RNDA);

	return EXIT_SUCCESS;
}

int main(void) {
	int out = EXIT_FAILURE;

	// ex 1
	out = exercise1();
	// ex 2
	out += exercise2();

	return out;
}

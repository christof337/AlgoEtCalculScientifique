/*
 ============================================================================
 Name        : TD1.2.c
 Author      : Christophe Pont
 Version     : 1.3
 Copyright   : MIT License
 Description : Exercise 2 of TD1 : Polynomial evaluation
 ============================================================================
 */

/*
 * Use `-lmpfr -lgmp -lm` in the compilation command line
 * `gcc src/TD1.2.c -o TD1.2 -lmpfr -lgmp -lm`
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>
#include <math.h>

#define DEGRE 15

// 53 is double. > 58 start to converge
#define PRECISION 57

/**
 * Declaring the polynome as an array, the first value being the coefficient with the higher degree
 * will be used in the whole program afterwards
 */
const double polynome[DEGRE + 1] = { 1, -30, 420, -3640, 21840, -96096, 320320,
		-823680, 1647360, -2562560, 3075072, -2795520, 1863680, -860160, 245760,
		-32768 };

/**
 * Evaluates the polynome by simply multiplying and adding the coefficient for a given x ; put the result in val.
 */
int evaluatePolynomeDirectly(mpfr_t val, const double xD) {
	mpfr_t s, t;
	mpfr_t x;

	mpfr_inits2(PRECISION, s, t, x, (mpfr_ptr) NULL);

	mpfr_set_d(x, xD, MPFR_RNDN);
	mpfr_set_d(val, 0.0, MPFR_RNDN);

	for (size_t i = 0; i <= DEGRE; ++i) {
		// val += pow(x, DEGRE - i) * polynome[i];
		mpfr_pow_si(s, x, DEGRE - i, MPFR_RNDN);
		mpfr_mul_d(t, s, polynome[i], MPFR_RNDN);
		mpfr_add(val, val, t, MPFR_RNDN);
	}
// equivalent to :
//	val = pow(x, 15) - 30 * pow(x, 14) + 420 * pow(x, 13) - 3640 * pow(x, 12)
//			+ 21840 * pow(x, 11) - 96096 * pow(x, 10) + 320320 * pow(x, 9)
//			- 823680 * pow(x, 8) + 1647360 * pow(x, 7) - 2562560 * pow(x, 6)
//			+ 3075072 * pow(x, 5) - 2795520 * pow(x, 4) + 1863680 * pow(x, 3)
//			- 860160 * pow(x, 2) + 245760 * pow(x, 1) - 32768;

	mpfr_clears(s, t, x, (mpfr_ptr) NULL);

	return EXIT_SUCCESS;
}

/**
 * Use horner to evaluates the polynome for the value x. Put the result in val.
 */
int evaluatePolynomeHorner(mpfr_t acc, const double xD) {
	mpfr_t x;

	mpfr_init2(x, PRECISION);

	mpfr_set_d(x, xD, MPFR_RNDN);
	mpfr_set_d(acc, polynome[0], MPFR_RNDN);

	for (size_t ind = 1; ind <= DEGRE; ++ind) {
//		acc = x * acc + polynome[ind];
		mpfr_mul(acc, acc, x, MPFR_RNDN);
		mpfr_add_d(acc, acc, polynome[ind], MPFR_RNDN);
	}

	mpfr_clear(x);

	return EXIT_SUCCESS;
}

/**
 * Evaluates the polynome this time with the factorised version, multiplication after multiplication
 * @deprecated
 */
int evaluatePolynomeMult(mpfr_t acc, const double x) {
	mpfr_set_d(acc, 1.0, MPFR_RNDN);

	for (int i = 0; i < DEGRE; ++i) {
//		acc *= x - 2;
		mpfr_mul_d(acc, acc, x - 2, MPFR_RNDN);
	}
	return EXIT_SUCCESS;
}

/**
 * Evaluates the factorised polynome, using its roots
 */
int evaluatePolynomeFactorised(mpfr_t val, const double xD) {
	mpfr_t x;

	mpfr_init2(x, PRECISION);

	mpfr_set_d(x, xD - 2, MPFR_RNDN);

	// pow(x-2,DEGRE);
	mpfr_pow_ui(val, x, DEGRE, MPFR_RNDN);

	return EXIT_SUCCESS;
}

/**
 * Print all the values of the polynome between lowerBound and upperBound (with step step), using the direct polynome evaluation method.
 */
int exercise1(const double lowerBound, const double upperBound,
		const double step) {
	mpfr_t val;

	mpfr_init2(val, PRECISION);

	for (double x = lowerBound; x < upperBound + step; x += step) {
		evaluatePolynomeDirectly(val, x);
		mpfr_printf("%f\t%RE\n", x, val);
	}

	mpfr_clear(val);

	return EXIT_SUCCESS;
}

/**
 * Print all the values of the polynome between lowerBound and upperBound (with step step), using Horner polynome evaluation method.
 */
int exercise2(const double lowerBound, const double upperBound,
		const double step) {
	mpfr_t val;

	mpfr_init2(val, PRECISION);

	for (double x = lowerBound; x < upperBound + step; x += step) {
		evaluatePolynomeHorner(val, x);
		mpfr_printf("%f\t%RE\n", x, val);
	}

	mpfr_clear(val);

	return EXIT_SUCCESS;
}

/**
 * Print all the values of the polynome between lowerBound and upperBound (with step step), using the factorised polynome.
 */
int exercise3(const double lowerBound, const double upperBound,
		const double step) {
	mpfr_t val;

	mpfr_init2(val, PRECISION);

	for (double x = lowerBound; x < upperBound + step; x += step) {
		evaluatePolynomeFactorised(val, x);
		mpfr_printf("%f\t%RE\n", x, val);
	}

	mpfr_clear(val);
	return EXIT_SUCCESS;
}

/**
 * Print all the values of the polynome between lowerBound and upperBound (with step step), using the factorised polynome (multiplication after multiplication).
 * @deprecated
 */
int exercise4(const double lowerBound, const double upperBound,
		const double step) {
	mpfr_t val;

	mpfr_init2(val, PRECISION);

	for (double x = lowerBound; x < upperBound + step; x += step) {
		evaluatePolynomeMult(val, x);
		mpfr_printf("%f\t%RE\n", x, val);
	}

	return EXIT_SUCCESS;
}

/**
 * command line :
 * `echo "m" | ./TD1.2 1> mpfr_XXX.dat`
 * m being 1, 2, 3 (or 4) for each evaluation method.
 * XXX being the filename you want for that evaluation method.
 * then simply
 * `gnuplot`
 * then
 * `plot "mpfr_direct.dat" w l, "mpfr_horner.dat" w l, "mpfr_facto.dat" w l`
 */
int main(void) {
	int out = EXIT_FAILURE;

	const double LOWER_BOUND = 1.6;
	const double UPPER_BOUND = 2.4;
	const double STEP = pow(10, -4);

	char choice = 0;

	// give the ability for the user to choose which evaluation to make.
	fprintf(stderr,
			"1 : Direct evaluation\n2 : Horner evaluation\n3 : Factorised evaluation\n4 : Singles mult\n? : ");
	scanf("%c", &choice);

	if (choice == '1') {
		out = exercise1(LOWER_BOUND, UPPER_BOUND, STEP);
	} else if (choice == '2') {
		out = exercise2(LOWER_BOUND, UPPER_BOUND, STEP);
	} else if (choice == '3') {
		out = exercise3(LOWER_BOUND, UPPER_BOUND, STEP);
	} else if (choice == '4') {
		out = exercise4(LOWER_BOUND, UPPER_BOUND, STEP);
	} else {
		fprintf(stderr, "\nWrong input.\n");
		out = EXIT_FAILURE;
	}

	fprintf(stderr, "\n");
	return out;
}

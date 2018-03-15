/*
 ============================================================================
 Name        : TD1.2.c
 Author      : Christophe Pont
 Version     : 1.0
 Copyright   : MIT License
 Description : Exercise 2 of TD1 : Polynomial evaluation
 ============================================================================
 */

/*
 * Use `-lmpfr -lgmp` in the compilation
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>
#include <math.h>

#define DEGRE 15

const double polynome[DEGRE+1] = { 1, -30, 420, -3640, 21840, -96096, 320320,
		-823680, 1647360, -2562560, 3075072, -2795520, 1863680, -860160, 245760,
		-32768 };

double evaluatePolynomeDirectly(const double x) {
	double val = 0;
	for (size_t i = 0; i <= DEGRE; ++i) {
		val += pow(x, DEGRE - i) * polynome[i];
	}
//	val = pow(x, 15) - 30 * pow(x, 14) + 420 * pow(x, 13) - 3640 * pow(x, 12)
//			+ 21840 * pow(x, 11) - 96096 * pow(x, 10) + 320320 * pow(x, 9)
//			- 823680 * pow(x, 8) + 1647360 * pow(x, 7) - 2562560 * pow(x, 6)
//			+ 3075072 * pow(x, 5) - 2795520 * pow(x, 4) + 1863680 * pow(x, 3)
//			- 860160 * pow(x, 2) + 245760 * pow(x, 1) - 32768;
	return val;
}

double evaluatePolynomeHorner(const double x) {
	double acc = polynome[0];

	for (size_t ind = 1; ind <= DEGRE; ++ind) {
		acc = x * acc + polynome[ind];
	}
	return acc;
}

double evaluatePolynomeMult(const double x) {
	double acc=1;
	for(int i = 0 ; i < DEGRE ; i++ ) {
		acc *= x-2;
	}
	return acc;
}

double evaluatePolynomeFactorised(const double x) {
	return pow(x-2,DEGRE);
}

int exercise1(const double lowerBound, const double upperBound, const double step) {
	for (double x = lowerBound; x < upperBound + step; x += step) {
		printf("%f\t%e\n", x, evaluatePolynomeDirectly(x));
	}

	return EXIT_SUCCESS;
}

int exercise2(const double lowerBound, const double upperBound, const double step) {
	for (double x = lowerBound; x < upperBound + step; x += step) {
		printf("%f\t%e\n", x, evaluatePolynomeHorner(x));
	}

	return EXIT_SUCCESS;
}

int exercise3(const double lowerBound, const double upperBound, const double step) {
	for (double x = lowerBound; x < upperBound + step; x += step) {
		printf("%f\t%e\n", x, evaluatePolynomeFactorised(x));
	}

	return EXIT_SUCCESS;
}

int exercise4(const double lowerBound, const double upperBound, const double step) {
	for (double x = lowerBound; x < upperBound + step; x += step) {
		printf("%f\t%e\n", x, evaluatePolynomeMult(x));
	}

	return EXIT_SUCCESS;
}

int main(void) {
	int out = EXIT_FAILURE;

	const double LOWER_BOUND = 1.6;
	const double UPPER_BOUND = 2.4;
	const double STEP = pow(10, -4);

	char choice = 0;

	fprintf(stderr, "1 : Direct evaluation\n2 : Horner evaluation\n3 : Factorised evaluation\n4 : Singles mult\n? : ");
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

	fprintf(stderr,"\n");
	return out;
}

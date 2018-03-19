#include "summations.h"

#include <stdio.h>
#include <mpfr.h>

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A1.
 * Sum must have been initialized with the desired precision.
 */
int sumA1(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* dans l’ordre croissant des indices : ((x 0 + x 1 ) + x 2 )..., */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A2.
 * Sum must have been initialized with the desired precision.
 */
int sumA2(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* dans l’ordre décroissant des indices */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A3.
 * Sum must have been initialized with the desired precision.
 */
int sumA3(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* opérandes positifs puis négatifs dans l’ordre croissant des indices */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A4.
 * Sum must have been initialized with the desired precision.
 */
int sumA4(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* opérandes négatifs puis positifs dans l’ordre croissant des indices */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A5.
 * Sum must have been initialized with the desired precision.
 */
int sumA5(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* somme partielle S + des opérandes positifs, puis somme partielle S − des opérandes négatifs chacune
	 dans l’ordre croissant des indices, puis somme de S + et S − */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A6.
 * Sum must have been initialized with the desired precision.
 */
int sumA6(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* Ordre croissant des valeurs absolues des opérandes */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A7.
 * Sum must have been initialized with the desired precision.
 */
int sumA7(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* Ordre décroissant des valeurs absolues des opérandes */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A8.
 * Sum must have been initialized with the desired precision.
 */
int sumA8(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* addition récursive par paire (pairwise) :
	 ((x 0 + x 1 ) + (x 2 + x 3 )) + ((x 4 + x 5 ) + (x 6 + x 7 )) pour n = 8 par exemple. */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A9.
 * Sum must have been initialized with the desired precision.
 */
int sumA9(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* Sommation compensée */

	return 0;
}

// BONUS
/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A10.
 * Sum must have been initialized with the desired precision.
 */
int sumA10(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* Sommation k-fois compensée */

	return 0;
}

/**
 * Put in `sum` the summation of the `n` elements of `array` considering the algorithm A11.
 * Sum must have been initialized with the desired precision.
 */
int sumA11(mpfr_t sum, const size_t n, const mpfr_t array[n]) {
	/* supprimer les deux opérandes de plus plus petite valeur absolue, les additionner, ajouter cette
	 somme comme un nouvel opérande et recommencer (addition des deux plus petites valeurs absolues,
	 ...) jusqu’à ce qu’il n’y ait plus d’opérande à additionner. Peut se faire en récursif. */

	return 0;
}

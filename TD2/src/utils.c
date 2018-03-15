#include "utils.h"

#include <stdio.h>
#include <mpfr.h>

void array_init(const size_t x, mpfr_t (**aptr)[x], mpfr_prec_t precision) {
	*aptr = malloc(sizeof(mpfr_t[x])); // allocate a true array
	assert(*aptr != NULL);
	for (size_t i = 0; i < x; i++) {
		m_init2((**aptr)[i], precision);
	}
}

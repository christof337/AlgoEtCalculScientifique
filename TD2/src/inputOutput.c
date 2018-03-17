#include "inputOutput.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mpfr.h>

#include "utils.h"

/**
 * Read from a given file and put the read lines in arrayToFill and the conditionning in "cond".
 * arrayToFill and cond must be initialized with the desired precision.
 * @param fileName The name of the file to be read
 * @param arrayToFill an array already initialized
 * @param cond the conditionning, initialized to
 * @return the number of lines read ; 0 if none
 */
int readFromFile(const char* fileName, mpfr_t arrayToFill[], mpfr_t cond) {
	FILE* file;
	int errnum;
	int nbFloats = 0;

	// try to open the file in read mode
	file = fopen(fileName, "r");
	errnum = errno;
	if (file == NULL) {
		// error while opening the file
		fprintf(stderr, "Error while opening the file %s : %s.\n", fileName,
				strerror(errnum));
		assert(0 /* Opening fail */);
	} else {
		// successfully opened the file
		char* line = NULL;
		size_t len = 0;
		ssize_t read;
		char** splittedLine = NULL;
		int it = 0;
		mpfr_prec_t precision = mpfr_get_prec(cond);
		mpfr_t tmpVal;
		mpfr_init2(tmpVal, precision);

		read = getline(&line, &len, file);
		if (read == -1) {
			fprintf(stderr, "Error while trying to read from empty file %s.\n",
					fileName);
			assert(0 /* Read fail */);
		} else {
			int idxToDel = 3;
			memmove(&line[idxToDel], &line[idxToDel + 1],
					strlen(line) - idxToDel);
			line[strlen(line) - 1] = 0;
			splittedLine = str_split(line, ' ');
			if (splittedLine == NULL) {
				// impossible to split : error?
				fprintf(stderr,
						"\nWrong format for the first line %s of %s. Expected : number of floating point numbers in file then conditionning.\n",
						line, fileName);
				assert(0 /* Split fail */);
			} else {
				sscanf(splittedLine[0], "%d", &nbFloats);

				assert(splittedLine[1]!=NULL /* Wrong file format */);
				// reading the conditionning
				int tmp = mpfr_set_str(cond, splittedLine[1], 10 /* base 10 */,
						MPFR_RNDN);
				assert(tmp == 0 /* mpfr_set_str fail*/);

				// initializing the array
				//array_init(nbFloats, arrayToFill, precision);

				while ((read = getline(&line, &len, file)) != -1) {
					line[strlen(line) - 1] = 0;
					int tmp = mpfr_set_str(tmpVal, line, 10 /* base 10 */,
							MPFR_RNDN);
					assert(tmp == 0 /* mpfr_set_str fail*/);
					mpfr_set(arrayToFill[it], tmpVal, MPFR_RNDN);
					++it;
				}

				cfree(splittedLine);
				cfree(line);
			}
		}

		mpfr_clear(tmpVal);
		fclose(file);

		assert(nbFloats==it /* Wrong number of lines */);
	}
	return nbFloats;
}

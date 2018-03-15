#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mpfr.h>

#include "utils.h"

/**
 * Read from a given file and put the read lines in arrayToFill and the conditionning in "cond".
 * arrayToFill must be freed afterwards. cond must be initialized with the desired precision, arrayToFill will
 * be initialized by this function at the same precision.
 * @param fileName The name of the file to be read
 * @param arrayToFill
 * @return the number of lines read ; 0 if none
 */
int readFromFile(const char* fileName, mpfr_t (**arrayToFill)[], mpfr_t * cond) {
	FILE* file;
	int errnum;

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
		long int it = 0;
		long int nbFloats = 0;
		mpfr_prec_t precision = mpfr_get_prec(cond);
		mpfr_t tmpVal;
		m_init2(tmpVal, precision);

		read = getline(&line, &len, file);
		if (read == -1) {
			fprintf(stderr, "Error while trying to read from empty file %s.\n",
					fileName);
			assert(0 /* Read fail */);
		} else {
			splittedLine = str_split(line, ' ');
			if (splittedLine == NULL) {
				// impossible to split : error?
				fprintf(stderr,
						"\nWrong format for the first line %s of %s. Expected : number of floating point numbers in file then conditionning.\n",
						line, fileName);
				assert(0 /* Split fail */);
			} else {
				sscanf(splittedLine[0], "%ld", &nbFloats);

				assert(splittedLine[1]!=NULL /* Wrong file format */);
				// reading the conditionning
				int tmp = mpfr_set_str(cond, splittedLine[1], 10 /* base 10 */,
						MPFR_RNDN);
				assert(tmp == 0 /* mpfr_set_str fail*/);

				// initializing the array
				array_init(nbFloats, arrayToFill, precision);

				while ((read = getline(&line, &len, file)) != -1) {
					int tmp = mpfr_set_str(tmpVal, line, 10 /* base 10 */,
							MPFR_RNDN);
					assert(tmp == 0 /* mpfr_set_str fail*/);
					mpfr_set((**arrayToFill)[it], tmpVal, MPFR_RNDN);
					++it;
				}

				free(splittedLine);
				free(line);
			}
		}

		mpfr_clear(tmpVal);
		fclose(file);
	}
	return errnum;
}

/**
 * Read exactly nColumns and nRows from the given file, and put it in matrix.
 * @param[in] fileName The file to read the matrix from.
 * @param[in] nColumns number of columns to read. The file must have at least this number of columns
 * @param[in] nRows number of rows to read.
 * @param[out] matrix The matrix to fill
 * @param[in] precision
 * @param[in] isHeader
 * @return
 */
int readMatrixFromFile(const char * fileName, const size_t nColumns,
		const size_t nRows, mpfr_t matrix[nColumns][nRows],
		const mpfr_prec_t precision, const int isHeader) {
	int err = EXIT_SUCCESS;

	FILE * file;

	file = fopen(fileName, "r");
	err = errno;
	if (file == NULL) {
// error while opening the file
		fprintf(stderr, "Error while opening the file `%s` : %s", fileName,
				strerror(err));
		err = EXIT_FAILURE;
	} else {
// successfully opened the file
		char* line = NULL;
		size_t len = 0;
		ssize_t read;
		char** splittedLine = NULL;
		if (isHeader) {
			// header line
			getline(&line, &len, file);
		}
		size_t row = 0;
		while ((read = getline(&line, &len, file)) != -1) {
			splittedLine = str_split(line, '\t');
			if (splittedLine == NULL) {
				// impossible to split : error?
				fprintf(stderr, "\nImpossible to split the line %s [%ld].\n",
						line, precision);
				/* Split fail */
				assert(0 /* Split fail */);
				err = EXIT_FAILURE;
			} else {
				assert(
						nColumns>0 && splittedLine[0]!=NULL /*"Wrong file format"*/);
				for (size_t i = 0; i < nColumns; ++i) {
					m_init2(matrix[row][i], precision);
					int tmp = mpfr_set_str(matrix[row][i], splittedLine[i], 10,
							MPFR_RNDN);
					assert(tmp == 0 /* mpfr_set_str fail*/);
				}
			}
			cfree(splittedLine);
			++row;
			// going to the next precision
		}
		fclose(file);
		cfree(line);
	}

	return err;
}

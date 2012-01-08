/*
memorylayout - shows the different address regions of a program on your platform
Copyright (C) 2012  Faisal Memon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINELENGTH	(80)
#define	TABLESIZE 	(5)

typedef int (*qsort_comparison)(const void *, const void *);

/*
 * Constant data is declared by symbols and further defined to particular values
 * and thus appear in the program as it is on disk.
 */
const char constant_data[]="defined constant data";

/*
 * Block Started by Symbol (BSS) is an area whose size is defined via symbol
 * declarations, but whose values are not defined (assumed 0).  This in practice
 * means that no space is occupied in the program as it appears on disk.  We
 * show this by having a huge BSS area for the "uninitialized_symbols" array
 */
int uninitialized_symbols[50000];

unsigned int get_heap_address()
{
	char* result;
	free (result = malloc (1));
	return (unsigned int)result;
}

int main(void) {

	int arbitrary_stack_variable = 0;

	char buffer[TABLESIZE][LINELENGTH] = {{ 0 }};
	snprintf(buffer[0], LINELENGTH, "0x%.8x %s", (unsigned int)main,
			"code      (Address of main function)\n");
	snprintf(buffer[1], LINELENGTH, "0x%.8x %s", (unsigned int)constant_data,
			"read only (constant data)\n");
	snprintf(buffer[2], LINELENGTH, "0x%.8x %s", (unsigned int)uninitialized_symbols,
			"bss       (uninitialized_symbols)\n");
	snprintf(buffer[3], LINELENGTH, "0x%.8x %s", (unsigned int)&arbitrary_stack_variable,
			"stack     (address of arbitrary_stack_variable)\n");
	snprintf(buffer[4], LINELENGTH, "0x%.8x %s", get_heap_address(),
			"heap      (address of a malloc)\n");

	qsort(buffer, TABLESIZE, sizeof(char[LINELENGTH]), (qsort_comparison)strcmp);

	int i;
	for (i = 0; i < TABLESIZE; i++)
	{
		fprintf(stdout, "%s", buffer[i]);
	}

	return EXIT_SUCCESS;
}

/* Test best fit functionality in palloc */

#include <stdio.h>
#include "threads/palloc.h"
#include "threads/pte.h"
#include "tests/threads/tests.h"

void
mine_bestfit_test (void) 
{
  void *block[100];
	size_t block_size[100];
	size_t n = 15;
	size_t i;

	/* Allocate some blocks of different sizes */
  for (i = 0; i < 10; i++) {
	block_size[i] = n;
	printf("palloc number %d of size %d\n", i, block_size[i]);

	n--;

	block[i] = palloc_get_multiple(PAL_ASSERT, block_size[i]);
	ASSERT(block[i] != NULL);
	ASSERT(pg_ofs(block[i]) == 0);
  }

	printf("palloc number %d of size %d\n", 10, 1);
	block[10] = palloc_get_multiple(PAL_ASSERT, 1);
	printf("palloc number %d of size %d\n", 11, 10);
	block[11] = palloc_get_multiple(PAL_ASSERT, 10);

	/* Free some of those blocks */ 
	for (i = 0; i < 10; i+=3) {
		printf("free block %d with size %d\n", i, block_size[i]);
		palloc_free_multiple(block[i], block_size[i]);
	}

	printf("free block %d with size %d\n", 10, 1);
  palloc_free_multiple(block[10],1);

	/* Allocate a single page */
	printf("palloc for 1 page\n");
	block[12] = palloc_get_multiple(PAL_ASSERT, 1);

	/* Allocate multiple pages */ 
	printf("palloc for 8 pages\n");
	block[12] = palloc_get_multiple(PAL_ASSERT, 8);
}

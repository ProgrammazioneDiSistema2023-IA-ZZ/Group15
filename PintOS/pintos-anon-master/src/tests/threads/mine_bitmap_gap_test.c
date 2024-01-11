/* Test gaps in palloc bitmap */

#include <stdio.h>
#include "threads/palloc.h"
#include "threads/pte.h"
#include "tests/threads/tests.h"

void
mine_bitmap_gap_test (void) 
{
  void *block[110];

	printf("start allocating\n");

	/* Allocate 100 times 3 pages */
  for (size_t i = 0; i < 100; i++) {
	block[i] = palloc_get_multiple(PAL_ASSERT, 3);
	ASSERT(block[i] != NULL);
	ASSERT(pg_ofs(block[i]) == 0);
	printf("palloc number %d\n", i);
  }

  printf("start freeing\n");
  
	/* Free 3 pages each 10 previous allocations */
  for (size_t i = 0; i < 100; i+= 10) {
	palloc_free_multiple(block[i], 3);
	printf("free number %d\n", i);
  }
}

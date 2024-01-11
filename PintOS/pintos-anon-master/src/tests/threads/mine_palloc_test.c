/* */

#include <stdio.h>
#include "threads/palloc.h"
#include "threads/pte.h"
#include "tests/threads/tests.h"

void
mine_palloc_test (void) 
{
  void *block = palloc_get_multiple(PAL_ASSERT, 1);
  ASSERT(block != NULL);
  ASSERT(pg_ofs(block) == 0);
  palloc_free_multiple(block, 1);
  msg("Test palloc_get_multiple passed");

}

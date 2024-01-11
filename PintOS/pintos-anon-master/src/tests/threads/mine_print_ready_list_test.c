/* Test the funtion thread_print_ready_list() */

#include <stdio.h>
#include "threads/thread.h"
#include "tests/threads/tests.h"
#include "threads/synch.h"

static void counting (void *);
static struct semaphore sem;

void
mine_print_ready_list_test (void) 
{
	int i, pri;

	sema_init(&sem, 0);

	for (i = 0; i < 10; i++) 
	{
		char name[16];
		snprintf (name, sizeof name, "thread_%d", i);
		if (i < 5) pri = PRI_MIN; 
		else pri = PRI_MAX; 
		thread_create (name, pri, counting, NULL);
		thread_print_ready_list();
	}

	for (i = 0; i < 10; i++) 
		sema_down(&sem);
}

static void
counting (void *ptr) 
{
	for (int i = 0; i < 2; i++) 
	{
		printf(" counting %d\n", i);
	}

	sema_up(&sem);
}

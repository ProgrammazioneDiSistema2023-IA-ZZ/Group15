/* Test the function next_thread_to_run_priority() */

#include <stdio.h>
#include "threads/thread.h"
#include "threads/synch.h"
#include "devices/timer.h"
#include "tests/threads/tests.h"

#define N 4

static void counting (void *);
static struct semaphore sem;

void
mine_next_thread_priority_test (void) 
{
	int i;
	int pri[N] = {PRI_MIN, PRI_DEFAULT, PRI_MAX, PRI_DEFAULT};

	sema_init(&sem, 0);

	for (i = 0; i < N; i++) 
	{
		char name[16];

		snprintf (name, sizeof name, "thread_%d", i);
 
		thread_create (name, pri[i], counting, NULL);
		thread_print_ready_list();
	}

	for (i = 0; i < N; i++) 
		sema_down(&sem);
}

static void
counting (void *args) 
{
	struct thread *t = thread_current ();
	printf("!!!I am <%s> with priority %d\n", t->name, t->priority);

	//printf("ticks: %lld\n", timer_ticks());
	for (int i = 0; i < 2; i++) 
	{
		printf(" counting %d\n", i+1);
	}

	sema_up(&sem);
}

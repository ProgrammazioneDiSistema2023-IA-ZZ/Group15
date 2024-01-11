/* Test priority shift */

#include <stdio.h>
#include "threads/thread.h"
#include "threads/synch.h"
#include "devices/timer.h"
#include "tests/threads/tests.h"

#define N 20

static void counting (void *);
static struct semaphore sem;

void
mine_priority_shift_test (void) 
{
	int i;
	int pri[N];
	for (i = 0; i < N; i++) pri[i] = PRI_MIN;

	sema_init(&sem, 0);

	for (i = 0; i < N; i++) 
	{
		char name[16];

		snprintf (name, sizeof name, "thread_%d", i);
 
		thread_create (name, pri[i], counting, NULL);
		printf("TICK %lld\n", timer_ticks());
		thread_print_ready_list();
	}

	for (i = 0; i < N; i++) {
		sema_down(&sem);
		printf("TICK %lld\n", timer_ticks());
		thread_print_ready_list();
	}
}

static void
counting (void *args) 
{
	struct thread *t = thread_current ();

	printf("TICK %lld\n", timer_ticks());
	printf("!!!I am <%s> with priority %d\n", t->name, t->priority);

	for (int i = 0; i < 5; i++) 
	{
		printf(" counting %d\n", i+1);
	}

	sema_up(&sem);
}

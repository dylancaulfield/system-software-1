#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include "time/reporting_time.h"
#include "daemon_tasks/daemon_task.h"
#include "event_logging/watch_directory.h"
#include "fork.h"
#include "ipc/log_task.h"
#include "signals/signal_handlers.h"

static void daemon_loop();

int main()
{

	// Daemonize process
	int pid = fork();
	if (pid != 0) exit(EXIT_SUCCESS);
	if (setsid() < 0) exit(EXIT_FAILURE);
	pid = fork();
	if (pid != 0) exit(EXIT_SUCCESS);

	// Set the file mode creation mask to 0
	umask(0);

	// Change to root to prevent issues with removable storage
	if (chdir("/") < 0) exit(EXIT_FAILURE);

	// Close open file descriptors
	long ofd;
	for (ofd = sysconf(_SC_OPEN_MAX); ofd >= 0; ofd--)
	{
		close((int)ofd);
	}

	// Handle signals
	signal(SIGINT, handle_interrupt);

	// Watch upload directory
	watch_directory();

	// Listen for completed tasks on queue
	listen_task_completion();

	// Run daemon loop
	daemon_loop();

	return 0;
}

static void daemon_loop()
{

	while (1)
	{

		report_time_t timeType = report_time_type();

		switch (timeType)
		{
		case Check:
			check_directory();
			break;
		case Transfer:
			transfer_reports();
		case None:
		default:
			break;
		}

		sleep(1);

	}

}

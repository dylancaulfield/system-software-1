//
// Created by dylan on 19/03/23.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "reporting_event.h"
#include "../time/reporting_time.h"
#include "../fork.h"
#include "../ipc/log_task.h"

// Log a message to the events log for the current day
void log_reporting_event(char* message)
{

	FORK();

	today(d);

	char fileName[250];
	sprintf(fileName, "/var/reporting/events/events_%s.log", d);

	FILE* todayEventFile = fopen(fileName, "a");
	if(todayEventFile == NULL)
	{
		log_task_completion("Unable to open today's event log");
		exit(EXIT_FAILURE);
	}
	fprintf(todayEventFile, "%s\n", message);
	fclose(todayEventFile);

	log_task_completion("Successfully logged a message in the event log");

	exit(EXIT_SUCCESS);

}

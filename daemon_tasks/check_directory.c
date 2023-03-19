//
// Created by dylan on 19/03/23.
//

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "daemon_task.h"
#include "../departments.h"
#include "../time/reporting_time.h"
#include "../event_logging/reporting_event.h"
#include "../fork.h"
#include "../ipc/log_task.h"

// Check the uploads directory for a report from each department
// and log if the report is present for the day or not
void check_directory()
{

	FORK();

	today(today);

	// Open upload directory
	DIR* d;
	struct dirent* dir;
	d = opendir("/var/reporting/upload");
	if (!d)
	{
		log_task_completion("Failed to open upload directory");
		exit(EXIT_FAILURE);
	}

	// Mark each report as not present to begin
	int n = sizeof(departments) / sizeof(departments[0]);
	int* present = (int*)calloc(n, sizeof(departments[0]));
	for (int i = 0; i < n; i++)
	{
		*(present + i) = 0;
	}

	// Mark any reports that are present
	while ((dir = readdir(d)) != NULL)
	{

		char* filename = dir->d_name;
		char departmentLogFilename[256];

		for (int i = 0; i < n; i++)
		{
			sprintf(departmentLogFilename, "%s_%s.xml\n", *(departments + i), today);

			if (strcmp(filename, departmentLogFilename) == 0)
			{
				*(present + i) = 1;
			}

		}

	}

	char message[250];
	sprintf(message, "\n\nFinal Report %s:\n", today);
	log_reporting_event(message);

	// Log if each report is present or not
	for (int i = 0; i < n; i++)
	{

		if (*(present + i))
		{
			sprintf(message, "- %-14s: xml report is present", *(departments + i));
			log_reporting_event(message);
			continue;
		}

		sprintf(message, "- %-14s: xml report is not present", *(departments + i));
		log_reporting_event(message);

	}

	free(present);
	closedir(d);

	log_task_completion("Successfully checked and logged upload directory contents");

	exit(EXIT_SUCCESS);

}


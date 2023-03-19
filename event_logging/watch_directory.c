//
// Created by dylan on 19/03/23.
//

#include <unistd.h>
#include "watch_directory.h"
#include "reporting_event.h"
#include "../fork.h"
#include "../ipc/log_task.h"
#include <sys/inotify.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <time.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

// Watch the uploads directory and log any events to the event log
// for today
void watch_directory()
{

	FORK();

	// Initialize inotify
	int fileDescriptor = inotify_init();
	if (fileDescriptor < 0)
	{
		log_task_completion("Error initializing inotify");
		exit(EXIT_FAILURE);
	}

	// Begin watching the directory
	int watchDirectory = inotify_add_watch(fileDescriptor, "/var/reporting/upload",
			IN_CREATE | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO | IN_DELETE);
	if (watchDirectory < 0)
	{
		log_task_completion("Error watching directory");
		exit(EXIT_FAILURE);
	}

	char buffer[EVENT_BUF_LEN];
	char message[250];

	while (1)
	{

		sleep(1);

		// Read the events from inotify
		ssize_t length = read(fileDescriptor, buffer, EVENT_BUF_LEN);
		if (length < 0)
		{
			log_task_completion("Error reading inotify event");
			exit(EXIT_FAILURE);
		}

		char timestamp[50];
		time_t now;
		time(&now);
		struct tm time = *localtime(&now);
		strftime(timestamp, sizeof(timestamp), "%a %Y-%m-%d %H:%M:%S", &time);

		int i = 0;
		while (i < length)
		{

			// Get the individual event
			struct inotify_event* event = (struct inotify_event*)&buffer[i];
			i += EVENT_SIZE + event->len;

			// Skip directories, we only care about files
			if (!event->len || event->mask & IN_ISDIR)
			{
				i++;
				continue;
			}

			if (event->mask & IN_MOVED_FROM)
			{
				sprintf(message, "%s: %s moved out of directory", timestamp, event->name);
				log_reporting_event(message);
				continue;
			}

			if (event->mask & IN_DELETE)
			{
				sprintf(message, "%s: %s was deleted", timestamp, event->name);
				log_reporting_event(message);
				continue;
			}

			// Find the owner of the file
			struct stat info;
			char absoluteFileName[256] = "/var/reporting/upload/";
			strcat(absoluteFileName, event->name);
			int statResult = stat(absoluteFileName, &info);
			if (statResult < 0)
			{
				log_task_completion("Error reading file metadata");
				exit(EXIT_FAILURE);
			}
			struct passwd* pw = getpwuid(info.st_uid);

			if (event->mask & IN_CREATE)
			{
				sprintf(message, "%s: %s created by %s", timestamp, event->name, pw->pw_name);
			}

			if (event->mask & IN_MOVED_TO)
			{
				sprintf(message, "%s: %s moved to directory by %s", timestamp, event->name, pw->pw_name);
			}

			if (event->mask & IN_MODIFY)
			{
				sprintf(message, "%s: %s modified by %s", timestamp, event->name, pw->pw_name);
			}

			log_reporting_event(message);

		}
	}

}
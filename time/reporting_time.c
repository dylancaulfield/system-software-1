//
// Created by dylan on 19/03/23.
//

#include <time.h>
#include "reporting_time.h"
#include <stdbool.h>
#include <stdio.h>

static bool is_check_directory_time(struct tm now);

static bool is_backup_directory_time(struct tm now);

// Determine if it is check-time, transfer-time or neither
report_time_t report_time_type()
{

	time_t now = time(NULL);
	struct tm currentTime = *localtime(&now);

	if (is_check_directory_time(currentTime)) return Check;
	if (is_backup_directory_time(currentTime)) return Transfer;

	return None;

}

// Write the current date in dd/mm/yyyy form to date
void current_date(char* date)
{
	time_t now = time(NULL);
	struct tm currentTime = *localtime(&now);

	sprintf(date, "%d-%d-%d", currentTime.tm_mday, currentTime.tm_mon, 1900 + currentTime.tm_year);
}

static bool is_check_directory_time(struct tm now)
{

	return (now.tm_hour == 23
			&& now.tm_min == 30
			&& now.tm_sec == 0);

}

static bool is_backup_directory_time(struct tm now)
{

	return (now.tm_hour == 1
			&& now.tm_min == 0
			&& now.tm_sec == 0);

}
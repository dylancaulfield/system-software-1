//
// Created by dylan on 19/03/23.
//

#ifndef REPORTING_DAEMON_REPORTING_TIME_H
#define REPORTING_DAEMON_REPORTING_TIME_H

#define today(name) \
char name[11]; \
current_date(name)

typedef enum report_time_t
{
	None = 0,
	Check = 1,
	Transfer = 2
} report_time_t;

report_time_t report_time_type();

void current_date(char* date);

#endif //REPORTING_DAEMON_REPORTING_TIME_H

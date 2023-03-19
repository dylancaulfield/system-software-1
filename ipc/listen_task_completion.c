//
// Created by dylan on 19/03/23.
//

#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <syslog.h>
#include "../fork.h"

// Listen for task completion messages on a queue
void listen_task_completion()
{

	FORK();

	mqd_t mq;
	struct mq_attr queue_attributes;
	char buffer[1024 + 1];

	queue_attributes.mq_flags = 0;
	queue_attributes.mq_maxmsg = 10;
	queue_attributes.mq_msgsize = 1024;
	queue_attributes.mq_curmsgs = 0;

	mq = mq_open("/reporting", O_CREAT | O_RDONLY, 0644, &queue_attributes);

	while (1)
	{
		ssize_t bytes_read;

		bytes_read = mq_receive(mq, buffer, 1024, NULL);

		buffer[bytes_read] = '\0';
		syslog(LOG_INFO, "%s", buffer);

	}

}
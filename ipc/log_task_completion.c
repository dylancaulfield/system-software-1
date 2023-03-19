//
// Created by dylan on 19/03/23.
//

#include <mqueue.h>

// Send a message on the queue to report task completion
void log_task_completion(char* message)
{

	mqd_t mq;

	mq = mq_open("/reporting", O_WRONLY);
	mq_send(mq, message, 1024, 0);
	mq_close(mq);

}
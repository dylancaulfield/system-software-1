//
// Created by dylan on 19/03/23.
//

#include "../daemon_tasks/daemon_task.h"

// Allow an interrupt signal to trigger a backup
void handle_interrupt(int signal)
{

	transfer_reports();

}
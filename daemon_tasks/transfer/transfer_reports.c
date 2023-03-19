//
// Created by dylan on 19/03/23.
//

#include <stdlib.h>
#include "../../fork.h"
#include "transfer.h"
#include "../../ipc/log_task.h"

void transfer_reports()
{

	FORK();

	lock_directories();
	log_task_completion("Locked directories");

	// Sleep to demonstrate locked directory
	sleep(30);

	backup_files();
	log_task_completion("Backed up files");

	transfer_uploads();
	log_task_completion("Transferred uploads");

	unlock_directories();
	log_task_completion("Unlocked directories");

	exit(EXIT_SUCCESS);

}
//
// Created by dylan on 19/03/23.
//

#include <wait.h>
#include <stdlib.h>
#include "../../fork.h"

void transfer_uploads()
{

	if (fork() != 0)
	{
		wait(NULL);
		return;
	}

	char* args[] = { "cp", "-r", "/var/reporting/upload/.", "/var/reporting/reporting", NULL };
	execvp("cp", args);

	exit(0);

}
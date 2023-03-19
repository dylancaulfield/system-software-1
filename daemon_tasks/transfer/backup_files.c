//
// Created by dylan on 19/03/23.
//

#include <wait.h>
#include <stdlib.h>
#include "../../fork.h"

void backup_files()
{

	if (fork() != 0)
	{
		wait(NULL);
		return;
	}

	char* args[] = { "cp", "-r", "/var/reporting/reporting/.", "/var/reporting/backup", NULL };
	execvp("cp", args);

	exit(0);

}
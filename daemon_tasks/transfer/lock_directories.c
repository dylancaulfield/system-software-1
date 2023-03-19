//
// Created by dylan on 19/03/23.
//

#include <sys/stat.h>

// Set read/write/execute for owner only
void lock_directories()
{

	int RWX = S_IRUSR | S_IWUSR | S_IXUSR;

	chmod("/var/reporting/upload", RWX);
	chmod("/var/reporting/reporting", RWX);
	chmod("/var/reporting/backup", RWX);

}
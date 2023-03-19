//
// Created by dylan on 19/03/23.
//

#include <sys/stat.h>

// Set read/write/execute for owner. Set read/execute for group with write on upload.
void unlock_directories()
{

	int RWXRX = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP;

	chmod("/var/reporting/upload", RWXRX | S_IWGRP);
	chmod("/var/reporting/reporting", RWXRX);
	chmod("/var/reporting/backup", RWXRX);

}
//
// Created by dylan on 19/03/23.
//

#include <unistd.h>


#ifndef REPORTING_DAEMON_FORK_H
#define REPORTING_DAEMON_FORK_H

#define FORK() if(fork() != 0) return


#endif //REPORTING_DAEMON_FORK_H

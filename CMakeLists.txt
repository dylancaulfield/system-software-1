cmake_minimum_required(VERSION 3.24)
project(reporting_daemon C)

set(CMAKE_C_STANDARD 11)

add_executable(reporting_daemon main.c time/reporting_time.h time/reporting_time.c daemon_tasks/check_directory.c daemon_tasks/daemon_task.h departments.h event_logging/reporting_event.c event_logging/reporting_event.h event_logging/watch_directory.c event_logging/watch_directory.h daemon_tasks/transfer/transfer_reports.c fork.h daemon_tasks/transfer/transfer.h daemon_tasks/transfer/backup_files.c daemon_tasks/transfer/lock_directories.c daemon_tasks/transfer/unlock_directories.c daemon_tasks/transfer/transfer_uploads.c ipc/log_task.h ipc/log_task_completion.c ipc/listen_task_completion.c signals/signal_handlers.h signals/handle_interrupt.c)

# process-info
loadable kernel module for retrieve or kill the valid processes

#### The module has 3 methods :
#### all_processes
- all the valid processes with their pid, ppid, name, uid and state info are returned.

#### pid_process
- pid and proc/inputid/cmdline info of the process that determined with the input id are returned.

#### kill_process
- process that determined with the input id is killed.

# process-info
loadable kernel module for retrieve or kill the valid processes  
  
The module has 3 methods :  
1- all_processes : retrieves all the valid processes with their pid, ppid, name, uid and state info.  
2- pid_process : retrieves pid and proc/inputid/cmdline info of the process that determined with the inputid.  
3- kill_process : kills process that determined with the inputid. 

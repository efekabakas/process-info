#include <linux/module.h>          //need libraries
#include <linux/kernel.h>  
#include <linux/fs.h>      
#include <asm/uaccess.h>   
#include <linux/string.h>
#include <linux/sched/signal.h>
#include <linux/uaccess.h> 

struct task_struct *task;         //creating variables
struct file *f;
char buf[150];
mm_segment_t fs;
int inputid = 1083;              //id of pid and kill functions, must be changed for different cases
char pathstr[50];
int i;

int all_processes(void)
{
        printk(KERN_INFO "PID \t PPID \tPNAME \t\t\t UID \t STATE \n");
        for_each_process(task) {                                       //getting all needed data of process and printing it
                printk(KERN_INFO "%d \t %d \t %s \t\t %u \t %li \n",          
                task->pid, task_ppid_nr(task), task->comm, current_uid().val, task->state);
	}
        printk(KERN_INFO "\n");
        return 0;
  
}

int pid_process(void){

        for(i=0;i<150;i++)              //creating buffer space
                buf[i] = 0;
        sprintf(pathstr, "/proc/%d/cmdline", inputid);  //copmlete path
        f = filp_open(pathstr, O_RDONLY, 0);    //file operations
        if(f == NULL)
                printk(KERN_ALERT "filp_open error!!.\n");
        else{
                fs = get_fs();
                set_fs(get_ds());
                f->f_op->read(f, buf, 150, &f->f_pos);
                set_fs(fs);
                printk(KERN_INFO "PID: %d \t CMDLINE: %s\n", inputid, buf);      
        }
        printk(KERN_INFO "\n");
        filp_close(f,NULL);

        return 0;
} 

int kill_process(void){                    
        int kill_pid(struct pid *pid, int sig, int priv);       
        for_each_process(task) {        //finding the task to kill and kill it
                if(inputid == task->pid){
                        kill_pid(get_task_pid(task, PIDTYPE_PID), SIGKILL, 1);
                        printk(KERN_INFO "PROCESS %d HAS BEEN KILLED.", inputid);
                        printk(KERN_INFO "\n");
                        break;
                }                 
	}
        return 0;
}


int simple_init(void) { //module entry point            
        printk(KERN_INFO "MODULE IS LOADED\n");
        printk(KERN_INFO "\n");
        //pid_process();
        //kill_process();                    
        all_processes();                 
        return 0;                      
}


/* This function is called when the module is removed. */
void simple_exit(void) {
        printk(KERN_INFO "MODULE HAS BEEN REMOVED\n");

}

/* Macros for registering module entry and exit points. */
module_init(simple_init); //when the module is loaded into the kernel.
module_exit(simple_exit); //when the module is removed from the kernel.

MODULE_LICENSE("GPL"); //software license
MODULE_DESCRIPTION("Kernel Module"); //description of the module
MODULE_AUTHOR("Efe Kaan Kabakas"); //author
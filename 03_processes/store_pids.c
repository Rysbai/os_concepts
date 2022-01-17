#include <sys/types.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


#define MIN_PID 300 
#define MAX_PID 5000

const int PID_ARR_SIZE = MAX_PID - MIN_PID;
int pids[PID_ARR_SIZE];


int allocate_map(void){
  int i;
  for (i = 0; i < PID_ARR_SIZE; i++)
    pids[i] = 0;
  
  return 0;
}


int allocate_pid(void){
  int i;
  for (i = 0; i < PID_ARR_SIZE; i++){
    int pid = pids[i];
    if (pid == 0){
      return MIN_PID + i;
    }
  }

  return 1;
}


void relase_pid(int pid){
  int pid_i = pid - MIN_PID;
  pids[pid_i] = 0;
}
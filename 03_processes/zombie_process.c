#include <sys/types.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
  pid_t pid, pid1;
  pid = fork();

  if (pid < 0) { /* error occurred */
   fprintf(stderr, "Fork Failed"); return 1;
  }else if (pid == 0) { /* child process */
    pid1 = getpid();
    printf("child: pid = %d\n",pid); /* A */
    printf("child: pid1 = %d\n",pid1); /* B */
    sleep(100);
    printf("Bye\n");
  }else { /* parent process */
    pid1 = getpid();
    printf("parent: pid = %d\n",pid); /* C */
    printf("parent: pid1 = %d\n",pid1); /* D */
  }
  return 0;
}
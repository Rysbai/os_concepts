#include <sys/types.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/shm.h> 
#include <sys/stat.h>



int digits_count(int number){
  int n=1;
	while ((number/=10) > 0) n++;
	return n;
}

int main(){
  pid_t pid;

  pid = fork();
  const int SIZE = 4096;
  const char *name = "OS";
  int shm_fd;


  if (pid < 0){
    fprintf(stderr, "Error occured when forking a child process");
    return 1;
  }

  if (pid == 0){
    int n;
    printf( "Enter a value : ");
    scanf("%d", &n);

    void *ptr;
      shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
      ftruncate(shm_fd, SIZE);

      ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

      while (n != 1)
      {
        sprintf(ptr, "%d, ", n);
        ptr += (digits_count(n) + 2);
        if (n % 2 == 0){
          n = n/2;
        } else {
          n = 3*n+1;
        }
      }
      printf("%d", n);
  } else {
    void *ptr;
      shm_fd = shm_open(name, O_RDONLY, 0666);
      ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
      wait(NULL);

      printf("%s",(char *)ptr);
      shm_unlink(name);
  }

  return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
  int i;
  for(i = 0; i<8; i++){
    pid_t child = fork();
    if(child == 0){
      break;
    }
    waitpid(child, NULL, 0);
    // int status;
    // waitpid(child, &status, 0);
  }
  printf("I am number %d, my pid is %d\n",i,getpid());
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int pipe_ids[2];
  int pipe2[2];
  if (pipe(pipe_ids) || pipe(pipe2)) {
    printf("pipe not created\n");
    return -1;
  }

  int f = fork();

  if (f) {
    close(pipe_ids[0]);
    close(pipe2[1]);
    int send_num = 15;
    printf("sending: 15\n");
    write(pipe_ids[1], &send_num, sizeof(send_num));
    int received_num;
    read(pipe2[0], &received_num, sizeof(received_num));
    printf("received: %d\n", received_num);
  }

  else {
    close(pipe_ids[1]);
    close(pipe2[0]);
    int received_num;
    read(pipe_ids[0], &received_num, sizeof(received_num));
    printf("doing maths on: %d\n", received_num);
    received_num *= received_num;
    write(pipe2[1], &received_num, sizeof(received_num));
  }
  return 0;
}
    

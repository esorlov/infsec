#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack1[1048576];
static char child_stack2[1048576];

static int child_fn() {
  printf("Мой PID: %ld\n", (long)getpid());
  printf("Родительский PID: %ld\n", (long)getppid());
  return 0;
}

int main() {
  printf("---Запуск дочернего процесса в системной иерархии PID---\n");
  pid_t child_pid2 = clone(child_fn, child_stack2+1048576, SIGCHLD, NULL);
  printf("PID дочернего процесса в системной иерархии: %ld\n", (long)child_pid2);
  waitpid(child_pid2, NULL, 0);
  printf("---Запуск дочернего процесса с изоляцией пространства PID---\n");
  pid_t child_pid1 = clone(child_fn, child_stack1+1048576, CLONE_NEWPID | SIGCHLD, NULL);
  printf("PID дочернего процесса в системной иерархии: %ld\n", (long)child_pid1);
  waitpid(child_pid1, NULL, 0);
  return 0;
}

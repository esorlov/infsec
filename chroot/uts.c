#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

static char child_stack[1048576];

static void print_nodename() {
  struct utsname utsname;
  uname(&utsname);
  printf("%s\n", utsname.nodename);
}

static int child_fn() {
  printf("Имя узла в дочернем процессе: ");
  print_nodename();

  printf("Имя будет изменено в новом пространстве имён!\n");
  sethostname("newname", 8);

  printf("Новое имя узла: ");
  print_nodename();
  return 0;
}

int main() {
  printf("Имя узла в системном пространстве имен: ");
  print_nodename();

  pid_t child_pid = clone(child_fn, child_stack+1048576, CLONE_NEWUTS | SIGCHLD, NULL);

  sleep(1);

  printf("Имя узла в системном пространстве имен: ");
  print_nodename();

  waitpid(child_pid, NULL, 0);

  return 0;
}

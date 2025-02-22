#include <stdio.h>
#include <unistd.h>
#include <linux/seccomp.h>
#include <sys/prctl.h>

int main () {
  pid_t pid;

  printf("Этап 1: ограничений не установлено\n");

  prctl (PR_SET_SECCOMP, SECCOMP_MODE_STRICT);
  printf ("Этап 2: переход в 'строгий' режим. Разрешены только системные вызовы read(), write(), exit() и sigreturn()\n");

  pid = getpid (); // Используем не разрешенный системный вызов
  printf ("!!ЭТОГО НЕ ДОЛЖНО БЫТЬ видно!! Мой PID = %d", pid);

  return 0;
}

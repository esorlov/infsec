#include <stdio.h>
#include <seccomp.h>
#include <unistd.h>

int main() {
    pid_t pid;

    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);

    // инициализируем фильтр и указываем, какое действие нужно осуществлять по умолчанию
    // — это SCMP_ACT_KILL, то есть немедленная остановка процесса,
    // который выполнит запрещённый системный вызов

//    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_TRAP);

    // другое действие по-умолчанию

    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(sigreturn), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);

    // правила seccomp, определяют системные вызовы, которые разрешено использовать

    printf ("Ограничений еще нет\n");

    pid = getpid();     // Пока все вызовы разрешены
    printf("Мой PID = %d\n", pid);

    seccomp_load(ctx);
    // Загрузка (активация) правил

    pid = getpid();     // Неразрешенный системный вызов

    printf("!! ЭТО НЕ ДОЛЖНО ОТОБРАЖАТЬСЯ !! Мой PID = %d\n", pid);

    seccomp_release(ctx);
    // Деактивация правил

    return 0;
}

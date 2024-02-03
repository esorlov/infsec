#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main(void) {

    // Текущий каталог процесса до chroot()
    char t_cwd[PATH_MAX];
    getcwd(t_cwd, sizeof(t_cwd));
    printf("Текущий каталог до chroot(): %s\n", t_cwd);

    // Выполнение chroot()
    chdir("/tmp/chroot/");
//    if (chroot("/tmp/chroot/") != 0) {
//        perror("chroot /tmp/chroot/");
//        return 1;
//    }

    // Текущий каталог процесса после chroot()
    char a_cwd[PATH_MAX];
    getcwd(a_cwd, sizeof(a_cwd));
    printf("Текущий каталог после chroot(): %s\n", a_cwd);

    // Получаем указатель на корень файловой системы
    struct dirent *de;
    DIR *dr = opendir("/");

    // Смотрим содержание корня ФС
    while ((de = readdir(dr)) != NULL)
        printf("%s\n", de->d_name);

    // Пытаемся открыть /etc/passwd хостовой ФС
    FILE *f;
    f = fopen("/etc/passwd", "r");

    if (f == NULL) {
        perror("/etc/passwd");
        return 1;
    } else {
        char buf[100];
        while (fgets(buf, sizeof(buf), f)) {
             printf("%s", buf);
        }
    }

    return 0;
}

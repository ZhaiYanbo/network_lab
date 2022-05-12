#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <worker.h>
#define MAX_CONNECTIONS 2048

char *err_msg;
//定义端口号
static int PORT = 9000, boss_fd;

static void sig_handle(int _s)
{
    if (boss_fd != -1)
    {
        close(boss_fd);
        printf("Server stopped.\n");
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, sig_handle);
    if (argc > 1)
    {
        char *ptr;
        PORT = strtol(argv[1], &ptr, 10);
        if (strlen(ptr) > 0)
        {
            err_msg = "Invalid port";
            goto exception;
        }
    }

    //1.建立套接字
    boss_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (boss_fd == -1)
        goto error;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    //2.bind() 将该套接字和本地网络地址联系在一起
    if (bind(boss_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        goto error;
    //3. listen() 使套接字做好侦听连接的准备
    if (listen(boss_fd, MAX_CONNECTIONS) == -1)
        goto error;
    while (1)
    {   //4.调用accept()返回连接，便于后面通信使用
        int fd = accept(boss_fd, (struct sockaddr *)NULL, NULL);
        if (fd == -1)
            goto error;
        pthread_t pid;
        if (pthread_create(&pid, NULL, work, (void *)(&fd)) != 0)
            goto error;
        pthread_detach(pid);
    }
exception:
    printf("%s\n", err_msg);
    exit(EXIT_FAILURE);
error:
    perror("Error");
    exit(EXIT_FAILURE);
end:
    exit(EXIT_SUCCESS);
}
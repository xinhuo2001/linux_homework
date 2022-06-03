#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(void)
{
    int fd[2]; //管道
    int sv; //默认值0
    //创建管道
    pipe(fd);

    //测试命令
    char ex_str[256] = "grep -v usr < /etc/passwd | wc -l > r.txt; cat r.txt";

    if(fork() == 0) {
        //更改进程输入端口 为 /etc/passwd
        int fd0 = -1; //重定向输入
        fd0 = open("/etc/passwd", O_RDONLY);
        if(fd0 != -1) { dup2(fd0, 0);close(fd0); }
        //更改进程输出端口 为 管道写
        dup2(fd[1], 1);
        //这里其实管道还在 只有管道所有写段读端全部关闭 管道才消失 下面同理
        close(fd[1]);
        close(fd[0]);
        
        execlp("grep", "grep", "-v", "usr", 0); //grep -v usr < /etc/passwd
        fprintf(stderr, "** bad command 1 : %m\n");
        exit(1);
    } else if(fork() == 0) {
        //更改进程输出端口 为 r.txt
        int fd1 = -1; //重定向输出
        fd1 = open("./r.txt", O_CREAT | O_WRONLY, 0666);
        if(fd1 != -1) { dup2(fd1, 1);close(fd1); }
        //更改进程输入端口 为 管道读
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", "-l", 0); //wc -l > r.txt
        fprintf(stderr, "** bad command 2 : %m\n");
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    wait(&sv);
    wait(&sv);
    execlp("cat", "cat", "r.txt", 0);
    return 0;
}
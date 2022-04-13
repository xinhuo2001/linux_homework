#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>

/* i节点属性 */
struct stat st;
// ret = stat(path,&st);

/* 判断节点是否为目录 */
// S_ISDIR(st.st_mode)

// 路径 + 打印形式 这里mode应该是结构体
void manager(char* path, int mode);



int main(int argc, char* argv[]) {
    printf("argc:%d\n",argc);
    for(int i = 0; i < argc; i++) {
        printf("%s\t", argv[i]);
    }
    printf("\n");

    /* 分析参数 */
    char* path = "/home/rock/Desktop";
    int mode = 0;

    /* 根据参数结果选择调用的函数 */
    manager(path,mode);
    return 0;
}


void manager(char* path, int mode)
{
    DIR* dirp = NULL;
    dirp = opendir(path);
    if(dirp == NULL) {
        printf("error");
        return;
    }

   struct dirent * direntp = NULL;
   direntp = readdir(dirp);
   while(direntp != NULL) {
       //获取文件信息
        printf("%s\t",direntp->d_name);
       //更新文件信息
       direntp = readdir(dirp);
   }
   printf("\n");
   closedir(dirp);
}
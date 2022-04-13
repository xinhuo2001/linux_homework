#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>

void test();



int main() {
    test();
    return 0;
}

void test()
{
    char * path = "/";
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
   closedir(dirp);
}
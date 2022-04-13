#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

/* i节点属性 */
// struct stat st;
// ret = stat(path,&st);
/* 判断节点是否为目录 */
// S_ISDIR(st.st_mode)


struct para
{
    int _r;
    int _a;
    int _l;
    int _lnum;
    int _h;
    int _hnum;
    int _m;
    int _mnum;
};

struct para MODE;


//初始化MODE
void initMode(int argc, char* argv[]);

// 路径 + 打印形式 这里mode应该是结构体
void manager(char* path, struct para mode);
// 获取文件详细信息
int getFileInfo(char* path, struct para mode);
//详细打印stat结构体
void showFileInfo(struct stat statbuf);

int main(int argc, char* argv[]) {
    printf("argc:%d\n",argc);
    for(int i = 0; i < argc; i++) {
        printf("%s\t", argv[i]);
    }
    printf("\n");

    /* 分析参数 */
    char* path = "/bin";
    struct para mode;
    /* 根据参数结果选择调用的函数 */
    manager(path,mode);
    return 0;
}


void initMode(int argc, char* argv[])
{
    MODE._r = 0;
    MODE._a = 0;
    MODE._h = 0;
    MODE._hnum = 0;
    MODE._l = 0;
    MODE._lnum = 0;
    MODE._m = 0;
    MODE._mnum = 0;
}

void manager(char* path, struct para mode)
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
        // 生成路径信息
        char dirbuf[512];
        memset(dirbuf,0,sizeof(dirbuf));
        strcat(dirbuf,path);
        strcat(dirbuf,"/");
        strcat(dirbuf,direntp->d_name);
       //打印文件信息
       getFileInfo(dirbuf, mode);
       //更新文件信息
       direntp = readdir(dirp);
   }
   printf("\n");
   closedir(dirp);
}

int getFileInfo(char* path, struct para mode)
{
//    printf("%s\n",path);
    struct stat statbuf;
    if(stat(path,&statbuf) == -1) {
        printf("error\n");
        return -1;
    }

    if(S_ISDIR(statbuf.st_mode)) {
        return -1;
    }

    if(S_ISREG(statbuf.st_mode)) {
        printf("%lu\t%s\n", statbuf.st_ino,path);
    }
    return 0;
}

void showFileInfo(struct stat statbuf)
{

// struct stat {   
//         mode_t     st_mode;       //文件访问权限   
//         ino_t      st_ino;       //索引节点号   
//         dev_t      st_dev;        //文件使用的设备号   
//         dev_t      st_rdev;       //设备文件的设备号   
//         nlink_t    st_nlink;      //文件的硬连接数   
//         uid_t      st_uid;        //所有者用户识别号   
//         gid_t      st_gid;        //组识别号   
//         off_t      st_size;       //以字节为单位的文件容量   
//         time_t     st_atime;      //最后一次访问该文件的时间   
//         time_t     st_mtime;      //最后一次修改该文件的时间   
//         time_t     st_ctime;      //最后一次改变该文件状态的时间   
//         blksize_t st_blksize;    //包含该文件的磁盘块的大小   
//         blkcnt_t   st_blocks;     //该文件所占的磁盘块   
// };

    /* 需要的参数 st_ino:unsighed short 以及文件路径*/

    printf("%ld\t",statbuf.st_ino);

}

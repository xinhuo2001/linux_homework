#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

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
const int MAX_PATH_LEN = 512;
const int MAX_PATH_NUM = 10;

//初始化MODE
void initMode();
//根据参数修改MODE 并返回路径数目
int changeMode(int argc, char* argv[], char ipath[][MAX_PATH_LEN]);

// 路径 + 打印形式 这里mode应该是结构体
int manager(char* path, struct para mode);
// 获取文件详细信息
int getFileInfo(char* path, struct para mode);
//详细打印stat结构体
void showFileInfo(struct stat statbuf);
//判断当前路径是否为隐藏路径
int isHidePath(char* path, int len);
//转化天数
int getTimeDays(time_t t);


int main(int argc, char* argv[]) {
    /* 分析参数 */
    //char* path = "/home/rock/test"; //默认开始目录
    // 获取当前路径
    char path[MAX_PATH_LEN];
    memset(path,0,MAX_PATH_LEN);
    getcwd(path,sizeof(path));
    puts(path);
    struct para mode;
    char ipath[MAX_PATH_NUM][MAX_PATH_LEN];
    /* 调整MODE */
    initMode();
    int inum = changeMode(argc,argv,ipath);
    for(int i = 0; i < inum; i++) {
        //printf("%s\n",ipath[i]);
        char curpath[MAX_PATH_LEN];
        memset(curpath,0,MAX_PATH_LEN);
        //根非目录 加上当前路径
        if(ipath[i][0] != '/') {
            strcat(curpath,path);
            strcat(curpath,"/");
        }
        strcat(curpath,ipath[i]);
        int mret = manager(curpath,mode);
        if(mret == -1) {
            //该文件不是目录 直接调文件读取
            getFileInfo(curpath,mode);
        }
    }
    if(inum == 0) {
        //没有额外参数 从当前目录遍历
        manager(path,mode);
    }
    return 0;
}


void initMode()
{
    MODE._r = 0; //递归
    MODE._a = 0; //显示隐藏
    
    MODE._l = 0; //最小文件限制
    MODE._lnum = 0;
    
    MODE._h = 0; //最大文件限制
    MODE._hnum = 0;
   
    MODE._m = 0; //时间限制
    MODE._mnum = 0;
}

int changeMode(int argc, char* argv[], char ipath[][100])
{
    
    printf("argc:%d\n",argc);
    for(int i = 0; i < argc; i++) {
        printf("%s\t", argv[i]);
    }
    printf("\n");

    int ret = 0;
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i],"-r") == 0) {
            MODE._r = 1;
        } else if(strcmp(argv[i],"-a") == 0) {
            MODE._a = 1;
        } else if(strcmp(argv[i], "-l") == 0) {
            MODE._l = 1;
            MODE._lnum = atoi(argv[++i]);
        } else if(strcmp(argv[i],"-h") == 0) {
            MODE._h = 1;
            MODE._hnum = atoi(argv[++i]);
        } else if(strcmp(argv[i],"-m") == 0) {
            MODE._m = 1;
            MODE._mnum = atoi(argv[++i]);
        } else {
            strcpy(ipath[ret++],argv[i]);
        }
    }
    return ret;
}

int manager(char* path, struct para mode)
{
    DIR* dirp = NULL;
    dirp = opendir(path);
    if(dirp == NULL) {
        return -1;
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
   //printf("\n");
   closedir(dirp);
   return 0;
}

int getFileInfo(char* path, struct para mode)
{


    int plen = strlen(path);
    int isHide = isHidePath(path,plen);
    //没有 -a 选项 跳过隐藏目录
    if(MODE._a == 0 && isHide == 1) {
        return -1;
    }


    //读取文件信息
    struct stat statbuf;
    if(stat(path,&statbuf) == -1) {
        printf("error:%s\n",path);
        return -1;
    }

    // 处理目录
    if(S_ISDIR(statbuf.st_mode)) {
        // 不处理回退目录,无法递归
        if(isHide == 1) {
            return -1;
        }
        // 有 -r 递归选项 处理该目录
        if(MODE._r == 1) {
            manager(path,mode);
        }
        return -1;
    }

    // 处理普通文件
    if(S_ISREG(statbuf.st_mode)) {
        /* 限制文件创建时间 */
        if(MODE._m == 1) {
            //获取文件创建天数
            time_t mtime = statbuf.st_mtime;
            int mfday = getTimeDays(mtime);
            //获取当前时间
            time_t ntime = time(0);
            int ndays = getTimeDays(ntime); 
            int dif_day = ndays - mfday;
            //不符合修改时间的直接退出
            if(dif_day > MODE._mnum) {
                return -1;
            }
        }
        
        //限制文件大小
        if(MODE._l == 1) {
            //获取文件大小
            off_t fsize = statbuf.st_size;
            if(fsize < MODE._lnum) {
                return -1;
            }
        }
        if(MODE._h == 1) {
            //获取文件大小
            off_t fsize = statbuf.st_size;
            if(fsize > MODE._hnum) {
                return -1;
            }
        }

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

int isHidePath(char* path, int len)
{
    for(int i = len-1; i >= 0; i--) {
        if(path[i] == '/') {
            if(i + 1 > len - 1) {
                return 0;
            } else {
                if(path[i+1] == '.') {
                    return 1;
                } else {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int getTimeDays(time_t t)
{
    struct tm * ftime = localtime(&t);
    int mdaynum = ftime->tm_mday + (ftime->tm_year - 1990) * 365;
    return mdaynum;
}
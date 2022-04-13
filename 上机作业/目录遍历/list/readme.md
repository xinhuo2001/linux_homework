### 思路
先分析参数
获取参数对应模式,可以使用结构体记录该模式
然后根据参数调用相应的函数
现在可以简单进行目录打印
但是,递归打印的话,还不行
应该将struct para mode 设置为全局变量,方便递归函数的执行

### 功能
```sh
# 基本命令
ls
    # 244 myap.c
ls file
ls dir

# 自定义选项
ls -r #这里对应 -R 递归打印 Linux中 -r 是 reverse
ls -a
ls -l num -h num
ls -m
-- #显式终止命令解析
```
### 参考链接
- https://blog.csdn.net/zhuyi2654715/article/details/7605051




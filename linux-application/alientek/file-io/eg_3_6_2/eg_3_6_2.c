/***********************************************************************************
 * @Author: Hu Yao
 * @Date: 2025-11-20 22:58:38
 * @LastEditTime: 2025-11-20 23:30:07
 * @LastEditors: Hu Yao
 * @Description: 嵌入式Linux应用手册，示例3.6.2,多次打开同一个文件测试
 ***********************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv[])
{
    int ret = 0;
    int fd1, fd2;
    char buf[4] = {0};

    fd1 = open("./test_file", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (-1 == fd1)
    {
        perror("fd1 open file error");
        exit(-1);
    }

    fd2 = open("./test_file", O_RDONLY);
    if (-1 == fd2)
    {
        perror("fd2 open file error");
        ret = -1;
        goto err1;
    }

    ret = lseek(fd1, 0, SEEK_SET);
    if (-1 == ret)
    {
        perror("fd1 lseek error");
        goto err2;
    }

    buf[0] = 0x11;
    buf[1] = 0x22;
    buf[2] = 0x33;
    buf[3] = 0x44;

    ret = write(fd1, buf, 4);
    if (-1 == ret)
    {
        perror("write error");
        goto err2;
    }

    memset(buf, 0x00, sizeof(buf));

    ret = lseek(fd2, 0, SEEK_SET);
    if (-1 == ret)
    {
        perror("fd2 lseek error");
        goto err2;
    }
    ret = read(fd2, buf, 4);
    if (-1 == ret)
    {
        perror("read error");
        goto err2;
    }

    printf("test_file:%x,%x,%x,%x\n", buf[0], buf[1], buf[2], buf[3]);

    ret = 0;

err2:
    close(fd2);
err1:
    close(fd1);

    exit(ret);
}

/***********************************************************************************
 * @Author: Hu Yao
 * @Date: 2025-11-28 23:10:25
 * @LastEditTime: 2025-12-10 22:25:44
 * @LastEditors: Hu Yao
 * @Version:
 * @Description:测试文件open标志：O_APPEND。加上此标志时
 ***********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    int ret;
    int fd1, fd2;
    unsigned char buf1[4] = {0};
    unsigned char buf2[4] = {0};

    int i;

    fd1 = open("./test_file", O_RDONLY);
    if (fd1 > 0)
    {
        close(fd1);
        system("rm test_file");
    }

    fd1 = open("./test_file", O_CREAT | O_RDWR | O_APPEND | O_EXCL, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if (fd1 < 0)
    {
        perror("open fd1");
        exit(-1);
    }

    fd2 = open("./test_file", O_WRONLY | O_APPEND);
    if (fd2 < 0)
    {
        perror("open fd2");
        ret = -1;
        goto exit1;
    }

    buf1[0] = 0x11;
    buf1[1] = 0x22;
    buf1[2] = 0x33;
    buf1[3] = 0x44;

    buf2[0] = 0xaa;
    buf2[1] = 0xbb;
    buf2[2] = 0xcc;
    buf2[3] = 0xdd;

    for (i = 0; i < 4; i++)
    {
        ret = write(fd1, buf1, sizeof(buf1));
        if (ret < 0)
        {
            perror("write fd1");
            goto exit0;
        }

        ret = write(fd2, buf2, sizeof(buf2));
        if (ret < 0)
        {
            perror("write fd2");
            goto exit0;
        }
    }

    ret = lseek(fd1, 0, SEEK_SET);
    if (ret < 0)
    {
        perror("lseek");
        goto exit0;
    }

    memset(buf2, 0, sizeof(buf2));
    for (i = 0; i < 8; i++)
    {
        ret = read(fd1, buf2, sizeof(buf2));
        if (ret < 0)
        {
            perror("read");
            goto exit0;
        }

        printf("%x%x%x%x", buf2[0], buf2[1], buf2[2], buf2[3]);
    }
    printf("\n");
    ret = 0;
exit0:
    close(fd2);
exit1:
    close(fd1);
    exit(ret);
}
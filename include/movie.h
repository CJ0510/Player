#ifndef __MOVIE_H__
#define __MOVIE_H__

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


static char movie_buf[128] = {0}; // 用于存放命令
static int fifo_fd; // 管道文件描述符
static int movie_flag = 0; // 用于标志是否正在播放视频

// 创建打开管道
int open_movie_pipe(void);
// 开始播放
int start_movie(char *moviepath, int lcd_x, int lcd_y, int length, int width);
// 发送控制命令
int send_cmd_pipe(int cmd);
// 关闭管道
int close_movie_pipe(void);


#endif
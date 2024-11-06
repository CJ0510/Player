#ifndef _COLOR_H
#define _COLOR_H

// open 头文件
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// ioctl 函数
#include <sys/ioctl.h>
// mmap 函数
#include <sys/mman.h>
#include <stdio.h>
//read、write、lseek函数
#include <unistd.h>
#include <linux/fb.h>

static int lcd_fb; // 显示屏文件描述符
static struct fb_var_screeninfo var; // 显示屏信息
static int screen_size; // 显示屏大小
static unsigned char *lcd_p; // 显示屏映射地址
static unsigned int line_width;
static unsigned int pixel_width;


// 打开显示屏
int open_lcd_color(void);
// 显示指定颜色
int show_color(int color);
// 显示bmp图片
int show_bmp(const char *bmp_path);
// 关闭显示屏
int close_lcd_color(void);


#endif
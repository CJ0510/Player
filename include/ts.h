#ifndef	_TS_H  //防止递归包含
#define	_BMP_H	

//====================一、函数头文件==============//
#include <stdio.h>
//open、lseek函数
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//read、write、lseek函数
#include <unistd.h>
//触摸屏的头文件
#include <linux/input.h>

//===================二、函数声明=================//
int open_ts(void);						//1、打开触摸屏
int get_ts_xy(int *ts_x, int *ts_y);	//2、获取触摸屏的坐标值
int close_ts(void);						//3、关闭触摸屏


#endif	/* bmp.h  */
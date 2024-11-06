#include "ts.h"

static int ts_fd;			//触摸屏的文件描述符

//1、打开触摸屏
int open_ts(void)
{
	ts_fd=open("/dev/input/event1", O_RDONLY);
	if (ts_fd == -1)
	{
		printf("open ts fail!\n");
		return -1;
	}
	return 0;
}

//2、获取触摸屏的坐标值
int get_ts_xy(int *ts_x, int *ts_y)
{
	struct input_event ts_buf;
	while(1)
	{
		read(ts_fd, &ts_buf, sizeof(ts_buf));		//相当于scanf函数
        // printf("Type: %d, Code: %d, Value: %d\n", ts_buf.type, ts_buf.code, ts_buf.value);
		//获取x轴的值
		if(ts_buf.type== EV_ABS && ts_buf.code==ABS_MT_POSITION_X)
		{
			*ts_x = ts_buf.value;					//蓝色边沿的开发板
		}

		//获取y轴的值
		if(ts_buf.type== EV_ABS && ts_buf.code==ABS_MT_POSITION_Y)
		{
			*ts_y = ts_buf.value;					//蓝色边沿的开发板
		}	
		//触摸值
		if(ts_buf.type== EV_KEY && ts_buf.code==BTN_TOUCH)
		{
			printf("touch = %d\n", ts_buf.value);
			if (ts_buf.value==0)
			{
				break;
			}
		}
	}
	printf("(%d, %d)\n", *ts_x, *ts_y);
}


//3、关闭触摸屏
int close_ts(void)
{
	close(ts_fd);
	return 0;
}
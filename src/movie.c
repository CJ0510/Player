#include "movie.h"

// 创建打开管道
int open_movie_pipe(void)
{
    // 检查管道是否存在，如果不存在则创建
    if(access("/tmp/fifo", F_OK))
    {
        int ret = mkfifo("/tmp/fifo", 0777);
        if(ret < 0)
        {
            perror("mkfifo");
            return -1;
        }
    }
    // 打开管道
    fifo_fd = open("/tmp/fifo", O_RDWR); 
    if(fifo_fd < 0)
    {
        perror("open");
        return -2;
    }
}

// 开始播放
int start_movie(char *moviepath, int lcd_x, int lcd_y, int length, int width)
{
    if(movie_flag == 0)
	{	
		open_movie_pipe();								//1、打开管道文件
		usleep(500000);									//延时0.5秒
		bzero(movie_buf, sizeof(movie_buf));			//清空字符串
		sprintf(movie_buf, "mplayer -slave -quiet -input file=/tmp/fifo -geometry %d:%d -zoom -x %d -y %d %s &", lcd_x, lcd_y, length, width, moviepath);	//拼接字符串
		system(movie_buf);								//执行字符串里的shell命令
		movie_flag = 1;							
	}
	return 0;
}

// 发送控制命令
int send_cmd_pipe(int cmd)
{
    open_movie_pipe();
    usleep(500000);
    bzero(movie_buf, sizeof(movie_buf));
    if(cmd == 1)
    {
        strcpy(movie_buf, "quit 0\n");
        write(fifo_fd, movie_buf, strlen(movie_buf));
        usleep(500000);
        movie_flag = 0;
        close_movie_pipe();
    }
    if(cmd == 2)
    {
        strcpy(movie_buf, "pause\n");
        write(fifo_fd, movie_buf, strlen(movie_buf));
    }
    if(cmd == 3)
    {
        strcpy(movie_buf, "volume 10\n");
        write(fifo_fd, movie_buf, strlen(movie_buf));
    }
    if(cmd == 4)
    {
        strcpy(movie_buf, "volume -10\n");
        write(fifo_fd, movie_buf, strlen(movie_buf));
    }
    if(cmd == 5)
    {
        strcpy(movie_buf, "seek -5\n");
        write(fifo_fd, movie_buf, strlen(movie_buf));
    }
    if(cmd == 6)
    {
        strcpy(movie_buf, "seek 5\n");
        write(fifo_fd, movie_buf, strlen(movie_buf));
    }
    return 0;
}

// 关闭管道
int close_movie_pipe(void)
{
    close(fifo_fd);
    return 0;
}
#include "color.h"


// 打开显示屏
int open_lcd_color(void)
{
    lcd_fb = open("/dev/fb0", O_RDWR);
    if (lcd_fb < 0)
    {
        perror("open lcd error");
        return -1;
    }
    if (ioctl(lcd_fb, FBIOGET_VSCREENINFO, &var))
	{
		printf("can't get var\n");
		return -1;
	}
    line_width  = var.xres * var.bits_per_pixel / 8;  
    pixel_width = var.bits_per_pixel / 8;  // 一个像素占用的字节数 4
    screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
    // printf("line_width = %d, pixel_width = %d, screen_size = %d\n", line_width, pixel_width, screen_size);
    // // 打印水平和垂直分辨率 1024 600
    // printf("xres = %d, yres = %d\n", var.xres, var.yres);
    // 映射内存
    lcd_p = mmap(NULL,
                 screen_size,  // 显示屏大小
                 PROT_READ | PROT_WRITE, // 读写
                 MAP_SHARED, // 共享
                 lcd_fb, // 文件描述符
                 0);
    
    if (lcd_p == (unsigned char *)-1)
    {
        perror("mmap error");
        return -1;
    }
    return 0;
}

// 显示指定颜色
int show_color(int color)
{
    unsigned int* ptr = (unsigned int*)lcd_p; // 将 lcd_p 转换为 unsigned int* 指针
    for (int i = 0; i < screen_size / sizeof(unsigned int); i++) {
        ptr[i] = color; // 将颜色写入每个像素
    }
    return 0;
}

// 显示bmp图片
int show_bmp(const char *bmp_path)
{
    int bmp_id = open(bmp_path, O_RDONLY);
    if (bmp_id < 0)
    {
        perror("open bmp error");
        return -1;
    }
    // 跳过前54个字节
    lseek(bmp_id, 54, SEEK_SET);
    // // 显示bmp文件的宽度和高度
    // unsigned int bmp_width = 0;
    // unsigned int bmp_height = 0;
    // read(bmp_id, &bmp_width, 4);
    // read(bmp_id, &bmp_height, 4);
    // printf("bmp_width = %d, bmp_height = %d\n", bmp_width, bmp_height);
    // 读取图片数据
    char bmp_buffer[1024*600*3] = {0};
    read(bmp_id, bmp_buffer, 1024*600*3);
    // 关闭文件
    close(bmp_id);

    // 将BGR数据转换为ARGB数据
    int lcd_buffer[1024*600] = {0};  // int 类型占用 4 字节
    for (int i = 0; i < 1024*600; i++)
    {
        lcd_buffer[i] = (bmp_buffer[3*i]<<0)+(bmp_buffer[3*i+1]<<8)+(bmp_buffer[3*i+2]<<16)+(0x00<24);
    }


    // 将图片数据写入显示屏
    for(int y = 0;y<600;y++)
    {
        for(int x = 0;x<1024;x++)
        {
            *((unsigned int*)lcd_p+1024*y+x) = lcd_buffer[x+(599-y)*1024];
        }
    }
}

// 关闭显示屏
int close_lcd_color(void)
{
    munmap(lcd_p, screen_size);
    close(lcd_fb);
    return 0;
}


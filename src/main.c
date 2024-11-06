#include "color.h"
#include <stdlib.h>
#include <string.h>
#include "ts.h"
#include "music.h"
#include "movie.h"


int main(int argc, char *argv[])
{
    int ts_x, ts_y;  // 触摸屏坐标
    int k = 0; // 图片数量
    int i = 0; // 音乐数量
    int j = 0; // 视频数量

    char bmp_path[5][32]={"./image/p1.bmp","./image/p2.bmp","./image/p3.bmp","./image/p4.bmp","./image/p5.bmp"};//相册目录
    char music_path[4][32]={"./music/1.mp3","./music/2.mp3","./music/3.mp3","./music/4.mp3"};//音乐目录 
    char music_imgpath[4][32]={"./image/1.bmp","./image/2.bmp","./image/3.bmp","./image/4.bmp"};//音乐图片目录
    char movie_path[2][32]={"./video/1.mp4","./video/2.mp4"};//视频目录

    // 打开显示屏
    open_lcd_color();
    // 打开触摸屏
    open_ts();
    // 显示主界面
    show_bmp("./image/init.bmp");
    while (1)
    {
        get_ts_xy(&ts_x, &ts_y);
        // 显示菜单栏
        show_bmp("./image/main.bmp");

        // 返回主界面
        if(ts_x>0&&ts_x<90&&ts_y>0&&ts_y<70)
        {
            show_bmp("./image/init.bmp");
        }
        // 电子相册
        if(ts_x>112&&ts_x<268&&ts_y>244&&ts_y<389)
        {
            printf("======电子相册======\n");
            show_bmp("./image/p1.bmp");
            while(1)
            {
                get_ts_xy(&ts_x, &ts_y);
                if(ts_x>0&&ts_x<512&&ts_y>70&&ts_y<600) // 点击左半边屏幕，切换上一张
                {
                    printf("切换上一张\n");
                    k--;
                    if(k==-1)
                    {
                        k = 4;
                    }
                    show_bmp(bmp_path[k]);
                }
                if(ts_x>512&&ts_x<1024&&ts_y>0&&ts_y<600) // 点击右半边屏幕，切换下一张
                {
                    printf("切换下一张\n");
                    k++;
                    if(k==5)
                    {
                        k = 0;
                    }
                    show_bmp(bmp_path[k]);
                }
                if(ts_x>0&&ts_x<90&&ts_y>0&&ts_y<70) // 点击左上角，返回主界面
                {
                    printf("====返回主界面====\n");
                    show_bmp("./image/main.bmp");
                    ts_x = 0;
                    ts_y = 0;
                    break;
                }
            }
        }
        // 音乐播放
        if(ts_x>370&&ts_x<526&&ts_y>244&&ts_y<389)
        {
            printf("======音乐播放======\n");
            show_bmp("./image/music.bmp");
            while(1)
            {
                get_ts_xy(&ts_x, &ts_y);
                if(ts_x>432&&ts_x<562&&ts_y>484&&ts_y<600) // 点击播放
                {
                    printf("播放音乐\n");
                    exit_music();
                    show_bmp(music_imgpath[0]);
                    start_music(music_path[0]);
                }
                // 第一首歌
                if(ts_x>824&&ts_x<1024&&ts_y>0&&ts_y<75)  
                {
                    exit_music();
                    show_bmp(music_imgpath[0]);
                    start_music(music_path[0]);
                }
                // 第二首歌
                if(ts_x>824&&ts_x<1024&&ts_y>75&&ts_y<150)  
                {
                    exit_music();
                    show_bmp(music_imgpath[1]);
                    start_music(music_path[1]);
                }
                // 第三首歌
                if(ts_x>824&&ts_x<1024&&ts_y>150&&ts_y<225)  
                {
                    exit_music();
                    show_bmp(music_imgpath[2]);
                    start_music(music_path[2]);
                }
                // 第四首歌
                if(ts_x>824&&ts_x<1024&&ts_y>225&&ts_y<300)  
                {
                    exit_music();
                    show_bmp(music_imgpath[3]);
                    start_music(music_path[3]);
                }
                // 上一首
                if(ts_x>650&&ts_x<709&&ts_y>484&&ts_y<600)  
                {
                    exit_music();
                    printf("上一首\n");
                    i--;
                    if(i == -1)
                    {
                        i = 3;
                    }
                    start_music(music_path[i]);
                    show_bmp(music_imgpath[i]);
                }
                // 下一首
                if(ts_x>747&&ts_x<806&&ts_y>484&&ts_y<600)  
                {
                    exit_music();
                    printf("下一首\n");
                    i++;
                    if(i == 4)
                    {
                        i = 0;
                    }
                    start_music(music_path[i]);
                    show_bmp(music_imgpath[i]);
                }
                // 退出，回答主界面
                if(ts_x>883&&ts_x<983&&ts_y>500&&ts_y<600)
                {
                    exit_music();
                    printf("====返回主界面====\n");
                    show_bmp("./image/main.bmp");
                    ts_x = 0;
                    ts_y = 0;
                    break;
                }
                // 暂停
                if(ts_x>47&&ts_x<147&&ts_y>500&&ts_y<600)
                {
                    printf("暂停音乐\n");
                    pause_music();  
                }
                // 继续
                if(ts_x>250&&ts_x<350&&ts_y>500&&ts_y<600)
                {
                    printf("继续音乐\n");
                    continue_music();  
                }
            }
        }
        // 视频播放
        if(ts_x>631&&ts_x<787&&ts_y>244&&ts_y<389)
        {
            printf("======视频播放======\n");
            show_bmp("./image/video.bmp");
            while(1)
            {
                get_ts_xy(&ts_x, &ts_y);

                // 开始播放第一个视频
                if(ts_x>0&&ts_x<190&&ts_y>500&&ts_y<600)
                {
                    printf("播放视频\n");
                    start_movie(movie_path[0], 193, 127, 630, 310);
                }
                // 退出
                if(ts_x>0&&ts_x<90&&ts_y>0&&ts_y<70)
                {
                    printf("====返回主界面====\n");
                    send_cmd_pipe(1);
                    show_bmp("./image/main.bmp");
                    ts_x = 0;
                    ts_y = 0;
                    break;
                }
                // 暂停/继续
                if(ts_x>450&&ts_x<575&&ts_y>500&&ts_y<600)
                {
                    printf("暂停视频/继续\n");
                    send_cmd_pipe(2);
                } 
                // 音量+
                if(ts_x>833&&ts_x<928&&ts_y>500&&ts_y<600)
                {
                    printf("音量+10\n");
                    send_cmd_pipe(3);
                }  
                // 音量-
                if(ts_x>929&&ts_x<1024&&ts_y>500&&ts_y<600)
                {
                    printf("音量-10\n");
                    send_cmd_pipe(4);
                }
                // 快退
                if(ts_x>323&&ts_x<448&&ts_y>500&&ts_y<600)
                {
                    printf("快退5s\n");
                    send_cmd_pipe(5);
                }
                // 快进
                if(ts_x>580&&ts_x<705&&ts_y>500&&ts_y<600)
                {
                    printf("快进5s\n");
                    send_cmd_pipe(6);
                }
                // 上一个视频
                if(ts_x>194&&ts_x<319&&ts_y>500&&ts_y<600)
                {
					send_cmd_pipe(1);
					usleep(500000);
					printf("上一个视频 \n");
                    j--;
                    if(j == -1)
                    {
                        j = 1;
                    }
                    start_movie(movie_path[1], 193, 127, 630, 310);
                }
                // 下一个视频
                if(ts_x>709&&ts_x<834&&ts_y>500&&ts_y<600)
                {
                    send_cmd_pipe(1);
                    usleep(500000);
                    printf("下一个视频 \n");
                    j++;
                    if(j == 2)
                    {
                        j = 0;
                    }
                    start_movie(movie_path[j], 193, 127, 630, 310);
                }
            }
        }
    }
    close_lcd_color();
    close_ts();
    return 0;
}
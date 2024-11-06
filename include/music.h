#ifndef _MUSIC_H
#define _MUSIC_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>


// 开始播放音乐
int start_music(char *music_path);
// 结束播放音乐
int exit_music(void);
// 暂停播放音乐
int pause_music(void);
// 继续播放音乐
int continue_music(void);


#endif
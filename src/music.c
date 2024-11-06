#include "music.h"

static char music_buf[128] = {0};

int start_music(char *music_path)
{
    bzero(music_buf, sizeof(music_buf));
    sprintf(music_buf, "mplayer %s &", music_path);
    system(music_buf);
    return 0;
}

int exit_music(void)
{
    system("killall -9 mplayer");
    return 0;
}

int pause_music(void)
{
    system("killall -STOP mplayer");
    return 0;
}

int continue_music(void)
{
    system("killall -CONT mplayer");
    return 0;
}
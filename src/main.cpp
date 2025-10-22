#include <iostream>
#include "windows.h"
#include <conio.h>
#include "../include/Game.h"
#include "../include/Block.h"
#include "../EasyX/include/easyx.h"
using std::cout;
int main() {
    Game game(20,10,25);
    game.init();
    // BeginBatchDraw();

    while (true) {
        //生成一个新方块
        Block *block=new Block(game,game.img_size);
        //生成检测 (默认新方块在最高行居中 落下,此时如果被占，直接结束)
        if (!block->isDrop()) {
            //游戏失败提示
            break;
        }
        //绘制新方块
        block->draw_block();
        //能掉落？
        while (block->isDrop()) {
            int delay=200;
            //纵坐标+1
            block->y++;
            //键盘操作
            if(_kbhit()) {
                int key = _getch();
                if (key=='a')
                    block->goLeft();
                else if (key=='d')
                    block->goRight();
                else if (key=='w')
                    block->rotate();
                else if (key=='s')
                    delay=10;
            }
            cleardevice();
            //绘制当前方块
            block->draw_block();
            //绘制已经被添加到地图里的方块
            game.drawMap();
            //
            FlushBatchDraw();
            //延时
            Sleep(delay);
            delay=200;
        }
        //方块已经不能掉落了，所以被添加到地图中
        block->addMap();
        //满行检测
        game.clearLine();
        //再次绘制地图
        game.drawMap();
        //

    }
    cout<<"Game over";
    _getch();
    return 0;
}
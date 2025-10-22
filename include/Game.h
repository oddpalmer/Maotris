//
// Created by ZJM on 2025/10/20.
//

#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "../include/easyx.h"

using std::vector;//个别引入

class Game {
public:
    int rows,cols,img_size;//map数组的行列，设定单个方块大小，以便初始化窗口
    static IMAGE dead_block;
public:
    Game(int rows,int cols,int img_size);
    void setMap(int x,int y,int isHere);//让方块能将位置写入到地图
    const int& getMap(int x, int y) const;//让方块获取地图信息
    void drawMap();//把地图被占的格子全部画出来
    void init();//初始化,窗口大小,地图数组map,控制延迟
    void clearLine();
    void keyEvent();
private:
    vector<vector<int>> map;//地图数组
};


#endif //MYGAME_GAME_H

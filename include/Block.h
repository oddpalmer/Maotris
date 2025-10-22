//
// Created by ZJM on 2025/10/20.
//

#ifndef MYGAME_BLOCK_H
#define MYGAME_BLOCK_H
#include <vector>
#include "../include/Game.h"
#include "../include/easyx.h"
using std::vector;

class Block{
public:
    Block(Game &game,int img_size);
    void draw_block() const;
    bool isDrop();                              //方块是否能下落
    void goLeft();                              //左移
    void goRight();                             //右移
    void rotate();                               //旋转
    void addMap();                              //将方块添加到地图上
    void removeMap();                           //将方块从地图上移除
    Game& getGameData;                          //主要是用于获取当前游戏的地图数据
public:
    int x,y;                                    //方块坐标
    int img_size;                               //方块大小
    int type;                                   //方块类型
    int indi_blocks[4][4];                      //当前类型,映射在map上
    int rotype;                                 //旋转类型
    /**********************静态*************************/
    static bool first_run;                      //第一次实例化方块检测
    static IMAGE blocks_img[7];                 //图片池
    static int blocks_type[7][4][4][4];            //状态池子 4行2列
    /****************************************************/
};


#endif //MYGAME_BLOCK_H
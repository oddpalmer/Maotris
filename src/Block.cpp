//
// Created by ZJM on 2025/10/20.
//
#include <iostream>
#include "../include/Block.h"

using std::cout;
using std::cin;
using std::endl;
// 静态成员变量定义和初始化（必须在类外）
/**********************静态*************************/
bool Block::first_run=true;
IMAGE Block::blocks_img[7];
int Block::blocks_type[7][4][4][4]={
    {
        {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},//I
        {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
        {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
    },
    {
        {0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0},//山
        {0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0},
       {0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0},
    },
    {
        {1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},//反L
        {0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0},
        {1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
        {0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0},
    },
    {
        {0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0},//正L
        {1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
        {1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0},
    },
    {
        {0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0},//口
        {0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0},//口
        {0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0},//口
        {0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0},//口
    },
    {
        {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},//z
        {0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0},//z
        {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},//z
        {0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0},//z
    },
    {
        {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},//反z
        {1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0},//反z
        {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},//反z
        {1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0},//反z
    },
};
/**********************静态*************************/
Block::Block(Game &game,int img_size):getGameData(game),img_size(img_size) {
    //状态池为空 说明还未初始化
    //[!][!][!][!][!][!][!][!]问题:图池改成image*指针就不行了
    if (first_run) {
        first_run = false;
        cout<<"create images pool successfully"<<endl;
        loadimage(&blocks_img[0],"../images/01.png",img_size,img_size);
        loadimage(&blocks_img[1],"../images/02.png",img_size,img_size);
        loadimage(&blocks_img[2],"../images/03.png",img_size,img_size);
        loadimage(&blocks_img[3],"../images/04.png",img_size,img_size);
        loadimage(&blocks_img[4],"../images/05.png",img_size,img_size);
        loadimage(&blocks_img[5],"../images/06.png",img_size,img_size);
        loadimage(&blocks_img[6],"../images/07.png",img_size,img_size);

    }
    type=rand()%7;
    rotype=rand()%4;
    //获取当前种类
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            indi_blocks[i][j]=blocks_type[type][rotype][i][j];
        }
    }
    cout<<"copy type successfully"<<endl;
    //设置方块初始坐标x,y (这块是理解重点)
    x=getGameData.cols/2-1;
    y=0;
    //测试图片是否正常输出
    // putimage(0,0,&blocks_img[0]);
    // putimage(0,img_size*1,&blocks_img[1]);
    // putimage(0,img_size*2,&blocks_img[2]);
    // putimage(0,img_size*3,&blocks_img[3]);
    // putimage(0,img_size*4,&blocks_img[4]);
    // putimage(0,img_size*5,&blocks_img[5]);
    // putimage(0,img_size*6,&blocks_img[6]);

}


void Block::draw_block() const {
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            if (indi_blocks[i][j])
                putimage(img_size*(x+j),img_size*(y+i),&blocks_img[type]);
    //x就是leftmargin，距离窗口左边的边距
    //y就是topmargin，距离窗口顶部的边距
    cout<<"draw successfully"<<endl;
}

//[!]出现过问题
bool Block::isDrop(){
    for (int i=3;i>=0;i--)
        for (int j=0;j<4;j++)
            //检测当前方块状态的下落位置是否有占用
            if (indi_blocks[i][j]) {
                if (y+i+1>=getGameData.rows||getGameData.getMap(y+i+1,x+j)==1)
                    return false;
            }
    return true;
}

void Block::goLeft() {
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            if (indi_blocks[i][j]) {
                if (x+j>0&&getGameData.getMap(y+i,x+j-1)==1)
                    return;
                if (x+j==0)
                    return;
            }
    x--;
}

void Block::goRight() {
    for (int i=0;i<4;i++)
        for (int j=3;j>=0;j--)
            if (indi_blocks[i][j]) {
                if (x+j<getGameData.cols-1&&getGameData.getMap(y+i,x+j+1)==1)
                    return;
                if (x+j==getGameData.cols-1)
                    return;
            }
    x++;
}

void Block::rotate() {
    int temp=rotype==3?0:rotype+1;
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            if (blocks_type[type][temp][i][j]) {
                if (getGameData.getMap(y+i,x+j)==1)
                    return;
            }
    rotype=temp;
    //第一次用这个拷贝，不想stl直接给名字就可以了
    memcpy(indi_blocks,blocks_type[type][rotype],sizeof(indi_blocks));
}

void Block::addMap() {
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            if (indi_blocks[i][j])
                getGameData.setMap(y+i,x+j,1);
    cout<<"add successfully"<<endl;
    for (int i=0;i<getGameData.rows;i++) {
        for (int j=0;j<getGameData.cols;j++)
            cout<<getGameData.getMap(i,j)<<" ";
        cout<<endl;
    }
}

// void Block::removeMap() {
//     for (int i=0;i<4;i++)
//         for (int j=0;j<4;j++)
//             if (indi_blocks[i][j]) {
//                 getGameData.setMap(y+i,x+j,0);//先前是y+i-1
//             }
//     cout<<"remove map successfully"<<endl;
// }

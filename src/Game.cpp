//
// Created by ZJM on 2025/10/20.
//
#include <conio.h>
#include "../include/Game.h"
#include "../include/Block.h"
#include <bits/fs_fwd.h>

IMAGE Game::dead_block;

Game::Game(int rows,int cols,int img_size):rows(rows),cols(cols),img_size(img_size) {}

void Game::init() {
    //初始化窗口 窗口宽度= 列*单个方块大小 长度= 行*单个方块大小
    initgraph(cols*img_size,rows*img_size);
    loadimage(&dead_block,"../images/08.png",img_size,img_size);
    map.resize(rows,vector<int>(cols,0));
    //设置随机数种子
    srand(time(nullptr));
}

void Game::clearLine() {
    int isFull;
    for (int i=rows-1;i>=0;i--) {
        isFull=true;
        for (int j=0;j<cols;j++) {
            if (map[i][j]==0) {
                isFull=false;
                break;
            }
        }
        if (isFull) {
            for (int k=i;k>0;k--)
                map[k]=map[k-1];
        }
    }

}

void Game::setMap(int x,int y,int isHere) {
    map[x][y]=isHere;
}

const int& Game::getMap(int x,int y) const {
    return map[x][y];
}

void Game::drawMap() {
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            if (map[i][j]==1) {
                putimage(img_size*j,img_size*i,&dead_block);
            }
        }
    }
}



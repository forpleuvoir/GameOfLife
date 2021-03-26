#pragma once

//初始化窗口
void initWindows();
//update
void update();
//初始化数据
void initData();
//cell update
void updateCell(int x,int y,int tag);
//获取周围细胞数量
int getCountOfSurroundingCells(int x,int y);
//生成temp
void initTemp();
//绘制
void draw();
//绘制细胞
void drawCell(int x,int y,int tag);
//绘制背景
void drawBackground();
//开始游戏
void start();
//随机生成活细胞
void randomCell();
//接受按键输入
void getKeyPress();
//接受鼠标按下
void getMouseMsg();
//设置细胞状态
void setCell(int x,int y,int tag);

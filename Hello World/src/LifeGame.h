#pragma once

//��ʼ������
void initWindows();
//update
void update();
//��ʼ������
void initData();
//cell update
void updateCell(int x,int y,int tag);
//��ȡ��Χϸ������
int getCountOfSurroundingCells(int x,int y);
//����temp
void initTemp();
//����
void draw();
//����ϸ��
void drawCell(int x,int y,int tag);
//���Ʊ���
void drawBackground();
//��ʼ��Ϸ
void start();
//������ɻ�ϸ��
void randomCell();
//���ܰ�������
void getKeyPress();
//������갴��
void getMouseMsg();
//����ϸ��״̬
void setCell(int x,int y,int tag);

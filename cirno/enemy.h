#pragma once
#include "image.h"
#include"time.h"


class ENEMY//敌机类
{
public:
	
	int x;
	int y;
	int a;//用于判断x轴的移动方向
	int iflive;//是否存活
	int life_en;//生命值
	int type;
	void enemy1_move();//移动
	void enemy_move();//移动
	void enemy_death_limit();//边缘碰撞死亡判定

};
extern ENEMY enemy[20];
extern ENEMY enemy1[10];
//敌人用个对象数组，在对象里调用敌人子弹的创建和移动函数

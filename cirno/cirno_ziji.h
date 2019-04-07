#pragma once
struct ZIJI//自机结构体
{
	int x = 100;
	int y = 100;
	int iflive = 50;
	int score = 0;
};
extern struct ZIJI ziji;
//自机碰撞体积 ziji.x,ziji.y   ziji.x+32,ziji.y-48
#pragma once
#include "image.h"
#include"time.h"


class ENEMY//�л���
{
public:
	
	int x;
	int y;
	int a;//�����ж�x����ƶ�����
	int iflive;//�Ƿ���
	int life_en;//����ֵ
	int type;
	void enemy1_move();//�ƶ�
	void enemy_move();//�ƶ�
	void enemy_death_limit();//��Ե��ײ�����ж�

};
extern ENEMY enemy[20];
extern ENEMY enemy1[10];
//�����ø��������飬�ڶ�������õ����ӵ��Ĵ������ƶ�����

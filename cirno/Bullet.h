#pragma once


#include "image.h"

struct Node//定义子弹结构体
{
	int y;
	int x;
	int type;
	struct Node *pNext;
};

extern struct Node *pBullet;//子弹指针
extern struct Node *gen_pBullet;//跟踪弹指针
extern struct Node *low_pBullet;//跟踪弹指针
extern struct Node *en_pBullet1;//敌弹指针
extern struct Node *en1_pBullet1;
class CBullet
{
public:

	void create_highL1();//创建高速左1子弹链表
	void create_highR1();//创建高速右1子弹链表
	void gen_createL();//创建高速跟踪弹左1链表
	void gen_createR();//创建高速跟踪弹右1链表


	void create_lowL1();//创建低速左1子弹链表
	void create_lowR1();//创建低速右1子弹链表
	void create_lowL2();//创建低速左2子弹链表
	void create_lowR2();//创建低速右2子弹链表
	
	void create_enL1(int i);
	void create_enR1(int i);

	void create_en1CENTER(int i);
	void create_en1R1(int i);
	void create_en1R2(int i);
	void create_en1R3(int i);
	void create_en1R4(int i);
	void create_en1L1(int i);
	void create_en1L2(int i);
	void create_en1L3(int i);
	void create_en1L4(int i);


	void show(Node * pnew);//显示高速子弹且移动
	void show_gen(Node * pnew_gen);//显示跟踪子弹且移动
	void show_low(Node * pnew_low);
	void show_en1(Node * pnew_en1);
	//显示低速子弹且移动
	void show_en(Node *pnew_en);
};
//子弹消失条件是碰到边界和敌人体积，写一个删除链表的函数，在函数里面遍历删除链表
//敌人和子弹的是否存活就用if 语句来判断是否putimage
//在生成敌人子弹的外面写一个if语句，每次更新遍历一次敌人数组，检测敌人是否存活（0 or 1）。不存活就不再生成这个敌人的子弹
//将敌人的位置信息和子弹位置信息绑在一起就可以了
//每次更新遍历一次敌人位置

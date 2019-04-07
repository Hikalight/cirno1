// cirno.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//氷妖紙華録

#include "pch.h"

#include <iostream>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include <fstream>

#include"Bullet.h"//子弹的创建和运动文件
#include"cirno_ziji.h"//自机坐标文件
#include "enemy.h"//敌人文件
using namespace std;
#pragma warning(disable:4996)
#pragma comment(lib,"winmm.lib")

MOUSEMSG mouse;//定义鼠标事件

struct score_player//玩家分数结构体
{
	char player[5] = { 0 };
	char enemynum1[10] = { 0 };
	char score1[10] = { 0 };
	char time[10] = { 0 };
	char q[10];

}sco[20];

CBullet zi_bullet;//自机子弹类
CBullet en_bullet;//敌人子弹类
//敌人的对象数组在enemy.h文件中定义为所有文件的全局变量
//自机的结构体在cirno_ziji.h中定义为所有文件的全局变量


void image_main();//图片加载
void Start();//开始界面
void chushihua();//初始化
void cirno();//自机操作
void back();//场景和自机图片的put
void enemy_m();//敌机弁弁的生成，移动，边界检测以及死亡
void enemy1_m();//敌机影狼的生成，移动，边界检测以及死亡
void enemy_mybullet_box();//敌机和自机子弹的碰撞判定
void bullet_del_limit();//自机子弹的碰撞检测和删除
void ziji_enbullet_box();//敌机子弹的碰撞检测和删除
void ending(clock_t end);//死亡界面
void score_show();//排行界面
void paint();//子弹的绘制，整型转字符型，游戏内右方数据的绘制

int enemynum = 0;//杀敌数
int score = 0;//分数
int speed_enemy_benben = 0;//敌机弁弁产生速度
int speed_enemy_wolf = 0;//敌机影狼产生速度

int speed_genzong = 0;//自机跟踪弹产生速度（子弹速度在bullet.cpp的外部成员函数里调节）
int speed_putong = 0;//自机高速弹产生速度
int speed_low = 0;//自机低速弹产生速度
int speed_en_benben_bullet = 0;//敌人弁弁子弹产生速度
int speed_en_wolf_bullet=0;//敌机影狼子弹产生速度


char player[5] = { 0 };
char enemynum1[10] = { 0 };
char score1[10] = { 0 };


int main()
{
	image_main();//加载图片
	initgraph(800, 700);//画布
	Start();//开始界面
	EndBatchDraw();//结束绘制
	cleardevice();//清屏
	clock_t start_time = clock();//开始计时，进入游戏while
	while (1)
	{
		chushihua();
		BeginBatchDraw();//开始批量绘图
		cirno();
		back();
		enemy_m();
		enemy1_m();
		enemy_mybullet_box();
	    bullet_del_limit();
		ziji_enbullet_box();
		if (ziji.iflive == 0)//死亡跳出循环
			break;
		paint();
		FlushBatchDraw();
	}
	EndBatchDraw();
	cleardevice();
	clock_t end = (clock() - start_time) / CLOCKS_PER_SEC;
	ending(end);
	_getch();
}

void image_main()
{
	loadimage(&start, _T("F:\\Cirno\\Cirno2.jpg"), 800, 700);//开始图片
	loadimage(&start_word, _T("F:\\Cirno\\start.jpg"));//start
	loadimage(&score_word, _T("F:\\Cirno\\score.jpg"));//score
	loadimage(&quit_word, _T("F:\\Cirno\\quit.jpg"));//quit
	loadimage(&bullet, _T("F:\\Cirno\\etama.bmp"));
	loadimage(&bullet_gen, _T("F:\\Cirno\\etama_star.bmp"));
	loadimage(&bullet_low_mask, _T("F:\\Cirno\\etama_low_mask.bmp"));
	loadimage(&bullet_low, _T("F:\\Cirno\\etama_low.bmp"));
	loadimage(&bullet_gen_mask, _T("F:\\Cirno\\etama_star_mask.bmp"));
	loadimage(&bullet_mask, _T("F:\\Cirno\\etama_mask.bmp"));
	loadimage(&en_Benben_mask, _T("F:\\Cirno\\Benben_mask.bmp"));
	loadimage(&en_Benben, _T("F:\\Cirno\\Benben.bmp"));
	loadimage(&ziji1_b, _T("F:\\Cirno\\pl1_mask.bmp"));
	loadimage(&ziji1, _T("F:\\Cirno\\pl1.bmp"));//自机人物
	loadimage(&en_Benben_bullet_mask, _T("F:\\Cirno\\bullet_music_mask.bmp"));
	loadimage(&en_Benben_bullet, _T("F:\\Cirno\\bullet_music.bmp"));
	loadimage(&wolf_mask, _T("F:\\Cirno\\wolf_mask.bmp"));
	loadimage(&wolf, _T("F:\\Cirno\\wolf.bmp"));
	loadimage(&cirno_death, _T("F:\\Cirno\\cirno_death.jpg"));
	loadimage(&circle1_mask, _T("F:\\Cirno\\circle_mask.bmp"));
	loadimage(&circle1, _T("F:\\Cirno\\circle.bmp"));
}
void Start()
{
	mciSendString(_T("open F:\\cirno\\voice\\cirno2.mp3 alias bkmusic"), NULL, 0, NULL);  // 背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  //循环播放
	remove("f1.dat");//删除f1文件
	while (1)
	{
		int e = 4;
		BeginBatchDraw();
		putimage(0, 0, &start);

		mouse = GetMouseMsg();
		if (mouse.x < 316 && mouse.x > 177&& mouse.y > 482 && mouse.y < 526)//当鼠标放在start按钮上
		{
			putimage(177, 482, &start_word);
			if (e != 0) mciSendString(_T("play F:\\cirno\\voice\\Switch.ogg"), NULL, 0, NULL);
			e = 0;

		}
		if (mouse.x <489 && mouse.x > 405 && mouse.y > 590 && mouse.y < 690)//当鼠标放在quit按钮上
		{
			putimage(405, 590, &quit_word);
			if (e != 1) mciSendString(_T("play F:\\cirno\\voice\\Switch.ogg"), NULL, 0, NULL);
			e = 1;
		}
		if (mouse.x < 298 && mouse.x > 167 && mouse.y > 250 && mouse.y < 357)//当鼠标放在score按钮上
		{
			putimage(158, 242, &score_word);
			if (e != 2) mciSendString(_T("play F:\\cirno\\voice\\Switch.ogg"), NULL, 0, NULL);
			e = 2;
		}
		if (mouse.mkLButton)//单击出现小圈
			circle(mouse.x, mouse.y, 5);

		    FlushBatchDraw();

		if (mouse.mkLButton && mouse.x < 316 && mouse.x > 177 && mouse.y > 482 && mouse.y < 526)//点击start按钮
		{
			FlushMouseMsgBuffer();
			break;
		}
		if (mouse.mkLButton &&mouse.x < 489 && mouse.x > 405 && mouse.y > 590 && mouse.y < 690)//点击quit按钮
		{
			FlushMouseMsgBuffer();
			closegraph();
			exit(0);
		}
		if (mouse.mkLButton &&mouse.x < 298 && mouse.x > 167 && mouse.y > 250 && mouse.y < 357)//点击score按钮
		{
			FlushMouseMsgBuffer();
			EndBatchDraw();
			cleardevice();
			score_show();
		}
	}
}
void chushihua()
{
	loadimage(&backi, _T("F:\\Cirno\\Cirnobattle.jpg"));//背景
}
void cirno()
{
		//高速
	if ((GetAsyncKeyState('W')) && (ziji.y >= 10))
		ziji.y -= 3;
	if ((GetAsyncKeyState('S')) && (ziji.y <= 700 - ziji1.getheight() - 10))
		ziji.y += 3;
	if ((GetAsyncKeyState('A')) && (ziji.x >= 10))
		ziji.x -= 3;
	if ((GetAsyncKeyState('D')) && (ziji.x <= 500 - ziji1.getwidth() - 10))
		ziji.x += 3;
	if (GetAsyncKeyState('K')&&(GetAsyncKeyState(VK_LSHIFT)==0))
	{
	

		if (speed_putong == 10)
		{
			//创建新子弹
			zi_bullet.create_highL1();
			zi_bullet.create_highR1();
		}

		if (speed_genzong == 20&&score>=200)
		{
			//创建升级的跟踪弹
		    zi_bullet.gen_createL();
			zi_bullet.gen_createR();
		}
	}

	  //低速
	if (GetAsyncKeyState(VK_LSHIFT))//shift慢速
	{
		if ((GetAsyncKeyState('W')) && (ziji.y >= 10))
			ziji.y += 2;
		if ((GetAsyncKeyState('S')) && (ziji.y <= 700 - ziji1.getheight() - 10))
			ziji.y -= 2;
		if ((GetAsyncKeyState('A')) && (ziji.x >= 10))
			ziji.x += 2;
		if ((GetAsyncKeyState('D')) && (ziji.x <= 500 - ziji1.getwidth() - 10))
			ziji.x -= 2;
	/*---------------弹---------------------*/
		if (GetAsyncKeyState('K'))
		{

			if (speed_low == 10)
			{
				//生成新低速子弹
				zi_bullet.create_lowL1();
				zi_bullet.create_lowR1();
			}
			if (speed_low == 10 && score >= 200)
			{
				//生成升级低速子弹
				zi_bullet.create_lowL2();
				zi_bullet.create_lowR2();
			}
		}
	/*---------------弹---------------------*/
	}
	

	//自机子弹速度调整
	if (speed_putong == 10)
		speed_putong = 0;
	speed_putong++;
	if (speed_genzong == 20)
		speed_genzong = 0;
	speed_genzong++;
	if (speed_low == 10)
		speed_low = 0;
	speed_low++;

	/*预留

	else if (m.uMsg == WM_LBUTTONDOWN) //按下鼠标左键时，发射子弹
	{

		mciSendString("close 8765", NULL, 0, NULL); //先把前面一次的音乐关闭
		mciSendString("open E:\\8765.mp3 alias 8765", NULL, 0, NULL); //打开跳动音乐
		mciSendString("play 8765", NULL, 0, NULL);  //仅播放一次

		zd_x = fj_x;
		zd_y = fj_y - 85;

	}*/

}
void enemy_m()//第一种敌人
{
	int i = 0; int j = 0;//临时变量，用于遍历

	//敌人生成速度
	if (speed_enemy_benben == 300)
	speed_enemy_benben = 0;
	speed_enemy_benben++;

	if (speed_enemy_benben == 300)
		for (i = 0; i < 20; i++)//遍历
			if (enemy[i].iflive != 1)//若死亡，赐予生命,初始化
			{
					enemy[i].iflive = 1;
					enemy[i].x = rand() % 450;
					enemy[i].y= -50;
					enemy[i].a = enemy[i].x;
					enemy[i].life_en = 15;
				    break;//跳出
			}

	for ( j = 0; j <20; j++)//遍历敌机数组，若发现存活，则进行移动,超出边界，则死亡，life为0，则死亡
	{
		if (enemy[j].iflive ==1)
			enemy[j].enemy_move();
		if (enemy[j].life_en == 0)//敌人生命值为0
		{
			enemy[j].x = 0;
			enemy[j].y = 0;
			enemy[j].iflive = 0;
			
			
		}

		enemy[j].enemy_death_limit();
	}


	if (speed_en_benben_bullet == 45)//遍历敌机数组，若发现存活则进行敌人的射击动作
	for (j = 0; j < 20; j++)
	{
		if (enemy[j].iflive == 1)
		en_bullet.create_enL1(j);
		en_bullet.create_enR1(j);
	}

	if (speed_en_benben_bullet == 45)
		speed_en_benben_bullet = 0;
	speed_en_benben_bullet++;


}
void back()

{
	putimage(0, 0, &backi);//背景

     //自机图
	putimage(ziji.x, ziji.y, &ziji1_b, SRCAND);
	putimage(ziji.x, ziji.y, &ziji1, SRCPAINT);
	
	
}
void enemy1_m()
//第二种敌人
{
	int i =0; int j = 0;//临时变量，用于遍历
	//敌人生成速度
	if (speed_enemy_wolf == 450)
		speed_enemy_wolf = 150;
	speed_enemy_wolf++;

	if (speed_enemy_wolf == 450)
		for (i = 0; i < 10; i++)//遍历
			if (enemy1[i].iflive != 1)//若死亡
			{
				enemy1[i].iflive = 1;//赐予生命,初始化
				enemy1[i].x =rand() % 450;
				enemy1[i].y = -50;
				enemy1[i].a = enemy1[i].x;
				enemy1[i].life_en = 15;
				break;//跳出
			}

	for (j = 0; j < 10; j++)//遍历敌机数组，若发现存活，则进行移动,超出边界，则死亡，life为0，则死亡
	{
		if (enemy1[j].iflive == 1)
			enemy1[j].enemy1_move();
		if (enemy1[j].life_en == 0)
		{
			enemy1[j].x = 0;
			enemy1[j].y = 0;
			enemy1[j].iflive = 0;
			
			//敌人死亡
		}
		enemy1[j].enemy_death_limit();
	}

	
	if (speed_en_wolf_bullet == 100)//遍历敌机数组，若发现存活则进行敌人的射击动作
		for (j = 0; j < 10; j++)
		{
			if (enemy1[j].iflive == 1)
			{
			en_bullet.create_en1CENTER(j);
			en_bullet.create_en1R2(j);
			en_bullet.create_en1L2(j);
			en_bullet.create_en1R1(j);
			en_bullet.create_en1L1(j);
			}
		}

	if (speed_en_wolf_bullet == 100)
		speed_en_wolf_bullet = 0;
	speed_en_wolf_bullet++;
	
	


}
void enemy_mybullet_box()//检测子弹和敌人碰撞
{
	for (int i = 0; i < 20; i++)
	{
		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		if (pBullet != NULL)
		{
			struct Node *pnew = pBullet;//头节点地址给当前节点
		struct Node *prev = NULL;//当前节点的前一个节点
		while ((pnew->pNext != NULL)&&(pnew!= NULL))//遍历，判断，删除
		{
			//碰撞判断
			prev = pnew;
			pnew = pnew->pNext;
			if ((!(pnew->x < enemy[i].x || pnew->x >(enemy[i].x + 50) || pnew->y < enemy[i].y || pnew->y >(enemy[i].y + 100)))&&(enemy[i].iflive==1))
			{
				enemy[i].life_en -= 1;
				if (enemy[i].life_en == 0)
				{
					score+=5;
					enemynum++;
				}
					
				if (pnew->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
				{
					prev->pNext = NULL;
					free(pnew);
					pnew = 0;
					break;
				}
				else {
					prev->pNext = pnew->pNext;
					free(pnew);
					pnew = prev->pNext;
				}	
				
			}	
			if(i<10)
			if ((!(pnew->x < enemy1[i].x || pnew->x >(enemy1[i].x + 50) || pnew->y < enemy1[i].y || pnew->y >(enemy1[i].y + 100))) && (enemy1[i].iflive == 1))
			{
				enemy1[i].life_en -= 1;
				if (enemy1[i].life_en == 0)
				{
					score += 5;
					enemynum++;
				}
				if (pnew->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
				{
					prev->pNext = NULL;
					free(pnew);
					pnew = 0;
					break;
				}
				else {
					prev->pNext = pnew->pNext;
					free(pnew);
					pnew = prev->pNext;
				}

			}
		}
		}
		
		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		if (gen_pBullet != NULL)
		{
			struct Node *pnew_gen = gen_pBullet;//头节点地址给当前节点
			struct Node *prev_gen = NULL;//当前节点的前一个节点
			while ((pnew_gen->pNext != NULL) && (pnew_gen != NULL))//遍历，判断，删除
			{
				//碰撞判断
				prev_gen = pnew_gen;
				pnew_gen = pnew_gen->pNext;
				if ((!(pnew_gen->x < enemy[i].x || pnew_gen->x >(enemy[i].x + 50) || pnew_gen->y < enemy[i].y || pnew_gen->y >(enemy[i].y + 100))) && (enemy[i].iflive == 1))
				{
					enemy[i].life_en -= 1;
					if (enemy[i].life_en == 0)
					{
						score += 5;
						enemynum++;
					}
					//敌人死亡
					if (pnew_gen->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
					{
						prev_gen->pNext = NULL;
						free(pnew_gen);
						pnew_gen = 0;
						break;
					}
					else {
						prev_gen->pNext = pnew_gen->pNext;
						free(pnew_gen);
						pnew_gen = prev_gen->pNext;
					}

				}
				if (i < 10)
					if ((!(pnew_gen->x < enemy1[i].x || pnew_gen->x >(enemy1[i].x + 50) || pnew_gen->y < enemy1[i].y || pnew_gen->y >(enemy1[i].y + 100))) && (enemy1[i].iflive == 1))
					{
						enemy1[i].life_en -= 1;
						if (enemy1[i].life_en == 0)
						{
							score += 5;
							enemynum++;
						}
						if (pnew_gen->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
						{
							prev_gen->pNext = NULL;
							free(pnew_gen);
							pnew_gen = 0;
							break;
						}
						else {
							prev_gen->pNext = pnew_gen->pNext;
							free(pnew_gen);
							pnew_gen = prev_gen->pNext;
						}

					}
			}
		}
		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		if (low_pBullet != NULL)
		{
			struct Node *pnew_low = low_pBullet;//头节点地址给当前节点
			struct Node *prev_low = NULL;//当前节点的前一个节点
			while ((pnew_low->pNext != NULL) && (pnew_low != NULL))//遍历，判断，删除
			{
				//碰撞判断
				prev_low = pnew_low;
				pnew_low = pnew_low->pNext;
				if ((!(pnew_low->x < enemy[i].x || pnew_low->x >(enemy[i].x + 50) || pnew_low->y < enemy[i].y || pnew_low->y >(enemy[i].y + 100))) && (enemy[i].iflive == 1))
				{
					enemy[i].life_en -= 1;
					if (enemy[i].life_en == 0)
					{
						score += 5;
						enemynum++;
					}
					//敌人死亡
					if (pnew_low->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
					{
						prev_low->pNext = NULL;
						free(pnew_low);
						pnew_low = 0;
						break;
					}
					else {
						prev_low->pNext = pnew_low->pNext;
						free(pnew_low);
						pnew_low = prev_low->pNext;
					}

				}
				if (i < 10)
					if ((!(pnew_low->x < enemy1[i].x || pnew_low->x >(enemy1[i].x + 50) || pnew_low->y < enemy1[i].y || pnew_low->y >(enemy1[i].y + 100))) && (enemy1[i].iflive == 1))
					{
						enemy1[i].life_en -= 1;
						if (enemy1[i].life_en == 0)
						{
							score += 5;
							enemynum++;
						}

						if (pnew_low->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
						{
							prev_low->pNext = NULL;
							free(pnew_low);
							pnew_low = 0;
							break;
						}
						else {
							prev_low->pNext = pnew_low->pNext;
							free(pnew_low);
							pnew_low = prev_low->pNext;
						}

					}
				
			}
		}

		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

	}

}
void bullet_del_limit()
{
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	if (pBullet != NULL)
	{
		struct Node *pnew = pBullet;//头节点地址给当前节点
		struct Node *prev = NULL;//当前节点的前一个节点
		while ((pnew->pNext != NULL) && (pnew != NULL))//遍历，判断，删除
		{
			//碰撞判断
			prev = pnew;
			pnew = pnew->pNext;
			if ((pnew->x < 0) || pnew->x > 500 || pnew->y < 0 || pnew->y >700)
			{

				if (pnew->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
				{
					prev->pNext = NULL;
					free(pnew);
					pnew = 0;
					break;
				}
				else {
					prev->pNext = pnew->pNext;
					free(pnew);
					pnew = prev->pNext;
				}

			}
		}
	}
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	if (gen_pBullet != NULL)
	{
		struct Node *pnew_gen = gen_pBullet;//头节点地址给当前节点
		struct Node *prev_gen = NULL;//当前节点的前一个节点
		while ((pnew_gen->pNext != NULL) && (pnew_gen != NULL))//遍历，判断，删除
		{
			//碰撞判断
			prev_gen = pnew_gen;
			pnew_gen = pnew_gen->pNext;
			if ((pnew_gen->x < 0) || pnew_gen->x > 500 || pnew_gen->y < 0 || pnew_gen->y >700)
			{
				if (pnew_gen == gen_pBullet)
				{
					free(pnew_gen);
					pnew_gen = 0;
					break;
				}

				if (pnew_gen->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
				{
					prev_gen->pNext = NULL;
					free(pnew_gen);
					pnew_gen = 0;
					break;
				}
				else {
					prev_gen->pNext = pnew_gen->pNext;
					free(pnew_gen);
					pnew_gen = prev_gen->pNext;
				}

			}
		}
	}
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	if (en_pBullet1 != 0)
	{
		struct Node *pnew_en = en_pBullet1;//头节点地址给当前节点
		struct Node *prev_en = NULL;//当前节点的前一个节点
		while ((pnew_en->pNext != NULL) && (pnew_en != NULL))//遍历，判断，删除
		{
			//碰撞判断
			prev_en = pnew_en;
			pnew_en = pnew_en->pNext;
			if ((pnew_en->x < 0) || pnew_en->x > 500 || pnew_en->y < 0 || pnew_en->y >650)
			{
				if (pnew_en == en_pBullet1)
				{
					free(pnew_en);
					pnew_en = 0;
					break;
				}

				if (pnew_en->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
				{
					prev_en->pNext = NULL;
					free(pnew_en);
					pnew_en = 0;
					break;
				}
				else {
					prev_en->pNext = pnew_en->pNext;
					free(pnew_en);
					pnew_en = prev_en->pNext;
				}

			}
		}
	}
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	if (en1_pBullet1 != 0)
	{
		struct Node *pnew_en1 = en1_pBullet1;//头节点地址给当前节点
		struct Node *prev_en1 = NULL;//当前节点的前一个节点
		while ((pnew_en1->pNext != NULL) && (pnew_en1 != NULL))//遍历，判断，删除
		{
			//碰撞判断
			prev_en1 = pnew_en1;
			pnew_en1 = pnew_en1->pNext;
			if ((pnew_en1->x < 0) || pnew_en1->x > 500 || pnew_en1->y < 0 || pnew_en1->y >650)
			{
				if (pnew_en1 == en1_pBullet1)
				{
					free(pnew_en1);
					pnew_en1 = 0;
					break;
				}

				if (pnew_en1->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
				{
					prev_en1->pNext = NULL;
					free(pnew_en1);
					pnew_en1 = 0;
					break;
				}
				else {
					prev_en1->pNext = pnew_en1->pNext;
					free(pnew_en1);
					pnew_en1 = prev_en1->pNext;
				}

			}
		}
	}
	/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
}
void ziji_enbullet_box()
{
	if (en_pBullet1 != 0)
	{
		struct Node *pnew_en = en_pBullet1;//头节点地址给当前节点
		struct Node *prev_en = NULL;//当前节点的前一个节点
		while ((pnew_en->pNext != NULL) && (pnew_en != NULL))//遍历，判断，删除
		{
			//碰撞判断

			prev_en = pnew_en;
			pnew_en = pnew_en->pNext;
			if (!((pnew_en->x < ziji.x) || (pnew_en->x > (ziji.x + 32)) || pnew_en->y < (ziji.y - 48) || pnew_en->y > ziji.y) && ((pnew_en->x < ziji.x + 8) || (pnew_en->x > (ziji.x + 24)) || pnew_en->y < (ziji.y - 32) || pnew_en->y > ziji.y + 16))
				score++;
			if (!((pnew_en->x < ziji.x + 8) || (pnew_en->x > (ziji.x + 24)) || pnew_en->y < (ziji.y - 32) || pnew_en->y > ziji.y + 16))
			{
				ziji.iflive--;
				if (ziji.iflive < 0)
					ziji.iflive = 0;

				if (pnew_en == en_pBullet1)
				{
					free(pnew_en);
					pnew_en = 0;
					break;
				}

				if (pnew_en->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
				{
					prev_en->pNext = NULL;
					free(pnew_en);
					pnew_en = 0;
					break;
				}
				else {
					prev_en->pNext = pnew_en->pNext;
					free(pnew_en);
					pnew_en = prev_en->pNext;
				}

			}
		}
	}

	if (en1_pBullet1 != 0)
		{
			struct Node *pnew_en1 = en1_pBullet1;//头节点地址给当前节点
			struct Node *prev_en1 = NULL;//当前节点的前一个节点
			while ((pnew_en1->pNext != NULL) && (pnew_en1 != NULL))//遍历，判断，删除
			{
				//碰撞判断

				prev_en1 = pnew_en1;
				pnew_en1 = pnew_en1->pNext;
				if (!((pnew_en1->x < ziji.x) || (pnew_en1->x > (ziji.x + 32)) || pnew_en1->y < (ziji.y - 48) || pnew_en1->y > ziji.y) && ((pnew_en1->x < ziji.x + 8) || (pnew_en1->x > (ziji.x + 24)) || pnew_en1->y < (ziji.y - 32) || pnew_en1->y > ziji.y + 16))
					score++;
				if (!((pnew_en1->x < ziji.x + 8) || (pnew_en1->x > (ziji.x + 24)) || pnew_en1->y < (ziji.y - 32) || pnew_en1->y > ziji.y + 16))
				{
					ziji.iflive--;
					if (ziji.iflive < 0)
						ziji.iflive = 0;

					if (pnew_en1 == en1_pBullet1)
					{
						free(pnew_en1);
						pnew_en1 = 0;
						break;
					}

					if (pnew_en1->pNext == NULL)//考虑尾节点的下一个节点为NULL的节点删除
					{
						prev_en1->pNext = NULL;
						free(pnew_en1);
						pnew_en1 = 0;
						break;
					}
					else {
						prev_en1->pNext = pnew_en1->pNext;
						free(pnew_en1);
						pnew_en1 = prev_en1->pNext;
					}

				}
			}
		}
	
}
void ending(clock_t end)
{
	
	int flag = 0,line = 0;
	while (1)//结束
	{
		BeginBatchDraw();
		putimage(0, 0, &cirno_death);
		int i;

		

		if (flag == 0)
		{
			InputBox(sco[0].q, 4, "YOU ARE DEAD!!Please type in your name");//输入玩家姓名



			ofstream fout("f2.dat", ios::app);//写入文件
			if (!fout)
			cout << "Cannot open output file.\n";
			fout << sco[0].q <<"       "<< end << "       "<< sco[0].enemynum1 << "       " << sco[0].score1 <<endl;
			fout.close();//关闭文件


			fstream fins("f2.dat");//修改文件
			if (!fins)
			cout << "Cannot open output file.\n";
				FILE  *ftp;
				char a[1000] = { NULL }, c;
				
				while (!fins.eof())
				{
					c = fins.get();
					if (c == '\n')
						line++;
				}
				fins.close();

				fstream fins1("f2.dat");//修改文件	
				ftp = fopen("tmp.dat", "w");//写打开临时文件tmp.txt

				if (line >= 9)//当玩家记录大于九条，删除一条玩家信息（将信息填入新文件，删除旧文件）
					
				{
					int flag1 = 0;
					while (!fins1.eof())
					{
						fins1.getline(a, 80);

						if (flag1 ==1)
						fputs(a, ftp);
							
						if (flag1 > 1)
						{
							fputs("\n", ftp);
							fputs(a, ftp);
						}
						
						flag1 +=1;
					}

					fclose(ftp);
					fins1.close();
					remove("f2.dat");//删除原文件
					rename("tmp.dat", "f2.dat");//将临时文件名改为原文件名
				}
				
				


			ifstream fin("f2.dat", ios::app);
			char str[80];
			while (fin)
			for (int i = 1; i <=9; i++)
				{
					fin.getline(str, 80);
					outtextxy(800* 0.03, 700 * (0.1 + (i - 1)*0.08), str);
					
					FlushBatchDraw();
				}
			fin.close();

		}
		
		flag = 1;
		if (GetAsyncKeyState(VK_ESCAPE))
			exit(0);
	}
}
void score_show()
{
	settextstyle(50, 0, _T("魂心"));
	settextcolor(BLUE);
	setbkmode(TRANSPARENT);
	ifstream fin1("f2.dat", ios::app);
	int i = 0;
	int tem[20];
	while (!fin1.eof())
	{
		fin1 >> sco[i].q >> sco[i].time >> sco[i].enemynum1 >> sco[i].score1;
		i++;
	}
	fin1.close();
	for(int j=0;j<i-1;j++)
	tem[j]=atoi(sco[j].score1);


	for (int l = 0; l < i - 2; l++)
	{
		for (int k= l+1; k< i - 1; k++)
		{
			if (tem[k] >= tem[l])
			{
				int tem2;
				struct score_player temp;

				tem2= tem[l];
				tem[l] = tem[k];
				tem[k] = tem2;

				temp = sco[l];
				sco[l] = sco[k];
				sco[k] = temp;
			}
		}
	}
	

	ofstream fout("f1.dat", ios::app);//写入文件
	for (int j = 0; j < i-1; j++)
	{
		fout << sco[j].q << "       " << sco[j].time << "       " << sco[j].enemynum1 << "       " << sco[j].score1 << endl;
	}
	fout.close();//关闭文件


	while (1)//结束
	{
		BeginBatchDraw();
		putimage(0, 0, &cirno_death);

	ifstream fin("f1.dat", ios::app);
	char str[80];
	while (fin)
		for (int i = 1; i <= 9; i++)
		{
			fin.getline(str, 80);
			outtextxy(800 * 0.03, 700 * (0.1 + (i - 1)*0.08), str);
		}
	FlushBatchDraw();
	fin.close();
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			remove("f1.dat");
			break;
		}
		
	}

}
void paint()
{
	zi_bullet.show(pBullet);//高速弹
	zi_bullet.show_gen(gen_pBullet);//跟踪弹
	zi_bullet.show_low(low_pBullet);//低速弹
	en_bullet.show_en1(en1_pBullet1);
	en_bullet.show_en(en_pBullet1);//敌人子弹

	_itoa_s(ziji.iflive, sco[0].player, 10);

	_itoa_s(enemynum, sco[0].enemynum1, 10);

	_itoa_s(score, sco[0].score1, 10);

	settextstyle(50, 0, _T("魂心"));
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	outtextxy(670, 38, sco[0].score1);
	outtextxy(670, 90, sco[0].enemynum1);
	outtextxy(670, 142, sco[0].player);
}

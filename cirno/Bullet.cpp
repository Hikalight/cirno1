#include "pch.h"
#include <easyx.h>
#include "Bullet.h"
#include "cirno_ziji.h"
#include "enemy.h"
#include <math.h>

struct Node *pBullet = NULL;//���ٵ�ָ��
struct Node *gen_pBullet = NULL;//���ٵ�ָ��
struct Node *low_pBullet=NULL;//���ٵ�ָ��
struct Node *en_pBullet1 = NULL;//�е�ָ��
struct Node *en1_pBullet1 = NULL;//�е�ָ��
void CBullet::create_highL1()//����������1�ӵ�����
{
	struct Node *pnew = (struct Node *)malloc(sizeof(struct Node));
	pnew->x = ziji.x;
	pnew->y = ziji.y - 5;
	pnew->pNext = NULL;
	if (pBullet == NULL)//���Ϊ��
	{
		pBullet = pnew;
	}
	else
	{
		pnew->pNext = pBullet;
		pBullet = pnew;
	}
}
void CBullet::create_highR1()//����������1�ӵ�����
{
	struct Node *pnew = (struct Node *)malloc(sizeof(struct Node));
	pnew->x = ziji.x + ziji1.getwidth() -16;
	pnew->y = ziji.y - 5;
	pnew->pNext = NULL;
	if (pBullet == NULL)//���Ϊ��
	{
		pBullet = pnew;
	}
	else
	{
		pnew->pNext = pBullet;
		pBullet = pnew;
	}
}
void CBullet::gen_createL()//�������ٸ��ٵ���1����
{
	struct Node *pnew_gen = (struct Node *)malloc(sizeof(struct Node));
	pnew_gen->x = ziji.x - 30;
	pnew_gen->y = ziji.y - 5;
	pnew_gen->pNext = NULL;
	if (gen_pBullet == NULL)//���Ϊ��
	{
		gen_pBullet = pnew_gen;
	}
	else
	{
		pnew_gen->pNext = gen_pBullet;
		gen_pBullet = pnew_gen;
	}
}
void CBullet::gen_createR()//�������ٸ��ٵ���1����
{
	struct Node *pnew_gen = (struct Node *)malloc(sizeof(struct Node));
	pnew_gen->x = ziji.x + ziji1.getwidth()-2;
	pnew_gen->y = ziji.y - 5;
	pnew_gen->pNext = NULL;
	if (gen_pBullet == NULL)//���Ϊ��
	{
		gen_pBullet = pnew_gen;
	}
	else
	{
		pnew_gen->pNext = gen_pBullet;
		gen_pBullet = pnew_gen;
	}
}

void CBullet::create_lowL1()//����������1�ӵ�����
{
	struct Node *pnew_low = (struct Node *)malloc(sizeof(struct Node));
	pnew_low->x = ziji.x;
	pnew_low->y = ziji.y - 5;
	pnew_low->pNext = NULL;
	if (low_pBullet == NULL)//���Ϊ��
	{
		low_pBullet = pnew_low;
	}
	else
	{
		pnew_low->pNext = low_pBullet;
		low_pBullet = pnew_low;
	}
}
void CBullet::create_lowR1()//����������1�ӵ�����
{
	struct Node *pnew_low = (struct Node *)malloc(sizeof(struct Node));
	pnew_low->x = ziji.x + ziji1.getwidth() - 16;
	pnew_low->y = ziji.y - 5;
	pnew_low->pNext = NULL;
	if (low_pBullet == NULL)//���Ϊ��
	{
		low_pBullet = pnew_low;
	}
	else
	{
		pnew_low->pNext = low_pBullet;
		low_pBullet = pnew_low;
	}
}
void CBullet::create_lowL2()//����������2�ӵ�����
{
	struct Node *pnew_low = (struct Node *)malloc(sizeof(struct Node));
	pnew_low->x = ziji.x - 13;
	pnew_low->y = ziji.y - 5;
	pnew_low->pNext = NULL;
	if (low_pBullet == NULL)//���Ϊ��
	{
		low_pBullet = pnew_low;
	}
	else
	{
		pnew_low->pNext = low_pBullet;
		low_pBullet = pnew_low;
	}
}
void CBullet::create_lowR2()//����������2�ӵ�����
{
	struct Node *pnew_low = (struct Node *)malloc(sizeof(struct Node));
	pnew_low->x = ziji.x + ziji1.getwidth() - 2;
	pnew_low->y = ziji.y - 5;
	pnew_low->pNext = NULL;
	if (low_pBullet == NULL)//���Ϊ��
	{
		low_pBullet = pnew_low;
	}
	else
	{
		pnew_low->pNext = low_pBullet;
		low_pBullet = pnew_low;
	}
}


void CBullet::create_enL1(int i)
{
	struct Node *pnew_en = (struct Node *)malloc(sizeof(struct Node));
	pnew_en->x = enemy[i].x+25;
	pnew_en->y = enemy[i].y+50;
	pnew_en->pNext = NULL;
	if (en_pBullet1 == NULL)//���Ϊ��
	{
		en_pBullet1 = pnew_en;
	}
	else
	{
		pnew_en->pNext = en_pBullet1;
		en_pBullet1 = pnew_en;
	}
}
void CBullet::create_enR1(int i)
{
	struct Node *pnew_en = (struct Node *)malloc(sizeof(struct Node));
	pnew_en->x = enemy[i].x - 50;
	pnew_en->y = enemy[i].y + 50;
	pnew_en->pNext = NULL;
	if (en_pBullet1 == NULL)//���Ϊ��
	{
		en_pBullet1 = pnew_en;
	}
	else
	{
		pnew_en->pNext = en_pBullet1;
		en_pBullet1 = pnew_en;
	}
}

void CBullet::create_en1CENTER(int i)
{
	struct Node *pnew_en1 = (struct Node *)malloc(sizeof(struct Node));
	pnew_en1->x = enemy1[i].x +25;
	pnew_en1->y = enemy1[i].y + 75;
	pnew_en1->type =0;
	pnew_en1->pNext = NULL;
	if (en1_pBullet1 == NULL)//���Ϊ��
	{
		en1_pBullet1 = pnew_en1;
	}
	else
	{
		pnew_en1->pNext = en1_pBullet1;
		en1_pBullet1 = pnew_en1;
	}
}
void CBullet::create_en1R1(int i)
{
	struct Node *pnew_en1 = (struct Node *)malloc(sizeof(struct Node));
	pnew_en1->x = enemy1[i].x + 50;
	pnew_en1->y = enemy1[i].y + 50;
	pnew_en1->pNext = NULL;
	if (en1_pBullet1 == NULL)//���Ϊ��
	{
		en1_pBullet1 = pnew_en1;
	}
	else
	{
		pnew_en1->pNext = en1_pBullet1;
		en1_pBullet1 = pnew_en1;
	}
}
void CBullet::create_en1R2(int i)
{
	struct Node *pnew_en1 = (struct Node *)malloc(sizeof(struct Node));
	pnew_en1->x = enemy1[i].x + 75;
	pnew_en1->y = enemy1[i].y + 25;
	pnew_en1->pNext = NULL;

	if (en1_pBullet1 == NULL)//���Ϊ��
	{
		en1_pBullet1 = pnew_en1;
	}
	else
	{
		pnew_en1->pNext = en1_pBullet1;
		en1_pBullet1 = pnew_en1;
	}
}
void CBullet::create_en1R3(int i)
{
	
}
void CBullet::create_en1R4(int i)
{
	
}
void CBullet::create_en1L1(int i)
{
	struct Node *pnew_en1 = (struct Node *)malloc(sizeof(struct Node));
	pnew_en1->x = enemy1[i].x ;
	pnew_en1->y = enemy1[i].y + 50;
	pnew_en1->pNext = NULL;
	if (en1_pBullet1 == NULL)//���Ϊ��
	{
		en1_pBullet1 = pnew_en1;
	}
	else
	{
		pnew_en1->pNext = en1_pBullet1;
		en1_pBullet1 = pnew_en1;
	}
}
void CBullet::create_en1L2(int i)
{
	struct Node *pnew_en1 = (struct Node *)malloc(sizeof(struct Node));
	pnew_en1->x = enemy1[i].x -25;
	pnew_en1->y = enemy1[i].y + 25;
	pnew_en1->pNext = NULL;
	if (en1_pBullet1 == NULL)//���Ϊ��
	{
		en1_pBullet1 = pnew_en1;
	}
	else
	{
		pnew_en1->pNext = en1_pBullet1;
		en1_pBullet1 = pnew_en1;
	}
}
void CBullet::create_en1L3(int i)
{
	
}
void CBullet::create_en1L4(int i)
{
	
}

void CBullet::show_en1(struct Node *pnew_en1)
{
	while (pnew_en1 != NULL)
	{
		putimage(pnew_en1->x, pnew_en1->y, &circle1_mask, SRCAND);
		putimage(pnew_en1->x, pnew_en1->y, &circle1, SRCPAINT);
		
			pnew_en1->y += 2;
			pnew_en1 = pnew_en1->pNext;
		

	}
}
void CBullet::show_en(struct Node *pnew_en)//��ʾ�����ӵ�
{
	while (pnew_en != NULL)
	{
		putimage(pnew_en->x, pnew_en->y, &en_Benben_bullet_mask, SRCAND);
		putimage(pnew_en->x, pnew_en->y, &en_Benben_bullet, SRCPAINT);
		pnew_en->y += 3;
		pnew_en = pnew_en->pNext;
	}
}
void CBullet::show(struct Node *pnew)//��ʾ�ӵ�
{
	while (pnew != NULL)
	{
		putimage(pnew->x, pnew->y, &bullet_mask, SRCAND);
		putimage(pnew->x, pnew->y, &bullet, SRCPAINT);
		pnew->y -= 8;
		pnew = pnew->pNext;
	}
}
void CBullet::show_gen(struct Node *pnew_gen)//��ʾ�����ӵ�
{
	int r = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	while (pnew_gen != NULL)
	{
		int i=0;
		putimage(pnew_gen->x, pnew_gen->y, &bullet_gen_mask, SRCAND);
		putimage(pnew_gen->x, pnew_gen->y, &bullet_gen, SRCINVERT);
		for (i = 0; i < 20; i++)//�������Ƿ���
		{
			if (enemy[i].iflive == 1)
				break;//����һ��α������ٵ��˳���
		}
		if (enemy[i].iflive == 1)
		{
			a = sqrt((pnew_gen->x - enemy[i].x)*(pnew_gen->x - enemy[i].x) + (pnew_gen->y - enemy[i].y)*(pnew_gen->y - enemy[i].y));
			b = pnew_gen->y - (enemy[i].y+50);
			c = pnew_gen->x - (enemy[i].x+25);
			if (a != 0)
			{
				pnew_gen->y -= 6 * b / a;
				pnew_gen->x -= 6 * c / a;
			}

		}
		
         if (enemy[i].iflive != 1)
		
			pnew_gen->y -= 6;

		pnew_gen = pnew_gen->pNext;
	}
}
void CBullet::show_low(struct Node * pnew_low)//��ʾ�����ӵ�
{
	while (pnew_low != NULL)
	{
		putimage(pnew_low->x, pnew_low->y, &bullet_low_mask, SRCAND);
		putimage(pnew_low->x, pnew_low->y, &bullet_low, SRCPAINT);
		pnew_low ->y -= 8;
		pnew_low = pnew_low->pNext;
	}
}


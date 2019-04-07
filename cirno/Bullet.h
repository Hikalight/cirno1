#pragma once


#include "image.h"

struct Node//�����ӵ��ṹ��
{
	int y;
	int x;
	int type;
	struct Node *pNext;
};

extern struct Node *pBullet;//�ӵ�ָ��
extern struct Node *gen_pBullet;//���ٵ�ָ��
extern struct Node *low_pBullet;//���ٵ�ָ��
extern struct Node *en_pBullet1;//�е�ָ��
extern struct Node *en1_pBullet1;
class CBullet
{
public:

	void create_highL1();//����������1�ӵ�����
	void create_highR1();//����������1�ӵ�����
	void gen_createL();//�������ٸ��ٵ���1����
	void gen_createR();//�������ٸ��ٵ���1����


	void create_lowL1();//����������1�ӵ�����
	void create_lowR1();//����������1�ӵ�����
	void create_lowL2();//����������2�ӵ�����
	void create_lowR2();//����������2�ӵ�����
	
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


	void show(Node * pnew);//��ʾ�����ӵ����ƶ�
	void show_gen(Node * pnew_gen);//��ʾ�����ӵ����ƶ�
	void show_low(Node * pnew_low);
	void show_en1(Node * pnew_en1);
	//��ʾ�����ӵ����ƶ�
	void show_en(Node *pnew_en);
};
//�ӵ���ʧ�����������߽�͵��������дһ��ɾ������ĺ������ں����������ɾ������
//���˺��ӵ����Ƿ������if ������ж��Ƿ�putimage
//�����ɵ����ӵ�������дһ��if��䣬ÿ�θ��±���һ�ε������飬�������Ƿ��0 or 1���������Ͳ�������������˵��ӵ�
//�����˵�λ����Ϣ���ӵ�λ����Ϣ����һ��Ϳ�����
//ÿ�θ��±���һ�ε���λ��

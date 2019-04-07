#include "pch.h"
#include "enemy.h"
#include"MMtimer.h"


ENEMY enemy[20];
ENEMY enemy1[10];

void ENEMY::enemy_move()
{
		putimage(x, y, &en_Benben_mask, SRCAND);
		putimage(x, y, &en_Benben, SRCPAINT);
		y += 1;
		if (a < 225)
			x++;
		if (a> 225&&a<500)
			x--;
}
void ENEMY::enemy1_move()
{

	putimage(x, y, &wolf_mask, SRCAND);
	putimage(x, y, &wolf, SRCPAINT);
	y += 1;
	if (a < 225)
		x++;
	if (a > 225 && a < 500)
		x--;

}
void ENEMY::enemy_death_limit()
{

	if ((iflive == 1) && (y >= 700))
		iflive = 0;
	if ((iflive == 1) && (x >= 500))
		iflive = 0;
	if ((iflive == 1) && (x <= 0))
		iflive = 0;
}

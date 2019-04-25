#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
static int box[930][630] = { 0 };//0没有 1箱子 2炸弹 3不可破坏障碍
static int b, m;
static int n = 1, ok=0;
static int  boom[930][630] = { 0 };
static HANDLE thread1, thread2;
static int direct, r1 =390, r2 = 240;
static int x = 0, y = 0;
DWORD ThreadID = NULL;

IMAGE tooth, bath, boxx,bomb,back,xg,xgu,xgd,xgr,xgl,gameover,gamewin,probat;
void game_over1() {
	closegraph();
	initgraph(930, 630);
	putimage(0, 0, &gameover);
	ok = 1;
	_getch();
}
void game_over() {
	
	TerminateThread(thread2, 0);
	closegraph();
	initgraph(930, 630);
	putimage(0, 0, &gameover);
	ok=1;
	_getch();
}
void game_win() {
	TerminateThread(thread2, 0);
	closegraph();
	initgraph(930, 630);
	putimage(0, 0, &gamewin);
	ok=1;
	_getch();
}
DWORD _stdcall bomb_show(LPVOID lpParameter)
{
	if (boom[b][m]== 1) {
		Sleep(3000);
		putimage(b, m, &xg);

		//上
		if (m != 0) {
			if (box[b][m - 30] != 3) {
				putimage(b, m - 30, &xgu);
				box[b][m - 30] = 0; box[b][m - 15] = 0; box[b + 15][m - 30] = 0; box[b + 15][m - 15] = 0;
			}
		}
		//下
		if (m != 600) {
			if (box[b][m + 30] != 3) {
				putimage(b, m + 30, &xgd);
				box[b][m + 30] = 0; box[b][m + 45] = 0; box[b + 15][m + 30] = 0; box[b + 15][m + 45] = 0;
			}
		}
		//左
		if (b != 0) {
			if (box[b - 30][m] != 3) {
				putimage(b - 30, m, &xgl);
				box[b - 30][m] = 0; box[b - 30][m + 15] = 0; box[b - 15][m] = 0; box[b - 15][m + 15] = 0;
			}
		}
		//右
		if (b != 900) {
			if (box[b + 30][m] != 3) {
				putimage(b + 30, m, &xgr);
				box[b + 30][m] = 0; box[b + 30][m + 15] = 0; box[b + 45][m] = 0; box[b + 45][m + 15] = 0;
			}
		}

		if ((r1 <= b + 45 && r1 >= b - 45 && r2 >= m - 15 && r2 <= m + 15) || (r2 <= m + 45 && r2 >= m - 45 && r1 >= b - 15 && r1 <= b + 15) ||(x<= b + 45 &&x>=b-45&&y>=m-15&&y<=m+15) || (y <= m + 45 && y >= m - 45 && x >= b - 15 && x <= b + 15)) {
			Sleep(450);
			game_over();
		}

		Sleep(900);
	
		//上
		if (box[b][m - 30] != 3) {
			putimage(b, m - 30, &back);
		}
		//下
		if (box[b][m + 30] != 3) {
			putimage(b, m + 30, &back);
		}
		//左
		if (box[b - 30][m] != 3) {
			putimage(b - 30, m, &back);
		}
		//右
		if (box[b + 30][m] != 3) {
			putimage(b + 30, m, &back);
		}
		putimage(b, m, &back);

		
	}
	box[b][m] = 0; box[b][m + 15] = 0; box[b + 15][m] = 0; box[b + 15][m + 15] = 0;
	boom[b][m] = 0;
	return 0;
}
DWORD _stdcall robat(LPVOID lpParameter) {
	putimage(r1, r2, &probat);
	while (1) {
		Sleep(300);
		direct = rand() % 4 +1;
		switch (direct) {

		case 1:r2 = r2 - 15;//up
			if ((r1 - 30) % 60 == 0 || r1 == 30) {
				r2 = r2 + 15;
				putimage(r1, r2, &probat);
			}
			else if ((r1 - 15) % 30 == 0 || r1 == 15) {
				r2 = r2 + 15;
				putimage(r1, r2, &probat);
			}
			else if (r2 < 0) {
				r2 = r2 + 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1][r2] == 1) {
				r2 = r2 + 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1][r2 + 15] == 2) {
				r2 = r2 - 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1][r2] == 2) {
				r2 = r2 + 15;

				putimage(r1, r2, &probat);
			}

			else
			{
				putimage(r1, r2 + 15, &back);

				putimage(r1, r2, &probat);
			}
			break;
		case 2:r2 = r2 + 15;//down
			if ((r1 - 30) % 60 == 0 || r1 == 30) {
				r2 = r2 - 15;
				putimage(r1, r2, &probat);
			}
			else if ((r1 - 15) % 30 == 0 || r1 == 15) {
				r2 = r2 - 15;
				putimage(r1, r2, &probat);
			}
			else if (r2 > 600) {
				r2 = r2 - 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1][r2 + 15] == 1) {
				r2 = r2 - 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1][r2 - 15] == 2) {
				r2 = r2 + 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1][r2 + 15] == 2) {
				r2 = r2 - 15;

				putimage(r1, r2, &probat);
			}
			else
			{
				putimage(r1, r2 - 15, &back);

				putimage(r1, r2, &probat);
			}
			break;
		case 3:r1 = r1 - 15;//left
			if ((r2 - 30) % 60 == 0 || r2 == 30) {
				r1 = r1 + 15;
				putimage(r1, r2, &probat);
			}
			else if ((r2 - 15) % 30 == 0 || r2 == 15) {
				r1 = r1 + 15;
				putimage(r1, r2, &probat);
			}
			else if (r1 < 0) {
				r1 = r1 + 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1][r2] == 1) {
				r1 = r1 + 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1 + 15][r2] == 2) {
				r1 = r1 - 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1][r2] == 2) {
				r1 = r1 + 15;

				putimage(r1, r2, &probat);
			}

			else
			{
				putimage(r1 + 15, r2, &back);

				putimage(r1, r2, &probat);
			}
			break;
		case 4:r1 = r1 + 15;//right
			if ((r2 - 30) % 60 == 0 || r2 == 30) {
				r1 = r1 - 15;
				putimage(r1, r2, &probat);
			}
			else if ((r2 - 15) % 30 == 0 || r2 == 15) {
				r1 = r1 - 15;
				putimage(r1, r2, &probat);
			}
			else if (r1 > 900) {
				r1 = r1 - 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1 + 15][r2] == 1) {
				r1 = r1 - 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1 - 15][r2] == 2) {
				r1 = r1 + 15;

				putimage(r1, r2, &probat);
			}
			else if (box[r1 + 15][r2] == 2) {
				r1 = r1 - 15;

				putimage(r1, r2, &probat);
			}

			else
			{
				putimage(r1 - 15, r2, &back);

				putimage(r1, r2, &probat);
			}
			break;
		}
		if (x<=r1+15&&x>=r1-15&&y<=r2+15&&y>=r2-15)
		{
			Sleep(350);
			game_over1();
			if (ok==1){
				ExitThread(0);
			}
		}
	}
	return 0;
}

void load()
{
loadimage(&probat, "probat.png");
loadimage(&boxx, "box.png"); 
loadimage(&bomb, "bomb.png");
loadimage(&back, "back.png");
loadimage(&xg, "xg.png");
loadimage(&xgu, "xgu.png");
loadimage(&xgd, "xgd.png");
loadimage(&xgr, "xgr.png");
loadimage(&xgl, "xgl.png");
loadimage(&gameover, "gameover.png");
loadimage(&gamewin, "gamewin.png");
}
void player()
{
	
	
	IMAGE player;
	loadimage(&player, "md.jpg");
	putimage(x,y, &player);
	while (1) {
		if (_kbhit())
		{
			int k = _getch();
			if ( k== 0xE0) {
				switch (_getch()) {
				case 72:y = y - 15;//up
					if ((x - 30) % 60 == 0 || x == 30) { y = y + 15; loadimage(&player, "mu.jpg");
					putimage(x, y, &player);
					}
					else if ((x - 15) % 30 == 0 || x == 15) { y = y + 15; loadimage(&player, "mu.jpg");
					putimage(x, y, &player);
					}
					else if (y < 0){ y = y + 15; 
						loadimage(&player, "mu.jpg");
						putimage(x, y, &player); }
					else if (box[x][y] == 1) {
						y = y + 15;
						loadimage(&player, "mu.jpg");
						putimage(x, y, &player);
					}
					else if (box[x][y + 15] == 2) {
						y = y - 15;
						loadimage(&player, "mu.jpg");
						putimage(x, y, &player);
					}
					else if (box[x][y] == 2) {
						y = y + 15;
						loadimage(&player, "mu.jpg");
						putimage(x, y, &player);
					}
					
					else
					{
					putimage(x, y+15, &back);
					loadimage(&player, "mu.jpg");
					putimage(x, y, &player);}
					break;
				case 80:y = y + 15;//down
					if ((x - 30) % 60 == 0 || x == 30) { y = y - 15; loadimage(&player, "md.jpg");
					putimage(x, y, &player);
					}
					else if ((x - 15) % 30 == 0 || x == 15) { y = y - 15; loadimage(&player, "md.jpg");
					putimage(x, y, &player);
					}
					else if (y > 600){ y = y - 15; 
						loadimage(&player, "md.jpg");
						putimage(x, y, &player); }
					else if (box[x][y + 15] == 1) {
						y = y - 15;
						loadimage(&player, "md.jpg");
						putimage(x, y, &player);
					}
					else if (box[x][y - 15] == 2) {
						y = y + 15;
						loadimage(&player, "md.jpg");
						putimage(x, y, &player);
					}
					else if (box[x][y+15] == 2) {
						y = y - 15;
						loadimage(&player, "md.jpg");
						putimage(x, y, &player);
					}
					else
					{
					putimage(x, y - 15, &back);
					loadimage(&player, "md.jpg");
					putimage(x, y, &player);}
					break;
				case 75:x = x - 15;//left
					if ((y- 30) % 60 == 0 || y == 30) { x = x + 15; loadimage(&player, "ml.jpg");
					putimage(x, y, &player);
					}
					else if ((y - 15) % 30 == 0 || y == 15) {x = x + 15; loadimage(&player, "ml.jpg");
					putimage(x, y, &player);
					}
					else if (x < 0) {x = x + 15; 
						loadimage(&player, "ml.jpg");
						putimage(x, y, &player);
					}
					else if (box[x][y] == 1) {
						x = x + 15;
						loadimage(&player, "ml.jpg");
						putimage(x, y, &player);
					}
					else if (box[x + 15][y] == 2) {
						x = x - 15;
						loadimage(&player, "ml.jpg");
						putimage(x, y, &player);
					}
					else if (box[x][y] == 2) {
						x = x + 15;
						loadimage(&player, "ml.jpg");
						putimage(x, y, &player);
					}
					
					else
					{
					putimage(x+15, y, &back);
					loadimage(&player, "ml.jpg");
					putimage(x, y, &player);}
					break;
				case 77:x = x + 15;//right
					if ((y - 30) % 60 == 0 || y == 30) { x = x - 15; loadimage(&player, "mr.jpg");
					putimage(x, y, &player);
					}
					else if ((y - 15) % 30 == 0 || y == 15) { x = x -15; loadimage(&player, "mr.jpg");
					putimage(x, y, &player);
					}
					else if (x > 900) {x = x - 15; 
						loadimage(&player, "mr.jpg");
						putimage(x, y, &player); }
					else if (box[x + 15][y] == 1) {
						x = x - 15;
						loadimage(&player, "mr.jpg");
						putimage(x, y, &player);
					}
					else if (box[x-15][y] == 2) {
						x = x + 15;
						loadimage(&player, "mr.jpg");
						putimage(x, y, &player);
					}
					else if (box[x+15][y] == 2) {
						x = x - 15;
						loadimage(&player, "mr.jpg");
						putimage(x, y, &player);
					}
					
					else
					{
					putimage(x - 15, y, &back);
					loadimage(&player, "mr.jpg");
					putimage(x, y, &player); }
					break;
				}
				
			}
			if (k == 0x20) {
				if (n == 1&&x%30==0&&y%30==0) {
					putimage(x, y, &bomb); box[x][y] = 2; box[x][y + 15] = 2; box[x + 15][y] = 2; box[x + 15][y + 15] = 2; n++; b = x; m = y; boom[b][m] = 1;
					thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bomb_show, NULL, 0, &ThreadID);
				}
				if (boom[b][m] != 1 && x % 30 == 0 && y % 30 == 0) {
					boom[x][y] = 1;
					putimage(x, y, &bomb); box[x][y] = 2; box[x][y + 15] = 2; box[x + 15][y] = 2; box[x + 15][y + 15] = 2; b = x; m = y; boom[b][m] = 1;
					thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bomb_show, NULL, 0, &ThreadID);
				}
			}
		}
	}
}
void background()
{
	initgraph(930, 630);											
	for (int y = 0; y <= 630; y++)										
	{
		setcolor(RGB(40,150,255));
		line(0, y, 930, y);
	}
	int i, j;
for (i = 30; i < 900; i = i + 60)												
	{
		for (j = 30; j < 600; j = j + 60)
		{
			loadimage(&tooth, "toothbrush.png");
			box[i][j] = 3;
			putimage(i, j, &tooth);										
		}
	}
for (i = 0; i <= 30; i = i + 2)
{
	for (j = 0; j <=11; j=j+1)
	{
		int y;
		y = rand() % 23;
		putimage(i*30, y*30, &boxx);
		box[i*30][y*30] = 1; box[i*30][y*30 + 15] =1; box[i*30 + 15][y*30] =1; box[i*30 + 15][y*30 + 15] = 1;
	}
}
}
int main()
{
	thread2 = CreateThread(NULL, 0, robat, NULL, 0, &ThreadID);
	load();
	background();
	while (true)
	{
		player();
		if (ok==1) {
			CloseHandle(thread1);
			CloseHandle(thread2);
			

			break;
		}
	}
	//_getch();
	closegraph();
	return 0;
}           
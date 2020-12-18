
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>


#pragma warning(disable:4996)
//#pragma warning(disable:2229)
constexpr auto maphigh = 28, mapwide = 84;

struct virus
{
	int x;
	int y;
}virus;
unsigned short snakesize = 50, speed = 300, len = 4;
struct snake
{
	int x[50];
	int y[50];
	int len;//蛇的長度
	int speed;//蛇的速度
}snake;
int key = 'w';//初始化方向
void gotoxy(int x, int y);
void drawmap();
void keydown();
void creatvirus();
int snakestatus();
void startgame();
int menuselect();
void goodbye();
void introduce();
void edition();
int setup();
void respect();
int setup1();
int modifydiffculty();
void diffculty();
int customize();
void customize1();
int main()
{
	for (;;)
	{
		system("cls");//清屏
		switch (menuselect())
		{
		case 1://開始遊戲
			startgame();
			break;
		case 2://介紹
			introduce();
			break;
		case 3://版本
			edition();
			break;
		case 4://設定
			setup1();
			break;
		case 5:
			goodbye();
			return 0;
		default:
			break;
		}
	}
}
void drawmap()//1.畫地圖
{
	//⊙:病毒    █：蛇身(佔用兩個字元）
	srand((unsigned int)time(NULL));//隨機病毒出現的位置
	int i, k;
	for (i = 0; i <= maphigh; i++)
	{
		gotoxy(0, i);
		printf("█");//列印左邊框
		gotoxy(mapwide, i);
		printf("█");//列印右邊框
	}
	for (i = 0; i <= mapwide; i += 2)//+=2因為 █佔兩個位元組
	{
		gotoxy(i, 0);
		printf("█");//列印下邊框
		gotoxy(i, maphigh);
		printf("█");//列印上邊框
	}
	//畫蛇
	snake.len = len;
	snake.speed = speed;
	//初始化蛇的位置
	snake.x[0] = mapwide / 2;
	snake.y[0] = maphigh / 2;//[0]為蛇頭的位置
	//畫蛇頭
	gotoxy(snake.x[0], snake.y[0]);
	printf("█");
	//畫蛇身
	for (k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 2;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		printf("█");
	}
	while (1)
	{
		virus.x = rand() % (mapwide - 4) + 2;//+2,+1這個與█所佔的字元有關，長佔兩個字元寬1個
		virus.y = rand() % (maphigh - 2) + 1;//畫個圖，顯而易見
		if (virus.x % 2 == 0)
			break;
	}
	gotoxy(virus.x, virus.y);
	printf("⊙");
	gotoxy(mapwide + 4, maphigh);
	printf("⊙:%d", snakesize - snake.len);
}
void creatvirus()//2.產生病毒
{
	if (snake.x[0] == virus.x && snake.y[0] == virus.y)
	{
		//printf("\a");//聲音
		snake.len++;
		srand((unsigned)time(NULL));
		while (1)
		{
			int flag = 1;
			virus.x = rand() % (mapwide - 4) + 2;//+2,+1這個與█所佔的字元有關，長佔兩個字元寬1個
			virus.y = rand() % (maphigh - 2) + 1;//畫個圖，顯而易見
		//產生的病毒不能在蛇的身上
			for (int k = 0; k < snake.len; k++)
			{
				if (snake.x[k] == virus.x && snake.y[k] == virus.y)
				{
					flag = 0;//virus不合適的標誌
					break;
				}
			}
			if (flag == 1 && virus.x % 2 == 0)//病毒位置合法且x座標為偶數
			{//x左右是以兩個位元組為單位運動的，若virus的x座標為奇數，就不存在snake.x[k] == virus.x
				break;
			}
		}
	}
	gotoxy(virus.x, virus.y);
	printf("⊙");
	gotoxy(mapwide + 8, 0);//將游標移走
	printf("W");
	gotoxy(mapwide + 6, 1);
	printf("A S D \t進行控制");
	gotoxy(mapwide + 4, maphigh);
	printf("⊙:%d", snakesize - snake.len);
}
void keydown()//3.按鍵
{
	int i, temp;
	if (_kbhit()) //kbhit函式檢查當前是否有鍵盤輸入，若有則返回一個非0值，否則返回0
	{
		fflush(stdin);// 清空輸入緩衝區，通常是為了確保不影響後面的資料讀取
		temp = _getch();//getch:從控制檯讀取一個字元，但不顯示在螢幕上
		if ((temp == 'a' || temp == 'A') && (key != 'D' && key != 'd'))//解決了按反方向鍵蛇自殺的問題
		{
			key = temp;
		}
		if ((temp == 'w' || temp == 'W') && (key != 's' && key != 'S'))
		{
			key = temp;
		}
		if ((temp == 's' || temp == 'S') && (key != 'W' && key != 'w'))
		{
			key = temp;
		}
		if ((temp == 'D' || temp == 'd') && (key != 'a' && key != 'A'))
		{
			key = temp;
		}
	}
	//擦除最後一節
	gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
	printf("  ");
	for (i = snake.len - 1; i > 0; i--)
	{
		snake.x[i] = snake.x[i - 1];//以前1的位置現在變成了2，0變成了1
		snake.y[i] = snake.y[i - 1];
	}
	switch (key)//最後一節已經擦出，前移後0,1位置重合,左上角座標為0，0
	{
	case'w':
	case'W':
		snake.y[0]--;
		break;
	case's':
	case'S':
		snake.y[0]++;
		break;
	case'a':
	case'A':
		snake.x[0] -= 2;
		break;
	case'd':
	case'D':
		snake.x[0] += 2;
		break;
	}
	gotoxy(snake.x[0], snake.y[0]);
	printf("█");
	gotoxy(mapwide + 2, 0);//將游標移走
}
int snakestatus()//4.蛇的狀態
{
	if ((snake.x[0] == 0 || snake.x[0] == mapwide) || (snake.y[0] == 0 || snake.y[0] == maphigh))
		return 0;
	for (int k = 1; k < snake.len; k++)
	{
		if (snake.x[0] == snake.x[k] && snake.y[0] == snake.y[k])
			return 0;
	}
	return 1;
}
void gotoxy(int x, int y)
{//1.找到控制檯這個視窗
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	/*HANDLE為控制程式碼  ↑得到（輸出視窗的）控制程式碼。
	Windows是一個以虛擬記憶體為基礎的作業系統，很多時候，
	程式的程式碼和資料並不全部裝入記憶體，程式的某一段裝入記憶體後，
	還可能被換出到外存，當再次需要時，再裝入記憶體。兩次裝入的地址絕大多數情況下是不一樣的。
	也就是說，同一物件在記憶體中的地址會變化。那麼，程式怎麼才能準確地訪問到物件呢？為了解決這個問題，Windows引入了控制程式碼。
	數值上，是一個32位無符號整型值（32位系統下）；邏輯上，相當於指標的指標；形象理解上，是Windows中各個物件的一個唯一的、固定不變的ID；
	作用上，Windows使用控制程式碼來標識諸如視窗、點陣圖、畫筆等物件，並通過控制程式碼找到這些物件。*/
	//2.設定游標
	COORD coord;
	/*COORD 為Windows.h中自帶函式原型大體為struct _coord{short x;short y;}coord;*/
	coord.X = x;
	coord.Y = y;
	//4.同步到控制檯SetConsoleCursorPosition
	SetConsoleCursorPosition(handle, coord);//定位到handle這個視窗，把游標打在coord座標
}
void startgame()
{
	system("cls");
	drawmap();
	while (1)
	{
		creatvirus();
		keydown();
		Sleep(snake.speed);//void sleep(int seconds)自帶函式引數 seconds 為要暫停的毫秒數。
		if (!snakestatus())//判斷死亡時snakestaus為0,
		{
			gotoxy(mapwide / 2, maphigh / 2);
			printf("Game Over");
			getchar();
			getchar();
			break;
		}
		if (snake.len == snakesize)
		{
			gotoxy(mapwide / 3, maphigh / 2);
			printf("恭喜您消滅了全部病毒，勝利(＾－＾)V");
			getchar();
			respect();
			break;
		}
	}
}
int menuselect()
{
	char number;
	int a;
	printf("\n\n\t\t\t\t\t\t1.開始遊戲\n");
	printf("\n\t\t\t\t\t\t2.遊戲介紹\n");
	printf("\n\t\t\t\t\t\t3.遊戲版本\n");
	printf("\n\t\t\t\t\t\t4.設定\n");
	printf("\n\t\t\t\t\t\t5.退出遊戲\n");
	printf("\n\t\t\t\t\t\t請選擇（數字）");
	while (1)
	{
		number = getchar();
		a = (int)number - 48;
		if (number <= '5' && number >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
void goodbye()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//設定紅色
	gotoxy(0, 12);
	printf("\t\t\t\t\t\t謝謝使用！再見！\n");
	getchar();
	getchar();
}
void respect()
{
	system("cls");
	gotoxy(0, 4);
	printf("\t\t*在此向全國的醫護人員表示敬意*\n\n");
	Sleep(1000);
	printf("\t\t*感謝他們的默默付出*\n\n");
	Sleep(1000);
	printf("\t\t*感謝他們對抗擊疫情做出的貢獻*\n\n");
	Sleep(1000);
	printf("\t\t*此致*\n\n");
	printf("\t\t*                      敬禮 *\n\n");
	Sleep(2000);
	getchar();
}
void introduce()
{
	system("cls");
	gotoxy(0, 4);
	printf("\t\t\t\t        遊戲規則           \n\n");
	printf("\t\t\t\t2020年新冠病毒肆虐，威脅著人類\n\n");
	printf("\t\t\t\t玩家將控制蛇消滅隨機出現的病毒⊙\n\n");
	printf("\t\t\t\t消滅所有病毒即可獲得勝利。\n\n");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\tEnter返回主選單");
	getchar();
	getchar();
}
void edition()
{
	system("cls");
	gotoxy(0, 4);
	printf("\t\t\t\t*********************************************\n\n");
	printf("\t\t\t\t*               歡         迎               *\n\n");
	printf("\t\t\t\t*                版本號： 1.2               *\n\n");
	printf("\t\t\t\t*        更新：1.修復了反方向自殺的問題     *\n\n");
	printf("\t\t\t\t*              2.修復了蛇吃牆的問題         *\n\n");
	printf("\t\t\t\t*              3.新增了選單與設定功能       *\n\n");
	printf("\t\t\t\t*              4.修改了部分整形變數節省空間 *\n\n");
	printf("\t\t\t\t*********************************************\n\n");
	printf("\t\t\t\t\tEnter返回主選單");
	getchar();
	getchar();
}
int setup()
{
	//system("color 6f"); //第一個為背景色，第二個為字型顏色
   /*0 = 黑色       8 = 灰色
	1 = 藍色       9 = 淡藍色
	2 = 綠色       A = 淡綠色
	3 = 湖藍色     B = 淡淺綠色
	4 = 紅色       C = 淡紅色
	5 = 紫色       D = 淡紫色
	6 = 黃色       E = 淡黃色
	7 = 白色       F = 亮白色*/
	char s;
	int a;
	system("cls");
	printf("\n\n\t\t\t\t\t\t1.修改難度\n");
	printf("\n\t\t\t\t\t\t2.自義定設定\n");
	printf("\n\t\t\t\t\t\t3.顏色設定\n");
	printf("\n\t\t\t\t\t\t4.音效設定\n");
	printf("\n\t\t\t\t\t\t5.返回\n");
	printf("\n\t\t\t\t\t\t請選擇（數字）");
	while (1)
	{
		s = getchar();
		a = (int)s - 48;
		if (s <= '5' && s >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
int setup1()
{
	switch (setup())
	{
	case 1:
		diffculty();
		break;
	case 2:
		customize1();
		break;
	default:
		break;
	}
	return 0;
}
int modifydiffculty()
{
	char s;
	int a;
	system("cls");
	printf("\n\n\t\t\t\t\t\t1.簡單\n");
	printf("\n\t\t\t\t\t\t2.普通\n");
	printf("\n\t\t\t\t\t\t3.困難\n");
	printf("\n\t\t\t\t\t\t4.修羅地獄\n");
	printf("\n\t\t\t\t\t\t請選擇（數字）");
	while (1)
	{
		s = getchar();
		a = (int)s - 48;
		if (s <= '4' && s >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
void diffculty()
{
	switch (modifydiffculty())
	{
	case 1:
		len = 4;
		speed = 500;
		snakesize = 10;
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t 修改成功！\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 2:
		len = 4;
		speed = 300;
		snakesize = 25;
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t 修改成功！\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 3:
		len = 4;
		speed = 70;
		snakesize = 50;
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t 修改成功！\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	case 4:
		len = 4;
		speed = 25;
		snakesize = 70;
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t\t\t 修改成功！\n");
		printf("\t\t\t\t\t\t \n");
		system("pause");
		break;
	default:
		break;
	}
}
int customize()
{
	char s;
	int a;
	system("cls");
	printf("\n\n\t\t\t\t\t\t1.自定義速度\n");
	printf("\n\t\t\t\t\t\t2.自定義初始長度\n");
	printf("\n\t\t\t\t\t\t請選擇（數字）");
	while (1)
	{
		s = getchar();
		a = (int)s - 48;
		if (s <= '2' && s >= '1')
			return a;
		printf("\n\t\t\t\t\t\t\t      ");
	}
}
void customize1()
{
	int s;
	switch (customize())
	{
	case 1://自定義速度
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t請輸入速度(1-999)");
		scanf_s("%d", &s);
		speed = (1000 - s);
		break;
	case 2:
		system("cls");
		gotoxy(8, 8);
		printf("\t\t\t\t請輸入初始長度：");
		scanf_s("%d", &s);
		len = s;
		break;
	default:
		break;
	}
}
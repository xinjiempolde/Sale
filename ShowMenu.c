/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: ShowMenu.c
 * Author:   刘小辉
 * Date:     2019年12月08日
 *
 * Description: 显示类函数定义
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "ShowMenu.h"
#include "time.h"
#include <stdio.h>
#include <Windows.h>
void SetColor(short x)
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //只有一个参数，改变字体颜色   
	else//默认的颜色白色  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void SetPos(int x, int y)
{
	COORD point = { x, y };//光标要设置的位置x,y
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
	SetConsoleCursorPosition(HOutput, point);//设置光标位置
}
void EchoTime()
{
	stTime now_time;
	GetTime(&now_time);
	SetPos(105, 0);
	printf("%d年%d月%d日", now_time.iYear, now_time.iMonth, now_time.iDay);
	SetPos(109, 1);
	printf("%d:%d", now_time.iHour, now_time.iMin);
	SetPos(0, 0);
}
void ShowMainMenu()
{
	SetConsoleTitleA("零售商业销售管理系统");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------欢迎进入---------------------------|\n");
	printf("\t\t\t|                     零售商业销售管理系统                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                            主菜单                            |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        0、退出系统                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        1、登录系统                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        2、系统说明                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	printf("\t\t\t请输入您的选择(0-2):");
}

void ShowProgressBar()
{
	system("cls");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
	for (int i = 0; i < 60; i++)
	{
		pos.X = 48;	pos.Y = 13;
		SetConsoleCursorPosition(hOut, pos);
		SetConsoleTextAttribute(hOut, 7);
		printf("密码正确，正在登陆系统........");
		printf("%d%%", 5 * i / 3 + 2);
		Sleep(15);
		pos.X = i + 28;	pos.Y = 15;
		SetConsoleCursorPosition(hOut, pos);
		SetConsoleTextAttribute(hOut, 240);
		printf("  ");
		Sleep(5);
	}
	SetConsoleTextAttribute(hOut, 7);
	cci.bVisible = 1;
	SetConsoleCursorInfo(hOut, &cci);
}

void ShowSysInfo()
{
	SetConsoleTitleA("零售商业销售管理系统的介绍");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------欢迎进入---------------------------|\n");
	printf("\t\t\t|                     零售商业销售管理系统                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|        本系统主要功能包括用户登录、购物车、结算等功能        |\n");
	printf("\t\t\t|        还包括面向管理的商品管理、库存管理、销售统计          |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                       按任意键返回                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	getch();
}

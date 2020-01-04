/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: ShowMenu.c
 * Author:   ��С��
 * Date:     2019��12��08��
 *
 * Description: ��ʾ�ຯ������
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "ShowMenu.h"
#include "time.h"
#include <stdio.h>
#include <Windows.h>
void SetColor(short x)
{
	if (x >= 0 && x <= 15)//������0-15�ķ�Χ��ɫ  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //ֻ��һ���������ı�������ɫ   
	else//Ĭ�ϵ���ɫ��ɫ  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void SetPos(int x, int y)
{
	COORD point = { x, y };//���Ҫ���õ�λ��x,y
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);//ʹ��GetStdHandle(STD_OUTPUT_HANDLE)����ȡ��׼����ľ��
	SetConsoleCursorPosition(HOutput, point);//���ù��λ��
}
void EchoTime()
{
	stTime now_time;
	GetTime(&now_time);
	SetPos(105, 0);
	printf("%d��%d��%d��", now_time.iYear, now_time.iMonth, now_time.iDay);
	SetPos(109, 1);
	printf("%d:%d", now_time.iHour, now_time.iMin);
	SetPos(0, 0);
}
void ShowMainMenu()
{
	SetConsoleTitleA("������ҵ���۹���ϵͳ");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------��ӭ����---------------------------|\n");
	printf("\t\t\t|                     ������ҵ���۹���ϵͳ                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                            ���˵�                            |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        0���˳�ϵͳ                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        1����¼ϵͳ                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        2��ϵͳ˵��                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	printf("\t\t\t����������ѡ��(0-2):");
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
		printf("������ȷ�����ڵ�½ϵͳ........");
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
	SetConsoleTitleA("������ҵ���۹���ϵͳ�Ľ���");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------��ӭ����---------------------------|\n");
	printf("\t\t\t|                     ������ҵ���۹���ϵͳ                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|        ��ϵͳ��Ҫ���ܰ����û���¼�����ﳵ������ȹ���        |\n");
	printf("\t\t\t|        ����������������Ʒ��������������ͳ��          |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                       �����������                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	getch();
}

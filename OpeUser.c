/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: OpeUser.c
 * Author:   ��С��
 * Date:     2019��12��08��
 *
 * Description: �̼Ҳ����ĺ�������
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "OpeUser.h"
#include "SafeUtils.h"
#include <stdio.h>
#include <stdlib.h>
extern int iGoodsRecord;
void ope_callback()
{
	int flag;
	while (1)
	{
		ShowOpeUserMenu();
		if (scanf("%d", &flag) != 1)
		{
			getchar();
		}
		switch (flag)
		{
		case 0:
			return;
		case 1:
			AddGoods();
			break;
		case 2:
			DeleteGoods();
			break;
		case 3:
			ShowSaleInfo();
			break;
		default:
			printf("�����ڸ�ѡ�����������");
			Sleep(1000);
			break;
		}
	}
}

void ShowOpeUserMenu()
{
	SetConsoleTitleA("�̼ҹ������");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------��ӭ����---------------------------|\n");
	printf("\t\t\t|                     ������ҵ���۹���ϵͳ                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                         �̼ҹ������                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        0��������һ��                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        1��������Ʒ                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        2���˹���Ʒ                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        3���鿴������Ʒ��Ϣ                   |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	printf("\t\t\t����������ѡ��(0-3):");
}

void AddGoods()
{
	system("cls");
	goods tmp;
	FILE* fpWriteDate;
	fpWriteDate = fopen("goods.dat", "ab+");
	printf("�����������Ʒ��ţ�");
	if (input_num(&tmp.number) == WRONG) return;
	printf("�����������Ʒ���ƣ�");
	scanf("%s", tmp.name);
	printf("�����������Ʒ������");
	if (input_num(&tmp.inventory) == WRONG) return;
	printf("��������Ʒ���ۣ�");
	scanf("%lf", &tmp.price);
	printf("��������Ʒ�ۿ�������");
	if (input_num(&tmp.span) == WRONG) return;
	tmp.saleNum = 0;
	GetTime(&tmp.time);
	fwrite(&tmp, LEN_GOODS, 1, fpWriteDate);
	fclose(fpWriteDate);
	printf("��ӳɹ�������������أ�");
	getch();
}

void DeleteGoods()
{
	int iGoodsRecord = GetGoodsFile();
	int number;
	printf("������Ҫ�˻�����Ʒ��ţ�");
	scanf("%d", &number);
	int position = SearchGoods(number);
	if (position == GOODS_NOT_FOUND)
	{
		printf("û�и���Ʒ������������أ�");
		getch();
	}
	for (int i = position; i < iGoodsRecord - 1; i++)
	{
		astGoods[i] = astGoods[i + 1];
	}
	iGoodsRecord--;
	FILE* fpWriteData = fopen("goods.dat", "wb");
	if (!fpWriteData)
	{
		printf("���ļ�ʧ�ܣ�");
		return;
	}
	for (int i = 0; i < iGoodsRecord; i++)
	{
		fwrite(&astGoods[i], LEN_GOODS, 1, fpWriteData);
	}
	fclose(fpWriteData);
	printf("�˹���Ʒ�ɹ����������������");
	getch();
}

void ShowSaleInfo()
{
	system("cls");
	printf("������Ʒ��Ϣ���£�\n");
	int iGoodsRecord = GetGoodsFile();
	printf("|----------------------------------------------------------------------------------------------------|\n");
	printf("%-8s %-20s %-8s %-8s %-8s %-20s %-10s\n", "��Ʒ���", "��Ʒ����", "��Ʒ�ۼ�", "���", "������", "�ۿۿ�ʼʱ��","�ۿ۳���");
	for (int i = 0; i < iGoodsRecord; i++)
	{
		printf("%-8d %-20s %-8.2lf %-8d %-8d ", astGoods[i].number, astGoods[i].name, astGoods[i].price, astGoods[i].inventory, astGoods[i].saleNum);
		printf("%-d��%d��%d%-9s", astGoods[i].time.iYear, astGoods[i].time.iMonth, astGoods[i].time.iDay, "��");
		printf("%-d��\n", astGoods[i].span);
	}
	printf("|----------------------------------------------------------------------------------------------------|\n");
	system("pause");
}

int GetGoodsFile()
{
	iGoodsRecord = 0;
	FILE* fpGetdata;
	fpGetdata = fopen("goods.dat", "rb");
	if (!fpGetdata)
	{
		printf("���ļ�ʧ�ܣ�");
		return 0;
	}
	while (!feof(fpGetdata))
	{
		if (fread(&astGoods[iGoodsRecord], LEN_GOODS, 1, fpGetdata) == 1)
		{
			iGoodsRecord++;
		}
	}
	return iGoodsRecord;
}

int SearchGoods(int number)
{
	iGoodsRecord = GetGoodsFile();
	for (int i = 0; i < iGoodsRecord; i++)
	{
		if (astGoods[i].number == number)
		{
			return i;
		}
	}
	return GOODS_NOT_FOUND;
}

void SaveGoodsData()
{
	FILE* fpWriteData = fopen("goods.dat", "wb");
	for (int i = 0; i < iGoodsRecord; i++)
	{
		fwrite(&astGoods[i], LEN_GOODS, 1, fpWriteData);
	}
	fclose(fpWriteData);
}

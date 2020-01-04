/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: OpeUser.c
 * Author:   刘小辉
 * Date:     2019年12月08日
 *
 * Description: 商家操作的函数定义
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
			printf("不存在该选项，请重新输入");
			Sleep(1000);
			break;
		}
	}
}

void ShowOpeUserMenu()
{
	SetConsoleTitleA("商家管理界面");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------欢迎进入---------------------------|\n");
	printf("\t\t\t|                     零售商业销售管理系统                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                         商家管理界面                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        0、返回上一级                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        1、进购商品                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        2、退购商品                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        3、查看所有商品信息                   |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	printf("\t\t\t请输入您的选择(0-3):");
}

void AddGoods()
{
	system("cls");
	goods tmp;
	FILE* fpWriteDate;
	fpWriteDate = fopen("goods.dat", "ab+");
	printf("请输入进购商品编号：");
	if (input_num(&tmp.number) == WRONG) return;
	printf("请输入进购商品名称：");
	scanf("%s", tmp.name);
	printf("请输入进购商品数量：");
	if (input_num(&tmp.inventory) == WRONG) return;
	printf("请输入商品卖价：");
	scanf("%lf", &tmp.price);
	printf("请输入商品折扣天数：");
	if (input_num(&tmp.span) == WRONG) return;
	tmp.saleNum = 0;
	GetTime(&tmp.time);
	fwrite(&tmp, LEN_GOODS, 1, fpWriteDate);
	fclose(fpWriteDate);
	printf("添加成功，按任意键返回！");
	getch();
}

void DeleteGoods()
{
	int iGoodsRecord = GetGoodsFile();
	int number;
	printf("请输入要退货的商品编号：");
	scanf("%d", &number);
	int position = SearchGoods(number);
	if (position == GOODS_NOT_FOUND)
	{
		printf("没有该商品，按任意键返回！");
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
		printf("打开文件失败！");
		return;
	}
	for (int i = 0; i < iGoodsRecord; i++)
	{
		fwrite(&astGoods[i], LEN_GOODS, 1, fpWriteData);
	}
	fclose(fpWriteData);
	printf("退购商品成功，按任意键继续！");
	getch();
}

void ShowSaleInfo()
{
	system("cls");
	printf("所有商品信息如下：\n");
	int iGoodsRecord = GetGoodsFile();
	printf("|----------------------------------------------------------------------------------------------------|\n");
	printf("%-8s %-20s %-8s %-8s %-8s %-20s %-10s\n", "商品编号", "商品名称", "商品售价", "库存", "销售量", "折扣开始时间","折扣持续");
	for (int i = 0; i < iGoodsRecord; i++)
	{
		printf("%-8d %-20s %-8.2lf %-8d %-8d ", astGoods[i].number, astGoods[i].name, astGoods[i].price, astGoods[i].inventory, astGoods[i].saleNum);
		printf("%-d年%d月%d%-9s", astGoods[i].time.iYear, astGoods[i].time.iMonth, astGoods[i].time.iDay, "日");
		printf("%-d天\n", astGoods[i].span);
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
		printf("打开文件失败！");
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

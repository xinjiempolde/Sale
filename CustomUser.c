/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: CustomUser.c
 * Author:   刘小辉
 * Date:     2019年12月08日
 *
 * Description: 用户操作的函数定义
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "CustomUser.h"
#include "OpeUser.h"
#include "SafeUtils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
void Customer_callback(int CustomerId)
{
	cart.count = 0;
	int flag;
	while (1)
	{
		ShowCustomerMenu();
		if (scanf("%d", &flag))
			getchar();
		switch (flag)
		{
		case 0:
			return;
		case 1:
			AddChart();
			break;
		case 2:
			break;
		case 3:
			ShowChart();
			break;
		case 4:
			ClearChart();
			break;
		case 5:
			CheckOut(CustomerId);
			break;
		case 6:
			ShowMyInfo(CustomerId);
			break;
		default:
			break;
		}
	}
}

void ShowCustomerMenu()
{
	SetConsoleTitleA("用户界面");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------欢迎进入---------------------------|\n");
	printf("\t\t\t|                     零售商业销售管理系统                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                           用户菜单                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        0、返回上一级                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        1、添加商品到购物车                   |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        2、减少购物车中的商品                 |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        3、查看购物车中的商品                 |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        4、清空购物车                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        5、结算购物车                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        6、查看我的购物详情                   |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	printf("\t\t\t请输入您的选择(0-5):");
}

void AddChart()
{
	int number, count;
	ShowSaleInfo();
	printf("请输入您想要购买的商品id：");
	if (scanf("%d", &number) != 1)
		getchar();
	int goodsSearchId = SearchGoods(number);
	if (goodsSearchId == GOODS_NOT_FOUND)
	{
		printf("不存在该商品ID，按任意键返回！");
		getch();
		return;
	}
	printf("请输入要购买的商品数量：");
	if (input_num(&count) == WRONG) return;
	// 商品库存不足
	if (count > astGoods[goodsSearchId].inventory)
	{
		printf("商品库存不足，按任意键返回！");
		getch();
		return;
	}
	stTime now_time, deadline_time;
	AddTime(astGoods[goodsSearchId].span, astGoods[goodsSearchId].time, &deadline_time);
	GetTime(&now_time);
	double iDiscountRatio = 1;
	// 在折扣时间内打折
	if (CompareTime(&now_time, &deadline_time) == TIME_OLDER)
	{
		iDiscountRatio = 0.7;
	}
	cart.aiGoodsId[cart.count] = number;
	cart.aiPrice[cart.count] = astGoods[goodsSearchId].price * (double)iDiscountRatio;
	strcpy(cart.goods[cart.count], astGoods[goodsSearchId].name);
	cart.goodsCount[cart.count] = count;
	cart.count++;
	printf("添加至购物车成功，按任意键继续！\n");
	getch();
}

void ClearChart()
{
	cart.count = 0;
	memset(cart.goods, 0, sizeof(cart.goods));
	printf("清空购物车成功，按任意键继续！\n");
	getch();
}

void ShowChart()
{
	system("cls");
	printf("您的购物车里商品如下：\n");
	printf("|= = = = = = = = = = = = = = = = = = = =|\n");
	printf("%-10s %-10s %-10s\n", "商品编号", "商品名称", "购买数量");
	for (int i = 0; i < cart.count; i++)
	{
		printf("%-10d %-10s %-10d\n", cart.aiGoodsId[i], cart.goods[i], cart.goodsCount[i]);
	}
	printf("|= = = = = = = = = = = = = = = = = = = =|\n");
	getch();
}

void CheckOut(int customerId)
{
	system("cls");
	double iTotalCost = 0;
	int position = SearchCustomer(customerId);
	GetGoodsFile();	// 读取商品信息，需要修改库存和月销量
	for (int i = 0; i < cart.count; i++)
	{
		astCustomer[position].aiGoodsID[i] = cart.aiGoodsId[i];
		strcpy(astCustomer[position].acGoodsName[i], cart.goods[i]);
		astCustomer[position].GoodsCount[i] = cart.goodsCount[i];
		iTotalCost += cart.aiPrice[i] * cart.goodsCount[i];
		int GoodsId = SearchGoods(cart.aiGoodsId[i]);
		astGoods[GoodsId].inventory -= cart.goodsCount[i];	// 库存减少用户购买数量
		astGoods[GoodsId].saleNum += cart.goodsCount[i];	// 销量增加用户购买数量
	}
	astCustomer[position].iAmount += cart.count;
	if (astCustomer[position].money <= iTotalCost)
	{
		printf("您的账户余额不足，无法购买！");
		Sleep(1000);
		return;
	}
	printf("您将一共需要花费%.2lf元，确认购买吗？(y)or(n)", iTotalCost);
	char ch = getchar();
	if (ch == 'n' || ch == 'N')
	{
		printf("您取消了结算购物车！");
		Sleep(1000);
		return;
	}
	astCustomer[position].money -= iTotalCost;
	SaveGoodsData();
	SaveCustomerData();
	ClearChart();
	printf("结算成功，按任意键继续！");
	getch();
}

void ShowMyInfo(int CustomerID)
{
	system("cls");
	int position = SearchCustomer(CustomerID);
	int count = astCustomer[position].iAmount;
	if (strcmp(astCustomer[position].sex, "男") == 0)
	{
		printf("%s先生", astCustomer[position].name);
	}
	else
	{
		printf("%s女生", astCustomer[position].name);
	}
	printf("您的账户余额为%.2lf\n", astCustomer[position].money);
	printf("您的购物信息如下：\n");
	printf("|= = = = = = = = = = = = = = = = = = = =|\n");
	printf("%-10s %-10s\n","商品名称","购买数量");
	for (int i = 0; i < count; i++)
	{
		printf("%-10s %-10d\n", astCustomer[position].acGoodsName[i], astCustomer[position].GoodsCount[i]);
	}
	printf("|= = = = = = = = = = = = = = = = = = = =|\n");
	system("pause");
}

int GetCustomerFile()
{
	CustomerRecord = 0;
	FILE* fpGetData = fopen("customer.dat", "rb+");
	if (!fpGetData)
	{
		return CustomerRecord;
	}
	while (!feof(fpGetData))
	{
		if (fread(&astCustomer[CustomerRecord], LEN_CUSTOM, 1, fpGetData) == 1)
		{
			CustomerRecord++;
		}
	}
	fclose(fpGetData);
	return CustomerRecord;
}

int SearchCustomer(int CustomerId)
{
	CustomerRecord = GetCustomerFile();
	for (int i = 0; i < CustomerRecord; i++)
	{
		if (astCustomer[i].number == CustomerId)
		{
			return i;
		}
	}
	return CUSTOMER_NOT_FOUND;
}

void SaveCustomerData()
{
	FILE* fpWriteData = fopen("customer.dat", "wb");
	for (int i = 0; i < CustomerRecord; i++)
	{
		fwrite(&astCustomer[i], LEN_CUSTOM, 1, fpWriteData);
	}
	fclose(fpWriteData);
}

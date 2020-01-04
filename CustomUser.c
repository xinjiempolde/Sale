/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: CustomUser.c
 * Author:   ��С��
 * Date:     2019��12��08��
 *
 * Description: �û������ĺ�������
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
	SetConsoleTitleA("�û�����");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------��ӭ����---------------------------|\n");
	printf("\t\t\t|                     ������ҵ���۹���ϵͳ                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                           �û��˵�                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        0��������һ��                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        1�������Ʒ�����ﳵ                   |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        2�����ٹ��ﳵ�е���Ʒ                 |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        3���鿴���ﳵ�е���Ʒ                 |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        4����չ��ﳵ                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        5�����㹺�ﳵ                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        6���鿴�ҵĹ�������                   |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	printf("\t\t\t����������ѡ��(0-5):");
}

void AddChart()
{
	int number, count;
	ShowSaleInfo();
	printf("����������Ҫ�������Ʒid��");
	if (scanf("%d", &number) != 1)
		getchar();
	int goodsSearchId = SearchGoods(number);
	if (goodsSearchId == GOODS_NOT_FOUND)
	{
		printf("�����ڸ���ƷID������������أ�");
		getch();
		return;
	}
	printf("������Ҫ�������Ʒ������");
	if (input_num(&count) == WRONG) return;
	// ��Ʒ��治��
	if (count > astGoods[goodsSearchId].inventory)
	{
		printf("��Ʒ��治�㣬����������أ�");
		getch();
		return;
	}
	stTime now_time, deadline_time;
	AddTime(astGoods[goodsSearchId].span, astGoods[goodsSearchId].time, &deadline_time);
	GetTime(&now_time);
	double iDiscountRatio = 1;
	// ���ۿ�ʱ���ڴ���
	if (CompareTime(&now_time, &deadline_time) == TIME_OLDER)
	{
		iDiscountRatio = 0.7;
	}
	cart.aiGoodsId[cart.count] = number;
	cart.aiPrice[cart.count] = astGoods[goodsSearchId].price * (double)iDiscountRatio;
	strcpy(cart.goods[cart.count], astGoods[goodsSearchId].name);
	cart.goodsCount[cart.count] = count;
	cart.count++;
	printf("��������ﳵ�ɹ����������������\n");
	getch();
}

void ClearChart()
{
	cart.count = 0;
	memset(cart.goods, 0, sizeof(cart.goods));
	printf("��չ��ﳵ�ɹ����������������\n");
	getch();
}

void ShowChart()
{
	system("cls");
	printf("���Ĺ��ﳵ����Ʒ���£�\n");
	printf("|= = = = = = = = = = = = = = = = = = = =|\n");
	printf("%-10s %-10s %-10s\n", "��Ʒ���", "��Ʒ����", "��������");
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
	GetGoodsFile();	// ��ȡ��Ʒ��Ϣ����Ҫ�޸Ŀ���������
	for (int i = 0; i < cart.count; i++)
	{
		astCustomer[position].aiGoodsID[i] = cart.aiGoodsId[i];
		strcpy(astCustomer[position].acGoodsName[i], cart.goods[i]);
		astCustomer[position].GoodsCount[i] = cart.goodsCount[i];
		iTotalCost += cart.aiPrice[i] * cart.goodsCount[i];
		int GoodsId = SearchGoods(cart.aiGoodsId[i]);
		astGoods[GoodsId].inventory -= cart.goodsCount[i];	// �������û���������
		astGoods[GoodsId].saleNum += cart.goodsCount[i];	// ���������û���������
	}
	astCustomer[position].iAmount += cart.count;
	if (astCustomer[position].money <= iTotalCost)
	{
		printf("�����˻����㣬�޷�����");
		Sleep(1000);
		return;
	}
	printf("����һ����Ҫ����%.2lfԪ��ȷ�Ϲ�����(y)or(n)", iTotalCost);
	char ch = getchar();
	if (ch == 'n' || ch == 'N')
	{
		printf("��ȡ���˽��㹺�ﳵ��");
		Sleep(1000);
		return;
	}
	astCustomer[position].money -= iTotalCost;
	SaveGoodsData();
	SaveCustomerData();
	ClearChart();
	printf("����ɹ����������������");
	getch();
}

void ShowMyInfo(int CustomerID)
{
	system("cls");
	int position = SearchCustomer(CustomerID);
	int count = astCustomer[position].iAmount;
	if (strcmp(astCustomer[position].sex, "��") == 0)
	{
		printf("%s����", astCustomer[position].name);
	}
	else
	{
		printf("%sŮ��", astCustomer[position].name);
	}
	printf("�����˻����Ϊ%.2lf\n", astCustomer[position].money);
	printf("���Ĺ�����Ϣ���£�\n");
	printf("|= = = = = = = = = = = = = = = = = = = =|\n");
	printf("%-10s %-10s\n","��Ʒ����","��������");
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: OpeUser.h
 * Author:   ��С��
 * Date:     2019��12��05��
 *
 * Description: �̼���غ���
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "time.h"
#define LEN_GOODS sizeof(goods)
#define GOODS_NOT_FOUND -1
typedef struct {
	int number;		// ��Ʒ���
	char name[30];	// ��Ʒ����
	int inventory;	// ��Ʒ���
	int saleNum;	// ��������
	double price;		// ��Ʒ�۸�
	stTime time;	// ��Ʒ��ʼ����ʱ��
	int span;		/// ��Ʒ������������
}goods;
goods astGoods[100];
int iGoodsRecord;	// ��Ʒ����
/*
 * ������:ope_callback
 * ��  ��:�����̼Ҳ���
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void ope_callback();
/*
 * ������:ShowOpeUserMenu
 * ��  ��:��ʾ�̼Ҳ����˵�
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void ShowOpeUserMenu();
/*
 * ������:AddGoods
 * ��  ��:������Ʒ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void AddGoods();
/*
 * ������:DeleteGoods
 * ��  ��:�˹���Ʒ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void DeleteGoods();
/*
 * ������:��ʾ������Ʒ��Ϣ
 * ��  ��:��ʾ��¼������
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void ShowSaleInfo();
/*
 * ������:GetGoodsFile
 * ��  ��:���ļ��ж�ȡ��Ʒ��Ϣ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
int GetGoodsFile();
/*
 * ������:SearchGoods
 * ��  ��:������Ʒ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:λ��
 */
int SearchGoods(int number);

/*
 * ������:SaveGoodsData
 * ��  ��:������Ʒ��Ϣ�������ļ�
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:λ��
 */
void SaveGoodsData();
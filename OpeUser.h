/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: OpeUser.h
 * Author:   刘小辉
 * Date:     2019年12月05日
 *
 * Description: 商家相关函数
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "time.h"
#define LEN_GOODS sizeof(goods)
#define GOODS_NOT_FOUND -1
typedef struct {
	int number;		// 商品编号
	char name[30];	// 商品名称
	int inventory;	// 商品库存
	int saleNum;	// 销售数量
	double price;		// 商品价格
	stTime time;	// 商品开始促销时间
	int span;		/// 商品促销持续天数
}goods;
goods astGoods[100];
int iGoodsRecord;	// 商品总数
/*
 * 函数名:ope_callback
 * 功  能:管理商家操作
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ope_callback();
/*
 * 函数名:ShowOpeUserMenu
 * 功  能:显示商家操作菜单
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ShowOpeUserMenu();
/*
 * 函数名:AddGoods
 * 功  能:进购商品
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void AddGoods();
/*
 * 函数名:DeleteGoods
 * 功  能:退购商品
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void DeleteGoods();
/*
 * 函数名:显示所有商品信息
 * 功  能:显示登录进度条
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ShowSaleInfo();
/*
 * 函数名:GetGoodsFile
 * 功  能:从文件中读取商品信息
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
int GetGoodsFile();
/*
 * 函数名:SearchGoods
 * 功  能:搜索商品
 * 输  入:无
 * 输  出:无
 * 返回值:位置
 */
int SearchGoods(int number);

/*
 * 函数名:SaveGoodsData
 * 功  能:保存商品信息到本地文件
 * 输  入:无
 * 输  出:无
 * 返回值:位置
 */
void SaveGoodsData();
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: CustomUser.h
 * Author:   刘小辉
 * Date:     2019年12月05日
 *
 * Description: 顾客类相关函数
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#define LEN_CUSTOM sizeof(customer)
#define CUSTOMER_NOT_FOUND -1
typedef struct {
	int number;		// 顾客编号
	char name[20];	// 顾客姓名
	char sex[4];	// 顾客性别
	double money;		// 顾客账户余额
	int iAmount;	// 购买商品数量
	int aiGoodsID[20];		// 已购商品编号
	char acGoodsName[20][40];	// 已购商品列表
	int GoodsCount[20];		// 已购商品的数量
}customer;
typedef struct {
	int count;
	char goods[20][40];		// 购物车里物品
	double aiPrice[20];		// 购物车里物品价格
	int aiGoodsId[20];		// 购物车物品的唯一编号
	int goodsCount[20];		// 购物车里每样物品有几件
}ShopCart;
ShopCart cart;
customer astCustomer[100];
int CustomerRecord;
/*
 * 函数名:Customer_callback
 * 功  能:卖家操作管理
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void Customer_callback(int CustomerId);
/*
 * 函数名:ShowCustomerMenu
 * 功  能:显示卖家操作菜单
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ShowCustomerMenu();
/*
 * 函数名:Addchart
 * 功  能:添加至购物车
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void AddChart();

/*
 * 函数名:ClearChart
 * 功  能:清空购物车
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ClearChart();
/*
 * 函数名:ShowChart
 * 功  能:显示购物车商品信息
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ShowChart();
/*
 * 函数名:CheckOut
 * 功  能:结算购物车
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void CheckOut(int customerId);
/*
 * 函数名:ShowMyInfo
 * 功  能:显示顾客购物信息
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ShowMyInfo(int CustomerId);
/*
 * 函数名:GetCustomerFile
 * 功  能:从文件读取顾客信息
 * 输  入:无
 * 输  出:顾客数量
 * 返回值:无
 */
int GetCustomerFile();
/*
 * 函数名:SearchCustomer
 * 功  能:搜索用户
 * 输  入:用户id
 * 输  出:位置
 * 返回值:无
 */
int SearchCustomer(int CustomerId);
/*
 * 函数名:SaveCustomerData
 * 功  能:保存顾客信息到文件中
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void SaveCustomerData();
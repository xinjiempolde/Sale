/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: CustomUser.h
 * Author:   ��С��
 * Date:     2019��12��05��
 *
 * Description: �˿�����غ���
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#define LEN_CUSTOM sizeof(customer)
#define CUSTOMER_NOT_FOUND -1
typedef struct {
	int number;		// �˿ͱ��
	char name[20];	// �˿�����
	char sex[4];	// �˿��Ա�
	double money;		// �˿��˻����
	int iAmount;	// ������Ʒ����
	int aiGoodsID[20];		// �ѹ���Ʒ���
	char acGoodsName[20][40];	// �ѹ���Ʒ�б�
	int GoodsCount[20];		// �ѹ���Ʒ������
}customer;
typedef struct {
	int count;
	char goods[20][40];		// ���ﳵ����Ʒ
	double aiPrice[20];		// ���ﳵ����Ʒ�۸�
	int aiGoodsId[20];		// ���ﳵ��Ʒ��Ψһ���
	int goodsCount[20];		// ���ﳵ��ÿ����Ʒ�м���
}ShopCart;
ShopCart cart;
customer astCustomer[100];
int CustomerRecord;
/*
 * ������:Customer_callback
 * ��  ��:���Ҳ�������
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void Customer_callback(int CustomerId);
/*
 * ������:ShowCustomerMenu
 * ��  ��:��ʾ���Ҳ����˵�
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void ShowCustomerMenu();
/*
 * ������:Addchart
 * ��  ��:��������ﳵ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void AddChart();

/*
 * ������:ClearChart
 * ��  ��:��չ��ﳵ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void ClearChart();
/*
 * ������:ShowChart
 * ��  ��:��ʾ���ﳵ��Ʒ��Ϣ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void ShowChart();
/*
 * ������:CheckOut
 * ��  ��:���㹺�ﳵ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void CheckOut(int customerId);
/*
 * ������:ShowMyInfo
 * ��  ��:��ʾ�˿͹�����Ϣ
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void ShowMyInfo(int CustomerId);
/*
 * ������:GetCustomerFile
 * ��  ��:���ļ���ȡ�˿���Ϣ
 * ��  ��:��
 * ��  ��:�˿�����
 * ����ֵ:��
 */
int GetCustomerFile();
/*
 * ������:SearchCustomer
 * ��  ��:�����û�
 * ��  ��:�û�id
 * ��  ��:λ��
 * ����ֵ:��
 */
int SearchCustomer(int CustomerId);
/*
 * ������:SaveCustomerData
 * ��  ��:����˿���Ϣ���ļ���
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void SaveCustomerData();
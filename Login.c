/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: Login.c
 * Author:   ��С��
 * Date:     2019��12��08��
 *
 * Description: �û���¼�ĺ�������
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "Login.h"
#include "ShowMenu.h"
#include "sqlite3.h"
#include "SysUser.h"
#include "OpeUser.h"
#include "CustomUser.h"
#include "SafeUtils.h"
#include <string.h>
#include <Windows.h>
#include <stdio.h>
#define N 5
void identify_Code()
{
	char str[N + 1], code[N + 1];
	int i, j, len, iNum = 5, iCleanFlag = 0;
	char* pstr = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJLMNOPQRSTUVWXYZ";
	len = strlen(pstr);         //���ַ���pstr�ĳ���
	srand(time(0));
	while (iNum--)
	{
		if (iCleanFlag == 3)
		{
			system("cls");
		}
		for (i = 0; i < N; i++)
		{
			j = rand() % len;        //����0~len-1�������
			str[i] = pstr[j];
		}
		str[i] = '\0';
		printf("\n\t\t\t������֤��Ϊ");
		SetColor(rand() % 16 + 1);		/*ÿ����֤�����ɫ��ͬ*/
		printf("%s", str);
		SetColor(16);
		printf("\n\t\t\t��������֤��: ");
		scanf("%s", code);
		iCleanFlag++;
		if (strcmp(code, str) == 0)		//���ִ�Сд����֤��
		{
			printf("\t\t\t��֤��ȷ\n");
			return;
		}
		else
		{
			printf("\t\t\t��֤���������\n");
		}
	}
	printf("��֤�������5�Σ������˳�ϵͳ��");
	Sleep(1000);
	exit(1);
}

loginType UserLogin()
{
	system("cls");
	int i = 0, iFlag = -1, userId = 0;	/*��½�Ƿ�ɹ���ʶ��*/
	sqlite3* db;
	char user[60], pwd[60], ch;
	char* zErrMsg = 0;
	int rc;
	const char* sql;

	//�ڽ����м���ʾ��½��ʾ
	SetPos(24, 6);
	printf("�����������˺ţ�");
	SetPos(24, 9);
	printf("�������������룺");

	//�����û��˻�
	SetPos(39, 6);
	scanf("%s", user);
	// Ĭ��#���˳�
	if (strcmp(user, "#") == 0)
	{
		return;
	}

	//�����û�����
	SetPos(39, 9);
	HidePass(pwd);
	md5_encrypt(pwd);
	/* ��ʾ��֤�� */
	identify_Code();

	/* �����ݿ� */
	rc = sqlite3_open("login.db", &db);
	if (rc) {
		printf("�޷������ݿ�\n");
		return;
	}
	/* ����sql��� */
	sql = sqlite3_mprintf("insert into user(id,pwd,type,number) values('%s','%s','%d','%d')", user, pwd, 2001,0);
	/* ִ��sql��� */
	rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (!rc) 
	{
		char* pSQL = sqlite3_mprintf("delete from user where id = '%s' and pwd = '%s' ", user, pwd);	/*����ɹ�ɾ������*/
		rc = sqlite3_exec(db, pSQL, NULL, NULL, &zErrMsg);
		iFlag = -1;
	}
	// ��¼�ɹ���Ѱ���û�����
	else 
	{
		char** table = NULL;
		int row;
		int column;
		sql = sqlite3_mprintf("select * from user where id = '%s'", user);
		rc = sqlite3_get_table(db, sql, &table, &row, &column, &zErrMsg);
		if (rc != SQLITE_OK) {
			sqlite3_free(zErrMsg);
		}
		iFlag = atoi(table[2 * column - 2]);
		userId = atoi(table[2 * column - 1]);
		sqlite3_free_table(table);
		ShowProgressBar();
	}
	sqlite3_close(db);
	loginType loginobj;
	loginobj.type = iFlag;
	loginobj.userId = userId;
	return loginobj;
}

void JumpUser()
{
	loginType loginobj = UserLogin();
	switch (loginobj.type)
	{
	case NOT_USER:
		printf("\n\t\t\t�˻���������󣬵�¼ʧ�ܣ������������");
		getch();
		return;
	case SYS_USER:
		Sys_callback();
		break;
	case OPE_USER:		
		ope_callback();
		break;
	case CUSTOM_USER:
		Customer_callback(loginobj.userId);
		break;
	default:
		printf("δ֪����");
		getch();
		break;
	}
}


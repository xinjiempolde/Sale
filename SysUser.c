/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: SysUser.c
 * Author:   ��С��
 * Date:     2019��12��08��
 *
 * Description: ϵͳ����Ա��غ�������
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "SysUser.h"
#include "CustomUser.h"
#include "Login.h"
#include "sqlite3.h"
#include "SafeUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "sqlite3.lib")
void Sys_callback()
{
	int flag = 0;
	while (1)
	{
		ShowSysUserMenu();
		scanf("%d", &flag);
		switch (flag)
		{
		case 0:
			return;
		case 1:
			AddUser();
			break;
		case 2:
			DeleteUser();
			break;
		case 3:
			ChangeUserPass();
			break;
		case 4:
			ShowAllUser();
			break;
		default:
			printf("û�д�ѡ����������룡");
			Sleep(500);
			break;
		}
	}
}
void ShowSysUserMenu()
{
	SetConsoleTitleA("ϵͳ����Ա����");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------��ӭ����---------------------------|\n");
	printf("\t\t\t|                     ������ҵ���۹���ϵͳ                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                       ϵͳ����Ա����                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        0���˳�ϵͳ                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        1������û�                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        2��ɾ���û�                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        3�������û�����                       |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        4���鿴�����û���Ϣ                   |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	printf("\t\t\t����������ѡ��(0-3):");
}
int AddUser()
{
	system("cls");
	char user[60], pwd[60];
	sqlite3* db;
	const char* sql;
	int rc, type = 2002;
	rc = sqlite3_open("login.db", &db);
	if (rc)
	{
		printf("�޷������ݿ�");
		return 0;
	}
	printf("�������û��˻���");
	scanf("%s", user);
	printf("�������û����룺");
	HidePass(pwd);
	md5_encrypt(pwd);
	printf("�������˻�����(ϵͳ�˻�2000���̼��˻�2001���˿��˻�2002)��");
	scanf("%d", &type);
	if (type == CUSTOM_USER)
	{
		customer tmp;
		while (1)
		{
			printf("�������û���ţ�");
			if (input_num(&tmp.number) == WRONG) return;
			if (SearchCustomer(tmp.number) != CUSTOMER_NOT_FOUND)
			{
				printf("���û�����Ѵ��ڣ����������룡\n");
			}
			else
			{
				break;
			}
		}
		printf("�������û�������");
		scanf("%s", tmp.name);
		printf("�������û��Ա�");
		scanf("%s", tmp.sex);
		tmp.iAmount = 0;
		tmp.money = 5000;	// ��ʼ���˻����Ϊ5000
		FILE* fpWriteData = fopen("customer.dat", "ab+");
		if (!fpWriteData)
		{
			printf("���ļ�ʧ�ܣ�");
			return;
		}
		fwrite(&tmp, LEN_CUSTOM, 1, fpWriteData);
		fclose(fpWriteData);
		sql = sqlite3_mprintf("insert into user values('%s','%s','%d','%d');", user, pwd, type, tmp.number);
		rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
		sqlite3_free(db);
		printf("����û��ɹ��������������");
		getch();
		return;
	}
	sql = sqlite3_mprintf("insert into user(id,pwd,type,number) values('%s','%s','%d','%d');", user, pwd, type,0);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	sqlite3_free(db);
	if (!rc)
	{
		printf("����û��ɹ��������������");
		getch();
	}
	else
	{
		printf("���ʧ�ܣ�����������أ�");
		getch();
	}

}

void DeleteUser()
{
	char user[60];
	sqlite3* db;
	const char* sql;
	int rc;
	system("cls");
	printf("�������û��˻���");
	scanf("%s", user);
	rc = sqlite3_open("login.db", &db);
	if (rc)
	{
		printf("�޷������ݿ�");
	}
	sql = sqlite3_mprintf("delete from user where id = '%s'", user);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (!rc)
	{
		printf("�ɹ�ɾ���û����������������");
		getch();
	}
	else
	{
		printf("ɾ���û�ʧ�ܣ��������������");
		getch();
	}
}

void ChangeUserPass()
{
	system("cls");
	char user[60], pwd[60], query_pwd;
	sqlite3* db;
	const char* sql;
	int rc;
	rc = sqlite3_open("login.db", &db);
	if (rc)
	{
		printf("�����ݿ�ʧ��");
		return;
	}
	printf("������Ҫ�޸�������˻���");
	scanf("%s", user);
	printf("�������޸ĺ�����룺");
	HidePass(pwd);
	printf("���ٴ������޸ĺ�����룺");
	HidePass(query_pwd);
	if (strcmp(pwd, query_pwd) != 0)
	{
		printf("�����������벻һ�£�����������أ�");
		getch();
		return;
	}
	md5_encrypt(pwd);
	sql = sqlite3_mprintf("update user set pwd = '%s' where id = '%s';", pwd, user);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (!rc)
	{
		printf("�޸�����ɹ�������������أ�");
		getch();
	}
	else
	{
		printf("�޸�����ʧ�ܣ�����������أ�");
		getch();
	}
}

void ShowAllUser()
{
	system("cls");
	printf("�Ӱ�ȫ�ĽǶȿ��ǣ���¶�û�����Ϣ��һ���ǳ�Σ�յ�����\n");
	printf("������ǹر��˴˹��ܣ����½�\n");
	printf("�������������");
	getch();
}

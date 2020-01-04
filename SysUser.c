/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: SysUser.c
 * Author:   刘小辉
 * Date:     2019年12月08日
 *
 * Description: 系统管理员相关函数定义
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
			printf("没有此选项，请重新输入！");
			Sleep(500);
			break;
		}
	}
}
void ShowSysUserMenu()
{
	SetConsoleTitleA("系统管理员界面");
	system("cls");
	EchoTime();
	printf("\n\n\n");
	printf("\t\t\t|---------------------------欢迎进入---------------------------|\n");
	printf("\t\t\t|                     零售商业销售管理系统                     |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                       系统管理员界面                         |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        0、退出系统                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        1、添加用户                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        2、删除用户                           |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        3、更改用户密码                       |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\t\t\t|                        4、查看所有用户信息                   |\n");
	printf("\t\t\t|--------------------------------------------------------------|\n");
	printf("\n");
	printf("\t\t\t请输入您的选择(0-3):");
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
		printf("无法打开数据库");
		return 0;
	}
	printf("请输入用户账户：");
	scanf("%s", user);
	printf("请输入用户密码：");
	HidePass(pwd);
	md5_encrypt(pwd);
	printf("请输入账户类型(系统账户2000，商家账户2001，顾客账户2002)：");
	scanf("%d", &type);
	if (type == CUSTOM_USER)
	{
		customer tmp;
		while (1)
		{
			printf("请输入用户编号：");
			if (input_num(&tmp.number) == WRONG) return;
			if (SearchCustomer(tmp.number) != CUSTOMER_NOT_FOUND)
			{
				printf("该用户编号已存在，请重新输入！\n");
			}
			else
			{
				break;
			}
		}
		printf("请输入用户姓名：");
		scanf("%s", tmp.name);
		printf("请输入用户性别：");
		scanf("%s", tmp.sex);
		tmp.iAmount = 0;
		tmp.money = 5000;	// 初始化账户余额为5000
		FILE* fpWriteData = fopen("customer.dat", "ab+");
		if (!fpWriteData)
		{
			printf("打开文件失败！");
			return;
		}
		fwrite(&tmp, LEN_CUSTOM, 1, fpWriteData);
		fclose(fpWriteData);
		sql = sqlite3_mprintf("insert into user values('%s','%s','%d','%d');", user, pwd, type, tmp.number);
		rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
		sqlite3_free(db);
		printf("添加用户成功，按任意键返回");
		getch();
		return;
	}
	sql = sqlite3_mprintf("insert into user(id,pwd,type,number) values('%s','%s','%d','%d');", user, pwd, type,0);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	sqlite3_free(db);
	if (!rc)
	{
		printf("添加用户成功，按任意键返回");
		getch();
	}
	else
	{
		printf("添加失败，按任意键返回！");
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
	printf("请输入用户账户：");
	scanf("%s", user);
	rc = sqlite3_open("login.db", &db);
	if (rc)
	{
		printf("无法打开数据库");
	}
	sql = sqlite3_mprintf("delete from user where id = '%s'", user);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (!rc)
	{
		printf("成功删除用户，按任意键继续！");
		getch();
	}
	else
	{
		printf("删除用户失败，按任意键继续！");
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
		printf("打开数据库失败");
		return;
	}
	printf("请输入要修改密码的账户：");
	scanf("%s", user);
	printf("请输入修改后的密码：");
	HidePass(pwd);
	printf("请再次输入修改后的密码：");
	HidePass(query_pwd);
	if (strcmp(pwd, query_pwd) != 0)
	{
		printf("两次输入密码不一致，按任意键返回！");
		getch();
		return;
	}
	md5_encrypt(pwd);
	sql = sqlite3_mprintf("update user set pwd = '%s' where id = '%s';", pwd, user);
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if (!rc)
	{
		printf("修改密码成功，按任意键返回！");
		getch();
	}
	else
	{
		printf("修改密码失败，按任意键返回！");
		getch();
	}
}

void ShowAllUser()
{
	system("cls");
	printf("从安全的角度考虑，暴露用户的信息是一件非常危险的事情\n");
	printf("因此我们关闭了此功能，请谅解\n");
	printf("按任意键继续！");
	getch();
}

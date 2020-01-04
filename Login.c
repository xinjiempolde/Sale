/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: Login.c
 * Author:   刘小辉
 * Date:     2019年12月08日
 *
 * Description: 用户登录的函数定义
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
	len = strlen(pstr);         //求字符串pstr的长度
	srand(time(0));
	while (iNum--)
	{
		if (iCleanFlag == 3)
		{
			system("cls");
		}
		for (i = 0; i < N; i++)
		{
			j = rand() % len;        //生成0~len-1的随机数
			str[i] = pstr[j];
		}
		str[i] = '\0';
		printf("\n\t\t\t您的验证码为");
		SetColor(rand() % 16 + 1);		/*每次验证码的颜色不同*/
		printf("%s", str);
		SetColor(16);
		printf("\n\t\t\t请输入验证码: ");
		scanf("%s", code);
		iCleanFlag++;
		if (strcmp(code, str) == 0)		//区分大小写的验证码
		{
			printf("\t\t\t验证正确\n");
			return;
		}
		else
		{
			printf("\t\t\t验证码输入错误\n");
		}
	}
	printf("验证码已输错5次，即将退出系统！");
	Sleep(1000);
	exit(1);
}

loginType UserLogin()
{
	system("cls");
	int i = 0, iFlag = -1, userId = 0;	/*登陆是否成功标识符*/
	sqlite3* db;
	char user[60], pwd[60], ch;
	char* zErrMsg = 0;
	int rc;
	const char* sql;

	//在界面中间显示登陆提示
	SetPos(24, 6);
	printf("请输入您的账号：");
	SetPos(24, 9);
	printf("请输入您的密码：");

	//输入用户账户
	SetPos(39, 6);
	scanf("%s", user);
	// 默认#号退出
	if (strcmp(user, "#") == 0)
	{
		return;
	}

	//输入用户密码
	SetPos(39, 9);
	HidePass(pwd);
	md5_encrypt(pwd);
	/* 显示验证码 */
	identify_Code();

	/* 打开数据库 */
	rc = sqlite3_open("login.db", &db);
	if (rc) {
		printf("无法打开数据库\n");
		return;
	}
	/* 创建sql语句 */
	sql = sqlite3_mprintf("insert into user(id,pwd,type,number) values('%s','%s','%d','%d')", user, pwd, 2001,0);
	/* 执行sql语句 */
	rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (!rc) 
	{
		char* pSQL = sqlite3_mprintf("delete from user where id = '%s' and pwd = '%s' ", user, pwd);	/*插入成功删除数据*/
		rc = sqlite3_exec(db, pSQL, NULL, NULL, &zErrMsg);
		iFlag = -1;
	}
	// 登录成功，寻找用户类型
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
		printf("\n\t\t\t账户或密码错误，登录失败，按任意键返回");
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
		printf("未知错误！");
		getch();
		break;
	}
}


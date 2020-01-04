/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: Sale.c
 * Author:   刘小辉
 * Date:     2019年12月08日
 *
 * Description: 主函数，程序入口
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include "ShowMenu.h"
#include "Login.h"
#include "SysUser.h"
#include "OpeUser.h"
#include "CustomUser.h"
#include "SafeUtils.h"
int main(void)
{
	int flag;
	while (1)
	{
		ShowMainMenu();
		if (scanf("%d", &flag) != 1)
		{
			// 输入的不是数字，清空缓存区
			// fflush(stdin);
			getchar();
		}
		switch (flag)
		{
		case 0:
			exit(0);
			break;
		case 1:
			JumpUser();
			break;
		case 2:
			ShowSysInfo();
			break;
		default:
			printf("您的输入有误，请重新输入！");
			break;
		}
	}
	return 0;
}
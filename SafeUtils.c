#include "SafeUtils.h"
#include "md5.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
void HidePass(char pwd[])
{
	char ch;
	int i = 0;
	while ((ch = getch()) != '\r')
	{
		if (ch == '\b' && i != 0)
		{
			printf("%c %c", ch, ch);	/*当用户输入退格时*/
			i--;
		}
		else if (ch == '\b' && i == 0)
		{
			continue;
		}
		else
		{
			putchar('*');	                  /*通过_getch()()()和putchar结合打造密码隐式输入的效果*/
			pwd[i++] = ch;
		}
	}
	pwd[i] = '\0';
	printf("\n");
}

void md5_encrypt(char pwd[])
{
	unsigned char encrypt[20];
	memset(encrypt, 0, sizeof(unsigned char) * 20);
	strcpy(encrypt, pwd);
	unsigned char decrypt[16];
	MD5_CTX md5;
	MD5Init(&md5);
	MD5Update(&md5, encrypt, strlen((char*)encrypt));
	MD5Final(&md5, decrypt);
	FILE* fpInput = fopen("Pwd.txt", "w");
	for (int i = 0; i < 16; i++)
	{
		fprintf(fpInput, "%02x", decrypt[i]);
	}
	fclose(fpInput);
	FILE* fp;
	fp = fopen("Pwd.txt", "r");
	fscanf(fp, "%32s", pwd);
	fclose(fp);
}

int input_num(int* num)
{
	if (scanf("%d", num) != 1)
	{
		getchar();
		printf("数据类型有误！");
		Sleep(500);
		return WRONG;
	}
	return OK;
}

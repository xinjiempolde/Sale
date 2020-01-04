/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: SafeUtils.h
 * Author:   刘小辉
 * Date:     2019年12月08日
 *
 * Description: 安全类相关函数
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#define WRONG -1
#define OK 0
 /*
  * 函数名:HidePass
  * 功  能:用户输入密码时不可见
  * 输  入:用户密码
  * 输  出:“******”；并将用户输入结果存放到数组中
  * 返回值:无
  */
void HidePass(char pwd[]);

/*
 * 函数名:md5_encrypt
 * 功  能:对字符串进行md5加密处理
 * 输  入:用户密码
 * 输  出:md5加密后的值
 * 返回值:无
 */
void md5_encrypt(char pwd[]);

/*
 * 函数名:input_num
 * 功  能:安全输入数字类型，确保程序不会因为
		 缓存区溢出而崩溃
 * 输  入:用户密码
 * 输  出:“******”；并将用户输入结果存放到数组中
 * 返回值:无
 */
int input_num(int* num);
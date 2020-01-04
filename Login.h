/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: Login.h
 * Author:   刘小辉
 * Date:     2019年12月05日
 *
 * Description: 登录类相关函数
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#define NOT_USER -1
#define SYS_USER 2000
#define OPE_USER 2001
#define CUSTOM_USER 2002
typedef struct {
	int type;
	int userId;
}loginType;
/*
 * 函数名:identify_Code
 * 功  能:显示验证码
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void identify_Code();
/*
 * 函数名:UserLogin
 * 功  能:用户登录函数
 * 输  入:无
 * 输  出:无
 * 返回值:操作结果
 */
loginType UserLogin();
/*
 * 函数名:JumpUser
 * 功  能:跳转用户
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void JumpUser();
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: SysUser.h
 * Author:   刘小辉
 * Date:     2019年12月05日
 *
 * Description: 系统管理员相关函数
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
 /*
  * 函数名:Sys_callback
  * 功  能:系统用户操作
  * 输  入:无
  * 输  出:无
  * 返回值:无
  */
void Sys_callback();

/*
 * 函数名:ShowSysUserMenu
 * 功  能:系统用户菜单
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */

void ShowSysUserMenu();

/*
 * 函数名:AddUser
 * 功  能:添加用户
 * 输  入:用户一系列信息
 * 输  出:保存用户信息到数据库
 * 返回值:操作结果
 */
int AddUser();

/*
 * 函数名:ShowProgressBar
 * 功  能:显示登录进度条
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void DeleteUser();
/*
 * 函数名:ChangeUserPass
 * 功  能:修改用户密码
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ChangeUserPass();

/*
 * 函数名:ShowAllUser
 * 功  能:显示所有用户信息
 * 输  入:无
 * 输  出:无
 * 返回值:无
 */
void ShowAllUser();
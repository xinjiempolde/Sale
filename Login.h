/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: Login.h
 * Author:   ��С��
 * Date:     2019��12��05��
 *
 * Description: ��¼����غ���
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
 * ������:identify_Code
 * ��  ��:��ʾ��֤��
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void identify_Code();
/*
 * ������:UserLogin
 * ��  ��:�û���¼����
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:�������
 */
loginType UserLogin();
/*
 * ������:JumpUser
 * ��  ��:��ת�û�
 * ��  ��:��
 * ��  ��:��
 * ����ֵ:��
 */
void JumpUser();
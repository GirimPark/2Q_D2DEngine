#pragma once

// ��� ����
#define FRAMEWORK_DEBUG
//#define FRAMEWORK_RELEASE

// ȭ�� ũ�� ����
#define ScreenWidth (1024)
#define ScreenHeight (768)

// �α׿� ��ũ�� �Լ�
#define PrintLog(message) printf("FILE : %s || LINENO : %d\n#MESSAGE : %s\n\n", __FILE__, __LINE__, message)
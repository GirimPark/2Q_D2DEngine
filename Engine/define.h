#pragma once

// 모드 설정
#define FRAMEWORK_DEBUG
//#define FRAMEWORK_RELEASE

// 화면 크기 설정
#define ScreenWidth (1024)
#define ScreenHeight (768)

// 로그용 매크로 함수
#define PrintLog(message) printf("FILE : %s || LINENO : %d\n#MESSAGE : %s\n\n", __FILE__, __LINE__, message)
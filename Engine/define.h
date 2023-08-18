#pragma once

#include <iostream>

// 모드 설정
#define FRAMEWORK_DEBUG
//#define FRAMEWORK_RELEASE

// 화면 크기 설정
#define ScreenWidth (1920)
#define ScreenHeight (1080)

// 로그용 매크로 함수
#define PrintLog(message) std::cout << "FILE : " << __FILE__ << " || LINENO : " << __LINE__ << "\n#MESSAGE : " << message << "\n\n"

#define ItemScale (40)
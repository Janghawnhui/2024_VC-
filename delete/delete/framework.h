// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once //헤더파일이 한번만 입력되게 해주는 전처리기

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h> // 가장 중요*** Widnwos GUI 사용하기 위해 필수적으로 사용하기 위한 api
// C 런타임 헤더 파일입니다.
#include <stdlib.h>//유틸리티
#include <malloc.h>//메모리 관리
#include <memory.h>//메모리 관리
#include <tchar.h>//문자열
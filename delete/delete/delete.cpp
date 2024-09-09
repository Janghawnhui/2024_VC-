// delete.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "delete.h"

///#define A B =>A는 앞으로 B로 사용
#define MAX_LOADSTRING 100

///자료형 : 기본적으로 숫자로 구성, 사용자 정의로 모두 구성
///규칙: 가장 앞자리가 H로 시작하면, Handle 제어기능
///         핸들은 정보를 처리 및 관리하기 위한 객체다.

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다. **정보체를 저장하기위한 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
/// WChar 와이드 charactor
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance); // MyeRegisterClass 세팅을 os한테 요청
BOOL                InitInstance(HINSTANCE, int); // 메모리에 올라갈 값을 초기화
// ******매우 중요
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM); 
// ******매우 중요
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM); // 도움말 띄워주는 함수


/*hInstance => 실행된 프로세스의 시작 주소*/
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // APIENTRY main 이라고 확정      
                     _In_opt_ HINSTANCE hPrevInstance,  //_In_opt_, _In_ 전부 입력값
                     _In_ LPWSTR    lpCmdLine, //입력파라미터에 인수 갯수
                     _In_ int       nCmdShow) //실행시 보여질지 
{
    UNREFERENCED_PARAMETER(hPrevInstance);//인수 사용하지 않을 시 정리
    UNREFERENCED_PARAMETER(lpCmdLine);//인수 사용하지 않을 시 정리

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); //
    LoadStringW(hInstance, IDC_DELETE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); // 윈도우 세팅

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DELETE)); // 패스

    MSG msg; //메시지

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0)) //GetMessage os가 받음
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) //번역기능
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);//메시지 처리할 수 있도록 던져줌
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    ///WND : Window
    ///EX : Extension 확장
    ///W : 유니코드 지원
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DELETE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DELETE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    //메모리 세팅 하기 위한 공간
    return RegisterClassExW(&wcex); //실제 OS 등록
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,// 창 여는 함수 
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   /// OS한테 윈도우를 화면에 표시 요청 
   ShowWindow(hWnd, nCmdShow);
   /// OS한테 윈도우 내용이 최신 정보가 되도록 확인 요청 
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
int g_px, g_py;
int time = 1000;
RECT g_me{ 10, 10, 100, 100 };
RECT g_you{ 500, 500, 590, 590 };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
/// CALLBACK: 외부에서 호출 할 수 있도록 구성되어 있는 함수.
/// CALLBACK 외부에서 함수를 부를 수 있다. *os에서 요청한다
/// HWND : 윈도우 핸들.
/// UNIT : 사용자의 요청을 숫자로 변환한 값.
/// *PARAM : 부가정보
/// WPARAM (WORD): 문자 데이터. 키보드 값과 관련된 정보.
/// LPARAM (LONG): 숫자 데이터. 마우스 값과 관련된 정보.
/// 이 윈도우(HWND)에서 사용자 입력(UNIT)을 처리하려면 정보(*PARAM),

{
   
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, time, NULL);
        break;
    case WM_TIMER:
        if (g_me.left >= g_you.left) //나는 몬스터의 오른쪽
        {
            g_you.left += 10;
            g_you.right +=10;
        }
        else {
            g_you.left -= 10;
            g_you.right -= 10;
        }
        if (g_me.top <= g_you.top) {
            g_you.top -= 10;
            g_you.bottom -= 10;
        }
        else {
            g_you.top += 10;
            g_you.bottom += 10;
        }
        InvalidateRect(hWnd, NULL, TRUE);

        break;
    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_LEFT:
            g_me.left -=10;
            g_me.right -= 10;
            break;
        case VK_RIGHT:
            g_me.left += 10;
            g_me.right += 10;
            break;
        case VK_UP:
            g_me.top -= 10;
            g_me.bottom -= 10;
            break;
        case VK_DOWN:
            g_me.top += 10;
            g_me.bottom += 10;
            break;
        }
        
        InvalidateRect(hWnd, NULL, TRUE);
    }
    case WM_MOUSEMOVE:
    {
        ///마우스의 정보를 저장
        int x, y;
        x = LOWORD(lParam); // LOW WORD : 하위 16비트 추출
        y = HIWORD(lParam); // HIGH WORD : 상위 16비트 추출
        
        ///마우스의 좌표 값을 획득, 마우스 위치까지 그리기
        ///마우스의 정보lParam에서 얻어오기
        /// PAINTSTRUCT ps;
        HDC hdc = GetDC(hWnd);
        /// Handle Device(화면) Context(정보체)
        /// hdc =>화면의 정보를 컨트롤 할 수 있음 

        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        /*MoveToEx(hdc, g_px, g_py, NULL);
        g_px = x;
        g_py = y;
        LineTo(hdc, x, y);
        /*
        Rectangle(hdc, 10, 10, x, y);

        Ellipse(hdc, 10, 10, x, y);

        ///EndPaint(hWnd, &ps);
        */
        ReleaseDC(hWnd, hdc);
    }
        //MessageBox(hWnd,  L"안녕",L"아녕2", MB_OK);
        
        break;
       // CASE WM_

    case WM_COMMAND: //메뉴나 버튼 입력 시에 발생하는 메시지
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    ///화면에 항상 그려져야 하는 내용을 작성하는 메시지
    ///WM_PAINT 항상 화면에 보여져야 하는 내용을 작성
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            /// Handle Device(화면) Context(정보체)
            /// hdc =>화면의 정보를 컨트롤 할 수 있음 
            
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

           Rectangle(hdc, g_me.left,g_me.top,g_me.right,g_me.bottom);
           Rectangle(hdc, g_you.left, g_you.top, g_you.right, g_you.bottom);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

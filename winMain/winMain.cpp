#include <Windows.h>
#include <time.h>

//전역변수
//인스턴스 : 윈도우 OS가 현재 실행되고 있는 프로그램이 뭔지 확인하기 위한 값
//같은프로그램이면 같은 인스턴스 값을 가지고 있다.
HINSTANCE _hInstance;
//윈도우 핸들 (윈도우 창)
HWND _hWnd;
//사각형. 사각형의 정보를 가지고 있다.
RECT _rc1 = { 10, 100, 100, 190 };
RECT _rc2 = { 180, 100, 270, 190 };
			//left, top, right, bottom
//윈도우 타이틀
LPTSTR _lpszClass = TEXT("인터스텔라 API!");

//CALLBACK
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//winMain 함수의 역할
	//WNDCLASS : 윈도우 창의 정보를 저장하기 위한 구조체
	//1.1 윈도우 창 구조체 선언 및 초기화

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//윈도우 창 정보 등록
	RegisterClass(&wndClass);

	//화면에 보여줄 윈도우 창을 생성
	_hWnd = CreateWindow(
		_lpszClass,		//윈도우 클래스 이름
		_lpszClass,		//윈도우 타이틀 바 이름
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		100,		//윈도우 화면의 시작 X좌표
		100,		//윈도우 화면의 시작 Y좌표
		640,		//윈도우 화면 가로크기
		480,		//윈도우 화면 세로크기
		NULL,		//부모 윈도우
		(HMENU)NULL,	//메뉴 핸들
		hInstance,	//인스턴스 값은 뭐냐
		NULL);		//자식 윈도우를 생성하는 경우 지정하고 아니면 NULL

					//윈도우 화면 보여주기!
	ShowWindow(_hWnd, nCmdShow);

	//운영체제에서 발생하는 메세지를 저장하기 위한 구조체
	MSG message;

	//메시지 루프
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

//윈도우 프로시저 : 메세지를 전달

//hWnd : 어느 윈도우 핸들에서 발생한 메시지인지
//iMessage : 메시지 구분 번호
//wParam : unsigned int : 마우스 버튼의 상태, 키보드 조합키의 상태를 전달.
//lParam : 마우스 클릭 좌표
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	HDC hdc;		//핸들DC 도화지
	PAINTSTRUCT ps; //페인트 구조체

	switch (iMessage)
	{
	case WM_CREATE: //생성자
		srand(time(NULL));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Rectangle(hdc, _rc1.left, _rc1.top, _rc1.right, _rc1.bottom);
		Rectangle(hdc, _rc2.left, _rc2.top, _rc2.right, _rc2.bottom);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
	{
		hdc = GetDC(hWnd); //도화지를 가져오자~!
		//SetTextColor(hdc, RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
		//TextOut(hdc, _startPt, _startPt, "박민 아프다고 뻥치지마라..",
		//	strlen("박민 아프다고 뻥치지마라.."));

		//선
		//점을 옮겨
		//선을 그린다.
		/*MoveToEx(hdc, 10, 10, NULL);
		LineTo(hdc, 400, 400);
		LineTo(hdc, 400, 0);
*/

		ReleaseDC(hWnd, hdc);
	}
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (_rc1.left <= 0) break;
			if (_rc1.left <= _rc2.right && _rc1.right >= _rc2.left)
			{

				if (_rc1.bottom >= _rc2.top && _rc1.top <= _rc2.bottom)
				{
					if (_rc1.left == _rc2.right)
					{
						_rc1.right -= 10;
						_rc1.left -= 10;
						_rc2.right -= 10;
						_rc2.left -= 10;
					}
					if (_rc1.right == _rc2.left || _rc1.top == _rc2.bottom || _rc1.bottom == _rc2.top)
					{
						_rc1.right -= 10;
						_rc1.left -= 10;
					}
					break;
				}
	
			}

			_rc1.right -= 10;
			_rc1.left  -= 10;
			break;
		case VK_RIGHT:
			if (_rc1.right >= 640) break;
			if (_rc1.right >= _rc2.left && _rc1.left <= _rc2.right)
			{
				if (_rc1.bottom >= _rc2.top && _rc1.top <= _rc2.bottom)
				{
					if (_rc1.right == _rc2.left)
					{
						_rc1.right += 10;
						_rc1.left += 10;
						_rc2.right += 10;
						_rc2.left += 10;
					}
					if (_rc1.left == _rc2.right || _rc1.top == _rc2.bottom || _rc1.bottom == _rc2.top)
					{
						_rc1.right += 10;
						_rc1.left += 10;
					}
					break;
				}

			}

			_rc1.right += 10;
			_rc1.left += 10;
			break;
		case VK_UP:
			if (_rc1.top <= 0) break;
			if (_rc1.top <= _rc2.bottom && _rc1.bottom >= _rc2.top)
			{
				if (_rc1.left <= _rc2.right && _rc1.right >= _rc2.left)
				{
					if (_rc1.top == _rc2.bottom)
					{
						_rc1.top -= 10;
						_rc1.bottom -= 10;
						_rc2.top -= 10;
						_rc2.bottom -= 10;
					}
					if (_rc1.bottom == _rc2.top || _rc1.left == _rc2.right|| _rc1.right == _rc2.left)
					{
						_rc1.top -= 10;
						_rc1.bottom -= 10;
					}
					break;
				}
			}

			_rc1.top -= 10;
			_rc1.bottom -= 10;
			break;
		case VK_DOWN:
			if (_rc1.bottom >= 480) break;
			if (_rc1.bottom >= _rc2.top && _rc1.top <= _rc2.bottom)
			{
				if (_rc1.left <= _rc2.right && _rc1.right >= _rc2.left)
				{
					if (_rc1.bottom == _rc2.top)
					{
						_rc1.top += 10;
						_rc1.bottom += 10;
						_rc2.top += 10;
						_rc2.bottom += 10;
					}
					if (_rc1.top == _rc2.bottom || _rc1.left == _rc2.right || _rc1.right == _rc2.left)
					{
						_rc1.top += 10;
						_rc1.bottom += 10;
					}
					break;
				}
			}

			_rc1.top += 10;
			_rc1.bottom += 10;
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}

		//핸들윈도우를 지우고 다시 그려라~
		//화면을 한번 지우고, 다시 그린다.
		InvalidateRect(hWnd, NULL, true);

		break;
	case WM_DESTROY: //윈도우가 파괴될 때 실행되는 메시지
		PostQuitMessage(0);
		return 0;
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
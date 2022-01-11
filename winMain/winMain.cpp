#include <Windows.h>
#include <time.h>

//��������
//�ν��Ͻ� : ������ OS�� ���� ����ǰ� �ִ� ���α׷��� ���� Ȯ���ϱ� ���� ��
//�������α׷��̸� ���� �ν��Ͻ� ���� ������ �ִ�.
HINSTANCE _hInstance;
//������ �ڵ� (������ â)
HWND _hWnd;
//�簢��. �簢���� ������ ������ �ִ�.
RECT _rc1 = { 10, 100, 100, 190 };
RECT _rc2 = { 180, 100, 270, 190 };
			//left, top, right, bottom
//������ Ÿ��Ʋ
LPTSTR _lpszClass = TEXT("���ͽ��ڶ� API!");

//CALLBACK
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//winMain �Լ��� ����
	//WNDCLASS : ������ â�� ������ �����ϱ� ���� ����ü
	//1.1 ������ â ����ü ���� �� �ʱ�ȭ

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

	//������ â ���� ���
	RegisterClass(&wndClass);

	//ȭ�鿡 ������ ������ â�� ����
	_hWnd = CreateWindow(
		_lpszClass,		//������ Ŭ���� �̸�
		_lpszClass,		//������ Ÿ��Ʋ �� �̸�
		WS_OVERLAPPEDWINDOW,	//������ ��Ÿ��
		100,		//������ ȭ���� ���� X��ǥ
		100,		//������ ȭ���� ���� Y��ǥ
		640,		//������ ȭ�� ����ũ��
		480,		//������ ȭ�� ����ũ��
		NULL,		//�θ� ������
		(HMENU)NULL,	//�޴� �ڵ�
		hInstance,	//�ν��Ͻ� ���� ����
		NULL);		//�ڽ� �����츦 �����ϴ� ��� �����ϰ� �ƴϸ� NULL

					//������ ȭ�� �����ֱ�!
	ShowWindow(_hWnd, nCmdShow);

	//�ü������ �߻��ϴ� �޼����� �����ϱ� ���� ����ü
	MSG message;

	//�޽��� ����
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

//������ ���ν��� : �޼����� ����

//hWnd : ��� ������ �ڵ鿡�� �߻��� �޽�������
//iMessage : �޽��� ���� ��ȣ
//wParam : unsigned int : ���콺 ��ư�� ����, Ű���� ����Ű�� ���¸� ����.
//lParam : ���콺 Ŭ�� ��ǥ
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam,
	LPARAM lParam)
{
	HDC hdc;		//�ڵ�DC ��ȭ��
	PAINTSTRUCT ps; //����Ʈ ����ü

	switch (iMessage)
	{
	case WM_CREATE: //������
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
		hdc = GetDC(hWnd); //��ȭ���� ��������~!
		//SetTextColor(hdc, RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
		//TextOut(hdc, _startPt, _startPt, "�ڹ� �����ٰ� ��ġ������..",
		//	strlen("�ڹ� �����ٰ� ��ġ������.."));

		//��
		//���� �Ű�
		//���� �׸���.
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

		//�ڵ������츦 ����� �ٽ� �׷���~
		//ȭ���� �ѹ� �����, �ٽ� �׸���.
		InvalidateRect(hWnd, NULL, true);

		break;
	case WM_DESTROY: //�����찡 �ı��� �� ����Ǵ� �޽���
		PostQuitMessage(0);
		return 0;
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
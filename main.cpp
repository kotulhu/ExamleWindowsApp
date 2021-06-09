#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <WinUser.h>

// Название класса
static TCHAR szWindowClass[] = _T("ExampleWindow");

HWND TextBox, SendButton, TextField, SubButtLabel;

// Название приложения
static TCHAR szTitle[] = _T("RequestMakerWin 0.1 by Khtulhu");

HINSTANCE hInst;

// Объяляем используемые ф-ии перед WinMain
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    // Иконка приложения
    LPCTSTR iconPathName = L"work.ico";
    UINT icon_flags = LR_LOADFROMFILE | LR_DEFAULTSIZE;
    HANDLE hIcon = LoadImage(hInstance, iconPathName, IMAGE_ICON, 0, 0, icon_flags);


    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = (HICON)hIcon; // set icon
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, // width
        500, // height
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// главная функця
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, Windows desktop!");


    static HWND hwndEdit;
    static HWND hwndRead;
    #define SUBMIT_BUTTON 1
    #define ID_EDIT 1
    #define ID_READONLY 1

    switch (message)
    {
    case WM_CREATE:

        // Текстовое поле для url
        CreateWindowEx(
            WS_EX_CLIENTEDGE,
            L"EDIT", // prevent error "argument of type const char * is incompatible with parameter of type lpcwstr"
            L"https://jsonplaceholder.typicode.com/posts",    // Содержимое по умолчанию
            WS_CHILD | WS_VISIBLE,
            25, // left
            45,
            730, // width
            24, // field height
            hWnd,
            (HMENU)100,
            hInst, // Comming from WinMain
            NULL
        );

        // Окно для ввода запроса
        hwndEdit = CreateWindowW(L"Edit", NULL,
            WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT |
            ES_MULTILINE | ES_AUTOVSCROLL,
            25,  // left
            85, // top
            360, // with
            240,
            hWnd,
            (HMENU)ID_EDIT,
            NULL, NULL);

        // Окно ответа
        hwndEdit = CreateWindowW(L"Edit", NULL,
            WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_RIGHT | ES_READONLY |
            ES_MULTILINE | ES_AUTOVSCROLL,
            400,  // left
            85, // top
            360, // with
            240,
            hWnd,
            (HMENU)ID_READONLY,
            NULL, NULL);

        CreateWindowW(L"Button", L"Send request",
            WS_VISIBLE | WS_CHILD,
            25, 350, 150, 25, hWnd, (HMENU)SUBMIT_BUTTON, NULL, NULL);

        return DefWindowProc(hWnd, message, lParam, wParam);

    case WM_COMMAND:
        switch (wParam) //the ID is is wParam
        {
            case SUBMIT_BUTTON: //check for our button ID
            {
                // button action
                break;
            }
        }
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

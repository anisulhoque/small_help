// AI.cpp :
// Defines the entry point for the application.
// START: SOS; ROGER, ERROR- WAIT< END> 		DELETE
// ERROR: ONE WORD
// DELETE: ONE LETTER
#include "framework.h"
#include "AI.h"
#include "morse_wrapper.h"
/*------------------------------------------------------------------------------------------------------------*/
/*
struct node {
    char data;
    char value;
    struct node* head;
    struct node* left;
    struct node* right;
    struct node* next;
};

struct node* newNode(char data, node* head) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    
    node->head = head;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
 
    return(node);
}

struct node* insert(struct node* head, const char* data, const char* value, struct node* link) {
    if (strlen(data) > 0) {
        char ch = data[0];
        if (ch == '.') {
            if (head->left == NULL) {
                head->left = newNode(ch, head);
            }
            insert(head->left, &data[1], value, link);
        }
        else if (ch == '-') {
            if (head->right == NULL) {
                head->right = newNode(ch, head);
            }
            insert(head->right, &data[1], value, link);
        }
    }
    else {
        head->value = value[0];
        link->next = head;
    }

    return NULL;
}

struct node* search(struct node* head, const char* data) {
    return NULL;
}
struct node* root = newNode(0, NULL);
    // insert(root, input, value, root);
    // insert(root, input, value, root->next);
*/


#include <process.h>    /* _beginthread, _endthread */
#include <string>
#include <chrono>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>

using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
std::chrono::time_point<std::chrono::high_resolution_clock> PREV;// = std::chrono::steady_clock::now();
void getDir(const char* d, vector<string>& f);

void handleHardwareFaults_2() {
//    char* s = "hello world";
//    *s = 'H';
    char s[] = "Test";
    s[0] = 'H';
}
void handleHardwareFaults_1() {
    try {
        *(int*)0 = 0;
    }
    catch (std::exception & e) {
        std::cerr << "Exception catched : " << e.what() << std::endl;
    }
    cout << "‚¢‚¢‚ËB" << endl;
}

void delFiles() {
    vector<string> files;
    getDir("C:\\Projects\\DOL\\A\\Platform\\train2014", files);
 //   filesystem::create_directories("sandbox/a/b");


    vector<string>::const_iterator it = files.begin();
    cout << "Printing Dir" << endl;

    while (it != files.end())
    {
        cout << *it << endl;
        it++;
    }
}
void getDir(const char* d, vector<string>& f) {
    FILE* pipe = NULL;
    string pCmd = "dir /B /S " + string(d);
    char buf[256];

    if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
    {
        cout << "Shit" << endl;
        return;
    }

    while (!feof(pipe))
    {
        if (fgets(buf, 256, pipe) != NULL)
        {
            f.push_back(string(buf));
        }

    }

    _pclose(pipe);


}
void calibTime(void* ignored)
{
	wchar_t mTimeInNs[32];
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - PREV).count();

	swprintf_s(mTimeInNs, L"%u\n", duration);
	PREV = now;
	OutputDebugStringW(mTimeInNs);
	
	_endthread();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	
    // TODO: Place code here.
    input("01 11 010101 ");
    /*
    handleHardwareFaults_1();
    */
    /*
    delFiles();
    */
    /*
	OutputDebugStringW(L"START.\n");
	PREV = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		_beginthread(calibTime, 0, NULL);
	}
	OutputDebugStringW(L"END.\n");
    */
	// Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_AI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_AI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
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
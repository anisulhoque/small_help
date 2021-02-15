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
/*--------------------------------------*/
struct node {
    char data;
    char value;
    char length;
    struct node* head;
    struct node* tail;
};

struct node* newNode(struct node* head, char data, char value, char length) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->data = data;
    node->value = value;
    node->length = length;
    node->head = head;
    return (node);
}

struct node* make(struct node* head, const char* data, const char* value, const char* length) {
    if (strlen(data) > 0) {
        struct node* node = newNode(head, data[0], value[0], length[0]);
        head->tail = node;
        head = make(node, &data[1], &value[1], &length[1]);
    }
    return head;
}

struct node* list() {
    char data[] = "+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char value[] = { 10,2,0,21,18,31,15,7,3,1,0,16,24,28,30,21,56,8,17,5,12,26,1,8,10,4,0,2,6,0,0,7,5,4,3,2,7,6,13,2,0,1,1,1,3,9,11,12 };
    char length[] = { 5,5,8,6,5,5,5,5,5,5,5,5,5,5,5,5,9,5,5,6,6,6,2,4,4,3,1,4,3,4,2,4,3,4,2,2,3,4,4,3,3,1,3,4,3,4,4,4 };

    struct node* head = newNode(0, data[0], value[0], length[0]);
    struct node* tail = make(head, &data[1], &value[1], &length[1]);
    head->head = tail;
    tail->tail = head;
    return head;
}

char* valToBin(char value, char length) {
    char* buff = (char*)malloc(sizeof(char) * length);
    buff[length] = 0;

    for (char i = length - 1; i >= 0; i--) {
        buff[i] = value % 2 + '0';
        value /= 2;
    }

    return buff;
}

char binToVal(const char* bin) {
    char val = 0;

    for (char i = 0; i < strlen(bin); i++) {
        val = val << 1;
        val += bin[i] - '0';
    }
    return val;
}

char format(char c) {
    if (c > 42 && c < 91) {
        return c;
    }
    else if (c > 96 && c < 122) {
        return c - 'a' + 'A';
    }
    else {
        return ' ';
    }
}

void (*cPtr) (const char*, char);
void stream(char* buff, char valIndex, char codec) {
    char* stream = (char*)malloc(sizeof(char) * valIndex);
    memcpy(stream, buff, valIndex);
    stream[valIndex] = 0;
    if (cPtr != 0) {
        (*cPtr)(stream, codec);
    }
}

struct node* morse;
void encode(const char* data) {
    char* buff = (char*)malloc(sizeof(char) * 256);
    char valIndex = 0;
    while (strlen(data) != 0) {
        char c = format(data[0]);
        // Streaming
        if (c == ' ') {
            buff[valIndex++] = '/';
            buff[valIndex++] = ' ';
            stream(buff, valIndex, ENCODE);
            valIndex = 0;
        }
        else {
            while (morse->data != c) {
                morse = morse->tail;
            }
            char* temp = valToBin(morse->value, morse->length);
            while (strlen(temp) != 0) {
                buff[valIndex++] = *temp++;
            }
            buff[valIndex++] = ' ';
        }
        data++;
    }
    stream(buff, valIndex, ENCODE);
    free(buff);
}

void code(char* buff, char buffIndex) {
    buff[buffIndex] = 0;
    char c = binToVal(buff);
    for (;;) {
        if (morse->value == c && morse->length == buffIndex) {
            stream(&morse->data, 1, DECODE);
            free(buff);
            break;
        }
        morse = morse->tail;
    }
}

void decode(const char* data) {
    char* buff = (char*)malloc(sizeof(char) * 16);
    char buffIndex = 0;
    while (strlen(data) != 0) {
        if (data[0] == ' ' && buffIndex > 0) {
            code(buff, buffIndex);
            buff = (char*)malloc(sizeof(char) * 16);
            buffIndex = 0;
        }
        else if (data[0] == '/') {
            char c = ' ';
            stream(&c, 1, DECODE);
        }
        else if (data[0] == '0' || data[0] == '1'){
            buff[buffIndex++] = data[0];
        }
        data++;
    }
    code(buff, buffIndex);
}

void (*fPtr[2]) (const char* data) = { decode, encode };
void input(const char* data, void output(const char*, char), char codec) {
    if (strlen(data) == 0) {
        return;
    }
    if (output == 0) {
        return;
    }
    if ((codec | ENCODE) != ENCODE) {
        return;
    }
    if (morse == 0) {
        morse = list();
    }
    if (cPtr == 0) {
        cPtr = output;
    }
    fPtr[codec](data);
}

/*
    short mark, dot or "dit" (0): 1
    longer mark, dash or "dah" (1): 111
    intra-character gap (between the dots and dashes within a character): 0
    short gap (between letters): 000
    medium gap (between words): 0000000
*/

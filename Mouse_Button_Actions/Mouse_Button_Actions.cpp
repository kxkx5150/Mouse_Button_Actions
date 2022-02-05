// Mouse_Button_Actions.cpp : Defines the entry point for the application.
#include "Mouse_Button_Actions.h"
#include "../MouseHook/MouseHook/MouseHook.h"
#include "framework.h"
#include <string>
#pragma comment(lib, "MouseHook.lib")

#define MAX_LOADSTRING 100
HINSTANCE hInst;
HWND g_hwnd = nullptr;
HFONT m_hFont = nullptr;
HFONT m_bhFont = nullptr;
NOTIFYICONDATA g_nid;
HMENU hPopMenu;
int active_button_id = 0;

HWND m_middle_set_btn = nullptr;
HWND m_right_set_btn = nullptr;
HWND m_x1_set_btn = nullptr;
HWND m_x2_set_btn = nullptr;
HWND m_lr_set_btn = nullptr;

HWND m_rm_set_btn = nullptr;
HWND m_rl_set_btn = nullptr;
HWND m_ml_set_btn = nullptr;
HWND m_mr_set_btn = nullptr;
HWND m_lm_set_btn = nullptr;
HWND m_lu_set_btn = nullptr;
HWND m_ld_set_btn = nullptr;

HWND g_eventedit_hwnd = nullptr;
HWND g_event_x_hwnd = nullptr;
HWND g_event_y_hwnd = nullptr;
HWND g_event_data_hwnd = nullptr;
HWND g_event_flg_hwnd = nullptr;
HWND g_event_time_hwnd = nullptr;

struct KeyObj {
    bool alt = false;
    bool ctrl = false;
    bool shift = false;
    TCHAR keycode = 0;
};

class KeyObjs {

public:
    KeyObj m_middle_key;
    KeyObj m_right_key;
    KeyObj m_x1_key;
    KeyObj m_x2_key;
    KeyObj m_lr_key;
    KeyObj m_rl_key;
    KeyObj m_rm_key;
    KeyObj m_ml_key;
    KeyObj m_mr_key;
    KeyObj m_lm_key;
    KeyObj m_lu_key;
    KeyObj m_ld_key;

public:
    KeyObjs()
    {
    }

    ~KeyObjs()
    {
    }

private:
};
KeyObjs* keyobjs = new KeyObjs();
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
void create_gui();
HFONT create_font(int fontsize);
void get_options();
HWND create_edittext(HWND hParent, int nX, int nY, int nWidth, int nHeight, int id);
bool set_regkey(HKEY hKey, std::wstring keystr);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hpins, _In_ LPWSTR lccmd, _In_ int mcmd)
{
    UNREFERENCED_PARAMETER(hpins);
    UNREFERENCED_PARAMETER(lccmd);
    LoadStringW(hInstance, IDC_MOUSEHOOKAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, mcmd)) {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOUSEHOOKAPP));
    create_gui();
    start_hook(g_hwnd, true, true, true, true, true, false);
    set_regkey(HKEY_CURRENT_USER, L"SOFTWARE\\Mouse_Button_Actions_kxkx5150");
    get_options();

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    end_hook();
    return (int)msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MOUSEHOOKAPP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;
    g_hwnd = CreateWindowW(szWindowClass, L"", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, 0, 264, 590, nullptr, nullptr, hInstance, nullptr);
    if (!g_hwnd) {
        return FALSE;
    }
    //nCmdShow = SW_MINIMIZE;
    ShowWindow(g_hwnd, nCmdShow);
    UpdateWindow(g_hwnd);
    return TRUE;
}
HWND create_button(HWND hParent, int nX, int nY, int nWidth, int nHeight, int id, TCHAR* txt)
{
    return CreateWindow(
        L"BUTTON", txt,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        nX, nY, nWidth, nHeight,
        hParent, (HMENU)id, hInst, NULL);
}
HWND create_edittext(HWND hParent, int nX, int nY, int nWidth, int nHeight, int id)
{
    return CreateWindow(
        TEXT("EDIT"), L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL,
        nX, nY, nWidth, nHeight,
        hParent, (HMENU)id, hInst, NULL);
}
HFONT create_font(int fontsize)
{
    return CreateFont(fontsize, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, 0,
        SHIFTJIS_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH, L"Segoe UI");
}
void create_gui()
{
    m_hFont = create_font(13);
    m_bhFont = create_font(15);

    m_middle_set_btn = create_button(g_hwnd, 32, 14, 180, 26, IDD_MIDDLE_SET_BUTTON, (TCHAR*)L"MIddle Button");
    m_right_set_btn = create_button(g_hwnd, 32, 46, 180, 26, IDD_RIGHT_SET_BUTTON, (TCHAR*)L"Right Button");
    m_x1_set_btn = create_button(g_hwnd, 32, 78, 180, 26, IDD_X1_SET_BUTTON, (TCHAR*)L"X1 Button");
    m_x2_set_btn = create_button(g_hwnd, 32, 110, 180, 26, IDD_X2_SET_BUTTON, (TCHAR*)L"X2 Button");
    m_lm_set_btn = create_button(g_hwnd, 32, 142, 180, 26, IDD_LM_SET_BUTTON, (TCHAR*)L"Left && MIddle Button");
    m_lr_set_btn = create_button(g_hwnd, 32, 174, 180, 26, IDD_LR_SET_BUTTON, (TCHAR*)L"Left && Right Button");
    //ShowWindow(m_rl_set_btn, SW_HIDE);
    m_ml_set_btn = create_button(g_hwnd, 32, 206, 180, 26, IDD_ML_SET_BUTTON, (TCHAR*)L"MIddle && Left Button");
    m_mr_set_btn = create_button(g_hwnd, 32, 238, 180, 26, IDD_MR_SET_BUTTON, (TCHAR*)L"MIddle && Right Button");
    m_rl_set_btn = create_button(g_hwnd, 32, 270, 180, 26, IDD_RL_SET_BUTTON, (TCHAR*)L"Right && Left Button");
    m_rm_set_btn = create_button(g_hwnd, 32, 302, 180, 26, IDD_RM_SET_BUTTON, (TCHAR*)L"Right && MIddle Button");
    m_lu_set_btn = create_button(g_hwnd, 32, 334, 180, 26, IDD_LU_SET_BUTTON, (TCHAR*)L"Left && Wheel Up");
    m_ld_set_btn = create_button(g_hwnd, 32, 366, 180, 26, IDD_LD_SET_BUTTON, (TCHAR*)L"Left && Wheel Down");

    g_eventedit_hwnd = create_edittext(g_hwnd, 4, 404, 240, 21, 0);
    g_event_x_hwnd = create_edittext(g_hwnd, 4, 424, 100, 21, 0);
    g_event_y_hwnd = create_edittext(g_hwnd, 4, 444, 100, 21, 0);
    g_event_data_hwnd = create_edittext(g_hwnd, 4, 464, 100, 21, 0);
    g_event_flg_hwnd = create_edittext(g_hwnd, 4, 484, 100, 21, 0);
    g_event_time_hwnd = create_edittext(g_hwnd, 4, 504, 100, 21, 0);

    SendMessage(m_middle_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_right_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_x1_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_x2_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_lr_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_rl_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_rm_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_ml_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_mr_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_lm_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_lu_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));
    SendMessage(m_ld_set_btn, WM_SETFONT, (WPARAM)m_bhFont, MAKELPARAM(FALSE, 0));

    SendMessage(g_eventedit_hwnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));
    SendMessage(g_event_x_hwnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));
    SendMessage(g_event_y_hwnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));
    SendMessage(g_event_data_hwnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));
    SendMessage(g_event_flg_hwnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));
    SendMessage(g_event_time_hwnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));
}

void show_event(UINT message, WPARAM wParam, LPMSLLHOOKSTRUCT mousell)
{

    std::wstring ptx = std::to_wstring(mousell->pt.x);
    std::wstring pty = std::to_wstring(mousell->pt.y);
    std::wstring data = std::to_wstring(mousell->mouseData);
    std::wstring flg = std::to_wstring(mousell->flags);
    std::wstring time = std::to_wstring(mousell->time);

    SetWindowText(g_event_x_hwnd, ptx.c_str());
    SetWindowText(g_event_y_hwnd, pty.c_str());
    SetWindowText(g_event_data_hwnd, data.c_str());
    SetWindowText(g_event_flg_hwnd, flg.c_str());
    SetWindowText(g_event_time_hwnd, time.c_str());

    if (WM_LBUTTONDBLCLK == wParam || WM_NCLBUTTONDBLCLK == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_LBUTTONDBLCLK");

    } else if (WM_LBUTTONDOWN == wParam || WM_NCLBUTTONDOWN == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_LBUTTONDOWN");

    } else if (WM_LBUTTONUP == wParam || WM_NCLBUTTONUP == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_LBUTTONUP");

    } else if (WM_MBUTTONDBLCLK == wParam || WM_NCMBUTTONDBLCLK == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MBUTTONDBLCLK");

    } else if (WM_MBUTTONDOWN == wParam || WM_NCMBUTTONDOWN == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MBUTTONDOWN");

    } else if (WM_MBUTTONUP == wParam || WM_NCMBUTTONUP == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MBUTTONUP");

    } else if (WM_RBUTTONDBLCLK == wParam || WM_NCRBUTTONDBLCLK == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_RBUTTONDBLCLK");

    } else if (WM_RBUTTONDOWN == wParam || WM_NCRBUTTONDOWN == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_RBUTTONDOWN");

    } else if (WM_RBUTTONUP == wParam || WM_NCRBUTTONUP == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_RBUTTONUP");

    } else if (WM_XBUTTONDBLCLK == wParam || WM_NCXBUTTONDBLCLK == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_XBUTTONDBLCLK");

    } else if (WM_XBUTTONDOWN == wParam || WM_NCXBUTTONDOWN == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_XBUTTONDOWN");

    } else if (WM_XBUTTONUP == wParam || WM_NCXBUTTONUP == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_XBUTTONUP");

    } else if (WM_MOUSEHWHEEL == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MOUSEHWHEEL");

    } else if (WM_MOUSEWHEEL == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MOUSEWHEEL");

    } else if (WM_MOUSEMOVE == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_MOUSEMOVE");

    } else if (WM_NCMOUSEMOVE == wParam) {
        SetWindowText(g_eventedit_hwnd, L"WM_NCMOUSEMOVE");
    }
}

void create_trayicon(HWND hWnd)
{
    g_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    g_nid.hWnd = hWnd;
    g_nid.uID = IDR_MAINFRAME;
    g_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    g_nid.uCallbackMessage = WM_TO_TRAY;
    g_nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcscpy_s(g_nid.szTip, _T("Mouse Button Actions"));
    Shell_NotifyIcon(NIM_ADD, &g_nid);
    ShowWindow(hWnd, SW_HIDE);
}
void show_main_window(HWND hWnd, bool tray = false)
{
    ShowWindow(hWnd, SW_SHOWNORMAL);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
}
void createContextMenu()
{
    hPopMenu = CreatePopupMenu();
    InsertMenu(hPopMenu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, IDM_EXIT, _T("Exit"));
}
HWND create_combobox(HWND hParent, int nX, int nY, int nWidth, int nHeight, int id)
{
    return CreateWindow(
        L"COMBOBOX", L"",
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_CLIPSIBLINGS | WS_VSCROLL,
        nX, nY, nWidth, nHeight,
        hParent, (HMENU)id, hInst, NULL);
}
void create_option_control(HWND hDlg)
{
    KeyObj keyobj;
    if (active_button_id == IDD_MIDDLE_SET_BUTTON) {
        keyobj = keyobjs->m_middle_key;
    } else if (active_button_id == IDD_RIGHT_SET_BUTTON) {
        keyobj = keyobjs->m_right_key;
    } else if (active_button_id == IDD_X1_SET_BUTTON) {
        keyobj = keyobjs->m_x1_key;
    } else if (active_button_id == IDD_X2_SET_BUTTON) {
        keyobj = keyobjs->m_x2_key;
    } else if (active_button_id == IDD_LR_SET_BUTTON) {
        keyobj = keyobjs->m_lr_key;
    } else if (active_button_id == IDD_RL_SET_BUTTON) {
        keyobj = keyobjs->m_rl_key;
    } else if (active_button_id == IDD_RM_SET_BUTTON) {
        keyobj = keyobjs->m_rm_key;
    } else if (active_button_id == IDD_ML_SET_BUTTON) {
        keyobj = keyobjs->m_ml_key;
    } else if (active_button_id == IDD_MR_SET_BUTTON) {
        keyobj = keyobjs->m_mr_key;
    } else if (active_button_id == IDD_LM_SET_BUTTON) {
        keyobj = keyobjs->m_lm_key;
    } else if (active_button_id == IDD_LU_SET_BUTTON) {
        keyobj = keyobjs->m_lu_key;
    } else if (active_button_id == IDD_LD_SET_BUTTON) {
        keyobj = keyobjs->m_ld_key;
    }

    HWND keylisthwnd = CreateWindow(
        L"COMBOBOX", NULL,
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_CLIPSIBLINGS | WS_VSCROLL,
        28, 20, 150, 200,
        hDlg, (HMENU)IDD_STR_SET_COMBOBOX, hInst, NULL);
    TCHAR i;
    int selidx = 0;
    int itemcnt = 0;

    for (i = 0x30; i <= 0x39; i++) {
        itemcnt++;
        std::wstring aaa = &i;
        aaa[1] = L'\0';
        SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)aaa.c_str());
        if (i == keyobj.keycode) {
            selidx = itemcnt;
        }
    }
    for (i = 0x41; i <= 0x5A; i++) {
        itemcnt++;
        std::wstring aaa = &i;
        aaa[1] = L'\0';
        SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)aaa.c_str());
        if (i == keyobj.keycode) {
            selidx = itemcnt;
        }
    }

    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"LEFT");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"UP");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"RIGHT");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"DOWN");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"END");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"HOME");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"BACK");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"TAB");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"SPACE");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"PAGEUP");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"PAGEDOWN");
    SendMessage(keylisthwnd, CB_ADDSTRING, 0, (LPARAM)L"NONE");

    SendMessage(keylisthwnd, CB_INSERTSTRING, 0, (LPARAM)L"");

    if (keyobj.keycode == 0x25) {
        selidx = itemcnt + 1;
    } else if (keyobj.keycode == 0x26) {
        selidx = itemcnt + 2;
    } else if (keyobj.keycode == 0x27) {
        selidx = itemcnt + 3;
    } else if (keyobj.keycode == 0x28) {
        selidx = itemcnt + 4;
    } else if (keyobj.keycode == 0x23) {
        selidx = itemcnt + 5;
    } else if (keyobj.keycode == 0x24) {
        selidx = itemcnt + 6;
    } else if (keyobj.keycode == 0x08) {
        selidx = itemcnt + 7;
    } else if (keyobj.keycode == 0x09) {
        selidx = itemcnt + 8;
    } else if (keyobj.keycode == 0x20) {
        selidx = itemcnt + 9;
    } else if (keyobj.keycode == 0x21) {
        selidx = itemcnt + 10;
    } else if (keyobj.keycode == 0x22) {
        selidx = itemcnt + 11;
    } else if (keyobj.keycode == 1) {
        selidx = itemcnt + 12;
    }

    SendMessage(keylisthwnd, CB_SETCURSEL, selidx, 0);

    HWND ctrlhwnd = create_combobox(hDlg, 28, 55, 150, 100, IDD_CTRL_SET_COMBOBOX);
    SendMessage(ctrlhwnd, CB_INSERTSTRING, 0, (LPARAM)L"CTRL");
    SendMessage(ctrlhwnd, CB_INSERTSTRING, 0, (LPARAM)L"");
    if (keyobj.ctrl) {
        SendMessage(ctrlhwnd, CB_SETCURSEL, 1, 0);
    } else {
        SendMessage(ctrlhwnd, CB_SETCURSEL, 0, 0);
    }

    HWND althwnd = create_combobox(hDlg, 28, 90, 150, 100, IDD_ALT_SET_COMBOBOX);
    SendMessage(althwnd, CB_INSERTSTRING, 0, (LPARAM)L"ALT");
    SendMessage(althwnd, CB_INSERTSTRING, 0, (LPARAM)L"");
    if (keyobj.alt) {
        SendMessage(althwnd, CB_SETCURSEL, 1, 0);
    } else {
        SendMessage(althwnd, CB_SETCURSEL, 0, 0);
    }

    HWND shifthwnd = create_combobox(hDlg, 28, 125, 150, 100, IDD_SHIFT_SET_COMBOBOX);
    SendMessage(shifthwnd, CB_INSERTSTRING, 0, (LPARAM)L"SHIFT");
    SendMessage(shifthwnd, CB_INSERTSTRING, 0, (LPARAM)L"");
    if (keyobj.shift) {
        SendMessage(shifthwnd, CB_SETCURSEL, 1, 0);
    } else {
        SendMessage(shifthwnd, CB_SETCURSEL, 0, 0);
    }

    create_button(hDlg, 14, 220, 90, 26, IDD_SET_OKBUTTON, (TCHAR*)L"OK");
    create_button(hDlg, 106, 220, 90, 26, IDD_SET_CANCELBUTTON, (TCHAR*)L"Cancel");
}
bool set_regkey(HKEY hKey, std::wstring keystr)
{
    HKEY usrhkey;
    DWORD dwDisposition;
    if (RegOpenKey(hKey, keystr.c_str(), &usrhkey) != ERROR_SUCCESS) {
        DWORD Ret = RegCreateKeyEx(hKey, keystr.c_str(), 0, NULL,
            REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);
        if (Ret != ERROR_SUCCESS)
            return false;
    }
    RegCloseKey(usrhkey);
    return true;
}
bool set_regval(HKEY hKey, std::wstring prntkey, std::wstring keystr, std::wstring valstr)
{
    HKEY newValue;
    BOOL rflg = FALSE;
    if (RegOpenKey(hKey, prntkey.c_str(), &newValue) != ERROR_SUCCESS)
        return rflg;

    DWORD valbytes = valstr.size() * sizeof(wchar_t);
    if (RegSetValueEx(newValue, keystr.c_str(), 0, REG_SZ, (LPBYTE)valstr.c_str(), valbytes) == ERROR_SUCCESS) {
        rflg = TRUE;
        BOOL bRet = SetEnvironmentVariable(keystr.c_str(), valstr.c_str());
    }
    RegCloseKey(newValue);
    return rflg;
}
int setStartUp(HWND hWnd)
{
    TCHAR szPath[MAX_PATH];
    DWORD pathLen = GetModuleFileName(NULL, szPath, MAX_PATH);
    if (pathLen == 0) {
        return -1;
    }
    HKEY newValue;
    std::wstring keystr = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    if (RegOpenKey(HKEY_CURRENT_USER, keystr.c_str(), &newValue) != ERROR_SUCCESS) {
        return -1;
    }

    HMENU hmenu = GetMenu(hWnd);
    UINT uState = GetMenuState(hmenu, ID_MENU_STARTUP, MF_BYCOMMAND);
    if (uState & MFS_CHECKED) {
        RegDeleteValue(newValue, TEXT("Mouse_Button_Actions_kxkx5150"));
        CheckMenuItem(hmenu, ID_MENU_STARTUP, MF_BYCOMMAND | MFS_UNCHECKED);

    } else {
        DWORD pathLenInBytes = pathLen * sizeof(*szPath);
        if (RegSetValueEx(newValue,
                TEXT("Mouse_Button_Actions_kxkx5150"),
                0,
                REG_SZ,
                (LPBYTE)szPath,
                pathLenInBytes)
            != ERROR_SUCCESS) {
            RegCloseKey(newValue);
            return -1;
        }
        CheckMenuItem(hmenu, ID_MENU_STARTUP, MF_BYCOMMAND | MFS_CHECKED);
    }

    RegCloseKey(newValue);
    return 0;
}
void send_key_option(int keyobjid, int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (keyobjid == IDD_MIDDLE_SET_BUTTON) {
        set_mouse_middle_button(0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_RIGHT_SET_BUTTON) {
        set_mouse_right_button(0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_X1_SET_BUTTON) {
        set_mouse_x1_button(0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_X2_SET_BUTTON) {
        set_mouse_x2_button(0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_LR_SET_BUTTON) {
        set_mouse_lr_button(0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_RL_SET_BUTTON) {
        set_mouse_rl_button(0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_RM_SET_BUTTON) {
        set_mouse_rm_button(0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_ML_SET_BUTTON) {
        set_mouse_ml_button(0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_MR_SET_BUTTON) {
        set_mouse_mr_button(0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_LM_SET_BUTTON) {
        set_mouse_lm_button(0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_LU_SET_BUTTON) {
        set_mouse_lu_button(0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_LD_SET_BUTTON) {
        set_mouse_ld_button(0, keycode, ctrl, alt, shift);
    }
}
void set_option_obj(int keyobjid, int keycode, bool ctrl, bool alt, bool shift)
{
    if (keyobjid == IDD_MIDDLE_SET_BUTTON) {
        keyobjs->m_middle_key.keycode = keycode;
        keyobjs->m_middle_key.ctrl = ctrl;
        keyobjs->m_middle_key.alt = alt;
        keyobjs->m_middle_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_RIGHT_SET_BUTTON) {
        keyobjs->m_right_key.keycode = keycode;
        keyobjs->m_right_key.ctrl = ctrl;
        keyobjs->m_right_key.alt = alt;
        keyobjs->m_right_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_X1_SET_BUTTON) {
        keyobjs->m_x1_key.keycode = keycode;
        keyobjs->m_x1_key.ctrl = ctrl;
        keyobjs->m_x1_key.alt = alt;
        keyobjs->m_x1_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_X2_SET_BUTTON) {
        keyobjs->m_x2_key.keycode = keycode;
        keyobjs->m_x2_key.ctrl = ctrl;
        keyobjs->m_x2_key.alt = alt;
        keyobjs->m_x2_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_LR_SET_BUTTON) {
        keyobjs->m_lr_key.keycode = keycode;
        keyobjs->m_lr_key.ctrl = ctrl;
        keyobjs->m_lr_key.alt = alt;
        keyobjs->m_lr_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_RL_SET_BUTTON) {
        keyobjs->m_rl_key.keycode = keycode;
        keyobjs->m_rl_key.ctrl = ctrl;
        keyobjs->m_rl_key.alt = alt;
        keyobjs->m_rl_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_RM_SET_BUTTON) {
        keyobjs->m_rm_key.keycode = keycode;
        keyobjs->m_rm_key.ctrl = ctrl;
        keyobjs->m_rm_key.alt = alt;
        keyobjs->m_rm_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_ML_SET_BUTTON) {
        keyobjs->m_ml_key.keycode = keycode;
        keyobjs->m_ml_key.ctrl = ctrl;
        keyobjs->m_ml_key.alt = alt;
        keyobjs->m_ml_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);

    } else if (keyobjid == IDD_MR_SET_BUTTON) {
        keyobjs->m_mr_key.keycode = keycode;
        keyobjs->m_mr_key.ctrl = ctrl;
        keyobjs->m_mr_key.alt = alt;
        keyobjs->m_mr_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_LM_SET_BUTTON) {
        keyobjs->m_lm_key.keycode = keycode;
        keyobjs->m_lm_key.ctrl = ctrl;
        keyobjs->m_lm_key.alt = alt;
        keyobjs->m_lm_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_LU_SET_BUTTON) {
        keyobjs->m_lu_key.keycode = keycode;
        keyobjs->m_lu_key.ctrl = ctrl;
        keyobjs->m_lu_key.alt = alt;
        keyobjs->m_lu_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);
    } else if (keyobjid == IDD_LD_SET_BUTTON) {
        keyobjs->m_ld_key.keycode = keycode;
        keyobjs->m_ld_key.ctrl = ctrl;
        keyobjs->m_ld_key.alt = alt;
        keyobjs->m_ld_key.shift = shift;
        send_key_option(keyobjid, 0, keycode, ctrl, alt, shift);
    }
}
void store_key(HWND hDlg)
{
    HWND keylisthwnd = GetDlgItem(hDlg, IDD_STR_SET_COMBOBOX);
    HWND ctrlhwnd = GetDlgItem(hDlg, IDD_CTRL_SET_COMBOBOX);
    HWND althwnd = GetDlgItem(hDlg, IDD_ALT_SET_COMBOBOX);
    HWND shifthwnd = GetDlgItem(hDlg, IDD_SHIFT_SET_COMBOBOX);

    TCHAR keytxt[10];
    GetWindowText(keylisthwnd, keytxt, 10);
    TCHAR ctrltxt[10];
    GetWindowText(ctrlhwnd, ctrltxt, 10);
    TCHAR alttxt[10];
    GetWindowText(althwnd, alttxt, 10);
    TCHAR shifttxt[10];
    GetWindowText(shifthwnd, shifttxt, 10);

    int regval = 0;

    UINT keycode = 0;
    if (keytxt != L"") {
        std::wstring keystr = keytxt;

        if (keystr.find(L"UP") == 0) {
            keycode = 0x26;
        } else if (keystr.find(L"DOWN") == 0) {
            keycode = 0x28;
        } else if (keystr.find(L"LEFT") == 0) {
            keycode = 0x25;
        } else if (keystr.find(L"RIGHT") == 0) {
            keycode = 0x27;
        } else if (keystr.find(L"END") == 0) {
            keycode = 0x23;
        } else if (keystr.find(L"HOME") == 0) {
            keycode = 0x24;
        } else if (keystr.find(L"BACK") == 0) {
            keycode = 0x08;
        } else if (keystr.find(L"TAB") == 0) {
            keycode = 0x09;
        } else if (keystr.find(L"SPACE") == 0) {
            keycode = 0x20;
        } else if (keystr.find(L"PAGEUP") == 0) {
            keycode = 0x21;
        } else if (keystr.find(L"PAGEDOWN") == 0) {
            keycode = 0x22;
        } else if (keystr.find(L"NONE") == 0) {
            keycode = 1;

        } else {
            keycode = *keytxt;
        }
        regval = 1000 * keycode;
    }

    bool ctrl = false;
    if (_tcslen(ctrltxt) != 0) {
        ctrl = true;
        regval += 100;
    }

    bool alt = false;
    if (_tcslen(alttxt) != 0) {
        alt = true;
        regval += 10;
    }

    bool shift = false;
    if (_tcslen(shifttxt) != 0) {
        shift = true;
        regval += 1;
    }

    set_option_obj(active_button_id, keycode, ctrl, alt, shift);
    std::wstring regkeystr = std::to_wstring(active_button_id);
    std::wstring regvalstr = std::to_wstring(regval);
    set_regval(HKEY_CURRENT_USER, L"SOFTWARE\\Mouse_Button_Actions_kxkx5150", regkeystr, regvalstr);
}
LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
{
    strValue = strDefaultValue;
    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
    if (ERROR_SUCCESS == nError) {
        strValue = szBuffer;
    }
    return nError;
}
std::wstring get_regval(HWND hWnd, std::wstring keystr, std::wstring subkeystr)
{
    HKEY hKey;
    if (RegOpenKey(HKEY_CURRENT_USER, keystr.c_str(), &hKey) == ERROR_SUCCESS) {
        std::wstring strValueOfBinDir;
        GetStringRegKey(hKey, subkeystr.c_str(), strValueOfBinDir, L"empty");
        return strValueOfBinDir;
    }
    return L"empty";
}
void load_key(int keyobjid)
{
    std::wstring regkeystr = std::to_wstring(keyobjid);
    std::wstring str = get_regval(g_hwnd, L"SOFTWARE\\Mouse_Button_Actions_kxkx5150", regkeystr);

    if (str != L"empty") {
        int sval = std::stoi(str);
        if (sval >= 1000) {
            UINT keycode = sval / 1000;
            sval -= keycode * 1000;

            bool ctrl = false;
            bool alt = false;
            bool shift = false;
            if (sval >= 100) {
                ctrl = true;
                sval -= 100;
            }
            if (sval >= 10) {
                alt = true;
                sval -= 10;
            }
            if (sval >= 1) {
                shift = true;
            }
            set_option_obj(keyobjid, keycode, ctrl, alt, shift);
        }
    }
}
void get_options()
{
    load_key(IDD_MIDDLE_SET_BUTTON);
    load_key(IDD_RIGHT_SET_BUTTON);
    load_key(IDD_X1_SET_BUTTON);
    load_key(IDD_X2_SET_BUTTON);
    load_key(IDD_LR_SET_BUTTON);
    load_key(IDD_RL_SET_BUTTON);
    load_key(IDD_RM_SET_BUTTON);
    load_key(IDD_ML_SET_BUTTON);
    load_key(IDD_MR_SET_BUTTON);
    load_key(IDD_LM_SET_BUTTON);
    load_key(IDD_LU_SET_BUTTON);
    load_key(IDD_LD_SET_BUTTON);
}
INT_PTR CALLBACK set_dialog_proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG: {
        create_option_control(hDlg);
        return (INT_PTR)TRUE;
    }
    case WM_CLOSE:
        EndDialog(hDlg, LOWORD(wParam));

    case WM_COMMAND:
        if (LOWORD(wParam) == IDD_SET_OKBUTTON) {
            store_key(hDlg);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        } else if (LOWORD(wParam) == IDD_SET_CANCELBUTTON) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case ID_MENU_STARTUP: {
            setStartUp(hWnd);
        } break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        case IDD_MIDDLE_SET_BUTTON:
        case IDD_RIGHT_SET_BUTTON:
        case IDD_X1_SET_BUTTON:
        case IDD_X2_SET_BUTTON:
        case IDD_LR_SET_BUTTON:
        case IDD_RL_SET_BUTTON:
        case IDD_RM_SET_BUTTON:
        case IDD_ML_SET_BUTTON:
        case IDD_MR_SET_BUTTON:
        case IDD_LM_SET_BUTTON:
        case IDD_LU_SET_BUTTON:
        case IDD_LD_SET_BUTTON:
            active_button_id = wmId;
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, set_dialog_proc);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    } break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    } break;

    case WM_CREATE: {
        createContextMenu();
        create_trayicon(hWnd);
    } break;

    case WM_TO_TRAY: {
        if (lParam == WM_LBUTTONDOWN) {
            show_main_window(hWnd, true);
        } else if (lParam == WM_RBUTTONUP) {
            POINT lpClickPoint;
            GetCursorPos(&lpClickPoint);
            TrackPopupMenu(hPopMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, lpClickPoint.x, lpClickPoint.y, 0, hWnd, NULL);
        }
    } break;

    case WM_SIZE: {
        if (wParam == SIZE_MINIMIZED) {
            ShowWindow(hWnd, SW_HIDE);
        }
    } break;

    case WM_CLOSE: {
        PostMessage(hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
    } break;

    case WM_MOUSE_GLOBAL_HOOK: {
        LPMSLLHOOKSTRUCT mousell = (LPMSLLHOOKSTRUCT)lParam;
        show_event(message, wParam, mousell);
        delete mousell;
    } break;

    case WM_DESTROY:
        DeleteObject(m_hFont);
        DeleteObject(m_bhFont);
        Shell_NotifyIcon(NIM_DELETE, &g_nid);
        PostQuitMessage(0);
        break;
    default: {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
    return 0;
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

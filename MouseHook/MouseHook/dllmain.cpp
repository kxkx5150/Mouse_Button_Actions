#include "pch.h"
#include <string>
#include <vector>
#include <windowsx.h>
#include "Key.h"
#include "MouseHook.h"
#include <crtdbg.h>

HHOOK g_hook = nullptr;
HWND g_hwnd = nullptr;
HINSTANCE g_hInst = nullptr;

KeyOptions* g_keyopts = nullptr;

bool caplbtn = false;
bool capmbtn = false;
bool caprbtn = false;
bool capxbtn = false;
bool capwheel = false;
bool capmove = false;

bool mouse_lbutton_hold = false;
bool mouse_rbutton_hold = false;
bool mouse_mbutton_hold = false;

bool mouse_x_upevent_cancel = false;
bool mouse_m_upevent_cancel = false;
bool mouse_l_upevent_cancel = false;
bool mouse_r_upevent_cancel = false;

int mouse_wheel_count = 0;
bool mouse_wheel_up = false;

int g_x = 0;
int g_y = 0;
int cancel_lclick = 0;
int cancel_mclick = 0;
int cancel_rclick = 0;

int rupflg = 0;
int g_rx = 0;
int g_ry = 0;

void create_wrap_window();
LRESULT CALLBACK hook_proc(int code, WPARAM wParam, LPARAM lParam);
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
void __cdecl start_hook(HINSTANCE hInstance, HWND hwnd, bool lbtn, bool mbtn, bool rbtn, bool xbtn, bool wheel, bool move)
{
    if (!g_hook) {
        if (!g_keyopts)
            g_keyopts = new KeyOptions();
        caplbtn = lbtn;
        capmbtn = mbtn;
        caprbtn = rbtn;
        capxbtn = xbtn;
        capwheel = wheel;
        capmove = move;

        g_hwnd = hwnd;
        g_hook = SetWindowsHookEx(WH_MOUSE_LL, hook_proc, nullptr, 0);
        g_hInst = hInstance;
    }
}
void __cdecl end_hook()
{
    if (g_hook)
        UnhookWindowsHookEx(g_hook);
    g_hook = nullptr;
    g_hwnd = nullptr;
    delete g_keyopts;
}
void __cdecl set_mouse_left_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_left_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_middle_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_middle_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_right_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_right_button(index, keycode, ctrl, alt, shift);
    OutputDebugString(L"");
}
void __cdecl set_mouse_x1_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_x1_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_x2_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_x2_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_lr_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_lr_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_rl_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_rl_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_rm_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_rm_button(index, keycode, ctrl, alt, shift);
}

void __cdecl set_mouse_ml_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_ml_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_mr_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_mr_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_lm_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_lm_button(index, keycode, ctrl, alt, shift);
}

void __cdecl set_mouse_lu_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_lu_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_ld_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_ld_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_ru_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_ru_button(index, keycode, ctrl, alt, shift);
}
void __cdecl set_mouse_rd_button(int index, int keycode, bool ctrl, bool alt, bool shift)
{
    if (g_keyopts)
        g_keyopts->set_mouse_rd_button(index, keycode, ctrl, alt, shift);
}

int click_xbutton(int state, WPARAM wParam, LPARAM lParam)
{
    MSLLHOOKSTRUCT* pmsllhook = (MSLLHOOKSTRUCT*)lParam;
    switch (HIWORD(pmsllhook->mouseData)) {
    case XBUTTON1: {
        Keyobj* kobj = g_keyopts->get_mouse_x1_button();
        int rval = kobj->send_key(lParam);

        return rval;
    } break;

    case XBUTTON2: {
        Keyobj* kobj = g_keyopts->get_mouse_x2_button();
        return kobj->send_key(lParam);
    } break;

    default: {
    }
    }
    return 0;
}


void create_wrap_window()
{
    HWND g_wrapwindow = CreateWindow(L"wrap_window", L"", WS_OVERLAPPEDWINDOW,
        100, 100, 200, 200,
        NULL, NULL,g_hInst, NULL);
    ShowWindow(g_wrapwindow, SW_SHOW);
}
void show_wrap_window()
{
    SetWindowPos(g_hwnd, HWND_TOPMOST, g_x - 10, g_y - 10, 0, 0, (SWP_NOSIZE));
}
void hide_wrap_window()
{
    SetWindowPos(g_hwnd, HWND_BOTTOM, g_x - 40, g_y - 10, 0, 0, (SWP_NOSIZE));
}





LRESULT CALLBACK hook_proc(int code, WPARAM wParam, LPARAM lParam)
{
    if (!g_hwnd || code < 0)
        return CallNextHookEx(g_hook, code, wParam, lParam);
    int rval = 0;
    bool enable = false;


    if (cancel_lclick == 2) {
        rval = 1;
        SetCursorPos(g_x, g_y);
        cancel_lclick = 3;
        INPUT Input = { 0 };
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        Input.mi.dx = 0;
        Input.mi.dy = g_y;
        SendInput(1, &Input, sizeof(INPUT));
    }else if (cancel_mclick == 2) {
        rval = 1;
        SetCursorPos(0, g_y);
        cancel_mclick = 3;
        INPUT Input = { 0 };
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
        Input.mi.dx = 0;
        Input.mi.dy = g_y;
        SendInput(1, &Input, sizeof(INPUT));
    }

    if (caplbtn && (WM_LBUTTONDBLCLK == wParam || WM_NCLBUTTONDBLCLK == wParam)) {
        enable = true;
    } else if (caplbtn && (WM_LBUTTONDOWN == wParam || WM_NCLBUTTONDOWN == wParam)) {
        enable = true;
        mouse_lbutton_hold = true;
        mouse_wheel_count = 0;
        cancel_lclick = 0;

        bool upcancel = false;
        if (mouse_rbutton_hold) {
            Keyobj* kobj = g_keyopts->get_mouse_rl_button();
            kobj->send_key(lParam);
            cancel_rclick = 1;
            upcancel = true;
        }
        if (mouse_mbutton_hold) {
            Keyobj* kobj = g_keyopts->get_mouse_ml_button();
            int rval2 = kobj->send_key(lParam);
            cancel_mclick = 1;
            upcancel = true;
        }

        if (upcancel) {
            rval = 1;
            mouse_l_upevent_cancel = true;
        } else {
            mouse_l_upevent_cancel = false;
        }
    } else if (caplbtn && (WM_LBUTTONUP == wParam || WM_NCLBUTTONUP == wParam)) {
        enable = true;
        mouse_lbutton_hold = false;
        if (mouse_l_upevent_cancel) {
            rval = 1;
        }
        mouse_l_upevent_cancel = false;

        if (cancel_lclick == 1) {
            rval = 1;
            cancel_lclick = 2;
            auto mousell = (LPMSLLHOOKSTRUCT)lParam;
            g_x = mousell->pt.x;
            g_y = mousell->pt.y;
            show_wrap_window();

        } else if (cancel_lclick == 3) {
            cancel_lclick = 0;
            SetCursorPos(g_x, g_y);
            hide_wrap_window();

        }
    } else if (capxbtn && (WM_MOUSEMOVE == wParam || WM_NCMOUSEMOVE == wParam)) {
        enable = true;
    } else if (capmbtn && (WM_MBUTTONDBLCLK == wParam || WM_NCMBUTTONDBLCLK == wParam)) {
        enable = true;
    } else if (capmbtn && (WM_MBUTTONDOWN == wParam || WM_NCMBUTTONDOWN == wParam)) {
        enable = true;
        mouse_mbutton_hold = true;
        cancel_mclick = 0;

        bool upcancel = false;
        Keyobj* kobj = g_keyopts->get_mouse_middle_button();
        rval = kobj->send_key(lParam);
        if (rval != 0) {
            upcancel = true;
        }

        if (mouse_lbutton_hold) {
            Keyobj* kobj = g_keyopts->get_mouse_lm_button();
            kobj->send_key(lParam);
            cancel_lclick = 1;
            upcancel = true;
        }

        if (mouse_rbutton_hold) {
            Keyobj* kobj = g_keyopts->get_mouse_rm_button();
            kobj->send_key(lParam);
            cancel_rclick = 1;
            upcancel = true;
        }

        if (upcancel) {
            rval = 1;
            mouse_m_upevent_cancel = true;
        } else {
            mouse_m_upevent_cancel = false;
        }
    } else if (capmbtn && (WM_MBUTTONUP == wParam || WM_NCMBUTTONUP == wParam)) {
        enable = true;
        mouse_mbutton_hold = false;
        if (mouse_m_upevent_cancel) {
            rval = 1;
        }
        mouse_m_upevent_cancel = false;

        if (cancel_mclick == 1) {
            rval = 1;
            cancel_mclick = 2;
            auto mousell = (LPMSLLHOOKSTRUCT)lParam;
            g_x = mousell->pt.x;
            g_y = mousell->pt.y;
        } else if (cancel_mclick == 3) {
            cancel_mclick = 0;
            SetCursorPos(g_x, g_y);
        }

    } else if (caprbtn && (WM_RBUTTONDBLCLK == wParam || WM_NCRBUTTONDBLCLK == wParam)) {
        enable = true;
    } else if (caprbtn && (WM_RBUTTONDOWN == wParam || WM_NCRBUTTONDOWN == wParam)) {
        enable = true;
        mouse_rbutton_hold = true;
        cancel_rclick = 0;
        mouse_wheel_count = 0;
        rupflg = 0;

        bool upcancel = false;
        Keyobj* kobj = g_keyopts->get_mouse_right_button();
        rval = kobj->send_key(lParam);
        if (rval != 0) {
            upcancel = true;
        }

        if (mouse_lbutton_hold) {
            cancel_rclick = 1;
            Keyobj* kobj = g_keyopts->get_mouse_lr_button();
            kobj->send_key(lParam);
            cancel_lclick = 1;
            upcancel = true;
        }
        if (mouse_mbutton_hold) {
            Keyobj* kobj = g_keyopts->get_mouse_mr_button();
            kobj->send_key(lParam);
            cancel_mclick = 1;
            upcancel = true;
        }

        MSLLHOOKSTRUCT* Mll = (MSLLHOOKSTRUCT*)lParam;
        g_rx = Mll->pt.x;
        g_ry = Mll->pt.y;

        if (upcancel) {
            rval = 1;
            mouse_r_upevent_cancel = true;
        } else {
            mouse_r_upevent_cancel = false;
        }

    } else if (caprbtn && (WM_RBUTTONUP == wParam || WM_NCRBUTTONUP == wParam)) {
        enable = true;
        mouse_rbutton_hold = false;
        if (rupflg == 10000) {
            rupflg = 0;
            return 0;
        }

        if (mouse_r_upevent_cancel) {
            rval = 1;
        }
        mouse_r_upevent_cancel = false;

        if (0 < cancel_rclick) {
            rval = 1;
            cancel_rclick = 0;
            rupflg = 10000;
            INPUT Input = { 0 };
            Input.type = INPUT_MOUSE;
            Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            Input.mi.dx = 0;
            Input.mi.dy = 0;
            ::SendInput(1, &Input, sizeof(INPUT));

            for (int i = 0; i < 11; i++) {
                Sleep(10);
                ZeroMemory(&Input, sizeof(Input));
                Input.type = INPUT_KEYBOARD;
                Input.ki.wScan = 0;
                Input.ki.time = 0;
                Input.ki.dwExtraInfo = 0;
                Input.ki.wVk = VK_ESCAPE;
                Input.ki.dwFlags = 0;
                SendInput(1, &Input, sizeof(INPUT));
                Sleep(20);
                Input.ki.wVk = VK_ESCAPE;
                Input.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &Input, sizeof(INPUT));
            }

        } else {
            rupflg = 0;
        }

    } else if (capxbtn && (WM_XBUTTONDBLCLK == wParam || WM_NCXBUTTONDBLCLK == wParam)) {
        enable = true;
    } else if (capxbtn && (WM_XBUTTONDOWN == wParam || WM_NCXBUTTONDOWN == wParam)) {
        enable = true;
        rval = click_xbutton(WM_XBUTTONDOWN, wParam, lParam);
        if (rval == 1) {
            mouse_x_upevent_cancel = true;
        } else {
            mouse_x_upevent_cancel = false;
        }
    } else if (capxbtn && (WM_XBUTTONUP == wParam || WM_NCXBUTTONUP == wParam)) {
        enable = true;
        if (mouse_x_upevent_cancel) {
            rval = 1;
        }
        mouse_x_upevent_cancel = false;


    } else if (capwheel && WM_MOUSEHWHEEL == wParam) {
        enable = true;
    } else if (capwheel && WM_MOUSEWHEEL == wParam) {
        enable = true;

        if (mouse_lbutton_hold || mouse_rbutton_hold) {
            rval = 1;
            MSLLHOOKSTRUCT* Mll = (MSLLHOOKSTRUCT*)lParam;
            int WheelDelta = GET_WHEEL_DELTA_WPARAM(Mll->mouseData);
            if (WheelDelta < 0) {
                if (mouse_wheel_up) {
                    mouse_wheel_up = false;
                    mouse_wheel_count = 0;
                }
            } else {
                if (!mouse_wheel_up) {
                    mouse_wheel_up = true;
                    mouse_wheel_count = 0;
                }
            }
            mouse_wheel_count += WheelDelta;

            if (mouse_lbutton_hold) {
                int rval2 = 0;
                if (100 < mouse_wheel_count) {
                    mouse_wheel_count = 0;
                    Keyobj* kobj = g_keyopts->get_mouse_lu_button();
                    rval2 = kobj->send_key(lParam);

                } else if (mouse_wheel_count < -100) {
                    mouse_wheel_count = 0;
                    Keyobj* kobj = g_keyopts->get_mouse_ld_button();
                    rval2 = kobj->send_key(lParam);
                }
                if (0 < rval2)
                    cancel_lclick = 1;
            }

            if (mouse_rbutton_hold) {
                int rval2 = 0;
                if (100 < mouse_wheel_count) {
                    mouse_wheel_count = 0;
                    Keyobj* kobj = g_keyopts->get_mouse_ru_button();
                    rval2 = kobj->send_key(lParam);

                } else if (mouse_wheel_count < -100) {
                    mouse_wheel_count = 0;
                    Keyobj* kobj = g_keyopts->get_mouse_rd_button();
                    rval2 = kobj->send_key(lParam);
                }
                if (0 < rval2) {
                    cancel_rclick = 2;
                }
            }
        }
    }

    if (enable) {
        LPMSLLHOOKSTRUCT lpmshook = new MSLLHOOKSTRUCT;
        memcpy(lpmshook, (LPMSLLHOOKSTRUCT)lParam, sizeof(MSLLHOOKSTRUCT));
        PostMessage(g_hwnd, WM_MOUSE_GLOBAL_HOOK, wParam, (LPARAM)lpmshook);
    }
    if (rval == 1)
        return 1;
    return CallNextHookEx(g_hook, code, wParam, lParam);
}

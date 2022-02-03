#include "pch.h"
#include <vector>
#include <windowsx.h>
#include "MouseHook.h"

struct Key {
    int keycode = 0;
    bool ctrl = false;
    bool alt = false;
    bool shift = false;
};
class Keyobj {

public:
    bool enable = false;
    std::vector<Key> m_keys;

public:
    Keyobj()
    {
    }

    ~Keyobj()
    {
    }

    void set_key(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        if (index == 0)
            m_keys.clear();
        if (keycode == 0)
            return;
        enable = true;
        Key key;
        key.keycode = keycode;
        key.ctrl = ctrl;
        key.alt = alt;
        key.shift = shift;
        m_keys.push_back(key);
    }
    int send_key(LPARAM lParam)
    {
        if (!enable)
            return 0;
        if (m_keys.size() < 1)
            return 0;

        INPUT ip;

        for (int i = 0; i < m_keys.size(); i++) {
            Key key = m_keys[i];
            if (key.keycode == 0)
                return 0;

            if (key.keycode == 1)
                return 1;

            /// Keyboard
            ip.type = INPUT_KEYBOARD;
            ip.ki.wScan = 0;
            ip.ki.time = 0;
            ip.ki.dwExtraInfo = 0;

            if (key.ctrl) {
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = 0;
                SendInput(1, &ip, sizeof(INPUT));
            }
            if (key.alt) {
                ip.ki.wVk = VK_MENU;
                ip.ki.dwFlags = 0;
                SendInput(1, &ip, sizeof(INPUT));
            }
            if (key.shift) {
                ip.ki.wVk = VK_SHIFT;
                ip.ki.dwFlags = 0;
                SendInput(1, &ip, sizeof(INPUT));
            }

            ip.ki.wVk = key.keycode;
            ip.ki.dwFlags = 0;
            SendInput(1, &ip, sizeof(INPUT));

            ip.ki.wVk = key.keycode;
            ip.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &ip, sizeof(INPUT));

            if (key.ctrl) {
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
            }
            if (key.alt) {
                ip.ki.wVk = VK_MENU;
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
            }
            if (key.shift) {
                ip.ki.wVk = VK_SHIFT;
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
            }
        }

        return 1;
    }
    void clear_key()
    {
        m_keys.clear();
    }

private:
};
class KeyOptions {
    Keyobj* m_leftbutton = nullptr;
    Keyobj* m_middlebutton = nullptr;
    Keyobj* m_rightbutton = nullptr;
    Keyobj* m_x1tbutton = nullptr;
    Keyobj* m_x2tbutton = nullptr;
    Keyobj* m_lrtbutton = nullptr;
    Keyobj* m_rltbutton = nullptr;
    Keyobj* m_mltbutton = nullptr;
    Keyobj* m_mrtbutton = nullptr;

public:
    KeyOptions()
    {
        m_leftbutton = new Keyobj();
        m_middlebutton = new Keyobj();
        m_rightbutton = new Keyobj();
        m_x1tbutton = new Keyobj();
        m_x2tbutton = new Keyobj();
        m_lrtbutton = new Keyobj();
        m_rltbutton = new Keyobj();
        m_mltbutton = new Keyobj();
        m_mrtbutton = new Keyobj();
    }

    ~KeyOptions()
    {
        delete m_leftbutton;
        delete m_middlebutton;
        delete m_rightbutton;
        delete m_x1tbutton;
        delete m_x2tbutton;
        delete m_lrtbutton;
        delete m_rltbutton;
        delete m_mltbutton;
        delete m_mrtbutton;
    }

    void set_mouse_left_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        //m_leftbutton->set_key(index, keycode , ctrl, alt, shift);
    }
    void set_mouse_middle_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_middlebutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_right_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_rightbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_x1_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_x1tbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_x2_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_x2tbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_lr_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_lrtbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_rl_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_rltbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_ml_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_mltbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_mr_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_mrtbutton->set_key(index, keycode, ctrl, alt, shift);
    }

    Keyobj* get_mouse_left_button()
    {
        return m_leftbutton;
    }
    Keyobj* get_mouse_middle_button()
    {
        return m_middlebutton;
    }
    Keyobj* get_mouse_right_button()
    {
        return m_rightbutton;
    }
    Keyobj* get_mouse_x1_button()
    {
        return m_x1tbutton;
    }
    Keyobj* get_mouse_x2_button()
    {
        return m_x2tbutton;
    }
    Keyobj* get_mouse_lr_button()
    {
        return m_lrtbutton;
    }
    Keyobj* get_mouse_rl_button()
    {
        return m_rltbutton;
    }
    Keyobj* get_mouse_ml_button()
    {
        return m_mltbutton;
    }
    Keyobj* get_mouse_mr_button()
    {
        return m_mrtbutton;
    }

private:
};

HHOOK g_hook = nullptr;
HWND g_hwnd = nullptr;
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
bool mouse_r_upevent_cancel = false;
bool mouse_m_upevent_cancel = false;
bool mouse_l_upevent_cancel = false;

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
void __cdecl start_hook(HWND hwnd, bool lbtn, bool mbtn, bool rbtn, bool xbtn, bool wheel, bool move)
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
LRESULT CALLBACK hook_proc(int code, WPARAM wParam, LPARAM lParam)
{
    int rval = 0;
    if (!g_hwnd || code < 0)
        return CallNextHookEx(g_hook, code, wParam, lParam);

    bool enable = false;





    if (caplbtn && (WM_LBUTTONDBLCLK == wParam || WM_NCLBUTTONDBLCLK == wParam)) {
        enable = true;
        mouse_lbutton_hold = false;
    } else if (caplbtn && (WM_LBUTTONDOWN == wParam || WM_NCLBUTTONDOWN == wParam)) {
        enable = true;
        mouse_lbutton_hold = true;

        if (mouse_rbutton_hold) {
            Keyobj* kobj = g_keyopts->get_mouse_rl_button();
            rval = kobj->send_key(lParam);
        }  
        if (mouse_mbutton_hold) {
            Keyobj* kobj = g_keyopts->get_mouse_ml_button();
            int rval2 = kobj->send_key(lParam);
            if(rval || rval2)
                rval = true;
        }

        if (rval == 1) {
            mouse_l_upevent_cancel = true;
        } else {
            mouse_l_upevent_cancel = false;
        }
    } else if (caplbtn && (WM_LBUTTONUP == wParam || WM_NCLBUTTONUP == wParam)) {
        enable = true;
        if (mouse_l_upevent_cancel) {
            rval = 1;
        }
        mouse_lbutton_hold = false;
        mouse_l_upevent_cancel = false;






    } else if (capmbtn && (WM_MBUTTONDBLCLK == wParam || WM_NCMBUTTONDBLCLK == wParam)) {
        enable = true;
        mouse_mbutton_hold = false;
    } else if (capmbtn && (WM_MBUTTONDOWN == wParam || WM_NCMBUTTONDOWN == wParam)) {
        enable = true;
        mouse_mbutton_hold = true;

        Keyobj* kobj = g_keyopts->get_mouse_middle_button();
        rval = kobj->send_key(lParam);
        if (rval == 1) {
            mouse_m_upevent_cancel = true;
        } else {
            mouse_m_upevent_cancel = false;
        }
    } else if (capmbtn && (WM_MBUTTONUP == wParam || WM_NCMBUTTONUP == wParam)) {
        enable = true;
        if (mouse_m_upevent_cancel) {
            rval = 1;
        }
        mouse_m_upevent_cancel = false;
        mouse_mbutton_hold = false;








    } else if (caprbtn && (WM_RBUTTONDBLCLK == wParam || WM_NCRBUTTONDBLCLK == wParam)) {
        enable = true;
        mouse_rbutton_hold = false;
    } else if (caprbtn && (WM_RBUTTONDOWN == wParam || WM_NCRBUTTONDOWN == wParam)) {
        enable = true;
        mouse_rbutton_hold = true;
        Keyobj* kobj = g_keyopts->get_mouse_right_button();
        rval = kobj->send_key(lParam);

        if (rval == 0) {
            if (mouse_lbutton_hold) {
                Keyobj* kobj = g_keyopts->get_mouse_lr_button();
                rval = kobj->send_key(lParam);
            } 
            if (mouse_mbutton_hold) {
                Keyobj* kobj = g_keyopts->get_mouse_mr_button();
                int rval2 = kobj->send_key(lParam);
                if (rval || rval2)
                    rval = true;
            }
        }

        if (rval == 1) {
            mouse_r_upevent_cancel = true;
        } else {
            mouse_r_upevent_cancel = false;
        }
    } else if (caprbtn && (WM_RBUTTONUP == wParam || WM_NCRBUTTONUP == wParam)) {
        enable = true;
        if (mouse_r_upevent_cancel) {
            rval = 1;
        }
        mouse_r_upevent_cancel = false;
        mouse_rbutton_hold = false;









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
    } else if (capmove && WM_MOUSEMOVE == wParam) {
        enable = true;
    } else if (capmove && WM_NCMOUSEMOVE == wParam) {
        enable = true;
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

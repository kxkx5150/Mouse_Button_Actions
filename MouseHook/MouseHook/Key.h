#pragma once

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
    void key_down(Key key)
    {
        INPUT ip;
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
    void mouse_down(Key key)
    {
        if (key.keycode == WM_XBUTTONDOWN) {
            key.keycode = VK_BROWSER_FORWARD;
            key_down(key);
        } else if (key.keycode == WM_XBUTTONDOWN + 1) {
            key.keycode = VK_BROWSER_BACK;
            key_down(key);
        }
    }
    int send_key(LPARAM lParam)
    {
        if (!enable)
            return 0;
        if (m_keys.size() < 1)
            return 0;

        for (int i = 0; i < m_keys.size(); i++) {
            Key key = m_keys[i];
            if (key.keycode == 0)
                return 0;

            if (key.keycode == 1)
                return 1;

            if (key.keycode == WM_XBUTTONDOWN || key.keycode == WM_XBUTTONDOWN + 1) {      
                mouse_down(key);
            } else {
                key_down(key);
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
    Keyobj* m_rmtbutton = nullptr;
    Keyobj* m_mltbutton = nullptr;
    Keyobj* m_mrtbutton = nullptr;
    Keyobj* m_lmtbutton = nullptr;
    Keyobj* m_lutbutton = nullptr;
    Keyobj* m_ldtbutton = nullptr;
    Keyobj* m_rutbutton = nullptr;
    Keyobj* m_rdtbutton = nullptr;

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
        m_rmtbutton = new Keyobj();
        m_mltbutton = new Keyobj();
        m_mrtbutton = new Keyobj();
        m_lmtbutton = new Keyobj();
        m_lutbutton = new Keyobj();
        m_ldtbutton = new Keyobj();
        m_rutbutton = new Keyobj();
        m_rdtbutton = new Keyobj();
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
        delete m_rmtbutton;
        delete m_mltbutton;
        delete m_mrtbutton;
        delete m_lmtbutton;
        delete m_lutbutton;
        delete m_ldtbutton;
        delete m_rutbutton;
        delete m_rdtbutton;
    }

    void set_mouse_left_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        // m_leftbutton->set_key(index, keycode , ctrl, alt, shift);
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
    void set_mouse_rm_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_rmtbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_ml_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_mltbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_mr_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_mrtbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_lm_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_lmtbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_lu_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_lutbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_ld_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_ldtbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_ru_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_rutbutton->set_key(index, keycode, ctrl, alt, shift);
    }
    void set_mouse_rd_button(int index, int keycode, bool ctrl, bool alt, bool shift)
    {
        m_rdtbutton->set_key(index, keycode, ctrl, alt, shift);
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
    Keyobj* get_mouse_rm_button()
    {
        return m_rmtbutton;
    }
    Keyobj* get_mouse_ml_button()
    {
        return m_mltbutton;
    }
    Keyobj* get_mouse_mr_button()
    {
        return m_mrtbutton;
    }
    Keyobj* get_mouse_lm_button()
    {
        return m_lmtbutton;
    }
    Keyobj* get_mouse_lu_button()
    {
        return m_lutbutton;
    }
    Keyobj* get_mouse_ld_button()
    {
        return m_ldtbutton;
    }
    Keyobj* get_mouse_ru_button()
    {
        return m_rutbutton;
    }
    Keyobj* get_mouse_rd_button()
    {
        return m_rdtbutton;
    }

private:
};

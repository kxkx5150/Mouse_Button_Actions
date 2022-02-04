#pragma once
#include <Windows.h>

#ifdef MOUSEHOOK_EXPORTS
#define __DLL_PORT extern "C" __declspec(dllexport)
#else
#define __DLL_PORT extern "C" __declspec(dllimport)
#endif
#define WM_MOUSE_GLOBAL_HOOK WM_APP + 55
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

__DLL_PORT void __cdecl start_hook(HWND hwnd, bool lbtn, bool mbtn, bool rbtn, bool xbtn, bool wheel, bool move);
__DLL_PORT void __cdecl end_hook();

__DLL_PORT void __cdecl set_mouse_left_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_middle_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_right_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_x1_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_x2_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_lr_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_rl_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_ml_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_mr_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_lm_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_lu_button(int index, int keycode, bool ctrl, bool alt, bool shift);
__DLL_PORT void __cdecl set_mouse_ld_button(int index, int keycode, bool ctrl, bool alt, bool shift);

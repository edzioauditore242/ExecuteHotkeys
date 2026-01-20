#pragma once
#include "Configuration.h"
#include "SKSEMenuFramework.h"

namespace UI {
    void Register();
    namespace HotkeyManager {
        void __stdcall Render();
        void __stdcall RenderAddHotkeyWindow();
        inline MENU_WINDOW AddHotkeyWindow;
    }
}
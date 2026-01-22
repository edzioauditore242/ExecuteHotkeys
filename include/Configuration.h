#pragma once
#include <string>
#include <vector>

namespace Configuration {
    struct Hotkey {
        std::string name;
        uint32_t dxCode;
        bool useLCtrl;
        bool useLAlt;
        bool useLShift;
        bool useRCtrl;
        bool useRAlt;
        bool useRShift;
        bool isPress;
        uint32_t holdMs;
        Hotkey() : name(""), dxCode(0), useLCtrl(false), useLAlt(false), useLShift(false), useRCtrl(false), useRAlt(false), useRShift(false), isPress(true), holdMs(1000) {}
        Hotkey(const std::string& n, uint32_t key, bool lctrl = false, bool lalt = false, bool lshift = false, bool rctrl = false, bool ralt = false, bool rshift = false, bool press = true, uint32_t ms = 1000)
            : name(n), dxCode(key), useLCtrl(lctrl), useLAlt(lalt), useLShift(lshift), useRCtrl(rctrl), useRAlt(ralt), useRShift(rshift), isPress(press), holdMs(ms) {}
    };
    inline std::vector<Hotkey> Hotkeys;
    void LoadConfiguration();
    void SaveConfiguration();
    void AddHotkey(const Hotkey& hotkey);
    void RemoveHotkey(size_t index);
    std::string GetKeyName(uint32_t dxCode);
}
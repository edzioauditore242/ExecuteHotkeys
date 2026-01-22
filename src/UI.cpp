#include "UI.h"

#include <Windows.h>

#include <algorithm>
#include <cctype>

// ============================================
// Configuration Implementation
// ============================================
namespace Configuration {
    std::string GetConfigPath() { return "Data\\SKSE\\Plugins\\ExecuteHotkeys.ini"; }
    void LoadConfiguration() {
        Hotkeys.clear();
        std::string configPath = GetConfigPath();
        std::ifstream file(configPath);
        if (!file.is_open()) {
            logger::info("No configuration file found at {}", configPath);
            return;
        }
        std::string line;
        bool needsUpgrade = false;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == ';' || line[0] == '#') continue;
            std::istringstream iss(line);
            std::string token;
            Hotkey hotkey;
            // Format: Name|DxCode|LCtrl|LAlt|LShift|RCtrl|RAlt|RShift|IsPress|HoldMs
            if (std::getline(iss, hotkey.name, '|') && std::getline(iss, token, '|')) {
                hotkey.dxCode = std::stoul(token);
                if (std::getline(iss, token, '|')) hotkey.useLCtrl = (token == "1");
                if (std::getline(iss, token, '|')) hotkey.useLAlt = (token == "1");
                if (std::getline(iss, token, '|')) hotkey.useLShift = (token == "1");
                if (std::getline(iss, token, '|')) hotkey.useRCtrl = (token == "1");
                if (std::getline(iss, token, '|')) hotkey.useRAlt = (token == "1");
                if (std::getline(iss, token, '|')) hotkey.useRShift = (token == "1");
                std::string isPressToken;
                if (std::getline(iss, isPressToken, '|')) {
                    hotkey.isPress = (isPressToken == "1");
                    if (std::getline(iss, token, '|')) hotkey.holdMs = std::stoul(token);
                } else {
                    // Old format detected: default to press
                    hotkey.isPress = true;
                    hotkey.holdMs = 1000;
                    needsUpgrade = true;
                }
                Hotkeys.push_back(hotkey);
            }
        }
        file.close();
        if (needsUpgrade) {
            SaveConfiguration();  // Upgrade and save with new fields
            logger::info("Upgraded old configuration file");
        }
        logger::info("Loaded {} hotkeys from configuration", Hotkeys.size());
    }
    void SaveConfiguration() {
        std::string configPath = GetConfigPath();
        std::ofstream file(configPath);
        if (!file.is_open()) {
            logger::error("Failed to save configuration to {}", configPath);
            return;
        }
        file << "; Execute Hotkeys Config\n";
        file << "; Format: Name|DxCode|LCtrl|LAlt|LShift|RCtrl|RAlt|RShift|IsPress(1=Press/0=Hold)|HoldMs\n";
        file << "; DxCode is the DirectX scan code in decimal (ck.uesp.net/wiki/Input_Script)\n";
        file << "; Do not use invalid DXScanCodes!!\n\n";
        for (const auto& hotkey : Hotkeys) {
            file << hotkey.name << "|" << hotkey.dxCode << "|" << (hotkey.useLCtrl ? "1" : "0") << "|" << (hotkey.useLAlt ? "1" : "0") << "|" << (hotkey.useLShift ? "1" : "0") << "|" << (hotkey.useRCtrl ? "1" : "0") << "|"
                 << (hotkey.useRAlt ? "1" : "0") << "|" << (hotkey.useRShift ? "1" : "0") << "|" << (hotkey.isPress ? "1" : "0") << "|" << hotkey.holdMs << "\n";
        }
        file.close();
        logger::info("Saved {} hotkeys to configuration", Hotkeys.size());
    }
    void AddHotkey(const Hotkey& hotkey) {
        Hotkeys.push_back(hotkey);
        SaveConfiguration();
    }
    void RemoveHotkey(size_t index) {
        if (index < Hotkeys.size()) {
            Hotkeys.erase(Hotkeys.begin() + index);
            SaveConfiguration();
        }
    }
    std::string GetKeyName(uint32_t dxCode) {
        switch (dxCode) {
            case 1:
                return "Esc";
            case 2:
                return "1";
            case 3:
                return "2";
            case 4:
                return "3";
            case 5:
                return "4";
            case 6:
                return "5";
            case 7:
                return "6";
            case 8:
                return "7";
            case 9:
                return "8";
            case 10:
                return "9";
            case 11:
                return "0";
            case 12:
                return "-";
            case 13:
                return "=";
            case 14:
                return "Backspace";
            case 15:
                return "Tab";
            case 16:
                return "Q";
            case 17:
                return "W";
            case 18:
                return "E";
            case 19:
                return "R";
            case 20:
                return "T";
            case 21:
                return "Y";
            case 22:
                return "U";
            case 23:
                return "I";
            case 24:
                return "O";
            case 25:
                return "P";
            case 26:
                return "[";
            case 27:
                return "]";
            case 28:
                return "Enter";
            case 29:
                return "LCtrl";
            case 30:
                return "A";
            case 31:
                return "S";
            case 32:
                return "D";
            case 33:
                return "F";
            case 34:
                return "G";
            case 35:
                return "H";
            case 36:
                return "J";
            case 37:
                return "K";
            case 38:
                return "L";
            case 39:
                return ";";
            case 40:
                return "'";
            case 41:
                return "~";
            case 42:
                return "LShift";
            case 43:
                return "\\";
            case 44:
                return "Z";
            case 45:
                return "X";
            case 46:
                return "C";
            case 47:
                return "V";
            case 48:
                return "B";
            case 49:
                return "N";
            case 50:
                return "M";
            case 51:
                return ",";
            case 52:
                return ".";
            case 53:
                return "/";
            case 54:
                return "RShift";
            case 55:
                return "NUM*";
            case 56:
                return "LAlt";
            case 57:
                return "Space";
            case 58:
                return "CapsLock";
            case 59:
                return "F1";
            case 60:
                return "F2";
            case 61:
                return "F3";
            case 62:
                return "F4";
            case 63:
                return "F5";
            case 64:
                return "F6";
            case 65:
                return "F7";
            case 66:
                return "F8";
            case 67:
                return "F9";
            case 68:
                return "F10";
            case 69:
                return "NumLock";
            case 70:
                return "ScrollLock";
            case 71:
                return "NUM7";
            case 72:
                return "NUM8";
            case 73:
                return "NUM9";
            case 74:
                return "NUM-";
            case 75:
                return "NUM4";
            case 76:
                return "NUM5";
            case 77:
                return "NUM6";
            case 78:
                return "NUM+";
            case 79:
                return "NUM1";
            case 80:
                return "NUM2";
            case 81:
                return "NUM3";
            case 82:
                return "NUM0";
            case 83:
                return "NUM.";
            case 87:
                return "F11";
            case 88:
                return "F12";
            case 100:
                return "F13";
            case 101:
                return "F14";
            case 102:
                return "F15";
            case 103:
                return "F16";
            case 104:
                return "F17";
            case 105:
                return "F18";
            case 106:
                return "F19";
            case 107:
                return "F20";
            case 108:
                return "F21";
            case 109:
                return "F22";
            case 110:
                return "F23";
            case 111:
                return "F24";
            case 156:
                return "NUMEnter";
            case 157:
                return "RCtrl";
            case 181:
                return "NUM/";
            case 183:
                return "PtrScr";
            case 184:
                return "RAlt";
            case 197:
                return "Pause";
            case 199:
                return "Home";
            case 200:
                return "Up";
            case 201:
                return "PgUp";
            case 203:
                return "Left";
            case 205:
                return "Right";
            case 207:
                return "End";
            case 208:
                return "Down";
            case 209:
                return "PgDown";
            case 210:
                return "Insert";
            case 211:
                return "Delete";
            case 256:
                return "LMB";
            case 257:
                return "RMB";
            case 258:
                return "MMB";
            case 259:
                return "MB3";
            case 260:
                return "MB4";
            case 261:
                return "MB5";
            case 262:
                return "MB6";
            case 263:
                return "MB7";
            case 264:
                return "MWUp";
            case 265:
                return "MWDown";
            default:
                return "Key" + std::to_string(dxCode);
        }
    }
}
// ============================================
// Key Executor Implementation
// ============================================
namespace KeyExecutor {
    void SendKey(uint32_t dxCode, bool down) {
        INPUT input = {0};
        if (dxCode < 256) {
            // Keyboard
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = 0;
            input.ki.wScan = static_cast<WORD>(dxCode);
            input.ki.dwFlags = KEYEVENTF_SCANCODE | (down ? 0 : KEYEVENTF_KEYUP);
            if (dxCode >= 0xE0) {
                input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
            }
        } else if (dxCode >= 256 && dxCode <= 265) {
            // Mouse
            input.type = INPUT_MOUSE;
            if (dxCode <= 263) {
                uint32_t buttonFlagDown, buttonFlagUp;
                DWORD mouseData = 0;
                switch (dxCode) {
                    case 256:
                        buttonFlagDown = MOUSEEVENTF_LEFTDOWN;
                        buttonFlagUp = MOUSEEVENTF_LEFTUP;
                        break;
                    case 257:
                        buttonFlagDown = MOUSEEVENTF_RIGHTDOWN;
                        buttonFlagUp = MOUSEEVENTF_RIGHTUP;
                        break;
                    case 258:
                        buttonFlagDown = MOUSEEVENTF_MIDDLEDOWN;
                        buttonFlagUp = MOUSEEVENTF_MIDDLEUP;
                        break;
                    case 259:
                        buttonFlagDown = MOUSEEVENTF_XDOWN;
                        buttonFlagUp = MOUSEEVENTF_XUP;
                        mouseData = XBUTTON1;
                        break;
                    case 260:
                        buttonFlagDown = MOUSEEVENTF_XDOWN;
                        buttonFlagUp = MOUSEEVENTF_XUP;
                        mouseData = XBUTTON2;
                        break;
                    case 261:
                        buttonFlagDown = MOUSEEVENTF_XDOWN;
                        buttonFlagUp = MOUSEEVENTF_XUP;
                        mouseData = XBUTTON1;
                        break;  // Assuming MB5 as XBUTTON1 repeat
                    case 262:
                        buttonFlagDown = MOUSEEVENTF_XDOWN;
                        buttonFlagUp = MOUSEEVENTF_XUP;
                        mouseData = XBUTTON2;
                        break;  // MB6 as XBUTTON2
                    case 263:
                        buttonFlagDown = MOUSEEVENTF_XDOWN;
                        buttonFlagUp = MOUSEEVENTF_XUP;
                        mouseData = XBUTTON1;
                        break;  // MB7 as XBUTTON1
                    default:
                        return;
                }
                input.mi.dwFlags = down ? buttonFlagDown : buttonFlagUp;
                input.mi.mouseData = mouseData;
            } else {
                // Wheel
                if (!down) return;  // No "up" for wheel
                input.mi.dwFlags = MOUSEEVENTF_WHEEL;
                input.mi.mouseData = (dxCode == 264) ? WHEEL_DELTA : -WHEEL_DELTA;
            }
        } else {
            // Unsupported (e.g., gamepad)
            logger::warn("Unsupported dxCode: {}", dxCode);
            return;
        }
        SendInput(1, &input, sizeof(INPUT));
    }
    void ExecuteKey(const Configuration::Hotkey& hotkey) {
        logger::info("Executing hotkey: {}", hotkey.name);
        std::vector<uint32_t> mods;
        if (hotkey.useLCtrl) mods.push_back(29);
        if (hotkey.useLAlt) mods.push_back(56);
        if (hotkey.useLShift) mods.push_back(42);
        if (hotkey.useRCtrl) mods.push_back(157);
        if (hotkey.useRAlt) mods.push_back(184);
        if (hotkey.useRShift) mods.push_back(54);
        for (auto mod : mods) {
            SendKey(mod, true);
            std::this_thread::sleep_for(10ms);
        }
        SendKey(hotkey.dxCode, true);
        if (hotkey.isPress) {
            std::this_thread::sleep_for(50ms);
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(hotkey.holdMs));
        }
        SendKey(hotkey.dxCode, false);
        std::this_thread::sleep_for(50ms);
        for (auto it = mods.rbegin(); it != mods.rend(); ++it) {
            SendKey(*it, false);
            std::this_thread::sleep_for(10ms);
        }
    }
}
// ============================================
// UI Implementation
// ============================================
void UI::Register() {
    if (!SKSEMenuFramework::IsInstalled()) {
        logger::error("SKSE Menu Framework not installed!");
        return;
    }
    SKSEMenuFramework::SetSection("Execute Hotkeys");
    SKSEMenuFramework::AddSectionItem("Hotkey Manager", HotkeyManager::Render);
    HotkeyManager::AddHotkeyWindow = SKSEMenuFramework::AddWindow(HotkeyManager::RenderAddHotkeyWindow, true);
    logger::info("UI registered successfully");
}
namespace UI::HotkeyManager {
    // State for adding new hotkey
    static char newHotkeyName[256] = "";
    static int selectedKeyIndex = 0;
    static bool useLCtrl = false;
    static bool useLAlt = false;
    static bool useLShift = false;
    static bool useRCtrl = false;
    static bool useRAlt = false;
    static bool useRShift = false;
    static bool isPress = true;
    static uint32_t holdMs = 1000;
    // Common keys for dropdown - ALL DX Scan Codes from UESP
    struct KeyOption {
        const char* name;
        uint32_t dxCode;
    };
    static KeyOption keyOptions[] = {
        {"Esc", 1},       {"1", 2},         {"2", 3},        {"3", 4},      {"4", 5},       {"5", 6},      {"6", 7},     {"7", 8},      {"8", 9},      {"9", 10},      {"0", 11},      {"-", 12},      {"=", 13},           {"Backspace", 14},
        {"Tab", 15},      {"Q", 16},        {"W", 17},       {"E", 18},     {"R", 19},      {"T", 20},     {"Y", 21},    {"U", 22},     {"I", 23},     {"O", 24},      {"P", 25},      {"[", 26},      {"]", 27},           {"Enter", 28},
        {"LCtrl", 29},    {"A", 30},        {"S", 31},       {"D", 32},     {"F", 33},      {"G", 34},     {"H", 35},    {"J", 36},     {"K", 37},     {"L", 38},      {";", 39},      {"'", 40},      {"~ (Console)", 41}, {"LShift", 42},
        {"\\", 43},       {"Z", 44},        {"X", 45},       {"C", 46},     {"V", 47},      {"B", 48},     {"N", 49},    {"M", 50},     {",", 51},     {".", 52},      {"/", 53},      {"RShift", 54}, {"NUM*", 55},        {"LAlt", 56},
        {"Spacebar", 57}, {"CapsLock", 58}, {"F1", 59},      {"F2", 60},    {"F3", 61},     {"F4", 62},    {"F5", 63},   {"F6", 64},    {"F7", 65},    {"F8", 66},     {"F9", 67},     {"F10", 68},    {"NumLock", 69},     {"ScrollLock", 70},
        {"NUM7", 71},     {"NUM8", 72},     {"NUM9", 73},    {"NUM-", 74},  {"NUM4", 75},   {"NUM5", 76},  {"NUM6", 77}, {"NUM+", 78},  {"NUM1", 79},  {"NUM2", 80},   {"NUM3", 81},   {"NUM0", 82},   {"NUM.", 83},        {"F11", 87},
        {"F12", 88},      {"F13", 100},     {"F14", 101},    {"F15", 102},  {"F16", 103},   {"F17", 104},  {"F18", 105}, {"F19", 106},  {"F20", 107},  {"F21", 108},   {"F22", 109},   {"F23", 110},   {"F24", 111},        {"NUMEnter", 156},
        {"RCtrl", 157},   {"NUM/", 181},    {"PtrScr", 183}, {"RAlt", 184}, {"Pause", 197}, {"Home", 199}, {"Up", 200},  {"PgUp", 201}, {"Left", 203}, {"Right", 205}, {"End", 207},   {"Down", 208},  {"PgDown", 209},     {"Insert", 210},
        {"Delete", 211},  {"LMB", 256},     {"RMB", 257},    {"MMB", 258},  {"MB3", 259},   {"MB4", 260},  {"MB5", 261}, {"MB6", 262},  {"MB7", 263},  {"MWUp", 264},  {"MWDown", 265}};
    static const int keyOptionsCount = sizeof(keyOptions) / sizeof(KeyOption);
    void __stdcall Render() {
        ImGuiMCP::Text("Hotkeys:");
        ImGuiMCP::SameLine();
        if (ImGuiMCP::Button("Add Hotkey")) {
            newHotkeyName[0] = '\0';
            selectedKeyIndex = 0;
            useLCtrl = false;
            useLAlt = false;
            useLShift = false;
            useRCtrl = false;
            useRAlt = false;
            useRShift = false;
            isPress = true;
            holdMs = 1000;
            AddHotkeyWindow->IsOpen = true;
        }
        ImGuiMCP::SameLine();
        if (ImGuiMCP::Button("Reload Config")) {
            Configuration::LoadConfiguration();
            logger::info("Configuration reloaded");
        }
        ImGuiMCP::SameLine();
        ImGuiMCP::Text("Search:");
        ImGuiMCP::SameLine();
        static char searchBuffer[256] = "";
        ImGuiMCP::InputText("##Search", searchBuffer, sizeof(searchBuffer));
        ImGuiMCP::Separator();
        if (Configuration::Hotkeys.empty()) {
            ImGuiMCP::TextColored(ImGuiMCP::ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "No hotkeys configured. Click 'Add Hotkey' to create one.");
        } else {
            static ImGuiMCP::ImGuiTableFlags flags = ImGuiMCP::ImGuiTableFlags_Borders | ImGuiMCP::ImGuiTableFlags_RowBg | ImGuiMCP::ImGuiTableFlags_ScrollY;
            if (ImGuiMCP::BeginTable("HotkeyTable", 3, flags)) {
                ImGuiMCP::TableSetupColumn("Name", ImGuiMCP::ImGuiTableColumnFlags_WidthStretch);
                ImGuiMCP::TableSetupColumn("Key Combination", ImGuiMCP::ImGuiTableColumnFlags_WidthStretch);
                ImGuiMCP::TableSetupColumn("Actions", ImGuiMCP::ImGuiTableColumnFlags_WidthFixed, 180.0f);
                ImGuiMCP::TableHeadersRow();
                std::string lowerSearch = searchBuffer;
                std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), ::tolower);
                for (size_t i = 0; i < Configuration::Hotkeys.size(); i++) {
                    const auto& hotkey = Configuration::Hotkeys[i];
                    std::string lowerName = hotkey.name;
                    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
                    if (!lowerSearch.empty() && lowerName.find(lowerSearch) == std::string::npos) continue;
                    ImGuiMCP::TableNextRow();
                    // Name column
                    ImGuiMCP::TableSetColumnIndex(0);
                    ImGuiMCP::Text(hotkey.name.c_str());
                    // Key combination column
                    ImGuiMCP::TableSetColumnIndex(1);
                    std::string keyCombo = "";
                    if (hotkey.useLCtrl) keyCombo += "LCtrl + ";
                    if (hotkey.useRCtrl) keyCombo += "RCtrl + ";
                    if (hotkey.useLAlt) keyCombo += "LAlt + ";
                    if (hotkey.useRAlt) keyCombo += "RAlt + ";
                    if (hotkey.useLShift) keyCombo += "LShift + ";
                    if (hotkey.useRShift) keyCombo += "RShift + ";
                    keyCombo += Configuration::GetKeyName(hotkey.dxCode);
                    ImGuiMCP::Text(keyCombo.c_str());
                    // Actions column
                    ImGuiMCP::TableSetColumnIndex(2);
                    std::string actionButtonId = (hotkey.isPress ? "Press##" : "Hold##") + std::to_string(i);
                    std::string deleteButtonId = "Delete##" + std::to_string(i);
                    if (ImGuiMCP::Button(actionButtonId.c_str())) {
                        logger::info("Executing hotkey: {}", hotkey.name);
                        // Execute in a separate thread with menu close
                        std::thread([hotkey]() {
                            std::this_thread::sleep_for(200ms);
                            // Send ESC to close menu
                            logger::info("Sending ESC to close menu");
                            KeyExecutor::SendKey(1, true);
                            std::this_thread::sleep_for(50ms);
                            KeyExecutor::SendKey(1, false);
                            std::this_thread::sleep_for(100ms);
                            // Execute the hotkey
                            KeyExecutor::ExecuteKey(hotkey);
                        }).detach();
                    }
                    ImGuiMCP::SameLine();
                    if (ImGuiMCP::Button(deleteButtonId.c_str())) {
                        Configuration::RemoveHotkey(i);
                        logger::info("Deleted hotkey: {}", hotkey.name);
                        break;  // Exit loop since vector was modified
                    }
                }
                ImGuiMCP::EndTable();
            }
        }
    }
    void __stdcall RenderAddHotkeyWindow() {
        auto viewport = ImGuiMCP::GetMainViewport();
        auto center = ImGuiMCP::ImVec2Manager::Create();
        ImGuiMCP::ImGuiViewportManager::GetCenter(center, viewport);
        ImGuiMCP::SetNextWindowPos(*center, ImGuiMCP::ImGuiCond_Appearing, ImGuiMCP::ImVec2{0.5f, 0.5f});
        ImGuiMCP::ImVec2Manager::Destroy(center);
        ImGuiMCP::SetNextWindowSize(ImGuiMCP::ImVec2{700, 500}, ImGuiMCP::ImGuiCond_Appearing);
        ImGuiMCP::Begin("Add Hotkey##ExecuteHotkeys", nullptr, ImGuiMCP::ImGuiWindowFlags_NoCollapse);
        ImGuiMCP::Text("Configure a new hotkey:");
        ImGuiMCP::Separator();
        ImGuiMCP::Spacing();
        ImGuiMCP::InputText("Hotkey Name", newHotkeyName, sizeof(newHotkeyName));
        ImGuiMCP::Spacing();
        ImGuiMCP::Text("Select Key:");
        if (ImGuiMCP::BeginCombo("##KeySelect", keyOptions[selectedKeyIndex].name)) {
            for (int i = 0; i < keyOptionsCount; i++) {
                bool isSelected = (selectedKeyIndex == i);
                if (ImGuiMCP::Selectable(keyOptions[i].name, isSelected)) {
                    selectedKeyIndex = i;
                }
                if (isSelected) {
                    ImGuiMCP::SetItemDefaultFocus();
                }
            }
            ImGuiMCP::EndCombo();
        }
        ImGuiMCP::Spacing();
        ImGuiMCP::Text("Modifiers:");
        ImGuiMCP::Checkbox("LCtrl", &useLCtrl);
        ImGuiMCP::SameLine();
        ImGuiMCP::Checkbox("LAlt", &useLAlt);
        ImGuiMCP::SameLine();
        ImGuiMCP::Checkbox("LShift", &useLShift);
        ImGuiMCP::Checkbox("RCtrl", &useRCtrl);
        ImGuiMCP::SameLine();
        ImGuiMCP::Checkbox("RAlt", &useRAlt);
        ImGuiMCP::SameLine();
        ImGuiMCP::Checkbox("RShift", &useRShift);
        ImGuiMCP::Spacing();
        ImGuiMCP::Text("Action Type:");
        if (ImGuiMCP::Checkbox("Press", &isPress)) {
            if (isPress) {
                // No action needed
            }
        }
        ImGuiMCP::SameLine();
        bool isHold = !isPress;
        if (ImGuiMCP::Checkbox("Hold", &isHold)) {
            isPress = !isHold;
        }
        if (isHold) {
            ImGuiMCP::SameLine();
            ImGuiMCP::InputScalar("ms", ImGuiMCP::ImGuiDataType_U32, &holdMs);
        }
        ImGuiMCP::Spacing();
        ImGuiMCP::Separator();
        ImGuiMCP::Spacing();
        bool canAdd = strlen(newHotkeyName) > 0;
        if (!canAdd) {
            ImGuiMCP::PushStyleVar(ImGuiMCP::ImGuiStyleVar_Alpha, 0.5f);
        }
        if (ImGuiMCP::Button("Add Hotkey") && canAdd) {
            Configuration::Hotkey newHotkey(std::string(newHotkeyName), keyOptions[selectedKeyIndex].dxCode, useLCtrl, useLAlt, useLShift, useRCtrl, useRAlt, useRShift, isPress, holdMs);
            Configuration::AddHotkey(newHotkey);
            logger::info("Added new hotkey: {}", newHotkey.name);
            AddHotkeyWindow->IsOpen = false;
        }
        if (!canAdd) {
            ImGuiMCP::PopStyleVar();
        }
        ImGuiMCP::SameLine();
        if (ImGuiMCP::Button("Cancel")) {
            AddHotkeyWindow->IsOpen = false;
        }
        if (ImGuiMCP::IsKeyPressed(ImGuiMCP::ImGuiKey_Escape)) {
            AddHotkeyWindow->IsOpen = false;
        }
        ImGuiMCP::End();
    }
}
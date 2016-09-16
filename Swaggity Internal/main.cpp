#include "Windows.h"
#include "VMTSwag.h"
#include "Interfaces.h"
#include "Hooks.h"
#include <iostream>
#include <TlHelp32.h>
#include "Offsets.h"
#include "Config.h"
#include "Global.h"
#include "IEngineTrace.h"
#include "OnDeath.h"

using namespace std;

vector<VMTSwag*> vVmts;
GameEvents::OnPlayerDeath* pEvent;

void WelcomeMessage()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
    cout << "This cheat is sponsored by: aimtec.io" << endl;
    cout << "Affordable and unique cheats for OverWatch" << endl << endl;
    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}

void LoadOffsets()
{
    Offsets::GrabOffsets();
    Interfaces::MoveHelper = reinterpret_cast<IMoveHelper*>(offsets.MoveHelper); //Sigg'd interface
    cout << uppercase << "Interfaces::MoveHelper -> 0x" << Interfaces::MoveHelper << endl;
}

void LoadInterfaces()
{
    cout << "Loading Interfaces......." << endl;

    Interfaces::Engine      = CreateInterface<IEngineClient*>("engine.dll", "VEngineClient014");
    Interfaces::EngineTrace = CreateInterface<IEngineTrace*>("engine.dll", "EngineTraceClient004");
    Interfaces::EntityList  = CreateInterface<IClientEntityList*>("client.dll", "VClientEntityList003");
    Interfaces::Client      = CreateInterface<IBaseClientDll*>("client.dll", "VClient017");
    Interfaces::ClientMode  = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<DWORD**>(Interfaces::Client))[10] + 0x5);
    Interfaces::GlobalVars  = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<DWORD**>(Interfaces::Client))[0] + 0x53);
    Interfaces::Events      = CreateInterface<IGameEventManager2*>("engine.dll", "GAMEEVENTSMANAGER002");
    Interfaces::Surface     = CreateInterface<ISurface*>("vguimatsurface.dll", "VGUI_Surface031");
    Interfaces::VPanel      = CreateInterface<IVPanel*>("vgui2.dll", "VGUI_Panel009");
    Interfaces::Prediction  = CreateInterface<CPrediction*>("client.dll", "VClientPrediction001");
    Interfaces::Movement    = CreateInterface<IGameMovement*>("client.dll", "GameMovement001");

    cout << uppercase << "Interfaces::Engine -> 0x" << Interfaces::Engine << endl;
    cout << uppercase << "Interfaces::EngineTrace -> 0x" << Interfaces::EngineTrace << endl;
    cout << uppercase << "Interfaces::EntityList -> 0x" << Interfaces::EntityList << endl;
    cout << uppercase << "Interfaces::Client -> 0x" << Interfaces::Client << endl;
    cout << uppercase << "Interfaces::ClientMode -> 0x" << Interfaces::ClientMode << endl;
    cout << uppercase << "Interfaces::GlobalVars -> 0x" << Interfaces::GlobalVars << endl;
    cout << uppercase << "Interfaces::Events -> 0x" << Interfaces::Events << endl;
    cout << uppercase << "Interfaces::Surface -> 0x" << Interfaces::Surface << endl;
    cout << uppercase << "Interfaces::VPanel -> 0x" << Interfaces::VPanel << endl;
    cout << uppercase << "Interfaces::Prediction -> 0x" << Interfaces::Prediction << endl;
    cout << uppercase << "Interfaces::Movement -> 0x" << Interfaces::Movement << endl;
}

void LoadHooks()
{
    cout << "\n\n\nLoading Hooks......." << endl;
    cout << "Hooks::Client -> ";
    Hooks::Client       = new VMTSwag(reinterpret_cast<DWORD**>(Interfaces::Client));
    cout << "Hooks::ClientMode -> ";
    Hooks::ClientMode   = new VMTSwag(reinterpret_cast<DWORD**>(Interfaces::ClientMode));
    cout << "Hooks::Surface -> ";
    Hooks::Surface      = new VMTSwag(reinterpret_cast<DWORD**>(Interfaces::Surface));
    cout << "Hooks::VPanel -> ";
    Hooks::VPanel       = new VMTSwag(reinterpret_cast<DWORD**>(Interfaces::VPanel));
    cout << "Hooks::D3D9 -> ";
    Hooks::D3D9         = new VMTSwag(reinterpret_cast<DWORD**>(offsets.d3d9Device));

    auto OnDeath = new GameEvents::OnPlayerDeath();

    vVmts = { Hooks::Client, Hooks::ClientMode, Hooks::Surface, Hooks::VPanel, Hooks::D3D9 };
    pEvent = OnDeath;

    if (!OnDeath)
        cout << "algo chungo ha pasao loko" << endl;

    oCreateMove     = reinterpret_cast<CreateMoveFn>(
        Hooks::ClientMode->hookFunc(reinterpret_cast<DWORD>(
            Hooks::CreateMove), 24));

    oOverrideView = reinterpret_cast<OverrideViewFn>(
        Hooks::ClientMode->hookFunc(reinterpret_cast<DWORD>(
            Hooks::OverrideView), 18));

    oFrameStageNotify = reinterpret_cast<FrameStageNotifyFn>(
        Hooks::Client->hookFunc(reinterpret_cast<DWORD>(
            Hooks::FrameStageNotify), 36));

    oPaintTraverse = reinterpret_cast<PaintTraverseFn>(
        Hooks::VPanel->hookFunc(reinterpret_cast<DWORD>(
            Hooks::PaintTraverse), 41));

    oEndScene = reinterpret_cast<EndSceneFn>(
        Hooks::D3D9->hookFunc(reinterpret_cast<DWORD>(
            Hooks::EndScene), 42));

    oReset = reinterpret_cast<ResetFn>(
        Hooks::D3D9->hookFunc(reinterpret_cast<DWORD>(
            Hooks::Reset), 43));
    /*
    oPlaySound = reinterpret_cast<PlaySoundFn>(
        Hooks::Surface->hookfunc(reinterpret_cast<DWORD>(
            Hooks::PlaySound), ))
        */


    cout << "oCreateMove -> 0x" << DWORD(oCreateMove) << endl;
    cout << "oOverrideView -> 0x" << DWORD(oOverrideView) << endl;
    cout << "oFrameStageNotify -> 0x" << DWORD(oFrameStageNotify) << endl;
    cout << "oPaintTraverse -> 0x" << DWORD(oPaintTraverse) << endl;
    cout << "oEndScene -> 0x" << DWORD(oEndScene) << endl;
    cout << "oReset -> 0x" << DWORD(oReset) << endl;
}

void LoadFonts()
{
    Interfaces::Surface->SetFontGlyphSet(Global::textFont = Interfaces::Surface->Create_Font(), "Verdana", 12, FW_DONTCARE, 0, 0, FONTFLAG_OUTLINE);
}

void writeFile(ofstream& ofs)
{
    ofs << "[General]" << endl;
    ofs << "RageRCS=" << Config::RageRCS << endl;
    ofs << "LegitRCS=" << Config::LegitRCS << endl;
    ofs << "NoVisRecoil=" << Config::NoVisRecoil << endl;
    ofs << "RageAimbot=" << Config::RageAimbot << endl;
    ofs << "LegitAimbot=" << Config::LegitAimbot << endl;
    ofs << "MinBullets=" << Config::MinBullets << endl;
    ofs << "MaxBullets=" << Config::MaxBullets << endl;
    ofs << "AimbotFOV=" << Config::AimbotFOV << endl;
    ofs << "DistanceBasedFOV=" << Config::DistanceBasedFOV << endl;
    ofs << "SmoothFactor=" << Config::SmoothFactor << endl;
    ofs << "SilentAim=" << Config::SilentAim << endl;
    ofs << "CrosshairRecoil=" << Config::CrosshairRecoil << endl;
    ofs << "NoFlash=" << Config::NoFlash << endl;
    ofs << "BunnyHop=" << Config::Bhop << endl;
    ofs << "BunnyHop_MinJumps=" << Config::BhopMinJumps << endl;
    ofs << "BunnyHop_MaxJumps=" << Config::BhopMaxJumps << endl;
    ofs << "ESP=" << Config::ESP << endl;
    ofs << "ESPName=" << Config::ESPFeatures[0] << endl;
    ofs << "ESPHealth=" << Config::ESPFeatures[1] << endl;
    ofs << "ESPDistance=" << Config::ESPFeatures[2] << endl;
    ofs << "ESPGun=" << Config::ESPFeatures[3] << endl;
    ofs << "ESPHead=" << Config::ESPFeatures[4] << endl;
    ofs << "ShitTalk=" << Config::ShitTalk << endl;
    ofs << "TriggerBot=" << Config::Trigger << endl;
    ofs << "TriggerBot_Delay=" << Config::TriggerDelay << endl;
    ofs << "TriggerBot_HitChance=" << Config::TriggerChance << endl;
    ofs << "TriggerBot_Key=" << Config::TriggerKey << endl;
    ofs << "TriggerBot_PSilent=" << Config::TriggerSilent << endl;
}

void LoadSettings()
{
    char path[256];
    GetModuleFileNameA(NULL, LPSTR(path), sizeof(path));
    string settings(path);
    size_t pos = settings.rfind("\\");
    settings.replace(pos + 1, string::npos, "settings.ini");

    ifstream ifs("settings.ini");
    if (!ifs.good())
    {
        ofstream ofs("settings.ini");
        writeFile(ofs);
    }
    else
    {
        Config::RageRCS         = GetPrivateProfileInt("General", "RageRCS", 1, settings.c_str())           != 0;
        Config::LegitRCS        = GetPrivateProfileInt("General", "LegitRCS", 0, settings.c_str())          != 0;
        Config::NoVisRecoil     = GetPrivateProfileInt("General", "NoVisRecoil", 1, settings.c_str())       != 0;
        Config::RageAimbot      = GetPrivateProfileInt("General", "RageAimbot", 1, settings.c_str()) != 0;
        Config::LegitAimbot     = GetPrivateProfileInt("General", "LegitAimbot", 0, settings.c_str()) != 0;
        Config::MinBullets      = GetPrivateProfileInt("General", "MinBullets", 2, settings.c_str());
        Config::MaxBullets      = GetPrivateProfileInt("General", "MaxBullets", 9, settings.c_str());
        Config::AimbotFOV       = GetPrivateProfileInt("General", "AimbotFOV", 6, settings.c_str());
        Config::DistanceBasedFOV = GetPrivateProfileInt("General", "DistanceBasedFOV", 1, settings.c_str()) != 0;
        Config::SmoothFactor    = GetPrivateProfileInt("General", "SmoothFactor", 8, settings.c_str());
        Config::SilentAim       = GetPrivateProfileInt("General", "SilentAim", 1, settings.c_str())         != 0;
        Config::CrosshairRecoil = GetPrivateProfileInt("General", "CrosshairRecoil", 0, settings.c_str())   != 0;
        Config::NoFlash         = GetPrivateProfileInt("General", "NoFlash", 1, settings.c_str())           != 0;
        Config::Bhop            = GetPrivateProfileInt("General", "BunnyHop", 1, settings.c_str())          != 0;
        Config::BhopMinJumps    = GetPrivateProfileInt("General", "BunnyHop_MinJumps", 3, settings.c_str());
        Config::BhopMaxJumps    = GetPrivateProfileInt("General", "BunnyHop_MaxJumps", 5, settings.c_str());
        Config::ESPFeatures[0]  = GetPrivateProfileInt("General", "ESPName", 1, settings.c_str())           != 0;  //Name
        Config::ESPFeatures[1]  = GetPrivateProfileInt("General", "ESPHealth", 1, settings.c_str())         != 0;  //Health
        Config::ESPFeatures[2]  = GetPrivateProfileInt("General", "ESPDistance", 1, settings.c_str())       != 0;  //Distance
        Config::ESPFeatures[3]  = GetPrivateProfileInt("General", "ESPGun", 1, settings.c_str())            != 0;  //Gun
        Config::ESPFeatures[4]  = GetPrivateProfileInt("General", "ESPHead", 1, settings.c_str())           != 0;  //Gun
        Config::ESP             = GetPrivateProfileInt("General", "ESP", 0, settings.c_str())               != 0;
        Config::ShitTalk        = GetPrivateProfileInt("General", "ShitTalk", 0, settings.c_str())          != 0;
        Config::Trigger         = GetPrivateProfileInt("General", "TriggerBot", 1, settings.c_str())        != 0;
        Config::TriggerDelay    = GetPrivateProfileInt("General", "TriggerBot_Delay", 7, settings.c_str());
        Config::TriggerChance   = GetPrivateProfileInt("General", "TriggerBot_HitChance", 90, settings.c_str());
        Config::TriggerKey      = GetPrivateProfileInt("General", "TriggerBot_Key", 0x05, settings.c_str());
        Config::TriggerSilent   = GetPrivateProfileInt("General", "TriggerBot_Silent", 1, settings.c_str()) != 0;
    }

}

void printStatus(HANDLE h, bool b, bool isNumber = false, uint value = 0, bool isHexa = false)
{
    cout << " [";

    if (!isNumber)
    {
        SetConsoleTextAttribute(h, b ? FOREGROUND_GREEN : FOREGROUND_RED);

        if (b)
            cout << "enabled";
        else
            cout << "disabled";
    }
    else
    {
        SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
        if (!isHexa)
            cout.setf(ios::dec, ios::basefield); //For decimal display in number settings
        else
        {
            cout << "0x";
            cout.setf(ios::hex, ios::basefield);
        }

        cout << value;

        if (!isHexa)
            cout.setf(ios::hex, ios::basefield);
    }

    SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    cout << "]" << endl;

}

void printMenu(HANDLE& hOut)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hOut = hConsole;

    system("cls");
    cout << "|||Swaggity 'Internal Menu: |||" << endl;
    cout << "#1  -> Toggle Rage Recoil"; printStatus(hConsole, Config::RageRCS);
    cout << "#2  -> Toggle Legit Recoil"; printStatus(hConsole, Config::LegitRCS);
    cout << "#3  -> Toggle NoVis Recoil"; printStatus(hConsole, Config::NoVisRecoil);
    cout << "#4  -> Toggle Rage Aimbot"; printStatus(hConsole, Config::RageAimbot);
    cout << "#5  -> Toggle Legit Aimbot"; printStatus(hConsole, Config::LegitAimbot);
    cout << "#6  -> Set Aimbot MinBullets to Start"; printStatus(hConsole, false, true, Config::MinBullets);
    cout << "#7  -> Set Aimbot MaxBullets to Head"; printStatus(hConsole, false, true, Config::MaxBullets);
    cout << "#8  -> Set Aimbot FOV"; printStatus(hConsole, false, true, Config::AimbotFOV);
    cout << "#9  -> Set Distance Based FOV"; printStatus(hConsole, Config::DistanceBasedFOV);
    cout << "#10 -> Set Smooth Factor"; printStatus(hConsole, false, true, Config::SmoothFactor);
    cout << "#11 -> Toggle Silent Aim"; printStatus(hConsole, Config::SilentAim);
    cout << "#12 -> Toggle Recoil Crosshair"; printStatus(hConsole, Config::CrosshairRecoil);
    cout << "#13 -> Toggle NoFlash"; printStatus(hConsole, Config::NoFlash);
    cout << "#14 -> Toggle BunnyHop"; printStatus(hConsole, Config::Bhop);
    cout << "#15 -> Set BunnyHop Minimum Successful Jumps"; printStatus(hConsole, false, true, Config::BhopMinJumps);
    cout << "#16 -> Set BunnyHop Maximum Successful Jumps"; printStatus(hConsole, false, true, Config::BhopMaxJumps);
    cout << "#17 -> Toggle ESP"; printStatus(hConsole, Config::ESP);
    cout << "#18 -> Toggle ESP Features" << endl;
    cout << "#19 -> Toggle TriggerBot"; printStatus(hConsole, Config::Trigger);
    cout << "#20 -> Toggle ShitTalk"; printStatus(hConsole, Config::ShitTalk);
    cout << "#21 -> Toggle TriggerBot PSilent"; printStatus(hConsole, Config::TriggerSilent);
    cout << "#22 -> Set TriggerBot Delay (ms)"; printStatus(hConsole, false, true, Config::TriggerDelay);
    cout << "#23 -> Set TriggerBot Hitchance (%)"; printStatus(hConsole, false, true, Config::TriggerChance);
    cout << "#24 -> Set TriggerBot Key (VK_KEY CODE)"; printStatus(hConsole, false, true, Config::TriggerKey);
}

void Setup(HINSTANCE hinstDLL)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    cout.setf(ios::hex, ios::basefield);
    WelcomeMessage();
    LoadInterfaces();
    LoadOffsets();
    LoadHooks();
    LoadSettings();
    LoadFonts();


    bool leave = false;
    cout << "\n\n\n";
    system("pause");
    while (!leave)
    {
        int n;
        HANDLE h;
        printMenu(h);
        cin >> n;

        switch (n)
        {
        case 1:
            if (Config::RageRCS)
                Config::RageRCS = false;
            else
            {
                Config::LegitRCS = false;
                Config::RageRCS = true;
            }
            break;

        case 2:
            if (Config::LegitRCS)
                Config::LegitRCS = false;
            else
            {
                Config::RageRCS = false;
                Config::LegitRCS = true;
            }
            break;

        case 3:
            Config::NoVisRecoil = !Config::NoVisRecoil;
            break;

        case 4:
            if (Config::RageAimbot)
                Config::RageAimbot = false;
            else
            {
                Config::LegitAimbot = false;
                Config::RageAimbot = true;
            }
            break;

        case 5:
            if (Config::LegitAimbot)
                Config::LegitAimbot = false;
            else
            {
                Config::RageAimbot = false;
                Config::LegitAimbot = true;
            }
            break;

        case 6:
            cout << "Specify Min Bullets to start Aimbotting: ";
            cin >> n;
            Config::MinBullets = n;
            break;


        case 7:
            cout << "Specify Max Bullets to the Head when Aimbotting: ";
            cin >> n;
            Config::MaxBullets = n;
            break;

        case 8:
            cout << "Specify a new Aimbot FOV: ";
            cin >> n;
            Config::AimbotFOV = n;
            break;

        case 9:
            Config::DistanceBasedFOV = !Config::DistanceBasedFOV;
            break;

        case 10:
            cout << "Specify a new Aimbot Smooth Factor: ";
            cin >> n;
            Config::SmoothFactor = n;
            break;

        case 11:
            Config::SilentAim = !Config::SilentAim;
            if (Config::SilentAim)
            {
                if (Config::LegitRCS)
                {
                    Config::LegitRCS = false;
                    Config::RageRCS = true;
                }
            }
            break;

        case 12:
            Config::CrosshairRecoil = !Config::CrosshairRecoil;
            break;

        case 13:
            Config::NoFlash = !Config::NoFlash;
            break;

        case 14:
            Config::Bhop = !Config::Bhop;
            break;

        case 15:
            cout << "Specify a number of Minimum Successful Bhops: ";
            cin >> n;
            Config::BhopMinJumps = n;
            break;

        case 16:
            cout << "Specify a number of Maximum Successful Bhops: ";
            cin >> n;
            Config::BhopMaxJumps = n;
            break;

        case 17:
            Config::ESP = !Config::ESP;
            break;

        case 18:
            do
            {
                system("cls");
                cout << "#1 -> ESP Name"; printStatus(h, Config::ESPFeatures[0]);
                cout << "#2 -> ESP Health"; printStatus(h, Config::ESPFeatures[1]);
                cout << "#3 -> ESP Distance"; printStatus(h, Config::ESPFeatures[2]);
                cout << "#4 -> ESP Gun"; printStatus(h, Config::ESPFeatures[3]);
                cout << "#5 -> ESP Head"; printStatus(h, Config::ESPFeatures[4]);
                cout << "Choose a feature to toggle (9 TO GO BACK TO MAIN MENU): ";
                cin >> n;

                if (n != 9)
                    Config::ESPFeatures[n-1] = !Config::ESPFeatures[n-1];

            } while (n != 9);
            break;

        case 19:
            Config::Trigger = !Config::Trigger;
            break;

        case 20:
            Config::ShitTalk = !Config::ShitTalk;
            break;

        case 21:
            Config::TriggerSilent = !Config::TriggerSilent;
            break;

        case 22:
            cout << "Specify a new trigger delay: ";
            cin >> n;
            Config::TriggerDelay = n;
            break;

        case 23:
            cout << "Specify a new trigger hitchance: ";
            cin >> n;
            Config::TriggerChance = n;
            break;

        case 24:
            cout << "Specify a new trigger key: ";
            cin.setf(ios::hex, ios::basefield);
            cin >> n;
            Config::TriggerKey = n;
            cin.setf(ios::dec, ios::basefield);
            break;


        case 99:
            leave = true;

        default:
            break;
        }

        ofstream ofs("settings.ini");
        writeFile(ofs);

        cout << endl;
    }

    FreeLibraryAndExitThread(hinstDLL, DLL_PROCESS_DETACH);
    
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, LPTHREAD_START_ROUTINE(Setup), hinstDLL, 0, 0);
    else if (fdwReason == DLL_PROCESS_DETACH)
    {
        Sleep(100);
        FreeConsole();
        Sleep(50);

        pEvent->Unhook();

        for (int i = 0; i < vVmts.size(); ++i)
            vVmts[i]->UnHook();

    }
    return true;
}


/*
int GetProcID(string name)
{
    HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProc, &pe32))
        return NULL;

    if (pe32.szExeFile == name)
        pe32.th32ProcessID;
    else
    {
        while (GetLastError() != ERROR_NO_MORE_FILES)
        {
            Process32Next(hProc, &pe32);
            if (pe32.szExeFile == name)
                return pe32.th32ProcessID;
        }
    }

    return NULL;
}

int main()
{
    LPCSTR mutex = "Wachiconteia";
    if (CreateMutex(NULL, FALSE, mutex) == NULL && GetLastError() == ERROR_ALREADY_EXISTS)
    {
        CreateThread(0, 0, LPTHREAD_START_ROUTINE(Setup), 0, 0, 0);
    }
    else
    {
        string tmp = "Swaggity Internal.exe";
        string proc = "csgo.exe";
        char path[256];

        GetModuleFileNameA(NULL, LPSTR(path), sizeof(path));
        string module(path);
        size_t pos = module.rfind("\\");
        module.replace(pos + 1, string::npos, tmp);

        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetProcID(proc)); //Open Handle
        void* address = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"); //Get LoadLibrary Address
        void* arg = VirtualAllocEx(hProc, nullptr, sizeof(module), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); //Reserve space
        WriteProcessMemory(hProc, arg, module.c_str(), strlen(module.c_str()), NULL); //Write Module Name (LoadLibrary Parameter)
        CreateRemoteThread(hProc, NULL, NULL, LPTHREAD_START_ROUTINE(address), arg, NULL, NULL); //Call LoadLibrary

        CloseHandle(hProc);
    }
    */
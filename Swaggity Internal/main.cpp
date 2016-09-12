#include "Windows.h"
#include "VMTSwag.h"
#include "Interfaces.h"
#include "Hooks.h"
#include <iostream>
#include <TlHelp32.h>
#include "Offsets.h"
#include "Config.h"
#include "IEngineTrace.h"
#include "OnDeath.h"
#include "D3D.h"

D3D pD3D;


using namespace std;

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

void unHook()
{
    delete Hooks::Client;
    delete Hooks::ClientMode;
    delete Hooks::Surface;
    delete Hooks::VPanel;
    delete Hooks::D3D9;

}

void writeFile(ofstream& ofs)
{ 
    ofs << "[General]" << endl;
    ofs << "RageRCS=" << Config::configuration[2].lbool[1].second << endl;
    ofs << "LegitRCS=" << Config::configuration[2].lbool[2].second << endl;
    ofs << "NoVisRecoil=" << Config::configuration[2].lbool[3].second << endl;
    ofs << "CrosshairRecoil=" << Config::configuration[2].lbool[4].second << endl;
    ofs << "RageAimbot=" << Config::configuration[3].lbool[1].second << endl;
    ofs << "LegitAimbot=" <<Config::configuration[3].lbool[2].second << endl;
    ofs << "AimbotFOV=" << Config::AimbotFOV << endl;
    ofs << "SmoothFactor=" << Config::SmoothFactor << endl;
    ofs << "SilentAim=" << Config::SilentAim << endl;
   
    ofs << "NoFlash=" << Config::configuration[5].lbool[0].second << endl;
    ofs << "BunnyHop=" << Config::configuration[5].lbool[1].second << endl;
    ofs << "ESP=" <<Config::configuration[1].lbool[1].second << endl;
    ofs << "ESPName=" << Config::ESPFeatures[0] << endl;
    ofs << "ESPHealth=" << Config::ESPFeatures[1] << endl;
    ofs << "ESPDistance=" << Config::ESPFeatures[2] << endl;
    ofs << "ESPGun=" << Config::ESPFeatures[3] << endl;
    ofs << "ESPHead=" << Config::ESPFeatures[4] << endl;
    ofs << "ShitTalk=" << Config::configuration[5].lbool[2].second << endl;
    ofs << "TriggerBot=" << Config::configuration[4].lbool[0].second<< endl;
 //   ofs << "TriggerBot_Delay=" << Config::TriggerDelay << endl;
   // ofs << "TriggerBot_HitChance=" << Config::TriggerChance << endl;
   // ofs << "TriggerBot_Key=" << Config::TriggerKey << endl;
  //  ofs << "TriggerBot_PSilent=" << Config::TriggerSilent << endl;
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
        Config::configuration[2].lbool[1].second         = GetPrivateProfileInt("General", "RageRCS", 1, settings.c_str())           != 0;
        Config::configuration[2].lbool[2].second        = GetPrivateProfileInt("General", "LegitRCS", 0, settings.c_str())          != 0;
        Config::configuration[2].lbool[3].second     = GetPrivateProfileInt("General", "NoVisRecoil", 1, settings.c_str())       != 0;
        Config::configuration[3].lbool[1].second      = GetPrivateProfileInt("General", "RageAimbot", 1, settings.c_str()) != 0;
       Config::configuration[3].lbool[2].second     = GetPrivateProfileInt("General", "LegitAimbot", 0, settings.c_str()) != 0;
        Config::AimbotFOV       = GetPrivateProfileInt("General", "AimbotFOV", 6, settings.c_str());
        Config::SmoothFactor    = GetPrivateProfileInt("General", "SmoothFactor", 8, settings.c_str());
        Config::SilentAim       = GetPrivateProfileInt("General", "SilentAim", 1, settings.c_str())         != 0;
        Config::configuration[2].lbool[4].second = GetPrivateProfileInt("General", "CrosshairRecoil", 0, settings.c_str())   != 0;
        Config::configuration[5].lbool[0].second         = GetPrivateProfileInt("General", "NoFlash", 1, settings.c_str())           != 0;
        Config::configuration[5].lbool[1].second            = GetPrivateProfileInt("General", "BunnyHop", 1, settings.c_str())          != 0;
        Config::ESPFeatures[0]  = GetPrivateProfileInt("General", "ESPName", 1, settings.c_str())           != 0;  //Name
        Config::ESPFeatures[1]  = GetPrivateProfileInt("General", "ESPHealth", 1, settings.c_str())         != 0;  //Health
        Config::ESPFeatures[2]  = GetPrivateProfileInt("General", "ESPDistance", 1, settings.c_str())       != 0;  //Distance
        Config::ESPFeatures[3]  = GetPrivateProfileInt("General", "ESPGun", 1, settings.c_str())            != 0;  //Gun
        Config::ESPFeatures[4]  = GetPrivateProfileInt("General", "ESPHead", 1, settings.c_str())           != 0;  //Gun
       Config::configuration[1].lbool[1].second            = GetPrivateProfileInt("General", "ESP", 0, settings.c_str())               != 0;
        Config::configuration[5].lbool[2].second        = GetPrivateProfileInt("General", "ShitTalk", 0, settings.c_str())          != 0;
        Config::configuration[4].lbool[0].second        = GetPrivateProfileInt("General", "TriggerBot", 1, settings.c_str())        != 0;
    //    Config::TriggerDelay    = GetPrivateProfileInt("General", "TriggerBot_Delay", 7, settings.c_str());
    //    Config::TriggerChance   = GetPrivateProfileInt("General", "TriggerBot_HitChance", 90, settings.c_str());
  //      Config::TriggerKey      = GetPrivateProfileInt("General", "TriggerBot_Key", 0x05, settings.c_str());
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
    cout << "#1  -> Toggle Rage Recoil"; printStatus(hConsole, Config::configuration[2].lbool[1].second);
    cout << "#2  -> Toggle Legit Recoil"; printStatus(hConsole, Config::configuration[2].lbool[2].second);
    cout << "#3  -> Toggle NoVis Recoil"; printStatus(hConsole, Config::configuration[2].lbool[3].second);
    cout << "#4  -> Toggle Rage Aimbot"; printStatus(hConsole, Config::configuration[3].lbool[1].second);
    cout << "#5  -> Toggle Legit Aimbot"; printStatus(hConsole,Config::configuration[3].lbool[2].second);
    cout << "#6  -> Set Aimbot FOV"; printStatus(hConsole, false, true, Config::AimbotFOV, false);
    cout << "#7  -> Set Smooth Factor"; printStatus(hConsole, false, true, Config::SmoothFactor, false);
    cout << "#8  -> Toggle Silent Aim"; printStatus(hConsole, Config::SilentAim);
    cout << "#9 -> Toggle Recoil Crosshair"; printStatus(hConsole, Config::configuration[2].lbool[4].second);
    cout << "#10 -> Toggle NoFlash"; printStatus(hConsole, Config::configuration[5].lbool[0].second);
    cout << "#11 -> Toggle BunnyHop"; printStatus(hConsole, Config::configuration[5].lbool[1].second);
    cout << "#12  -> Toggle ESP"; printStatus(hConsole, Config::configuration[1].lbool[1].second);
    cout << "#13 -> Toggle ESP Features" << endl;
    cout << "#14 -> Toggle TriggerBot"; printStatus(hConsole, Config::configuration[4].lbool[0].second);
    cout << "#15 -> Toggle ShitTalk"; printStatus(hConsole, Config::configuration[5].lbool[2].second);
    cout << "#16 -> Toggle TriggerBot PSilent"; printStatus(hConsole, Config::TriggerSilent);
  //  cout << "#17 -> Set TriggerBot Delay (ms)"; printStatus(hConsole, false, true, Config::TriggerDelay, false);
  //  cout << "#18 -> Set TriggerBot Hitchance (%)"; printStatus(hConsole, false, true, Config::TriggerChance, false);
    //cout << "#19 -> Set TriggerBot Key (VK_KEY CODE)"; printStatus(hConsole, false, true, Config::TriggerKey, true);
    cout << "#50 ->Exit " << endl; 

}

void Setup()
{
init:
    pD3D.initui();
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    cout.setf(ios::hex, ios::basefield);
    WelcomeMessage();
    LoadInterfaces();
    LoadOffsets();
    LoadHooks();
    LoadSettings();
    int width, height;

    Interfaces::Engine->GetScreenSize(width, height);
    Config::configuration[0].lbool[3].second = width;
    Config::configuration[0].lbool[2].second = height;
    cout << "\n\n\n";
    system("pause");
    while (true)
    {
        int n;
        HANDLE h;
        printMenu(h);
        cin >> n;

        switch (n)
        {
        case 1:
            if (Config::configuration[2].lbool[1].second)
                Config::configuration[2].lbool[1].second = false;
            else
            {
                Config::configuration[2].lbool[2].second = false;
                Config::configuration[2].lbool[1].second = true;
            }
            break;

        case 2:
            if (Config::configuration[2].lbool[2].second)
                Config::configuration[2].lbool[2].second = false;
            else
            {
                Config::configuration[2].lbool[1].second = false;
                Config::configuration[2].lbool[2].second = true;
            }
            break;

        case 3:
            Config::configuration[2].lbool[3].second = !Config::configuration[2].lbool[3].second;
            break;

        case 4:
            if (Config::configuration[3].lbool[1].second)
                Config::configuration[3].lbool[1].second = false;
            else
            {
               Config::configuration[3].lbool[2].second = false;
                Config::configuration[3].lbool[1].second = true;
            }
            break;

        case 5:
            if (Config::configuration[3].lbool[2].second)
               Config::configuration[3].lbool[2].second = false;
            else
            {
                Config::configuration[3].lbool[1].second = false;
               Config::configuration[3].lbool[2].second = true;
            }
            break;
        case 6:
            cout << "Specify a new Aimbot FOV: ";
            cin >> n;
            Config::AimbotFOV = n;
        case 7:
            cout << "Specify a new Aimbot Smooth Factor: ";
            cin >> n;
            Config::SmoothFactor = n;
            
        case 8:
                    Config::SilentAim = !Config::SilentAim;
                    if (Config::SilentAim)
                         Config::configuration[2].lbool[2].second = false;
                    break;
                    
               case 9:

       
            Config::configuration[2].lbool[4].second = !Config::configuration[2].lbool[4].second;
            break;

        case 10:
            Config::configuration[5].lbool[0].second = !Config::configuration[5].lbool[0].second;
            break;

        case 11:
            Config::configuration[5].lbool[1].second = !Config::configuration[5].lbool[1].second;
            break;

        case 12:
           Config::configuration[1].lbool[1].second= !Config::configuration[1].lbool[1].second;
            break;

        case 13:
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

        case 14:
            Config::configuration[4].lbool[0].second= !Config::configuration[4].lbool[0].second;
            break;

        case 15:
            Config::configuration[5].lbool[2].second = !Config::configuration[5].lbool[2].second;
            break;

        case 16:
            Config::TriggerSilent = !Config::TriggerSilent;
            break;

        case 17:
            cout << "Specify a new trigger delay: ";
            cin >> n;
           // Config::TriggerDelay = n;
            break;

        case 18:
            cout << "Specify a new trigger hitchance: ";
            cin >> n;
          //  Config::TriggerChance = n;
            break;

        case 19:
            cout << "Specify a new trigger key: ";
            cin.setf(ios::hex, ios::basefield);
            cin >> n;
          //  Config::TriggerKey = n;
            cin.setf(ios::dec, ios::basefield);
            break;

        case 50:
            unHook();
//   Config::kill = true;


        default:
            break;
        }

        ofstream ofs("settings.ini");
        writeFile(ofs);

        cout << endl;
    }
    int n;
    
    cout << "#0 -> Load Cheat" << endl;
    cout << "#1 -> Exit" << endl;
    cin >> n;

    if (n == 0)goto init;
    
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, LPTHREAD_START_ROUTINE(Setup), 0, 0, 0);

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
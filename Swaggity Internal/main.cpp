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

using namespace std;
Config General;

D3D Direct3D;

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

	Interfaces::Engine = CreateInterface<IEngineClient*>("engine.dll", "VEngineClient014");
	Interfaces::EngineTrace = CreateInterface<IEngineTrace*>("engine.dll", "EngineTraceClient004");
	Interfaces::EntityList = CreateInterface<IClientEntityList*>("client.dll", "VClientEntityList003");
	Interfaces::Client = CreateInterface<IBaseClientDll*>("client.dll", "VClient017");
	Interfaces::ClientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<DWORD**>(Interfaces::Client))[10] + 0x5);
	Interfaces::GlobalVars = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<DWORD**>(Interfaces::Client))[0] + 0x53);
	Interfaces::Events = CreateInterface<IGameEventManager2*>("engine.dll", "GAMEEVENTSMANAGER002");
	Interfaces::Surface = CreateInterface<ISurface*>("vguimatsurface.dll", "VGUI_Surface031");
	Interfaces::VPanel = CreateInterface<IVPanel*>("vgui2.dll", "VGUI_Panel009");
	Interfaces::Prediction = CreateInterface<CPrediction*>("client.dll", "VClientPrediction001");
	Interfaces::Movement = CreateInterface<IGameMovement*>("client.dll", "GameMovement001");

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
	Hooks::Client = new VMTSwag(reinterpret_cast<DWORD**>(Interfaces::Client));
	cout << "Hooks::ClientMode -> ";
	Hooks::ClientMode = new VMTSwag(reinterpret_cast<DWORD**>(Interfaces::ClientMode));
	cout << "Hooks::Surface -> ";
	Hooks::Surface = new VMTSwag(reinterpret_cast<DWORD**>(Interfaces::Surface));
	cout << "Hooks::VPanel -> ";
	Hooks::VPanel = new VMTSwag(reinterpret_cast<DWORD**>(Interfaces::VPanel));
	cout << "Hooks::D3D9 -> ";
	Hooks::D3D9 = new VMTSwag(reinterpret_cast<DWORD**>(offsets.d3d9Device));

	auto OnDeath = new GameEvents::OnPlayerDeath();

	if (!OnDeath)
		cout << "algo chungo ha pasao loko" << endl;

	oCreateMove = reinterpret_cast<CreateMoveFn>(
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

void writeFile(ofstream& ofs)
{
	ofs << "[General]" << endl;
	ofs << "RageRCS=" << General.getRageRCS()<< endl;
	ofs << "LegitRCS=" << General.getLegitRCS() << endl;
	ofs << "NoVisRecoil=" << General.getNoVisRecoil() << endl;
	ofs << "RageAimbot=" << General.getRageAimbot() << endl;
	ofs << "LegitAimbot=" << General.getLegitAimbot() << endl;
	ofs << "AimbotFOV=" << General.getAimbotFOV() << endl;
//	ofs << "DistanceBasedFOV=" << General.getDistanceBasedFOV << endl;
//	ofs << "SmoothFactor=" << General.getSmoothFactor << endl;
	ofs << "SilentAim=" << General.getSilentAim() << endl;
	ofs << "CrosshairRecoil=" << General.getCorsshairRecoil() << endl;
	ofs << "NoFlash=" << General.getNoFlash() << endl;
	ofs << "BunnyHop=" << General.getBhop() << endl;
	ofs << "ESP=" << General.getESP() << endl;
	ofs << "ESPName=" << General.getESP() << endl;
	ofs << "ESPHealth=" << General.getESPHealth() << endl;
	ofs << "ESPDistance=" << General.getESPDistance() << endl;
	ofs << "ESPGun=" << General.getESPGun() << endl;
	ofs << "ESPHead=" << General.getESPHead() << endl;
	ofs << "ShitTalk=" << General.getShitTalk() << endl;
	ofs << "TriggerBot=" << General.getActiveTrigger() << endl;
	ofs << "TriggerBot_Delay=" << General.getTriggerDelay() << endl;
	ofs << "TriggerBot_HitChance=" << General.getTriggerChance() << endl;
	ofs << "TriggerBot_Key=" << General.getTriggerKey() << endl;
	ofs << "TriggerBot_PSilent=" << General.getTriggerSilent() << endl;
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
		General.setRageRCS(GetPrivateProfileInt("General", "RageRCS", 1, settings.c_str()) != 0);
		General.setLegitRCS(GetPrivateProfileInt("General", "LegitRCS", 0, settings.c_str()) != 0);
		General.setNoVisRecoil(GetPrivateProfileInt("General", "NoVisRecoil", 1, settings.c_str()) != 0);
		General.setRageAimbot( GetPrivateProfileInt("General", "RageAimbot", 1, settings.c_str()) != 0);
		General.setLegitAimbot(GetPrivateProfileInt("General", "LegitAimbot", 0, settings.c_str()) != 0);
		General.setAimbotFOV(GetPrivateProfileInt("General", "AimbotFOV", 6, settings.c_str()));
		//General.getDistanceBasedFOV = GetPrivateProfileInt("General", "DistanceBasedFOV", 1, settings.c_str()) != 0;
		//General.getSmoothFactor = GetPrivateProfileInt("General", "SmoothFactor", 8, settings.c_str());
		General.setSilentAim( GetPrivateProfileInt("General", "SilentAim", 1, settings.c_str()) != 0);
		General.setCorsshairRecoil(GetPrivateProfileInt("General", "CrosshairRecoil", 0, settings.c_str()) != 0);
		General.setNoFlash( GetPrivateProfileInt("General", "NoFlash", 1, settings.c_str()) != 0);
		General.setBhop( GetPrivateProfileInt("General", "BunnyHop", 1, settings.c_str()) != 0);
		General.setESPName(GetPrivateProfileInt("General", "ESPName", 1, settings.c_str()) != 0);  //Name
		General.setESPHealth(GetPrivateProfileInt("General", "ESPHealth", 1, settings.c_str()) != 0);  //Health
		General.setESPDistance(GetPrivateProfileInt("General", "ESPDistance", 1, settings.c_str()) != 0);  //Distance
		General.setESPGun(GetPrivateProfileInt("General", "ESPGun", 1, settings.c_str()) != 0);  //Gun
		General.setESPHead(GetPrivateProfileInt("General", "ESPHead", 1, settings.c_str()) != 0);  //Gun
		General.setESP( GetPrivateProfileInt("General", "ESP", 0, settings.c_str()) != 0);
		General.setShitTalk( GetPrivateProfileInt("General", "ShitTalk", 0, settings.c_str()) != 0);
		General.setActiveTrigger(GetPrivateProfileInt("General", "TriggerBot", 1, settings.c_str()) != 0);
		General.setTriggerDelay(GetPrivateProfileInt("General", "TriggerBot_Delay", 7, settings.c_str()));
		General.setTriggerChance(GetPrivateProfileInt("General", "TriggerBot_HitChance", 90, settings.c_str()));
		General.setTriggerKey(GetPrivateProfileInt("General", "TriggerBot_Key", 0x05, settings.c_str()));
		General.setTriggerSilent(GetPrivateProfileInt("General", "TriggerBot_Silent", 1, settings.c_str()) != 0);
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
	cout << "#1  -> Toggle Rage Recoil"; printStatus(hConsole, General.getRageRCS());
	cout << "#2  -> Toggle Legit Recoil"; printStatus(hConsole, General.getLegitRCS());
	cout << "#3  -> Toggle NoVis Recoil"; printStatus(hConsole, General.getNoVisRecoil());
	cout << "#4  -> Toggle Rage Aimbot"; printStatus(hConsole, General.getRageAimbot());
	cout << "#5  -> Toggle Legit Aimbot"; printStatus(hConsole, General.getLegitAimbot());
//	cout << "#6  -> Set Aimbot FOV"; printStatus(hConsole, false, true, General., false);
//	cout << "#7  -> Set Distance Based FOV"; printStatus(hConsole, Config::DistanceBasedFOV);
//	cout << "#8  -> Set Smooth Factor"; printStatus(hConsole, false, true, Config::SmoothFactor, false);
	cout << "#9  -> Toggle Silent Aim"; printStatus(hConsole, General.getSilentAim());
	cout << "#10 -> Toggle Recoil Crosshair"; printStatus(hConsole, General.getCorsshairRecoil());
	cout << "#11 -> Toggle NoFlash"; printStatus(hConsole, General.getNoFlash());
	cout << "#12 -> Toggle BunnyHop"; printStatus(hConsole, General.getBhop());
	cout << "#13 -> Toggle ESP"; printStatus(hConsole, General.getESP());
	cout << "#14 -> Toggle ESP Features" << endl;
	cout << "#15 -> Toggle TriggerBot"; printStatus(hConsole, General.getActiveTrigger());
	cout << "#16 -> Toggle ShitTalk"; printStatus(hConsole, General.getShitTalk());
	cout << "#17 -> Toggle TriggerBot PSilent"; printStatus(hConsole, General.getTriggerSilent());
	cout << "#18 -> Set TriggerBot Delay (ms)"; printStatus(hConsole, false, true, General.getTriggerDelay(), false);
	cout << "#19 -> Set TriggerBot Hitchance (%)"; printStatus(hConsole, false, true, General.getTriggerChance(), false);
	cout << "#20 -> Set TriggerBot Key (VK_KEY CODE)"; printStatus(hConsole, false, true, General.getTriggerKey(), true);
}

void Setup()
{
   
    Direct3D.makeovr();
	AllocConsole();
    Direct3D.initui();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	cout.setf(ios::hex, ios::basefield);
	WelcomeMessage();
	LoadInterfaces();
	LoadOffsets();
	LoadHooks();
    int height, width;
    Interfaces::Engine->GetScreenSize(width, height);
    General.setwidth(width);
    General.setheight(height);
	LoadSettings();

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
			if (General.getRageRCS())
				General.setRageRCS(false);
			else
			{
				General.setLegitRCS(false);
				General.setRageRCS(true);
			}
			break;

		case 2:
			if (General.getLegitRCS())
				General.setLegitRCS(false);
			else
			{
				General.setRageRCS(false);
				General.setLegitRCS(true);
			}
			break;

		case 3:
			General.setNoVisRecoil(!General.getNoVisRecoil());
			break;

		case 4:
			if (General.getRageAimbot())
				General.setRageAimbot(false);
			else
			{
				General.setLegitAimbot(false);
				General.setRageAimbot(true);
			}
			break;

		case 5:
			if (General.getLegitAimbot())
				General.setLegitAimbot(false);
			else
			{
				General.setRageAimbot( false);
				General.setLegitAimbot(true);
			}
			break;

		case 6:
			cout << "Specify a new Aimbot FOV: ";
			cin >> n;
			General.setAimbotFOV(n);
			break;

		case 7:
			//Config::DistanceBasedFOV = !Config::DistanceBasedFOV;
			break;

		case 8:
			cout << "Specify a new Aimbot Smooth Factor: ";
			cin >> n;
			//Config::SmoothFactor = n;
			break;

		case 9:
			General.setSilentAim(!General.getSilentAim());
			if (General.getSilentAim())
			{
				if (General.getLegitRCS())
				{
					General.setLegitRCS(false);
					General.setRageRCS(true);
				}
			}
			break;

		case 10:
			General.setCorsshairRecoil(!General.getCorsshairRecoil());
			break;

		case 11:
			General.setNoFlash(!General.getNoFlash());
			break;

		case 12:
			General.setBhop(!General.getBhop());
			break;

		case 13:
			General.setESP(!General.getESP());
			break;

		case 14:
			do
			{
				system("cls");
				cout << "#1 -> ESP Name"; printStatus(h, General.getESPName());
				cout << "#2 -> ESP Health"; printStatus(h, General.getESPHealth());
				cout << "#3 -> ESP Distance"; printStatus(h, General.getESPDistance());
				cout << "#4 -> ESP Gun"; printStatus(h, General.getESPGun());
				cout << "#5 -> ESP Head"; printStatus(h, General.getESPHead());
				cout << "Choose a feature to toggle (9 TO GO BACK TO MAIN MENU): ";
				cin >> n;

				if (n != 9){}
				//	Config::ESPFeatures[n - 1] = !Config::ESPFeatures[n - 1];

			} while (n != 9);
			break;

		case 15:
			General.setActiveTrigger(!General.getActiveTrigger());
			break;

		case 16:
			General.setShitTalk(!General.getShitTalk());
			break;

		case 17:
			General.setTriggerSilent(!General.getTriggerSilent());
			break;

		case 18:
			cout << "Specify a new trigger delay: ";
			cin >> n;
			General.setTriggerDelay(n);
			break;

		case 19:
			cout << "Specify a new trigger hitchance: ";
			cin >> n;
			General.setTriggerChance(n);
			break;

		case 20:
			cout << "Specify a new trigger key: ";
			cin.setf(ios::hex, ios::basefield);
			cin >> n;
			General.setTriggerKey(n);
			cin.setf(ios::dec, ios::basefield);
        case 50:
            delete Hooks::Client;
            delete Hooks::ClientMode;
            delete Hooks::VPanel;
            delete Hooks::Surface;
            delete Hooks::D3D9;
            break;

		default:
			break;
		}

		ofstream ofs("settings.ini");
		writeFile(ofs);

		cout << endl;
	}

   
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
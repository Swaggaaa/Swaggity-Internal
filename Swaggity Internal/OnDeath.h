#pragma once
#include <random>
#include "ShitTalk.h"
#include "Interfaces.h"
#include <iostream>

using namespace std;
#define CEL_PROCEED_EVENT_HANDLING 0x2A

namespace GameEvents
{
    default_random_engine generator;
    uniform_int_distribution<int> phrase(0, 12);
    uniform_int_distribution<int> column(0, 1);
    void replaceAll(std::string& str, const std::string& from, const std::string& to)
    {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            size_t end_pos = start_pos + from.length();
            str.replace(start_pos, from.length(), to);
            start_pos += (to.length()); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

    class OnPlayerDeath : public IGameEventListener2
    {
    public:
        virtual ~OnPlayerDeath()
        {
        }

        bool enabled = true;
    private:
        std::string szEventName;
    public:
        OnPlayerDeath() : szEventName("player_death")
        {
            if (!RegListener())
                cout << "ayy lmao no listen u deaf keko" << endl;
        }

        virtual void FireGameEvent(IGameEvent *pEvent)
        {
            if (!enabled || !pEvent || !General.getShitTalk())
            {
                return;
            }
            int killer = Interfaces::Engine->GetPlayerForUserID(pEvent->GetInt("attacker"));
            int victim = Interfaces::Engine->GetPlayerForUserID(pEvent->GetInt("userid"));
            int me = Interfaces::Engine->GetLocalPlayer();

            if (killer != me || victim == me)
            {
                return;
            }
            player_info_t victimInfo;
            Interfaces::Engine->GetPlayerInfo(victim, &victimInfo);
            const string *list;
            switch (column(generator))
            {
            case 0:
                list = ShitTalk::gentleman;
                break;
            case 1:
                list = ShitTalk::zodiacmode;
                break;
            default:
                return;
            }
            string salt = list[phrase(generator)];
            //char buffer[salt.size() + strlen(victimInfo.name) + 1]; << Cancer André Code. Not constant value, can't initialize. I love him still but he's a pussy ass bitch.
            //size_t pos = salt.find("%s");
            replaceAll(salt, string("*player*"), string(victimInfo.name));
            //if (pos != string::npos)
            //{
            //  salt.replace(pos, 2, victimInfo.name);
            //sprintf(buffer, salt.c_str(), victimInfo.name);
            //}

            Interfaces::Engine->ExecuteClientCmd(salt.c_str());
            //int killed = pEvent->GetInt("userid");//*/
        }

        virtual int IndicateEventHandling(void)
        {
            //Indicate whether 'HandleGameEvent()' shall get called or not

            return CEL_PROCEED_EVENT_HANDLING;
        }

        bool RegListener()
        {
            //Register game event listener

            if (!Interfaces::Events)
            {
                cout << "events null" << endl;
                return false;
            }

            if (!this->szEventName.length())
            {
                cout << "name null" << endl;
                return false;
            }

            return Interfaces::Events->AddListener(this, this->szEventName.c_str(), false);
        }
    };
}
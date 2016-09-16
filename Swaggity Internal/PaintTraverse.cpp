#include "Hooks.h"
#include "ISurface.h"
#include "Interfaces.h"
#include "Entity.h"
#include "SDK.h"
#include "Global.h"
#include "Config.h"
#include <iostream>
#include "RayTrace.h"
#include "Utils.h"

typedef unsigned int uint;

#pragma warning (disable : 4244)

void CrosshairRecoil()
{
    if (GetTickCount() - Global::LastShot > 1000)
    {
        int width, height;
        Interfaces::Engine->GetScreenSize(width, height);
        width /= 2;
        height /= 2;
        Interfaces::Surface->DrawSetColor(102, 255, 255, 60);
        Interfaces::Surface->DrawOutlinedCircle(width, height, 8, 10);
        Interfaces::Surface->DrawSetColor(0, 0, 0, 60);
        Interfaces::Surface->DrawOutlinedCircle(width, height, 7, 10);
        Interfaces::Surface->DrawOutlinedCircle(width, height, 9, 10);
        return;
    }

    trace_t trace;
    Ray_t ray;
    CTraceFilter filter;

    Vector viewAngle = Global::UserCmd->viewangles;
    if (Config::LegitRCS)
        viewAngle += Global::LocalPlayer->GetPunch() * 2.f;


    float cy, sy, cx, sx;
    Vector forward, src, dst;

    SinCos(DEG2RAD(viewAngle.y), &sx, &cx);
    SinCos(DEG2RAD(viewAngle.x), &sy, &cy);

    forward.x = cy*cx;
    forward.y = cy*sx;
    forward.z = -sy;

    forward *= 8192;
    filter.pSkip = Global::LocalPlayer;
    src = Global::LocalPlayer->GetEyePosition();
    dst = src + forward;

    ray.Init(src, dst);
    Interfaces::EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);

    Vector screenPos;
    Utils::WorldToScreen(trace.endpos, screenPos);

    Interfaces::Surface->DrawSetColor(102, 255, 255, 255);
    Interfaces::Surface->DrawOutlinedCircle(screenPos.x, screenPos.y, 8, 10);
    Interfaces::Surface->DrawSetColor(0, 0, 0, 255);
    Interfaces::Surface->DrawOutlinedCircle(screenPos.x, screenPos.y, 7, 10);
    Interfaces::Surface->DrawOutlinedCircle(screenPos.x, screenPos.y, 9, 10);

    //Interfaces::Surface->DrawOutlinedRect(screenPos.x, screenPos.y, screenPos.x + 100, screenPos.y + 100);
}

void SetVisibleColor(bool visible)
{
    if (visible)
    {
        Interfaces::Surface->DrawSetColor(0, 240, 61, 255);
        Interfaces::Surface->DrawSetTextColor(0, 240, 61, 255);
    }
    else
    {
        Interfaces::Surface->DrawSetColor(255, 0, 0, 255);
        Interfaces::Surface->DrawSetTextColor(255, 0, 0, 255);
    }
}

void __fastcall Hooks::PaintTraverse(void* thisptr, void* edx, unsigned int panel, bool forceRepaint, bool allowForce)
{
    if (!Global::LocalPlayer || !Interfaces::Engine->IsInGame() || Global::LocalPlayer->GetTeam() == 0)
    {
        oPaintTraverse(thisptr, edx, panel, forceRepaint, allowForce);
        return;
    }

    if (Config::ESP)
    {
        for (uint i = 0; i < uint(Interfaces::EntityList->GetHighestEntityIndex()); ++i)
        {
            CBaseEntity* entity = Interfaces::EntityList->GetClientEntity(i);


            if (!entity->IsValid())
                continue;

            Vector max = entity->GetCollideable()->OBBMaxs();

            Vector pos, pos3D = entity->GetOrigin();
            Vector top, top3D = pos3D + Vector(0, 0, max.z);

            if (!Utils::WorldToScreen(pos3D, pos) || !Utils::WorldToScreen(top3D, top))
                continue;

            float height = pos.y - top.y;
            float width = height / 4.f;

            bool visible = entity->IsVisible(6);
            SetVisibleColor(visible);

            int lastX = top.x - width - 40;
            int lastY = top.y + height/2; //They specify latest ESP feature position aka to make it dynamic
 
            Interfaces::Surface->DrawSetTextFont(Global::textFont);
            SetVisibleColor(visible);

            if (Config::ESPFeatures[0])
            {
                wchar_t name[1024];
                char buf[1024];
                strcpy(buf, entity->GetName().c_str());
                MultiByteToWideChar(CP_UTF8, NULL, buf, 256, name, 256);
                Interfaces::Surface->DrawSetTextPos(lastX, lastY);
                Interfaces::Surface->DrawPrintText(name, wcslen(name));

                lastY += 10;
            }

            if (Config::ESPFeatures[1])
            {
                int iHealth = entity->GetHealth();
                wchar_t health[256];

                swprintf_s(health, L"%d", iHealth);
                Interfaces::Surface->DrawSetTextPos(lastX, lastY);
                Interfaces::Surface->DrawPrintText(health, wcslen(health));
            }
            

            if (Config::ESPFeatures[4]) //HeadPos
            {
                Vector headPos;
                int crouchModifier = entity->GetFlags() & FL_DUCKING ? height / 4 : 0;
                Utils::WorldToScreen(entity->GetBonePosition(6), headPos);

                Interfaces::Surface->DrawOutlinedCircle(headPos.x, headPos.y + crouchModifier, 3, 10); //Head Pos
                Interfaces::Surface->DrawSetColor(0, 0, 0, 255);
                Interfaces::Surface->DrawOutlinedCircle(headPos.x, headPos.y + crouchModifier, 2, 10); //Head Circle Contour
                Interfaces::Surface->DrawOutlinedCircle(headPos.x, headPos.y + crouchModifier, 4, 10);
            }

            SetVisibleColor(visible);
            Interfaces::Surface->DrawOutlinedRect(top.x - width, top.y, top.x + width, top.y + height);
            Interfaces::Surface->DrawSetColor(0, 0, 0, 255);
            Interfaces::Surface->DrawOutlinedRect(top.x - width - 1, top.y - 1, top.x + width + 1, top.y + height + 1); //ESP Box Contour
            Interfaces::Surface->DrawOutlinedRect(top.x - width + 1, top.y + 1, top.x + width - 1, top.y + height - 1);

        }
    }

    if (Config::CrosshairRecoil && Global::LocalPlayer->GetAlive())
        CrosshairRecoil();

    oPaintTraverse(thisptr, edx, panel, forceRepaint, allowForce);
}
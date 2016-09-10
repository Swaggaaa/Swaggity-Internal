#include "Utils.h"
#include "Cheat.h"

#pragma warning (disable : 4244)

bool Utils::ScreenTransform(const Vector &point, Vector &screen) // tots not pasted
{
    float w;
    const VMatrix &worldToScreen = Interfaces::Engine->WorldToScreenMatrix();

    screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
    screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
    w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
    screen.z = 0.0f;

    bool behind = false;

    if (w < 0.001f)
    {
        behind = true;
        screen.x *= 100000;
        screen.y *= 100000;
    }
    else
    {
        behind = false;
        float invw = 1.0f / w;
        screen.x *= invw;
        screen.y *= invw;
    }

    return behind;
}

void Utils::AngleVectors(const QAngle &angles, Vector *forward)
{
    float sp, sy, cp, cy;

    SinCos(DEG2RAD(angles[1]), &sy, &cy); //YAW
    SinCos(DEG2RAD(angles[0]), &sp, &cp); //PITCH

    forward->x = cp*cy;
    forward->y = cp*sy;
    forward->z = -sp;
}

bool Utils::WorldToScreen(const Vector &origin, Vector &screen)
{
    if (!Utils::ScreenTransform(origin, screen))
    {
        int ScreenWidth, ScreenHeight;
        Interfaces::Engine->GetScreenSize(ScreenWidth, ScreenHeight);
        float x = ScreenWidth / 2;
        float y = ScreenHeight / 2;
        x += 0.5 * screen.x * ScreenWidth + 0.5;
        y -= 0.5 * screen.y * ScreenHeight + 0.5;
        screen.x = x;
        screen.y = y;
        return true;
    }

    return false;
}

void Utils::VectorAngles(const Vector& forward, QAngle& angles) //Converts Vector to QAngle (pitch, yaw, roll)
{
    if (forward[1] == 0.0f && forward[0] == 0.0f)
    {
        angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
        angles[1] = 0.0f;  //yaw left/right
    }
    else
    {
        angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
        angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

        if (angles[1] > 90) angles[1] -= 180;
        else if (angles[1] < 90) angles[1] += 180;
        else if (angles[1] == 90) angles[1] = 0;
    }

    angles[2] = 0.0f;
}

QAngle Utils::CalcAngle(const Vector& source, const Vector& destination) //Not normalized tho
{
    QAngle angles;
    Vector direction = source - destination;
    VectorAngles(direction, angles);
    return angles;
}

float Utils::GetFOV(const Vector& aimAngle)
{
    Vector ang, aim;
    AngleVectors(Global::UserCmd->viewangles, &ang);
    AngleVectors(aimAngle, &aim);

    return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}
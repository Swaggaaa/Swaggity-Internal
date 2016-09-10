#pragma once
#include "SDK.h"
#include "Interfaces.h"

namespace Utils
{
    bool ScreenTransform(const Vector &point, Vector &screen); // tots not pasted

    void AngleVectors(const QAngle & angles, Vector * forward);

    bool WorldToScreen(const Vector &origin, Vector &screen);

    void VectorAngles(const Vector& forward, QAngle& angles); //Converts Vector to QAngle (pitch, yaw, roll)

    QAngle CalcAngle(const Vector &source, const Vector &destination);

    float GetFOV(const Vector & aimAngle);
}
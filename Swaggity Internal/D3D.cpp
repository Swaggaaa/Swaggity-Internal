
#include "D3D.h"
#include <iso646.h>

void D3D::DrawLine(float X, float Y, float XX, float YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
    D3DXVECTOR2 Points[2];
    Points[0] = D3DXVECTOR2(X, Y);
    Points[1] = D3DXVECTOR2(XX, YY);
    if (Outlined)
        {
            pD3D.Line->SetWidth(OutlineWidth * 2.f + LineWidth);
            pD3D.Line->Draw(Points, 2, OutlineColor);
        }
    pD3D.Line->SetWidth(LineWidth);
    pD3D.Line->Draw(Points, 2, LineColor);
}

void D3D::DrawCircle(float X, float Y, float Radius, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
	D3DXVECTOR2 Points[50];
	for (int i = 0; i < 50; i++)
	{
		Points[i] = D3DXVECTOR2(X + (Radius * cos(i)), Y + (Radius * sin(i)));
	}
    if (Outlined)
        {
            pD3D.Line->SetWidth(LineWidth + OutlineWidth * 2);
            pD3D.Line->Draw(Points, 50, OutlineColor);
        }
    pD3D.Line->SetWidth(LineWidth);
    pD3D.Line->Draw(Points, 50, LineColor);
}

void D3D::DrawCheck(float X, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Checked, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
    if (Checked)
    {
        if (Outlined)
        {
            DrawLine(X - OutlineWidth, X + Height / 2, X + Width + OutlineWidth, X + Height / 2.f, Height, OutlineColor, true, OutlineWidth, OutlineColor);
        }
        DrawLine(X, X + Height / 2.f, X + Width, X + Height / 2, Height, LineColor, false, 0, 0);
    }
    else
    {
        if (Outlined)
        {
            OutlineWidth *= 2.f + LineWidth;
            DrawLine(X, X, X, X + Height, OutlineWidth, OutlineColor, false, 0, 0);
            DrawLine(X, X + Height, X + Width, X + Height, OutlineWidth, OutlineColor, false, 0, 0);
            DrawLine(X + Width, X + Height, X + Width, X, OutlineWidth, OutlineColor, false, 0, 0);
            DrawLine(X + Width, X, X, X, OutlineWidth, OutlineColor, false, 0, 0);
            DrawLine(X, X, X, X + Height, LineWidth, LineColor, false, 0, 0);
            DrawLine(X, X + Height, X + Width, X + Height, LineWidth, LineColor, false, 0, 0);
            DrawLine(X + Width, X + Height, X + Width, X, LineWidth, LineColor, false, 0, 0);
            DrawLine(X + Width, X, X, X, LineWidth, LineColor, false, 0, 0);
        }
        else
        {
            DrawLine(X, X, X, X + Height, LineWidth, LineColor, false, 0, 0);
            DrawLine(X, X + Height, X + Width, X + Height, LineWidth, LineColor, false, 0, 0);
            DrawLine(X + Width, X + Height, X + Width, X, LineWidth, LineColor, false, 0, 0);
            DrawLine(X + Width, X, X, X, LineWidth, LineColor, false, 0, 0);
        }
    }
}

void D3D::DrawRect(float X, float Y, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
    if (Filled)
        {
            if (Outlined)
                {
                    DrawLine(X - OutlineWidth, Y + Height / 2, X + Width + OutlineWidth, Y + Height / 2.f, Height, OutlineColor, true, OutlineWidth, OutlineColor);
                }
            DrawLine(X, Y + Height / 2.f, X + Width, Y + Height / 2, Height, LineColor, false, 0, 0);
        }
    else
        {
            if (Outlined)
                {
                    OutlineWidth *= 2.f + LineWidth;
                    DrawLine(X, Y, X, Y + Height, OutlineWidth, OutlineColor, false, 0, 0);
                    DrawLine(X, Y + Height, X + Width, Y + Height, OutlineWidth, OutlineColor, false, 0, 0);
                    DrawLine(X + Width, Y + Height, X + Width, Y, OutlineWidth, OutlineColor, false, 0, 0);
                    DrawLine(X + Width, Y, X, Y, OutlineWidth, OutlineColor, false, 0, 0);
                    DrawLine(X, Y, X, Y + Height, LineWidth, LineColor, false, 0, 0);
                    DrawLine(X, Y + Height, X + Width, Y + Height, LineWidth, LineColor, false, 0, 0);
                    DrawLine(X + Width, Y + Height, X + Width, Y, LineWidth, LineColor, false, 0, 0);
                    DrawLine(X + Width, Y, X, Y, LineWidth, LineColor, false , 0, 0);
                }
            else
                {
                    DrawLine(X, Y, X, Y + Height, LineWidth, LineColor, false, 0, 0);
                    DrawLine(X, Y + Height, X + Width, Y + Height, LineWidth, LineColor, false, 0, 0);
                    DrawLine(X + Width, Y + Height, X + Width, Y, LineWidth, LineColor, false, 0, 0);
                    DrawLine(X + Width, Y, X, Y, LineWidth, LineColor, false, 0, 0);
                }
        }
}

void D3D::DrawString(float X, float Y, std::string Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor, bool Centered)
{
    RECT Rect;
    Rect.top = Y;
    Rect.left = X;
	Rect.bottom = Y;
	Rect.right = X;
    if (Outlined)
        {
            RECT OutlineRectTop;
            OutlineRectTop.top = Y - 1.f;
            OutlineRectTop.left = X;
			OutlineRectTop.bottom = Y;
			OutlineRectTop.right = X - 1.f;
            RECT OutlineRectLeft;
            OutlineRectLeft.top = Y;
            OutlineRectLeft.left = X - 1.f;
			OutlineRectLeft.bottom = Y;
			OutlineRectLeft.right = X - 1.f;
            RECT OutlineRectRight;
            OutlineRectRight.top = Y;
            OutlineRectRight.left = X + 1.f;
			OutlineRectRight.bottom = Y;
			OutlineRectRight.right = X + 1.f;
            RECT OutlineRectBottom;
            OutlineRectBottom.top = Y + 1.f;
            OutlineRectBottom.left = X;
			OutlineRectBottom.bottom = Y + 1.f;
			OutlineRectBottom.right = X;
            if (Centered)
                {
					pD3D.Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectTop, DT_CENTER | DT_NOCLIP, OutlineColor);
					pD3D.Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectLeft, DT_CENTER | DT_NOCLIP, OutlineColor);
					pD3D.Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectRight, DT_CENTER | DT_NOCLIP, OutlineColor);
					pD3D.Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectBottom, DT_CENTER | DT_NOCLIP, OutlineColor);
                }
            else
                {
                    pD3D.Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectTop, DT_NOCLIP, OutlineColor);
                    pD3D.Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectLeft, DT_NOCLIP, OutlineColor);
                    pD3D.Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectRight, DT_NOCLIP, OutlineColor);
                    pD3D.Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectBottom, DT_NOCLIP, OutlineColor);
                }
        }
    if (Centered)
        {
			pD3D.Font->DrawTextA(NULL, Text.c_str(), strlen(Text.c_str()), &Rect, DT_CENTER | DT_NOCLIP, TextColor);
        }
    else
        {
            pD3D.Font->DrawTextA(NULL, Text.c_str(), strlen(Text.c_str()), &Rect, DT_NOCLIP, TextColor);
        }
}

void D3D::DrawCross(float X, float Y, float Size, float WidthL, D3DCOLOR CrossColor, bool Outlined, float OutWidthL, D3DCOLOR OutlineColor)
{
    if (Outlined)
        {
            DrawLine(X - Size / 2.f - OutWidthL, Y, X - 1.f, Y, WidthL, OutlineColor, true, OutWidthL, OutlineColor);
            DrawLine(X + Size / 2.f + OutWidthL, Y, X, Y, WidthL, OutlineColor, true, OutWidthL, OutlineColor);
            DrawLine(X, Y - Size / 2.f - OutWidthL, X, Y - 1.f, WidthL, OutlineColor, true, OutWidthL, OutlineColor);
            DrawLine(X, Y + Size / 2.f + OutWidthL, X, Y, WidthL, OutlineColor, true, OutWidthL, OutlineColor);
        }
	DrawLine(X - Size / 2.f, Y, X - 1.f, Y, WidthL, CrossColor, false, OutWidthL, OutlineColor);
	DrawLine(X + Size / 2.f, Y, X, Y, WidthL, CrossColor, false, OutWidthL, OutlineColor);
	DrawLine(X, Y - Size / 2.f, X, Y - 1.f, WidthL, CrossColor, false, OutWidthL, OutlineColor);
	DrawLine(X, Y + Size / 2.f, X, Y, WidthL, CrossColor, false, OutWidthL, OutlineColor);
}

bool D3D::init(IDirect3DDevice9 *pDevice)
{
    if (pD3D.Device != pDevice)pD3D.Device = pDevice;
     if (pD3D.Device)
                {
                    D3DXCreateLine(pD3D.Device, &pD3D.Line);
                    if (pD3D.Line)
                        {
							D3DXCreateFont(pD3D.Device, 18, NULL, FW_NORMAL, NULL, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, "Calibri", &pD3D.Font);
                            if (pD3D.Font)
                                {
                                    pD3D.Line->SetAntialias(TRUE);
                                    return true;
                                }
                            else
                                {
                                    MessageBoxW(NULL, L"D3DXCreateFont failed!", L"Fatal Error", MB_OK);
                                }
                        }
                    else
                        {
                            MessageBoxW(NULL, L"D3DXCreateLine failed!", L"Fatal Error", MB_OK);
                        }
                }
            else
                {
                    MessageBoxW(NULL, L"CreateDeviceEx failed!", L"Fatal Error", MB_OK);
                }

    

}

void D3D::addelement(int howmany, rolf whatis, int x, int y, int xx, int yy, bool horizontal, int middle, int whr)
{
     if (p1.vpages.size() <= 0)return;

    for (int i = 0; i < howmany; ++i)
    {
        element el1;
        if (horizontal)
        {
            if (middle < (xx - x))middle = xx - x;
            el1.x = x+ middle*i;
            el1.y = y;
            el1.xx = xx+ middle*i;
            el1.yy = yy;
            el1.whotis = whatis;
            el1.middle = whr;
        }
        else
        {
            if (middle < (yy - y))middle = yy - y;
            el1.x = x;
            el1.y = y+ middle*i;
            el1.xx = xx;
            el1.yy = yy + middle*i;
            el1.whotis = whatis;
            el1.middle = whr;
        }
        if(whatis == LABEL)p1.vpages[p1.actpage].labels.push_back(el1);
        if(whatis == BOX)p1.vpages[p1.actpage].boxes.push_back(el1);

    }

}

void D3D::addpage(int howmany)
{
    for (int i = 0; i < howmany; ++i)
    {
        page page1;
        p1.vpages.push_back(page1);
    }
}

void D3D::setpage(int page)
{
    if (page > p1.vpages.size())return;

    p1.actpage = page-1;

}

void D3D::initui()
{
    addpage(1);
    setpage(1);
    addelement(13, BOX, 20, 50, 180, 70, false, 20,120);
}

void D3D::DestructUI()
{
    p1.vpages = std::vector<page>(0);
}

void D3D::Destruct()
{
    
        pD3D.Line->Release();
        pD3D.Font->Release();
    
}



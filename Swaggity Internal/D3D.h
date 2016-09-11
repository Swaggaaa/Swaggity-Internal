
#ifndef _INCL_D3D
#define _INCL_D3D

#include "stdafx.h"

enum rolf
{
    BOX,
    CHECKBOX,
    PAGE,
    LABEL
};

struct element
{
    rolf whotis;
    int x, y, xx, yy;
    int middle;
};

struct page
{
    std::vector<element> boxes;
    std::vector<element> labels;
};

struct pages
{
    std::vector<page> vpages;
    int actpage = 0;
};



struct D3D
{
    IDirect3DDevice9* Device;
    ID3DXLine* Line;
    ID3DXFont* Font;

    pages p1;

    void DrawLine(float X, float Y, float XX, float YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCircle(float X, float Y, float Radius, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCheck(float X, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawRect(float X, float Y, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCross(float X, float Y, float Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawString(float X, float Y, std::string Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor, bool Centered);

    bool init(IDirect3DDevice9* pDevice);

    void addelement(int howmany, rolf whatis,int x, int y, int xx, int yy, bool horizontal, int middle, int whr);

    void addpage(int howmany);

    void setpage(int page);

    void initui();

    
    void DestructUI();
    void Destruct();
    
};

extern D3D pD3D;
#endif

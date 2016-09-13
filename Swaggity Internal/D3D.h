
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
    D3DCOLOR colourin;
    std::string write;
};

struct page
{
    std::vector<element> boxes;
    std::vector<element> labels;
};

struct D3D
{
    IDirect3DDevice9* Device;
    ID3DXLine* Line;
    ID3DXFont* Font;
    ID3DXFont* Font20;
    page overlay;
    std::vector<page> vpages;
    int actpage = 0;

    void DrawLine(float X, float Y, float XX, float YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCircle(float X, float Y, float Radius, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCheck(float X, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawRect(float X, float Y, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCross(float X, float Y, float Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawString(float X, float Y, std::string Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor, bool Centered, int huge);

    bool init(IDirect3DDevice9* pDevice);

    void addelement(int howmany, rolf whatis,int x, int y, int xx, int yy, bool horizontal, int middle, int whr);

    void addpage(int howmany);

    void setpage(int page);

    //page1 overlay

    //page2 misc

    enum COLORS
    { // Normal Colors
        WHITE = D3DCOLOR_ARGB(255, 255, 255, 255),
        BLACK_NOTMUCH = D3DCOLOR_ARGB(255,60, 60, 60),
        RED = D3DCOLOR_ARGB(255, 220, 20, 60),
        GREEN = D3DCOLOR_ARGB(255, 0, 255, 0),
        BLUE = D3DCOLOR_ARGB(255, 0, 0, 255),
        BLACK = D3DCOLOR_ARGB(255, 0, 0, 0),
        PURPLE = D3DCOLOR_ARGB(255, 125, 0, 255),
        GREY = D3DCOLOR_ARGB(255, 128, 128, 128),
        YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0),
        ORANGE = D3DCOLOR_ARGB(255, 255, 125, 0),
        BLUE2 = D3DCOLOR_ARGB(255, 0, 200,180)
    };

    void makeovr();
    void initui();

    
    void DestructUI();
    void Destruct();
    
};

extern D3D pD3D;
#endif


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

struct box
{
    int x, y, xx, yy;
    D3DCOLOR colourin;
    std::string write;
	bool line;
	D3DCOLOR linecolourin;
};

struct checkbox
{
   
    int x,y;

    int size;
    int checkedbox;
    int distance;
    std::string write;
    D3DCOLOR colourin;
    bool checked;

   
    D3DCOLOR boxcolor;
    D3DCOLOR checkedcolor;
    D3DCOLOR stringcolor;
};


struct label
{
   
    int x, y;
    D3DCOLOR colourin;
    std::string write;
    bool line;
    D3DCOLOR linecolourin;
};



struct page
{
    std::vector<box> boxes;
    std::vector<label> labels;
	
};

struct top
{
    std::vector<box> boxes;
    std::vector<label> labels;
    std::vector <box> boxes4;

    label Titulo;
};

struct D3D
{
    IDirect3DDevice9* Device;
    ID3DXLine* Line;
    ID3DXFont* Font;//18
    ID3DXFont* Font20;
    top overlay;
    std::vector<page> vpages;
    int actpage = 0;

    void DrawLine(float X, float Y, float XX, float YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCircle(float X, float Y, float Radius, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCheck(checkbox ron, bool drawstring);
   
    void DrawRect(float X, float Y, float Width, float Height, float LineWidth, D3DCOLOR LineColor, bool Filled, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawCross(float X, float Y, float Size, float LineWidth, D3DCOLOR CrossColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor);
    void DrawString(float X, float Y, std::string Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor, bool Centered, int huge);

    bool init(IDirect3DDevice9* pDevice);

    void addbox(int howmany, rolf whatis,int x, int y, int xx, int yy, bool horizontal, int middle, int whr);

    void addlabel(int howmany, rolf whatis, int x, int y, int xx, int yy, bool horizontal, int middle, int whr);

    void addpage(int howmany);

    void setpage(int page);


    bool ini = false;
    //page1 overlay

    //page2 misc

    enum COLORS
    { // Normal Colors
        WHITE = D3DCOLOR_ARGB(255, 255, 255, 255),
        BLACK_NOTMUCH = D3DCOLOR_ARGB(255,60, 60, 60),
		SRSLYNOTGBLACK = D3DCOLOR_ARGB(255, 30, 30, 30),
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

    void makerage();

    
    void DestructUI();
    void Destruct();
    
};

extern D3D Direct3D;
#endif

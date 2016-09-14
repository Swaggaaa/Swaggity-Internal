
#include "D3D.h"
#include <iso646.h>
#include "Config.h"

void D3D::DrawLine(float X, float Y, float XX, float YY, float LineWidth, D3DCOLOR LineColor, bool Outlined, float OutlineWidth, D3DCOLOR OutlineColor)
{
    D3DXVECTOR2 Points[2];
    Points[0] = D3DXVECTOR2(X, Y);
    Points[1] = D3DXVECTOR2(XX, YY);
    if (Outlined)
        {
            this->Line->SetWidth(OutlineWidth * 2.f + LineWidth);
            this->Line->Draw(Points, 2, OutlineColor);
        }
    this->Line->SetWidth(LineWidth);
    this->Line->Draw(Points, 2, LineColor);
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
            this->Line->SetWidth(LineWidth + OutlineWidth * 2);
            this->Line->Draw(Points, 50, OutlineColor);
        }
    this->Line->SetWidth(LineWidth);
    this->Line->Draw(Points, 50, LineColor);
}

void D3D::DrawCheck(checkbox ron,bool drawstring)
{
    if (ron.checked)
    {
        this->DrawRect(ron.x, ron.y, ron.size, ron.size, 1, ron.boxcolor, true, false, 1, BLACK);
        this->DrawRect(ron.x + ron.distance, ron.y + ron.distance,ron.size - 2*ron.distance, ron.size - 2 * ron.distance, 1, ron.checkedcolor, true, false, 1, BLACK);
        if (drawstring) {
            int x, y;
            x = ron.x + ron.size + 10;
            y = ron.y + (ron.size) / 4;
            this->DrawString(x, y, ron.write, ron.stringcolor, false, BLACK, false, 18);
        }
    }
    else
    {
        this->DrawRect(ron.x, ron.y, ron.size, ron.size, 1, ron.boxcolor, true, false, 1, BLACK);
        if (drawstring){
            int x, y;
            x = ron.x + ron.size + 10;
            y = ron.y + (ron.size / 4) ;
            this->DrawString(x, y, ron.write, ron.stringcolor, false, BLACK, false, 18);
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

void D3D::DrawString(float X, float Y, std::string Text, D3DCOLOR TextColor, bool Outlined, D3DCOLOR OutlineColor, bool Centered, int huge)
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
                    if (huge == 20) {
                       
                        this->Font20->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectTop, DT_CENTER | DT_NOCLIP, OutlineColor);
                        this->Font20->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectLeft, DT_CENTER | DT_NOCLIP, OutlineColor);
                        this->Font20->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectRight, DT_CENTER | DT_NOCLIP, OutlineColor);
                        this->Font20->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectBottom, DT_CENTER | DT_NOCLIP, OutlineColor);
                    }
                    else
                    {
                        this->Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectTop, DT_CENTER | DT_NOCLIP, OutlineColor);
                        this->Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectLeft, DT_CENTER | DT_NOCLIP, OutlineColor);
                        this->Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectRight, DT_CENTER | DT_NOCLIP, OutlineColor);
                        this->Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectBottom, DT_CENTER | DT_NOCLIP, OutlineColor);
                    }
                }
            else
                {
                    if (huge == 20) {
                        this->Font20->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectTop, DT_NOCLIP, OutlineColor);
                        this->Font20->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectLeft, DT_NOCLIP, OutlineColor);
                        this->Font20->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectRight, DT_NOCLIP, OutlineColor);
                        this->Font20->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectBottom, DT_NOCLIP, OutlineColor);

                    }
                    else
                    {
                        this->Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectTop, DT_NOCLIP, OutlineColor);
                        this->Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectLeft, DT_NOCLIP, OutlineColor);
                        this->Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectRight, DT_NOCLIP, OutlineColor);
                        this->Font->DrawTextA(nullptr, Text.c_str(), strlen(Text.c_str()), &OutlineRectBottom, DT_NOCLIP, OutlineColor);

                    }
                }
        }
    if (Centered)
        {
			this->Font->DrawTextA(NULL, Text.c_str(), strlen(Text.c_str()), &Rect, DT_CENTER | DT_NOCLIP, TextColor);
        }
    else
        {
            this->Font->DrawTextA(NULL, Text.c_str(), strlen(Text.c_str()), &Rect, DT_NOCLIP, TextColor);
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
    if (this->Device != pDevice)this->Device = pDevice;
     if (this->Device)
                {
                    D3DXCreateLine(this->Device, &this->Line);
                    if (this->Line)
                        {
							D3DXCreateFont(this->Device, 18, NULL, FW_NORMAL, NULL, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, "Calibri", &this->Font);
                            D3DXCreateFont(this->Device, 20, NULL, FW_NORMAL, NULL, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, "Calibri", &this->Font20);

                            if (this->Font)
                                {
                                    this->Line->SetAntialias(TRUE);
                                    ini = true;
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

void D3D::addbox(int howmany, rolf whatis, int x, int y, int xx, int yy, bool horizontal, int middle, int whr)
{
     if (vpages.size() <= 0)return;

    for (int i = 0; i < howmany; ++i)
    {
        
        box el1;
        if (horizontal)
        {
            if (middle < (xx - x))middle = xx - x;
            el1.x = x+ middle*i;
            el1.y = y;
            el1.xx = xx+ middle*i;
            el1.yy = yy;
            
        }
        else
        {
            if (middle < (yy - y))middle = yy - y;
            el1.x = x;
            el1.y = y+ middle*i;
            el1.xx = xx;
            el1.yy = yy + middle*i;
            
        }
       if(whatis == BOX)vpages[actpage].boxes.push_back(el1);

    }

}

void D3D::addlabel(int howmany, rolf whatis, int x, int y, int xx, int yy, bool horizontal, int middle, int whr)
{
    if (vpages.size() <= 0)return;

    for (int i = 0; i < howmany; ++i)
    {

        label el1;
        if (horizontal)
        {
            if (middle < (xx - x))middle = xx - x;
            el1.x = x + middle*i;
            el1.y = y;
           
        }
        else
        {
            if (middle < (yy - y))middle = yy - y;
            el1.x = x;
            el1.y = y + middle*i;
           
        }
        if (whatis == LABEL)vpages[actpage].labels.push_back(el1);
       

    }

}

void D3D::addpage(int howmany)
{
    for (int i = 0; i < howmany; ++i)
    {
        page page1;
        vpages.push_back(page1);
    }
}

void D3D::setpage(int page)
{
    if (page > vpages.size())return;

    actpage = page-1;

}

void D3D::makeovr()
{
    box l1;
    l1.x = 15;
    l1.xx = 600;
    l1.y = 50;
    l1.yy = 380;
    
    l1.colourin = SRSLYNOTGBLACK;
	l1.line = true;
	l1.linecolourin = BLACK;

    overlay.boxes.push_back(l1);

    l1.x = 15;
    l1.xx = 600;
    l1.y = 80;
    l1.yy = 350;
    
    l1.colourin = BLACK_NOTMUCH;
	l1.line = false;
	l1.linecolourin = BLACK;

    overlay.boxes.push_back(l1);

	l1.x = 15;
	l1.xx = 115;
	l1.y = 80;
	l1.yy = 280;
	
	l1.colourin = SRSLYNOTGBLACK;
	l1.line = false;
	l1.linecolourin = BLACK;

	overlay.boxes.push_back(l1);

    label l3; 

    l3.x = 35;
    l3.y = 55;
    l3.colourin = WHITE;
   
    l3.write = "ESP v2";
	l3.line = false;
	l3.linecolourin = WHITE;

    
	overlay.Titulo = l3;


    for (int i = 0; i < General.viewoptions.size();++i)
    {
        label pp;
        pp.x = 25;
        pp.y = 90 + i * 50;
      
        pp.write = General.viewoptions[i].first;
        pp.colourin = WHITE;
		pp.line = false;
		pp.linecolourin = BLACK;

		box pa;

		pa.x = 90;
		pa.xx = 100;
		pa.y = 80 + i * 50;
		pa.yy = 120 + i * 50;
		
		pa.colourin = BLACK;
		pa.line = false;
		pa.linecolourin = BLACK;
		
		overlay.boxes4.push_back(pa);
        overlay.labels.push_back(pp);
    }



    
  //  pD3D.DrawRect(10, 30, 200, 150, 1, GREY, true, true, 1, BLACK);


}

void D3D::initui()
{
    addpage(4);

    setpage(1);
   
  // addelement(13, BOX, 20, 50, 180, 70, false, 20,120);

    
}

void D3D::makerage()
{
    setpage(0);



}



void D3D::DestructUI()
{
    vpages = std::vector<page>(0);
}

void D3D::Destruct()
{
    // pD3D.Line* = NULL;
   //  pD3D.Font* = NULL;
    if (ini) {
    this->Line->Release();
    this->Font->Release();
    this->Font20->Release();
    ini = false;

    }
}



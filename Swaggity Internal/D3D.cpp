
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

void D3D::DrawCheck(checkbox chk, int movex, int movey ,bool drawstring)
{
    if (chk.checked)
    {
        this->DrawRect(chk.x+ movex, chk.y+ movey, chk.size, chk.size, 1, chk.boxcolor, true, false, 1, BLACK);
        this->DrawRect(chk.x + chk.distance + movex, chk.y + chk.distance + movey,chk.size - 2*chk.distance, chk.size - 2 * chk.distance, 1, chk.checkedcolor, true, false, 1, BLACK);
        if (drawstring) {
            int x, y;
            x = chk.x + chk.size + 10;
			y = chk.y;// +(chk.size / 5);
            this->DrawString(x + movex, y + movey, chk.write, chk.stringcolor, false, BLACK, false, 18);
        }
    }
    else
    {
        this->DrawRect(chk.x+ movex, chk.y+ movey, chk.size, chk.size, 1, chk.boxcolor, true, false, 1, BLACK);
        if (drawstring){
            int x, y;
            x = chk.x + chk.size + 10;
			y = chk.y;// +(chk.size / 5);
            this->DrawString(x+movex, y+ movey, chk.write, chk.stringcolor, false, BLACK, false, 18);
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

void D3D::DrawSlider(slider& s1)
{
   
    DrawRect(s1.x + General.movex + s1.xpos, s1.y + General.movey, s1.width - s1.xpos, s1.height, 1, s1.linecolor, true, false, 1, BLACK);
    DrawRect(s1.x + General.movex, s1.y + General.movey, s1.xpos, s1.height, 1,BLUE2, true, false, 1, BLUE2);
    DrawRect(s1.x + s1.xpos + General.movex, s1.ypos + General.movey,s1.sliderwidth,s1.sliderheight, 1, BLUE2, true, false,1,BLACK);
    DrawString(s1.x + s1.width + 10 + General.movex, s1.y + General.movey - 5, to_string(s1.value), WHITE, false, BLACK, false, 18);
}

void D3D::DrawCombo(combobox& c1)
{
	DrawRect(c1.x + General.movex , c1.y + General.movey, c1.width, c1.height, 1, c1.linecolor, true, false, 1, BLACK);
	for (int i = 0; i < c1.input.size();++i)
	{
		DrawRect(c1.x + General.movex, c1.y + General.movey + c1.height * i, c1.width, c1.height, 1, c1.background, true, false, 1, BLACK);
		DrawString(c1.x + c1.width + 10 + General.movex, c1.y + General.movey - 5 + c1.height *i, to_string(c1.input[i]), WHITE, false, BLACK, false, 18);
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

     return false;

}

void D3D::addbox(int howmany, int x, int y, int xx, int yy, bool horizontal, int middle, int whr)
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
       vpages[actpage].boxes.push_back(el1);

    }

}

void D3D::addlabel(int howmany, int x, int y, int xx, int yy, bool horizontal, int middle, int whr)
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
       vpages[actpage].labels.push_back(el1);
       

    }

}

void D3D::addslider(int howmany, int x, int y, bool horizontal, D3DCOLOR slidecolor, D3DCOLOR RegColor, D3DCOLOR linecolor, int middle)
{
    if (vpages.size() <= 0)return;

    for (int i = 0; i < howmany; ++i)
    {

        slider el1;
        if (horizontal)
        {
            el1.xpos = 0;
            el1.x = x + middle*i;
            el1.y = y;
            el1.height = 8;
            el1.width = 180;
            el1.poscolor = RegColor;
            el1.ypos = y - 8;
            el1.sliderheight = 24;
            el1.sliderwidth = 6;
            el1.slidecolor = YELLOW;
            el1.linecolor = BLACK;
               
        }
        else
        {
            el1.xpos = 0;
           
            el1.x = x;
            el1.height = 8;
            el1.width = 180;
           
            el1.poscolor = RegColor;
            el1.y = y + middle*i;
            el1.ypos = y - 8;
            el1.sliderheight = 24;
            el1.sliderwidth = 6;
            el1.slidecolor = YELLOW;
            el1.linecolor = BLACK;

        }
        vpages[actpage].sliders.push_back(el1);


    }

}

void D3D::addcombobox(int howmany, int x, int y, D3DCOLOR boxcolors,  D3DCOLOR linecolor, std::vector<int> values)
{
	combobox c1;
	c1.x = x;
	c1.y = y;
	c1.height = 20;
	c1.width = 180;
	c1.linecolor = linecolor;
	c1.input = values;
	c1.background = YELLOW;
	c1.arrowcolor = BLUE2;
	c1.linecolor = BLACK;

}


void D3D::addcheckbox(int howmany, int x, int y, int size, D3DCOLOR boxcolor,D3DCOLOR checkcolor, D3DCOLOR labelcolor, bool horizontal, int middle)
{
	if (vpages.size() <= 0)return;

	for (int i = 0; i < howmany; ++i)
	{

		checkbox el1;
		if (horizontal)
		{
			el1.x = x + (middle+ size)*i;
			el1.y = y;
			el1.size = size;
			el1.distance = 3;
			el1.boxcolor = boxcolor;
			el1.checkedcolor = checkcolor;
			el1.stringcolor = labelcolor;

		}
		else
		{
			el1.x = x;
			el1.y = y + i*(size + middle);
			el1.size = size;
			el1.distance = 3;
			el1.boxcolor = boxcolor;
			el1.checkedcolor = checkcolor;
			el1.stringcolor = labelcolor;

		}
		vpages[actpage].checkboxes.push_back(el1);


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
   
   this->addcheckbox(1, 150,90, 15, BLACK, BLUE2, WHITE, false, 20);
   this->addslider(1, 150, 125, false, BLUE2, RED, WHITE,20);
   this->addcheckbox(1, 150,150, 15, BLACK, BLUE2, WHITE, false, 20);
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



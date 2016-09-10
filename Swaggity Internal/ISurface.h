#pragma once

#include "SDK.h"
class Vector2D;

#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

enum FontFlags_t
{
    FONTFLAG_NONE,
    FONTFLAG_ITALIC = 0x001,
    FONTFLAG_UNDERLINE = 0x002,
    FONTFLAG_STRIKEOUT = 0x004,
    FONTFLAG_SYMBOL = 0x008,
    FONTFLAG_ANTIALIAS = 0x010,
    FONTFLAG_GAUSSIANBLUR = 0x020,
    FONTFLAG_ROTARY = 0x040,
    FONTFLAG_DROPSHADOW = 0x080,
    FONTFLAG_ADDITIVE = 0x100,
    FONTFLAG_OUTLINE = 0x200,
    FONTFLAG_CUSTOM = 0x400,
    FONTFLAG_BITMAP = 0x800,
};

typedef float vec_t;
class Vector2D
{
public:
    // Members
    vec_t x, y;

    // Construction/destruction
    Vector2D(void);
    Vector2D(vec_t X, vec_t Y);
    Vector2D(const float *pFloat);

    // Initialization
    void Init(vec_t ix = 0.0f, vec_t iy = 0.0f);

    // Got any nasty NAN's?
    bool IsValid() const;

    // array access...
    vec_t operator[](int i) const;
    vec_t& operator[](int i);

    // Base address...
    vec_t* Base();
    vec_t const* Base() const;

    // Initialization methods
    void Random(float minVal, float maxVal);

    // equality
    bool operator==(const Vector2D& v) const;
    bool operator!=(const Vector2D& v) const;

    // arithmetic operations
    Vector2D&	operator+=(const Vector2D &v);
    Vector2D&	operator-=(const Vector2D &v);
    Vector2D&	operator*=(const Vector2D &v);
    Vector2D&	operator*=(float s);
    Vector2D&	operator/=(const Vector2D &v);
    Vector2D&	operator/=(float s);

    // negate the Vector2D components
    void	Negate();

    // Get the Vector2D's magnitude.
    vec_t	Length() const;

    // Get the Vector2D's magnitude squared.
    vec_t	LengthSqr(void) const;

    // return true if this vector is (0,0) within tolerance
    bool IsZero(float tolerance = 0.01f) const
    {
        return (x > -tolerance && x < tolerance &&
            y > -tolerance && y < tolerance);
    }

    // Normalize in place and return the old length.
    vec_t	NormalizeInPlace();

    // Compare length.
    bool	IsLengthGreaterThan(float val) const;
    bool	IsLengthLessThan(float val) const;

    // Get the distance from this Vector2D to the other one.
    vec_t	DistTo(const Vector2D &vOther) const;

    // Get the distance from this Vector2D to the other one squared.
    vec_t	DistToSqr(const Vector2D &vOther) const;

    // Copy
    void	CopyToArray(float* rgfl) const;

    // Multiply, add, and assign to this (ie: *this = a + b * scalar). This
    // is about 12% faster than the actual Vector2D equation (because it's done per-component
    // rather than per-Vector2D).
    void	MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

    // Dot product.
    vec_t	Dot(const Vector2D& vOther) const;

    // assignment
    Vector2D& operator=(const Vector2D &vOther);

#ifndef VECTOR_NO_SLOW_OPERATIONS
    // copy constructors
    Vector2D(const Vector2D &vOther);

    // arithmetic operations
    Vector2D	operator-(void) const;

    Vector2D	operator+(const Vector2D& v) const;
    Vector2D	operator-(const Vector2D& v) const;
    Vector2D	operator*(const Vector2D& v) const;
    Vector2D	operator/(const Vector2D& v) const;
    Vector2D	operator*(float fl) const;
    Vector2D	operator/(float fl) const;

    // Cross product between two vectors.
    Vector2D	Cross(const Vector2D &vOther) const;

    // Returns a Vector2D with the min or max in X, Y, and Z.
    Vector2D	Min(const Vector2D &vOther) const;
    Vector2D	Max(const Vector2D &vOther) const;

#else

private:
    // No copy constructors allowed if we're in optimal mode
    Vector2D(const Vector2D& vOther);
#endif
};


struct Vertex_t
{
    Vertex_t() {}
    Vertex_t(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
    {
        m_Position = pos;
        m_TexCoord = coord;
    }
    void Init(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
    {
        m_Position = pos;
        m_TexCoord = coord;
    }

    Vector2D	m_Position;
    Vector2D	m_TexCoord;
};


enum FontDrawType_t
{
    // Use the "additive" value from the scheme file
    FONT_DRAW_DEFAULT = 0,

    // Overrides
    FONT_DRAW_NONADDITIVE,
    FONT_DRAW_ADDITIVE,

    FONT_DRAW_TYPE_COUNT = 2,
};

class ISurface
{
public:
    void		DrawSetColor(int r, int g, int b, int a);
    void		DrawSetColor(Color col);
    void		DrawFilledRect(int x0, int y0, int x1, int y1);
    void		DrawOutlinedRect(int x0, int y0, int x1, int y1);
    void		DrawLine(int x0, int y0, int x1, int y1);
    void		DrawPolyLine(int *px, int *py, int numPoints);
    void		DrawSetTextFont(HFont font);
    void		DrawSetTextColor(int r, int g, int b, int a);
    void		DrawSetTextColor(Color col);
    void		DrawSetTextPos(int x, int y);
    void		DrawPrintText(const wchar_t *text, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT);
    void		DrawSetTextureRGBA(int id, const unsigned char *rgba, int wide, int tall);
    void		DrawSetTexture(int id);
    int			CreateNewTextureID(bool procedural = false);
    HFont		Create_Font();
    bool		SetFontGlyphSet(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0);
    void		GetTextSize(HFont font, const wchar_t *text, int &wide, int &tall);
    void		DrawOutlinedCircle(int x, int y, int radius, int segments);
    void		DrawTexturedPolygon(int n, Vertex_t *pVertice, bool bClipVertices = true);
};
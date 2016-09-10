#pragma once
#include <cmath>

#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
#define VEC_T_NAN FLOAT32_NAN
#define FLOAT32_NAN_BITS     (uint32)0x7FC00000	// not a number!
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )
#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define IN_ATTACK				(1 << 0)
#define IN_JUMP					(1 << 1)
#define IN_DUCK					(1 << 2)
#define IN_FORWARD				(1 << 3)
#define IN_BACK					(1 << 4)
#define IN_USE					(1 << 5)
#define IN_CANCEL				(1 << 6)
#define IN_LEFT					(1 << 7)
#define IN_RIGHT				(1 << 8)
#define IN_MOVELEFT				(1 << 9)
#define IN_MOVERIGHT			(1 << 10)
#define IN_ATTACK2				(1 << 11)
#define IN_RUN					(1 << 12)
#define IN_RELOAD				(1 << 13)
#define IN_ALT1					(1 << 14)
#define IN_ALT2					(1 << 15)
#define IN_SCORE				(1 << 16)
#define IN_SPEED				(1 << 17)
#define IN_WALK					(1 << 18)
#define IN_ZOOM					(1 << 19)
#define IN_WEAPON1				(1 << 20)
#define IN_WEAPON2				(1 << 21)
#define IN_BULLRUSH				(1 << 22)
#define	FL_ONGROUND				(1 << 0)	
#define FL_DUCKING				(1 << 1)	
#define	FL_WATERJUMP			(1 << 3)	
#define FL_ONTRAIN				(1 << 4) 
#define FL_INRAIN				(1 << 5)	
#define FL_FROZEN				(1 << 6) 
#define FL_ATCONTROLS			(1 << 7) 
#define	FL_CLIENT				(1 << 8)	
#define FL_FAKECLIENT			(1 << 9)	
#define	FL_INWATER				(1 << 10)
#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10			// alerts NPC, but doesn't do damage or bleed (1/100th damage)

#define MAXSTUDIOBONES 128

class QAngle;
class Vector;
typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;

inline float BitsToFloat(uint32 i)
{
    union Convertor_t
    {
        float f;
        unsigned long ul;
    }tmp;
    tmp.ul = i;
    return tmp.f;
}

struct model_t
{
    char        name[255];
};

struct player_info_t
{
    char __pad0[0x8];

    int xuidlow;
    int xuidhigh;

    char name[128];
    int userid;
    char guid[33];

    char __pad1[0x17B];
};

struct VMatrix
{
    float m[4][4];

    inline float* operator[](int i)
    {
        return m[i];
    }

    inline const float* operator[](int i) const
    {
        return m[i];
    }
};

typedef unsigned long HFont;


class Color
{
public:
    Color()
    {
        *((int *)this) = 0;
    }
    Color(int color32)
    {
        *((int *)this) = color32;
    }
    Color(int _r, int _g, int _b)
    {
        SetColor(_r, _g, _b, 255);
    }
    Color(int _r, int _g, int _b, int _a)
    {
        SetColor(_r, _g, _b, _a);
    }

    void SetColor(int _r, int _g, int _b, int _a = 255)
    {
        _color[0] = (unsigned char)_r;
        _color[1] = (unsigned char)_g;
        _color[2] = (unsigned char)_b;
        _color[3] = (unsigned char)_a;
    }

    void GetColor(int &_r, int &_g, int &_b, int &_a) const
    {
        _r = _color[0];
        _g = _color[1];
        _b = _color[2];
        _a = _color[3];
    }

    void SetRawColor(int color32)
    {
        *((int*)this) = color32;
    }

    int GetRawColor() const
    {
        return *((int*)this);
    }

    int GetD3DColor() const
    {
        return ((int)((((_color[3]) & 0xff) << 24) | (((_color[0]) & 0xff) << 16) | (((_color[1]) & 0xff) << 8) | ((_color[2]) & 0xff)));
    }

    inline int r() const { return _color[0]; }
    inline int g() const { return _color[1]; }
    inline int b() const { return _color[2]; }
    inline int a() const { return _color[3]; }

    inline float rBase() const { return _color[0] / 255.0f; }
    inline float gBase() const { return _color[1] / 255.0f; }
    inline float bBase() const { return _color[2] / 255.0f; }
    inline float aBase() const { return _color[3] / 255.0f; }

    unsigned char &operator[](int index)
    {
        return _color[index];
    }

    const unsigned char &operator[](int index) const
    {
        return _color[index];
    }

    bool operator == (const Color &rhs) const
    {
        return (*((int *)this) == *((int *)&rhs));
    }

    bool operator != (const Color &rhs) const
    {
        return !(operator==(rhs));
    }

    Color &operator=(const Color &rhs)
    {
        SetRawColor(rhs.GetRawColor());
        return *this;
    }

    float* Base()
    {
        float clr[3];

        clr[0] = _color[0] / 255.0f;
        clr[1] = _color[1] / 255.0f;
        clr[2] = _color[2] / 255.0f;

        return &clr[0];
    }

    float* BaseAlpha()
    {
        float clr[4];

        clr[0] = _color[0] / 255.0f;
        clr[1] = _color[1] / 255.0f;
        clr[2] = _color[2] / 255.0f;
        clr[3] = _color[3] / 255.0f;

        return &clr[0];
    }

    float Hue() const
    {
        if (_color[0] == _color[1] && _color[1] == _color[2])
        {
            return 0.0f;
        }

        float r = _color[0] / 255.0f;
        float g = _color[1] / 255.0f;
        float b = _color[2] / 255.0f;

        float max = r > g ? r : g > b ? g : b,
            min = r < g ? r : g < b ? g : b;
        float delta = max - min;
        float hue = 0.0f;

        if (r == max)
        {
            hue = (g - b) / delta;
        }
        else if (g == max)
        {
            hue = 2 + (b - r) / delta;
        }
        else if (b == max)
        {
            hue = 4 + (r - g) / delta;
        }
        hue *= 60;

        if (hue < 0.0f)
        {
            hue += 360.0f;
        }
        return hue;
    }

    float Saturation() const
    {
        float r = _color[0] / 255.0f;
        float g = _color[1] / 255.0f;
        float b = _color[2] / 255.0f;

        float max = r > g ? r : g > b ? g : b,
            min = r < g ? r : g < b ? g : b;
        float l, s = 0;

        if (max != min)
        {
            l = (max + min) / 2;
            if (l <= 0.5f)
                s = (max - min) / (max + min);
            else
                s = (max - min) / (2 - max - min);
        }
        return s;
    }

    float Brightness() const
    {
        float r = _color[0] / 255.0f;
        float g = _color[1] / 255.0f;
        float b = _color[2] / 255.0f;

        float max = r > g ? r : g > b ? g : b,
            min = r < g ? r : g < b ? g : b;
        return (max + min) / 2;
    }

    static Color FromHSB(float hue, float saturation, float brightness)
    {
        float h = hue == 1.0f ? 0 : hue * 6.0f;
        float f = h - (int)h;
        float p = brightness * (1.0f - saturation);
        float q = brightness * (1.0f - saturation * f);
        float t = brightness * (1.0f - (saturation * (1.0f - f)));

        if (h < 1)
        {
            return Color(
                (unsigned char)(brightness * 255),
                (unsigned char)(t * 255),
                (unsigned char)(p * 255)
                );
        }
        else if (h < 2)
        {
            return Color(
                (unsigned char)(q * 255),
                (unsigned char)(brightness * 255),
                (unsigned char)(p * 255)
                );
        }
        else if (h < 3)
        {
            return Color(
                (unsigned char)(p * 255),
                (unsigned char)(brightness * 255),
                (unsigned char)(t * 255)
                );
        }
        else if (h < 4)
        {
            return Color(
                (unsigned char)(p * 255),
                (unsigned char)(q * 255),
                (unsigned char)(brightness * 255)
                );
        }
        else if (h < 5)
        {
            return Color(
                (unsigned char)(t * 255),
                (unsigned char)(p * 255),
                (unsigned char)(brightness * 255)
                );
        }
        else
        {
            return Color(
                (unsigned char)(brightness * 255),
                (unsigned char)(p * 255),
                (unsigned char)(q * 255)
                );
        }
    }

    static Color Red() { return Color(255, 0, 0); }
    static Color Green() { return Color(0, 255, 0); }
    static Color Blue() { return Color(0, 0, 255); }
    static Color LightBlue() { return Color(100, 100, 255); }
    static Color Grey() { return Color(128, 128, 128); }
    static Color DarkGrey() { return Color(45, 45, 45); }
    static Color Black() { return Color(0, 0, 0); }
    static Color White() { return Color(255, 255, 255); }
    static Color Purple() { return Color(220, 0, 220); }

    //Menu
    static Color Background() { return Color(55, 55, 55); }
    static Color FrameBorder() { return Color(80, 80, 80); }
    static Color MainText() { return Color(230, 230, 230); }
    static Color HeaderText() { return Color(49, 124, 230); }
    static Color CurrentTab() { return Color(55, 55, 55); }
    static Color Tabs() { return Color(23, 23, 23); }
    static Color Highlight() { return Color(49, 124, 230); }
    static Color ElementBorder() { return Color(0, 0, 0); }
    static Color SliderScroll() { return Color(78, 143, 230); }


private:
    unsigned char _color[4];
};

class ICollideable
{
public:
    virtual void pad0();
    virtual const Vector& OBBMins() const;
    virtual const Vector& OBBMaxs() const;
};

class Vector
{
public:
    float x, y, z;
    Vector(void);
    Vector(float X, float Y, float Z);
    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
    bool IsValid() const;
    float operator[](int i) const;
    float& operator[](int i);
    inline void Zero();
    bool operator==(const Vector& v) const;
    bool operator!=(const Vector& v) const;
    __forceinline Vector&	operator+=(const Vector &v);
    __forceinline Vector&	operator-=(const Vector &v);
    __forceinline Vector&	operator*=(const Vector &v);
    __forceinline Vector&	operator*=(float s);
    __forceinline Vector&	operator/=(const Vector &v);
    __forceinline Vector&	operator/=(float s);
    __forceinline Vector&	operator+=(float fl);
    __forceinline Vector&	operator-=(float fl);
    inline float	Length() const;
    __forceinline float LengthSqr(void) const
    {
        CHECK_VALID(*this);
        return (this->x*this->x + this->y*this->y + this->z*this->z);
    }
    bool IsZero(float tolerance = 0.01f) const
    {
        return (x > -tolerance && x < tolerance &&
            y > -tolerance && y < tolerance &&
            z > -tolerance && z < tolerance);
    }
    float	NormalizeInPlace();
    Vector	Normalize();
    __forceinline float	DistToSqr(const Vector &vOther) const;
    __forceinline float	Dist(const Vector &vOther) const;
    float	Dot(const Vector& vOther) const;
    float	Dot(const float* fOther) const;
    float	Length2D(void) const;
    float	Length2DSqr(void) const;
    Vector& operator=(const Vector &vOther);
    Vector	operator-(const Vector& v) const;
    Vector	operator+(const Vector& v) const;
    Vector	operator*(const Vector& v) const;
    Vector	operator/(const Vector& v) const;
    Vector	operator*(float fl) const;
    Vector	operator/(float fl) const;
    // Base address...
    float* Base();
    float const* Base() const;
};

//===============================================
inline void Vector::Init(float ix, float iy, float iz)
{
    x = ix; y = iy; z = iz;
    CHECK_VALID(*this);
}
//===============================================
inline Vector::Vector(float X, float Y, float Z)
{
    x = X; y = Y; z = Z;
    CHECK_VALID(*this);
}
//===============================================
inline Vector::Vector(void) { }
//===============================================
inline void Vector::Zero()
{
    x = y = z = 0.0f;
}
//===============================================
inline void VectorClear(Vector& a)
{
    a.x = a.y = a.z = 0.0f;
}
//===============================================
inline Vector& Vector::operator=(const Vector &vOther)
{
    CHECK_VALID(vOther);
    x = vOther.x; y = vOther.y; z = vOther.z;
    return *this;
}
//===============================================
inline float& Vector::operator[](int i)
{
    Assert((i >= 0) && (i < 3));
    return ((float*)this)[i];
}
//===============================================
inline float Vector::operator[](int i) const
{
    Assert((i >= 0) && (i < 3));
    return ((float*)this)[i];
}
//===============================================
inline bool Vector::operator==(const Vector& src) const
{
    CHECK_VALID(src);
    CHECK_VALID(*this);
    return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool Vector::operator!=(const Vector& src) const
{
    CHECK_VALID(src);
    CHECK_VALID(*this);
    return (src.x != x) || (src.y != y) || (src.z != z);
}

//===============================================
__forceinline void VectorCopy(const Vector& src, Vector& dst)
{
    CHECK_VALID(src);
    dst.x = src.x;
    dst.y = src.y;
    dst.z = src.z;
}
//===============================================
__forceinline  Vector& Vector::operator+=(const Vector& v)
{
    CHECK_VALID(*this);
    CHECK_VALID(v);
    x += v.x; y += v.y; z += v.z;
    return *this;
}
//===============================================
__forceinline  Vector& Vector::operator-=(const Vector& v)
{
    CHECK_VALID(*this);
    CHECK_VALID(v);
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}
//===============================================
__forceinline  Vector& Vector::operator*=(float fl)
{
    x *= fl;
    y *= fl;
    z *= fl;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
__forceinline  Vector& Vector::operator*=(const Vector& v)
{
    CHECK_VALID(v);
    x *= v.x;
    y *= v.y;
    z *= v.z;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
__forceinline Vector&	Vector::operator+=(float fl)
{
    x += fl;
    y += fl;
    z += fl;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
__forceinline Vector&	Vector::operator-=(float fl)
{
    x -= fl;
    y -= fl;
    z -= fl;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
__forceinline  Vector& Vector::operator/=(float fl)
{
    Assert(fl != 0.0f);
    float oofl = 1.0f / fl;
    x *= oofl;
    y *= oofl;
    z *= oofl;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
__forceinline  Vector& Vector::operator/=(const Vector& v)
{
    CHECK_VALID(v);
    Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
    x /= v.x;
    y /= v.y;
    z /= v.z;
    CHECK_VALID(*this);
    return *this;
}
//===============================================
inline float Vector::Length(void) const
{
    CHECK_VALID(*this);

    float root = 0.0f;

    float sqsr = x*x + y*y + z*z;

    __asm sqrtss xmm0, sqsr
    __asm movss root, xmm0

    return root;
}
//===============================================
inline float Vector::Length2D(void) const
{
    CHECK_VALID(*this);

    float root = 0.0f;

    float sqst = x*x + y*y;

    __asm
    {
        sqrtss xmm0, sqst
        movss root, xmm0
    }

    return root;
}
//===============================================
inline float Vector::Length2DSqr(void) const
{
    return (x*x + y*y);
}
//===============================================
inline Vector CrossProduct(const Vector& a, const Vector& b)
{
    return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
//===============================================
float Vector::DistToSqr(const Vector &vOther) const
{
    Vector delta;

    delta.x = x - vOther.x;
    delta.y = y - vOther.y;
    delta.z = z - vOther.z;

    return delta.LengthSqr();
}

float Vector::Dist(const Vector &vOther) const
{
    Vector delta;

    delta.x = x - vOther.x;
    delta.y = y - vOther.y;
    delta.z = z - vOther.z;

    return delta.Length();
}

inline Vector Vector::Normalize()
{
    Vector vector;
    float length = this->Length();

    if (length != 0) {
        vector.x = x / length;
        vector.y = y / length;
        vector.z = z / length;
    }
    else
        vector.x = vector.y = 0.0f; vector.z = 1.0f;

    return vector;
}

//===============================================
inline float Vector::NormalizeInPlace()
{
    Vector& v = *this;

    float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

    v.x *= iradius;
    v.y *= iradius;
    v.z *= iradius;
}
//===============================================
inline float VectorNormalize(Vector& v)
{
    Assert(v.IsValid());
    float l = v.Length();
    if (l != 0.0f)
    {
        v /= l;
    }
    else
    {
        v.x = v.y = 0.0f; v.z = 1.0f;
    }
    return l;
}
//===============================================
__forceinline float VectorNormalize(float * v)
{
    return VectorNormalize(*(reinterpret_cast<Vector *>(v)));
}
//===============================================
inline Vector Vector::operator+(const Vector& v) const
{
    Vector res;
    res.x = x + v.x;
    res.y = y + v.y;
    res.z = z + v.z;
    return res;
}

//===============================================
inline Vector Vector::operator-(const Vector& v) const
{
    Vector res;
    res.x = x - v.x;
    res.y = y - v.y;
    res.z = z - v.z;
    return res;
}
//===============================================
inline Vector Vector::operator*(float fl) const
{
    Vector res;
    res.x = x * fl;
    res.y = y * fl;
    res.z = z * fl;
    return res;
}
//===============================================
inline Vector Vector::operator*(const Vector& v) const
{
    Vector res;
    res.x = x * v.x;
    res.y = y * v.y;
    res.z = z * v.z;
    return res;
}
//===============================================
inline Vector Vector::operator/(float fl) const
{
    Vector res;
    res.x = x / fl;
    res.y = y / fl;
    res.z = z / fl;
    return res;
}
//===============================================
inline Vector Vector::operator/(const Vector& v) const
{
    Vector res;
    res.x = x / v.x;
    res.y = y / v.y;
    res.z = z / v.z;
    return res;
}
inline float Vector::Dot(const Vector& vOther) const
{
    const Vector& a = *this;

    return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

inline float Vector::Dot(const float* fOther) const
{
    const Vector& a = *this;

    return(a.x*fOther[0] + a.y*fOther[1] + a.z*fOther[2]);
}

inline float* Vector::Base()
{
    return (float*)this;
}

inline float const* Vector::Base() const
{
    return (float const*)this;
}

class QAngleByValue;
class QAngle
{
public:
    float x, y, z;

    QAngle(void);
    QAngle(float X, float Y, float Z);
    QAngle(const Vector& vec);

    operator QAngleByValue &() { return *((QAngleByValue *)(this)); }
    operator const QAngleByValue &() const { return *((const QAngleByValue *)(this)); }

    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
    void Random(float minVal, float maxVal);

    bool IsValid() const;
    void Invalidate();

    bool IsZero()
    {
        CHECK_VALID(*this);
        if (this->x == 0.f && this->y == 0.f && this->z == 0.f)
            return true;

        return false;
    }

    float operator[](int i) const;
    float& operator[](int i);

    float* Base();
    float const* Base() const;

    bool operator==(const QAngle& v) const;
    bool operator!=(const QAngle& v) const;

    QAngle& operator+=(const QAngle &v);
    QAngle& operator-=(const QAngle &v);
    QAngle& operator*=(float s);
    QAngle& operator/=(float s);

    float   Length() const;
    float   LengthSqr() const;

    QAngle& operator=(const QAngle& src);

    QAngle  operator-(void) const;

    QAngle  operator+(const QAngle& v) const;
    QAngle  operator-(const QAngle& v) const;
    QAngle  operator*(float fl) const;
    QAngle  operator/(float fl) const;

    QAngle Clamp();
    QAngle Mod(float N);

    inline QAngle QAngle::Normalize()
    {
        QAngle vector;
        float length = this->Length();

        if (length != 0) {
            vector.x = x / length;
            vector.y = y / length;
            vector.z = z / length;
        }
        else
            vector.x = vector.y = 0.0f; vector.z = 1.0f;

        return vector;
    }

    QAngle Normalized()
    {
        if (this->x != this->x)
            this->x = 0;
        if (this->y != this->y)
            this->y = 0;
        if (this->z != this->z)
            this->z = 0;

        if (this->x > 89.f)
            this->x = 89.f;
        if (this->x < -89.f)
            this->x = -89.f;

        while (this->y > 180)
            this->y -= 360;
        while (this->y <= -180)
            this->y += 360;

        if (this->y > 180.f)
            this->y = 180.f;
        if (this->y < -180.f)
            this->y = -180.f;

        this->z = 0;

        return *this;
    }
};

//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
    // Initialize to NAN to catch errors
    x = y = z = float_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
    x = X; y = Y; z = Z;
    CHECK_VALID(*this);
}

inline QAngle::QAngle(const Vector& vec)
{
    x = vec.x; y = vec.y; z = vec.z;
    CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init(float ix, float iy, float iz)
{
    x = ix; y = iy; z = iz;
    CHECK_VALID(*this);
}

inline void QAngle::Random(float minVal, float maxVal)
{
    x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle &vOther)
{
    CHECK_VALID(vOther);
    x = vOther.x; y = vOther.y; z = vOther.z;
    return *this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==(const QAngle& src) const
{
    CHECK_VALID(src);
    CHECK_VALID(*this);
    return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=(const QAngle& src) const
{
    CHECK_VALID(src);
    CHECK_VALID(*this);
    return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)
{
    CHECK_VALID(*this);
    CHECK_VALID(v);
    x += v.x; y += v.y; z += v.z;
    return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)
{
    CHECK_VALID(*this);
    CHECK_VALID(v);
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

inline QAngle& QAngle::operator*=(float fl)
{
    x *= fl;
    y *= fl;
    z *= fl;
    CHECK_VALID(*this);
    return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
    Assert(fl != 0.0f);
    float oofl = 1.0f / fl;
    x *= oofl;
    y *= oofl;
    z *= oofl;
    CHECK_VALID(*this);
    return *this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
    return (float*)this;
}

inline float const* QAngle::Base() const
{
    return (float const*)this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
    Assert((i >= 0) && (i < 3));
    return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
    Assert((i >= 0) && (i < 3));
    return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length() const
{
    CHECK_VALID(*this);
    return (float)sqrt(LengthSqr()); //todo replace with fastsqrt
}


inline float QAngle::LengthSqr() const
{
    CHECK_VALID(*this);
    return x * x + y * y;
}

inline QAngle QAngle::operator-(void) const
{
    return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+(const QAngle& v) const
{
    QAngle res;
    res.x = x + v.x;
    res.y = y + v.y;
    res.z = z + v.z;
    return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
    QAngle res;
    res.x = x - v.x;
    res.y = y - v.y;
    res.z = z - v.z;
    return res;
}

inline QAngle QAngle::operator*(float fl) const
{
    QAngle res;
    res.x = x * fl;
    res.y = y * fl;
    res.z = z * fl;
    return res;
}

inline QAngle QAngle::operator/(float fl) const
{
    QAngle res;
    res.x = x / fl;
    res.y = y / fl;
    res.z = z / fl;
    return res;
}

inline QAngle QAngle::Clamp()
{
    CHECK_VALID(*this);

    if (this->x < -89.0f)
        this->x = -89.0f;

    if (this->x >  89.0f)
        this->x = 89.0f;

    while (this->y < -180.0f)
        this->y += 360.0f;

    while (this->y >  180.0f)
        this->y -= 360.0f;

    this->z = 0.0f;

    return *this;
}

inline QAngle QAngle::Mod(float N)
{
    CHECK_VALID(*this);
    this->x = fmod(x, N);
    this->y = fmod(y, N);
    this->z = fmod(z, N);

    return *this;
}

struct matrix3x4_t
{
    matrix3x4_t() {}
    matrix3x4_t(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23)
    {
        m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
        m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
        m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
    }

    //-----------------------------------------------------------------------------
    // Creates a matrix where the X axis = forward
    // the Y axis = left, and the Z axis = up
    //-----------------------------------------------------------------------------
    void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
    {
        m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
        m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
        m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
    }

    //-----------------------------------------------------------------------------
    // Creates a matrix where the X axis = forward
    // the Y axis = left, and the Z axis = up
    //-----------------------------------------------------------------------------
    matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
    {
        Init(xAxis, yAxis, zAxis, vecOrigin);
    }

    inline void SetOrigin(Vector const & p)
    {
        m_flMatVal[0][3] = p.x;
        m_flMatVal[1][3] = p.y;
        m_flMatVal[2][3] = p.z;
    }

    inline void Invalidate(void)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                m_flMatVal[i][j] = VEC_T_NAN;
            }
        }
    }

    float *operator[](int i) { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
    const float *operator[](int i) const { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
    float *Base() { return &m_flMatVal[0][0]; }
    const float *Base() const { return &m_flMatVal[0][0]; }

    float m_flMatVal[3][4];
};

void inline SinCos(float radians, float *sine, float *cosine)
{
    *sine = sin(radians);
    *cosine = cos(radians);
}

enum StereoEye_t
{
    STEREO_EYE_MONO = 0,
    STEREO_EYE_LEFT = 1,
    STEREO_EYE_RIGHT = 2,
    STEREO_EYE_MAX = 3,
};

enum ClientFrameStage_t {
    FRAME_UNDEFINED = -1,
    FRAME_START,
    FRAME_NET_UPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_END,
    FRAME_NET_UPDATE_END,
    FRAME_RENDER_START,
    FRAME_RENDER_END
};

class CViewSetup
{
public:
    CViewSetup()
    {
        m_flAspectRatio = 0.0f;
        m_bRenderToSubrectOfLargerScreen = false;
        m_bDoBloomAndToneMapping = true;
        m_bOrtho = false;
        m_bOffCenter = false;
        m_bCacheFullSceneState = false;
        //		m_bUseExplicitViewVector = false;
        m_bViewToProjectionOverride = false;
        m_eStereoEye = STEREO_EYE_MONO;
    }

    // shared by 2D & 3D views

    // left side of view window
    int			x;
    int			m_nUnscaledX;
    // top side of view window
    int			y;
    int			m_nUnscaledY;
    // width of view window
    int			width;
    int			m_nUnscaledWidth;
    // height of view window
    int			height;
    // which eye are we rendering?
    StereoEye_t m_eStereoEye;
    int			m_nUnscaledHeight;

    // the rest are only used by 3D views

    // Orthographic projection?
    bool		m_bOrtho;
    // View-space rectangle for ortho projection.
    float		m_OrthoLeft;
    float		m_OrthoTop;
    float		m_OrthoRight;
    float		m_OrthoBottom;

    // horizontal FOV in degrees
    float		fov;
    // horizontal FOV in degrees for in-view model
    float		fovViewmodel;

    // 3D origin of camera
    Vector		origin;

    // heading of camera (pitch, yaw, roll)
    QAngle		angles;
    // local Z coordinate of near plane of camera
    float		zNear;
    // local Z coordinate of far plane of camera
    float		zFar;

    // local Z coordinate of near plane of camera ( when rendering view model )
    float		zNearViewmodel;
    // local Z coordinate of far plane of camera ( when rendering view model )
    float		zFarViewmodel;

    // set to true if this is to draw into a subrect of the larger screen
    // this really is a hack, but no more than the rest of the way this class is used
    bool		m_bRenderToSubrectOfLargerScreen;

    // The aspect ratio to use for computing the perspective projection matrix
    // (0.0f means use the viewport)
    float		m_flAspectRatio;

    // Controls for off-center projection (needed for poster rendering)
    bool		m_bOffCenter;
    float		m_flOffCenterTop;
    float		m_flOffCenterBottom;
    float		m_flOffCenterLeft;
    float		m_flOffCenterRight;

    // Control that the SFM needs to tell the engine not to do certain post-processing steps
    bool		m_bDoBloomAndToneMapping;

    // Cached mode for certain full-scene per-frame varying state such as sun entity coverage
    bool		m_bCacheFullSceneState;

    // If using VR, the headset calibration will feed you a projection matrix per-eye.
    // This does NOT override the Z range - that will be set up as normal (i.e. the values in this matrix will be ignored).
    bool        m_bViewToProjectionOverride;
    VMatrix     m_ViewToProjection;
};

typedef float EntityHandle_t; //patillada loko

class CMoveData
{
    //public:
    //    char pad_0x00[183];
public:
    bool            m_bFirstRunOfFunctions : 1;
    bool            m_bGameCodeMovedPlayer : 1;
    bool            m_bNoAirControl : 1;

    EntityHandle_t    m_nPlayerHandle;    // edict index on server, client entity handle on client

    int                m_nImpulseCommand;    // Impulse command issued.
    QAngle            m_vecViewAngles;    // Command view angles (local space)
    QAngle            m_vecAbsViewAngles;    // Command view angles (world space)
    int                m_nButtons;            // Attack buttons.
    int                m_nOldButtons;        // From host_client->oldbuttons;
    float            m_flForwardMove;
    float            m_flSideMove;
    float            m_flUpMove;

    float            m_flMaxSpeed;
    float            m_flClientMaxSpeed;

    // Variables from the player edict (sv_player) or entvars on the client.
    // These are copied in here before calling and copied out after calling.
    Vector            m_vecVelocity;        // edict::velocity        // Current movement direction.
    Vector            m_vecOldVelocity;
    float            somefloat;
    QAngle            m_vecAngles;        // edict::angles
    QAngle            m_vecOldAngles;

    // Output only
    float            m_outStepHeight;    // how much you climbed this move
    Vector            m_outWishVel;        // This is where you tried 
    Vector            m_outJumpVel;        // This is your jump velocity

                                           // Movement constraints    (radius 0 means no constraint)
    Vector            m_vecConstraintCenter;
    float            m_flConstraintRadius;
    float            m_flConstraintWidth;
    float            m_flConstraintSpeedFactor;
    bool            m_bConstraintPastRadius;        ///< If no, do no constraining past Radius.  If yes, cap them to SpeedFactor past radius

    void            SetAbsOrigin(const Vector &vec);
    const Vector    &GetAbsOrigin() const;

private:
    Vector            m_vecAbsOrigin;        // edict::origin

};
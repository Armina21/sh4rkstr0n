#ifndef _VEC2D
#define _VEC2D

struct vec2D {
    float x, y;

    vec2D() ;
    vec2D(float a, float b) ;

    bool operator==(const vec2D &v) const ;
    bool operator!=(const vec2D &v) const ;
    void operator=(const vec2D &v) ; 

    vec2D operator+(const vec2D &v) const ;
    vec2D operator/(const int &v) const ;
    vec2D operator*(const vec2D &v) const;
    vec2D operator-(const vec2D &v) const ;
    vec2D operator-() ; 
};

#endif

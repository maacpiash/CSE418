//
//  main.cpp
//  RGB HSV conversion
//
//  Created by Piash on 4/9/17.
//  Copyright © 2017 Maacintush. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;


float MIN(float a, float b, float c)
{
    if(a < b && a < c) return a;
    if(b < a && b < c) return b;
    return c;
}

float MAX(float a, float b, float c)
{
    if(a > b && a > c) return a;
    if(b > a && b > c) return b;
    return c;
}

void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v)
{
    int i;
    float f, p, q, t;
    if(s == 0)
    {
        *r = *g = *b = v;
        return;
    }
    h /= 60;
    i = floor(h);
    f = h - i;
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));
    
    switch (i) {
        case 0: *r = v; *g = t; * b = p; break;
        case 1: *r = q; *g = v; * b = p; break;
        case 2: *r = p; *g = v; * b = t; break;
        case 3: *r = p; *g = q; * b = v; break;
        case 4: *r = t; *g = p; * b = v; break;
        case 5: *r = v; *g = p; * b = q; break;
        default: break;
    }
}

void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v)
{
    float min, max, delta;
    min = MIN( r, g, b );
    max = MAX( r, g, b );
    *v = max;
    delta = max - min;
    if( max != 0 )
        *s = delta / max;
    else {
        *s = 0; *h = -1; return;
    }
    if( r == max )
        *h = ( g - b ) / delta; else if( g == max )
            *h = 2 + ( b - r ) / delta;
        else
            *h = 4 + ( r - g ) / delta; *h *= 60;
    if( *h < 0 )
        *h += 360;
}

int main(int argc, const char * argv[]) {
    
    float r, g, b, h, s, v;
    r = 0.7;
    g = 0.2;
    b = 0.6;
    RGBtoHSV(r, g, b, &h, &s, &v);
    cout << h << ", " << s << ", " << v << endl;
    
    return 0;
}


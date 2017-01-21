//
//  OverlapTester.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__OverlapTester__
#define __noctisgames__OverlapTester__

class Vector2D;
class Circle;
class NGRect;
class Triangle;
class Line;

class OverlapTester
{
public:
    static bool doCirclesOverlap(Circle &c1, Circle &c2);
    
    static bool doNGRectsOverlap(NGRect &r1, NGRect &r2);
    
    static bool doesNGRectOverlapTriangle(NGRect &r, Triangle &t);
    
    static bool overlapCircleNGRect(Circle &c, NGRect &r);
    
    static bool isPointInNGRect(Vector2D p, NGRect &r);
    
    static bool isPointInCircle(Vector2D &p, Circle &c);
    
    static bool isPointInTriangle(Vector2D &p, Triangle &t);
    
    static bool doLineAndNGRectOverlap(Line &l, NGRect &r);

private:
    /* A utility function to calculate area of triangle formed by (x1, y1), (x2, y2) and (x3, y3) */
    static float calcArea(float x1, float y1, float x2, float y2, float x3, float y3);
    static bool doLinesIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    
    // ctor, copy ctor, and assignment should be private in a Static Utility Class
    OverlapTester();
    OverlapTester(const OverlapTester&);
    OverlapTester& operator=(const OverlapTester&);
};

#endif /* defined(__noctisgames__OverlapTester__) */

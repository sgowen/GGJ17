//
//  OverlapTester.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "OverlapTester.h"

#include "macros.h"
#include "NGRect.h"
#include "Circle.h"
#include "Vector2D.h"
#include "Triangle.h"
#include "Line.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool OverlapTester::doCirclesOverlap(Circle &c1, Circle &c2)
{
    Vector2D c1Center = c1.getCenter();
    Vector2D c2Center = c2.getCenter();
    float distance = c1Center.distSquared(c2Center);
    float radiusSum = c1.getRadius() + c2.getRadius();
    
    return distance <= radiusSum * radiusSum;
}

bool OverlapTester::doNGRectsOverlap(NGRect &r1, NGRect &r2)
{
    if (r1.getAngle() > 0)
    {
        float halfWidth = r1.getWidth() / 2;
        float halfHeight = r1.getHeight() / 2;
        
        float rad = DEGREES_TO_RADIANS(r1.getAngle());
        float cos = cosf(rad);
        float sin = sinf(rad);
        
        float x1 = -halfWidth * cos - (-halfHeight) * sin;
        float y1 = -halfWidth * sin + (-halfHeight) * cos;
        
        float x2 = halfWidth * cos - (-halfHeight) * sin;
        float y2 = halfWidth * sin + (-halfHeight) * cos;
        
        float x3 = halfWidth * cos - halfHeight * sin;
        float y3 = halfWidth * sin + halfHeight * cos;
        
        float x4 = -halfWidth * cos - halfHeight * sin;
        float y4 = -halfWidth * sin + halfHeight * cos;
        
        float x = r1.getLeft() + r1.getWidth() / 2;
        float y = r1.getBottom() + r1.getHeight() / 2;
        
        x1 += x;
        y1 += y;
        
        x2 += x;
        y2 += y;
        
        x3 += x;
        y3 += y;
        
        x4 += x;
        y4 += y;
        
        return isPointInNGRect(Vector2D(x1, y1), r2) || isPointInNGRect(Vector2D(x2, y2), r2) || isPointInNGRect(Vector2D(x3, y3), r2) || isPointInNGRect(Vector2D(x4, y4), r2);
    }
    else
    {
        return (r1.getLeft() < r2.getLeft() + r2.getWidth() && r1.getLeft() + r1.getWidth() > r2.getLeft() && r1.getBottom() < r2.getTop() && r1.getTop() > r2.getBottom());
    }
}

bool OverlapTester::overlapCircleNGRect(Circle &c, NGRect &r)
{
    float closestX = c.getCenter().getX();
    float closestY = c.getCenter().getY();
    
    if (c.getCenter().getX() < r.getLeft())
    {
        closestX = r.getLeft();
    }
    else if (c.getCenter().getX() > r.getLeft() + r.getWidth())
    {
        closestX = r.getLeft() + r.getWidth();
    }
    
    if (c.getCenter().getY() < r.getBottom())
    {
        closestY = r.getBottom();
    }
    else if (c.getCenter().getY() > r.getTop())
    {
        closestY = r.getTop();
    }
    
    return c.getCenter().distSquared(closestX, closestY) < c.getRadius() * c.getRadius();
}

bool OverlapTester::doesNGRectOverlapTriangle(NGRect &r, Triangle &t)
{
    return doLineAndNGRectOverlap(t.getSideA(), r) || doLineAndNGRectOverlap(t.getSideB(), r) || doLineAndNGRectOverlap(t.getSideC(), r);
}

bool OverlapTester::isPointInNGRect(Vector2D p, NGRect &r)
{
    return r.getLeft() <= p.getX() && r.getLeft() + r.getWidth() >= p.getX() && r.getBottom() <= p.getY() && r.getTop() >= p.getY();
}

bool OverlapTester::isPointInCircle(Vector2D &p, Circle &c)
{
    return c.getCenter().distSquared(p) < c.getRadius() * c.getRadius();
}

bool OverlapTester::isPointInTriangle(Vector2D &p, Triangle &tr)
{
    float pX = p.getX();
    float pY = p.getY();
    float p0X = tr.getPointA().getX();
    float p0Y = tr.getPointA().getY();
    float p1X = tr.getPointB().getX();
    float p1Y = tr.getPointB().getY();
    float p2X = tr.getPointC().getX();
    float p2Y = tr.getPointC().getY();
    
    /* Calculate area of triangle ABC */
    float a = calcArea(p0X, p0Y, p1X, p1Y, p2X, p2Y);
    
    /* Calculate area of triangle PBC */
    float a1 = calcArea (pX, pY, p1X, p1Y, p2X, p2Y);
    
    /* Calculate area of triangle PAC */
    float a2 = calcArea (p0X, p0Y, pX, pY, p2X, p2Y);
    
    /* Calculate area of triangle PAB */
    float a3 = calcArea (p0X, p0Y, p1X, p1Y, pX, pY);
    
    float aSum = a1 + a2 + a3;
    
    /* Check if sum of A1, A2 and A3 is same as A */
    return a < (aSum + 0.1f) && a > (aSum - 0.1f);
}

bool OverlapTester::doLineAndNGRectOverlap(Line &l, NGRect &r)
{
    if (doLinesIntersect(l.getOrigin().getX(), l.getOrigin().getY(), l.getEnd().getX(), l.getEnd().getY(), r.getLeft(), r.getBottom() + r.getHeight() / 2, r.getLeft() + r.getWidth(), r.getBottom() + r.getHeight() / 2))
    {
        return true;
    }
    
    if (doLinesIntersect(l.getOrigin().getX(), l.getOrigin().getY(), l.getEnd().getX(), l.getEnd().getY(), r.getLeft() + r.getWidth() / 2, r.getBottom(), r.getLeft() + r.getWidth() / 2, r.getTop()))
    {
        return true;
    }
    
    return false;
}

// Private Methods

float OverlapTester::calcArea(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float sideADistance = sqrtf(powf((x2 - x1), 2) + powf((y2 - y1), 2));
    float sideBDistance = sqrtf(powf((x3 - x2), 2) + powf((y3 - y2), 2));
    float sideCDistance = sqrtf(powf((x1 - x3), 2) + powf((y1 - y3), 2));
    
    float sp = (sideADistance + sideBDistance + sideCDistance) / 2;
    
    return sqrtf(sp * (sp - sideADistance) * (sp - sideBDistance) * (sp - sideCDistance));
}

bool OverlapTester::doLinesIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    // Return false if either of the lines have zero length
    if ((x1 == x2 && y1 == y2) || (x3 == x4 && y3 == y4))
    {
        return false;
    }
    // Fastest method, based on Franklin Antonio's "Faster Line Segment Intersection" topic "in Graphics Gems III" book (http://www.graphicsgems.org/)
    double ax = x2 - x1;
    double ay = y2 - y1;
    double bx = x3 - x4;
    double by = y3 - y4;
    double cx = x1 - x3;
    double cy = y1 - y3;
    
    double alphaNumerator = by * cx - bx * cy;
    double commonDenominator = ay * bx - ax * by;
    if (commonDenominator > 0)
    {
        if (alphaNumerator < 0 || alphaNumerator > commonDenominator)
        {
            return false;
        }
    }
    else if (commonDenominator < 0)
    {
        if (alphaNumerator > 0 || alphaNumerator < commonDenominator)
        {
            return false;
        }
    }
    double betaNumerator = ax * cy - ay * cx;
    if (commonDenominator > 0)
    {
        if (betaNumerator < 0 || betaNumerator > commonDenominator)
        {
            return false;
        }
    }
    else if (commonDenominator < 0)
    {
        if (betaNumerator > 0 || betaNumerator < commonDenominator)
        {
            return false;
        }
    }
    if (commonDenominator == 0)
    {
        // This code wasn't in Franklin Antonio's method. It was added by Keith Woodward.
        // The lines are parallel.
        // Check if they're collinear.
        double y3LessY1 = y3 - y1;
        double collinearityTestForP3 = x1 * (y2 - y3) + x2 * (y3LessY1) + x3 * (y1 - y2); // see http://mathworld.wolfram.com/Collinear.html
        // If p3 is collinear with p1 and p2 then p4 will also be collinear, since p1-p2 is parallel with p3-p4
        if (collinearityTestForP3 == 0)
        {
            // The lines are collinear. Now check if they overlap.
            if ((x1 >= x3 && x1 <= x4) || (x1 <= x3 && x1 >= x4) || (x2 >= x3 && x2 <= x4) || (x2 <= x3 && x2 >= x4) || (x3 >= x1 && x3 <= x2) || (x3 <= x1 && x3 >= x2))
            {
                if ((y1 >= y3 && y1 <= y4) || (y1 <= y3 && y1 >= y4) || (y2 >= y3 && y2 <= y4) || (y2 <= y3 && y2 >= y4) || (y3 >= y1 && y3 <= y2) || (y3 <= y1 && y3 >= y2))
                {
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}

OverlapTester::OverlapTester()
{
	// Hide Constructor
}

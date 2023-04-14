#pragma once

/*
	Intersection :	Given two straight line segments (represnted as a start point and an end point). Compute the point of
					intersection if any.

					Approach :
						Equation of Line => y = mx + c;
						m = slope = gradient = tangent = (y2- y1) / (x2 - x1) 
						if m > 0 : Line going up from left to right
						if m < 0 : Line going down from left to right
						if m == 0 : Line is parallel to x

					How to find interception point;
						Consider two lines 
							y1 = ax + c;		Eq 1
							y2 = bx + d;		Eq 2

						For these two line to intercept at new point, at that point y should be same so we can solve for that
							ax + c = bx + d
							ax - bx = d - c
							x = (d - c) / (a - x)

							to find y substitue x in any of two equations Eq 1 or Eq 2
							We take Eq 1
							X = (d - c) / (a - x)
							Y = a * X + c
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef struct Point
{
	double x;
	double y;

	Point(double xx, double yy)
		: x(xx)
		, y(yy)
	{}

	Point(const Point &p)
		: x(p.x)
		, y(p.y)
	{}

	void setLocation(Point &p)
	{
		x = p.x;
		y = p.y;
	}

	void setLocation(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
}Point;

typedef struct Line
{
	double slope;
	double yIntercept;

	Line(Point start, Point end)
	{
		double deltaY = end.y - start.y;
		double deltaX = end.x - start.x;
		slope = deltaY / deltaX;
		yIntercept = end.y - slope * end.x;
	}
}Line;

bool isBetween(int start, int middle, int end)
{
	if (start > end)
	{
		return middle >= end && middle <= start;
	}
	else if (start < end)
	{
		return middle >= start && middle <= end;
	}
}

bool isBetween(const Point &start, const Point &middle, const Point &end)
{
	return isBetween(start.x, middle.x, end.x) && isBetween(start.y, middle.y, end.y);
}

class Solution
{
public:
	Point* intersection(const Point &start1, const Point &end1, const Point &start2, const Point &end2)
	{
		/* START Rearranging these so that, in order of x values: start is before end and point1 is before point 2.*/
		if (start1.x > end1.x)
		{
			swap(start1, end1);
		}

		if (start2.x > end2.x)
		{
			swap(start2, end2);
		}

		if (start1.x > start2.x)
		{
			swap(start1, start2);
			swap(end1, end2);
		}
		/* END Rearranging these so that, in order of x values: start is before end and point1 is before point 2.*/

		/* Now computes lines */
		Line line1(start1, end1);
		Line line2(start2, end2);

		/*Check if thsese are parallel line */
		if (line1.slope == line2.slope)
		{
			if (line1.yIntercept == line2.yIntercept
				&& isBetween(start1, start2, end1))
			{
				return new Point(start2);
			}
			return nullptr;
		}

		/* Get intersect coordinates */
		double x = (line2.yIntercept - line1.yIntercept) / (line1.slope - line2.slope);
		double y = x * line1.slope + line1.yIntercept;

		Point *intersectionPoint = new Point(x, y);

		if (isBetween(start1, *intersectionPoint, end1) && isBetween(start2, *intersectionPoint, end2))
		{
			return intersectionPoint;
		}
		delete intersectionPoint;
		return nullptr;
	}
};

int main()
{
	Solution sol;

	return 0;
}

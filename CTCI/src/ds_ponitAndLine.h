#pragma once

#include <iostream>

struct Point
{
	double x;
	double y;

	Point(double xx, double yy)
		: x(xx)
		, y(yy)
	{}

	Point(const Point& p)
		: x(p.x)
		, y(p.y)
	{}

	void setLocation(Point& p)
	{
		x = p.x;
		y = p.y;
	}

	void setLocation(double xx, double yy)
	{
		x = xx;
		y = yy;
	}

	void print()
	{
		std::cout << "x = " << x << ", y = " << y << std::endl;
	}
};

struct Line
{
	Point	pstart;
	Point	pend;
	double	slope;
	double	yIntercept;

	Line(Point start, Point end)
		: pstart(start)
		, pend(end)
	{
		double deltaY = end.y - start.y;
		double deltaX = end.x - start.x;
		slope = deltaY / deltaX;
		yIntercept = end.y - slope * end.x;
	}
};

bool isBetween(double start, double middle, double end)
{
	if (start > end)
	{
		return middle >= end && middle <= start;
	}
	return middle >= start && middle <= end;
}

bool isBetween(int start, int middle, int end)
{
	if (start > end)
	{
		return middle >= end && middle <= start;
	}
	return middle >= start && middle <= end;
}

bool isBetween(const Point& start, const Point& middle, const Point& end)
{
	return isBetween(start.x, middle.x, end.x) && isBetween(start.y, middle.y, end.y);
}
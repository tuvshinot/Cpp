/*
OneLoneCoder.com - Splines Part 2
"Bendier Wavier Curlier" - @Javidx9

License
~~~~~~~
Copyright (C) 2018  Javidx9
This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions; See license for details. 
Original works located at:
https://www.github.com/onelonecoder
https://www.onelonecoder.com
https://www.youtube.com/javidx9

GNU GPLv3
https://github.com/OneLoneCoder/videos/blob/master/LICENSE

From Javidx9 :)
~~~~~~~~~~~~~~~
Hello! Ultimately I don't care what you use this for. It's intended to be 
educational, and perhaps to the oddly minded - a little bit of fun. 
Please hack this, change it and use it in any way you see fit. You acknowledge 
that I am not responsible for anything bad that happens as a result of 
your actions. However this code is protected by GNU GPLv3, see the license in the
github repo. This means you must attribute me if you use it. You can view this
license here: https://github.com/OneLoneCoder/videos/blob/master/LICENSE
Cheers!


Background
~~~~~~~~~~
Curvy things are always better. Splines are a nice way to approximate
curves and loops for games. This video is the first of two parts
demonstrating how Catmull-Rom splines can be implemented.

Use Z + X to select a point and move it with the arrow keys
Use A + S to move the agent around the spline loop

Author
~~~~~~
Twitter: @javidx9
Blog: www.onelonecoder.com

Video:
~~~~~~
https://youtu.be/9_aJGUTePYo
https://youtu.be/DzjtU4WLYNs

Last Updated: 25/09/2017
*/
#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngine.h"

struct sPoint2D
{
	float x;
	float y;
	float length;
};

struct sSpline
{
	vector<sPoint2D> points;
	float fTotalSplineLength = 0.0f;

	sPoint2D GetSplinePoint(float t, bool bLooped = false)
	{
		int p0, p1, p2, p3;
		if (!bLooped)
		{
			p1 = (int)t + 1;
			p2 = p1 + 1;
			p3 = p2 + 1;
			p0 = p1 - 1;
		}
		else
		{
			p1 = (int)t;
			p2 = (p1 + 1) % points.size();
			p3 = (p2 + 1) % points.size();
			p0 = p1 >= 1 ? p1 - 1 : points.size() - 1;
		}

		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;

		float q1 = -ttt + 2.0f*tt - t;
		float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
		float q3 = -3.0f*ttt + 4.0f*tt + t;
		float q4 = ttt - tt;

		float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
		float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

		return{ tx, ty };
	}

	sPoint2D GetSplineGradient(float t, bool bLooped = false)
	{
		int p0, p1, p2, p3;
		if (!bLooped)
		{
			p1 = (int)t + 1;
			p2 = p1 + 1;
			p3 = p2 + 1;
			p0 = p1 - 1;
		}
		else
		{
			p1 = (int)t;
			p2 = (p1 + 1) % points.size();
			p3 = (p2 + 1) % points.size();
			p0 = p1 >= 1 ? p1 - 1 : points.size() - 1;
		}

		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;

		float q1 = -3.0f * tt + 4.0f*t - 1;
		float q2 = 9.0f*tt - 10.0f*t;
		float q3 = -9.0f*tt + 8.0f*t + 1.0f;
		float q4 = 3.0f*tt - 2.0f*t;

		float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
		float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

		return{ tx, ty };
	}

	float CalculateSegmentLength(int node, bool bLooped = false)
	{
		float fLength = 0.0f;
		float fStepSize = 0.005;

		sPoint2D old_point, new_point;
		old_point = GetSplinePoint((float)node, bLooped);

		for (float t = 0; t < 1.0f; t += fStepSize)
		{
			new_point = GetSplinePoint((float)node + t, bLooped);
			fLength += sqrtf((new_point.x - old_point.x)*(new_point.x - old_point.x) 
						   + (new_point.y - old_point.y)*(new_point.y - old_point.y));
			old_point = new_point;
		}

		return fLength;
	}


	float GetNormalisedOffset(float p)
	{
		// Which node is the base?
		int i = 0;
		while (p > points[i].length)
		{
			p -= points[i].length;
			i++;
		}

		// The fractional is the offset 
		return (float)i + (p / points[i].length);
	}

};

class OneLoneCoder_Splines : public olcConsoleGameEngine
{
public:
	OneLoneCoder_Splines()
	{
		m_sAppName = L"Splines 2";
	}

private:
	sSpline path;
	int nSelectedPoint = 0;
	float fMarker = 0.0f;

	vector<pair<float, float>> vecModelCar;

protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		//path.points = { { 10, 41 },{ 40, 41 },{ 70, 41 },{ 100, 41 } };
		//path.points = { { 10, 41 },{ 20, 41 },{ 30, 41 },{ 40, 41 },{ 50, 41 },{ 60, 41 },{ 70, 41 },{ 80, 41 },{ 90, 41 },{ 100, 41 } };

		for (int i = 0; i < 10; i++)
			path.points.push_back({ 30.0f * sinf((float)i / 10.0f * 3.14159f * 2.0f) + ScreenWidth() / 2,
									30.0f * cosf((float)i / 10.0f * 3.14159f * 2.0f) + ScreenHeight() / 2 });

		vecModelCar = { { 1,1 },{ 1,3 },{ 3,0 },{ 0,-3 },{ -3,0 },{ -1, 3 },{ -1,1 } };


		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// Clear Screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		// Handle input
		if (m_keys[L'X'].bReleased)
		{
			nSelectedPoint++;
			if (nSelectedPoint >= path.points.size())
				nSelectedPoint = 0;
		}

		if (m_keys[L'Z'].bReleased)
		{
			nSelectedPoint--;
			if (nSelectedPoint < 0)
				nSelectedPoint = path.points.size() - 1;
		}

		if (m_keys[VK_LEFT].bHeld)
			path.points[nSelectedPoint].x -= 30.0f * fElapsedTime;

		if (m_keys[VK_RIGHT].bHeld)
			path.points[nSelectedPoint].x += 30.0f * fElapsedTime;

		if (m_keys[VK_UP].bHeld)
			path.points[nSelectedPoint].y -= 30.0f * fElapsedTime;

		if (m_keys[VK_DOWN].bHeld)
			path.points[nSelectedPoint].y += 30.0f * fElapsedTime;

		if (m_keys[L'A'].bHeld)
			fMarker -= 20.0f * fElapsedTime;

		if (m_keys[L'S'].bHeld)
			fMarker += 20.0f * fElapsedTime;

		if (fMarker >= (float)path.fTotalSplineLength)
			fMarker -= (float)path.fTotalSplineLength;

		if (fMarker < 0.0f)
			fMarker += (float)path.fTotalSplineLength;

		// Draw Spline
		for (float t = 0; t < (float)path.points.size(); t += 0.005f)
		{
			sPoint2D pos = path.GetSplinePoint(t, true);
			Draw(pos.x, pos.y);
		}

		path.fTotalSplineLength = 0.0f;

		// Draw Control Points
		for (int i = 0; i < path.points.size(); i++)
		{
			path.fTotalSplineLength += (path.points[i].length = path.CalculateSegmentLength(i, true));
			Fill(path.points[i].x - 1, path.points[i].y - 1, path.points[i].x + 2, path.points[i].y + 2, PIXEL_SOLID, FG_RED);
			DrawString(path.points[i].x, path.points[i].y, to_wstring(i));
			DrawString(path.points[i].x + 3, path.points[i].y, to_wstring(path.points[i].length));
		}

		// Highlight control point
		Fill(path.points[nSelectedPoint].x - 1, path.points[nSelectedPoint].y - 1, path.points[nSelectedPoint].x + 2, path.points[nSelectedPoint].y + 2, PIXEL_SOLID, FG_YELLOW);
		DrawString(path.points[nSelectedPoint].x, path.points[nSelectedPoint].y, to_wstring(nSelectedPoint));

		// Draw agent to demonstrate gradient
		float fOffset = path.GetNormalisedOffset(fMarker);
		sPoint2D p1 = path.GetSplinePoint(fOffset, true);
		sPoint2D g1 = path.GetSplineGradient(fOffset, true);
		float r = atan2(-g1.y, g1.x);
		DrawLine(5.0f * sin(r) + p1.x, 5.0f * cos(r) + p1.y, -5.0f * sin(r) + p1.x, -5.0f * cos(r) + p1.y, PIXEL_SOLID, FG_BLUE);

		DrawWireFrameModel(vecModelCar, p1.x, p1.y, -r + (3.14159f / 2.0f), 5.0f, FG_CYAN);


		DrawString(2, 2, to_wstring(fOffset));
		DrawString(2, 4, to_wstring(fMarker));

		return true;
	}
};

int main()
{
	OneLoneCoder_Splines demo;
	demo.ConstructConsole(160, 80, 10, 10);
	demo.Start();
	return 0;
}

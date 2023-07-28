#pragma once

#include <math.h>
#include <cassert>

namespace framework
{
	struct Rect
	{
		float left;
		float top;
		float right;
		float bottom;

		Rect(float left = 0.f, float top = 0.f, float right = 0.f, float bottom = 0.f)
			: left(left), top(top), right(right), bottom(bottom)
		{

		}
	};

	struct Vector2D
	{
		float x;
		float y;

		Vector2D(float x = 0.f, float y = 0.f) : x(x), y(y) { }

		Vector2D& operator= (const Vector2D& o)
		{
			this->x = o.x;	this->y = o.y;
			return *this;
		}

		Vector2D operator+ (const Vector2D& o)
		{
			return Vector2D(this->x + o.x, this->y + o.y);
		}

		Vector2D operator- (const Vector2D& o)
		{
			return Vector2D(this->x - o.x, this->y - o.y);
		}

		Vector2D operator* (const Vector2D& o)
		{
			return Vector2D(this->x * o.x, this->y * o.y);
		}

		Vector2D operator/ (const Vector2D& o)
		{
			assert(o.x != 0.f && o.y != 0.f);
			return Vector2D(this->x / o.x, this->y / o.y);
		}

		Vector2D operator/ (float num)
		{
			assert(num != 0.f);
			return Vector2D(this->x / num, this->y / num);
		}

		Vector2D& Normalize()
		{
			float length = sqrt(this->x * this->x + this->y * this->y);
			*this / length;
			return *this;
		}
	};

/*---------------------------------------
애니메이션 프레임 정보
---------------------------------------*/
	struct FRAME_INFO
	{
		D2D1_RECT_F Source;		// 이미지 파일에서 어느 영역 Rect가 실제 프레임인지 저장한다.
		float		RenderTime; // 그리는 시간

		FRAME_INFO(int x, int y, int width, int height, float time)
		{
			Source.left = (float)x;
			Source.top = (float)y;
			Source.right = (float)x + (float)width;
			Source.bottom = (float)y + (float)height;
			RenderTime = time;
		}
		FRAME_INFO(D2D1_RECT_F rect, float time)
		{
			Source = rect;
			RenderTime = time;
		}
	};
}
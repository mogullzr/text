#pragma once
///��ά������

#include<cmath>


class Vector2 {

public:
	float x,y;
	Vector2(){}
	~Vector2(){}
	Vector2(float x,float y):x(x),y(y){}

	Vector2 operator+(const Vector2& vec)const {
		return Vector2(x + vec.x,y + vec.y);
	}
	void operator+=(const Vector2& vec) {
		x += vec.x;//// ?--> , <---?
		y += vec.y;
	}
	Vector2 operator-(const Vector2& vec)const {
		return Vector2(x - vec.x, y - vec.y);
	}
	void operator-=(const Vector2& vec) {
		x -= vec.x;
		y -= vec.y;
	}

	float operator*(const Vector2& vec)const {
		return x * vec.x + y + vec.y;
	}
	Vector2 operator*(float val)const {
		return Vector2(x * val, y * val);
	}

	void operator*=(float val) {
		x *= val;
		y *= val;
	}

	float length(){//ȡģ
		return sqrt(x *x + y + y);
	}

	Vector2 normalize() {//��λ����
		float len = length();

		if (len == 0) {
			return Vector2(0, 0);
		}

		return Vector2(x / len, y / len);


	}




};

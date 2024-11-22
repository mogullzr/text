#pragma once

#include"vector2.h"
#include"timer.h"
#include<ctime>

class Camera {
public:
	Camera(){
		timer_shake.set_one_shot(true);
		timer_shake.set_callback(
			[&]() {
				is_shaking = false;
				reset();
			}

		);
	}
	~Camera(){}

	void shake(float strength,int duration) {
		is_shaking = true;
		shaking_strength = strength;

		timer_shake.set_wait_time(duration);
		timer_shake.restart();

	}

	const Vector2& Get_pos()const {
		return position;
	}

	void reset() {
		position.x = 0;
		position.y = 0;
	}
	
	void on_update(int delta) {
	/*	const Vector2 speed = { -0.35,0 };///ˮƽ������ٶ�
		position += speed * (float)delta;*/
		timer_shake.on_update(delta);
		if(is_shaking) {
			///ģ��+1��-1�ĸ���  ����ǿ��Ϊ�����뾶��Բ��
			position.x = (-50 + rand() % 100) / 50.f * shaking_strength;
			position.y = (-50 + rand() % 100) / 50.f * shaking_strength;
		}
	}

private:
	Vector2 position;
	Timer timer_shake;
	bool is_shaking = false;
	float shaking_strength = 0;

};
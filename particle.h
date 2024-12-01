#pragma once

#include"atlas.h"
#include"vector2.h"
#include"camera.h"
#include"tools.h"


class Particle {
public:
	Particle(){}
	Particle(const Vector2&pos,Atlas*atlas,int life_span):position(pos),atlas(atlas),life_span(life_span)
	{}

	~Particle(){}
	
	void set_atlas(Atlas* new_altas) {
		atlas = new_altas;
	}

	void set_pos(Vector2 pos) {
		position = pos;
	}

	void set_lifespan(int val) {
		life_span = val;
	}

	bool check_valid()const {
		return valid;
	}

	void on_update(int delta) {
		timer += delta;
		if (timer >= life_span) {
			timer = 0;
			idx_frame++;
			if(idx_frame >= atlas->get_size()) {
				idx_frame = atlas->get_size() - 1;//��ֹԽ�磿 
				valid = false;

			}
		}
	}

	void on_draw(const Camera& camera)const
	{
		putimage_Alpha(camera,position.x, position.y, atlas->get_image(idx_frame));
		///
	}
private:

	int timer = 0;
	int life_span = 0;///��֡���Ӷ�������ʱ��
	int idx_frame = 0;
	Vector2 position;
	bool valid = true;///���Ӷ����Ƿ���Ч
	Atlas* atlas = nullptr;


};
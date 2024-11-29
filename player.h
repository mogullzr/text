#pragma once
#include"camera.h"
#include<easyx.h>
#include"vector2.h"
#include"animation.h"
#include"player_id.h"
#include"platform.h"
#include"bullet.h"
#include"tools.h"

extern bool is_debug;

extern std::vector<Platform> platform_list;

extern std::vector< Bullet* >bullet_list;

class Player {
public:
	Player(){
		current_animation = &animation_idle_right;

		timer_attack_cd.set_wait_time(attack_cd);
		timer_attack_cd.set_one_shot(true);
		timer_attack_cd.set_callback(
			[&](){
				can_attack = true;
			}
		);

		timer_invulnerable.set_wait_time(750);
		timer_invulnerable.set_one_shot(true);
		timer_invulnerable.set_callback(
			[&]() {
				is_invulnerable = false;
			}
		);
		
		timer_invulnerable_blink.set_wait_time(75);
		//timer_invulnerable_blink.set_one_shot(true);///!!!ע�⣡����ȫ��֡��ʱ����Ҫloop��Ȼ����ʵ����˸������һֱ�׵� 
		timer_invulnerable_blink.set_callback
		(
			[&]() 
			{	
				//cout << "sketch_change_before: " << is_showing_sketch_frame << std::endl;
				is_showing_sketch_frame = !is_showing_sketch_frame;
				//cout << "sketch_change_after: " << is_showing_sketch_frame << std::endl;

			}
		);

		


	}
	~Player(){}

	virtual void on_update(int delta) {//��������
		int direction = is_right_key_down - is_left_key_down;
		if (direction != 0) {
			if(!is_attacking_ex)///�ж��Ƿ�Ŵ�ʹ�Ŵ�ʱ��ת��
				is_facing_right = (direction > 0);
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float distance = direction * run_v * delta;
			on_run(distance);
		
		}
		else {

			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;

		} 

		if (is_attacking_ex)
		{
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		}

		current_animation->on_update(delta);

		timer_attack_cd.on_update(delta);


		timer_invulnerable.on_update(delta);
		timer_invulnerable_blink.on_update(delta);


		if (is_showing_sketch_frame) {
			sketch_image(current_animation->get_frame(),&img_sketch);
		}

		move_and_collide(delta);


		//std::cout <<"invu:"<< is_invulnerable << std::endl;
		//std::cout << "_sketch:" << is_showing_sketch_frame << std::endl;

	}

	virtual void on_draw(const Camera& camera) {//����
		if (hp > 0 && is_invulnerable && is_showing_sketch_frame) {
			putimage_Alpha(camera, (int)position.x, (int)position.y,&img_sketch);///���׼�Ӱ֡

		}else
		current_animation->on_draw(camera, (int)position.x, (int)position.y);//��������֡

		if(is_debug)
		{
			setlinecolor(RGB(0, 125, 255));
			rectangle(position.x, position.y, position.x + size.x, position.y + size.y);
		}


	}

	virtual void on_input(const ExMessage& msg) {///�����������
		switch (msg.message) {
			case WM_KEYDOWN:
				switch (player_id) {
				case PlayerID::P1:
					switch (msg.vkcode) {
					case 0x41://��
						is_left_key_down = true;
						break;
					case 0x44://��
						is_right_key_down = true;
						break;
					case 0x57:///��
						on_jump();
						break;
					case 0x46://ƽA
						if (can_attack) {
							on_attack();
							can_attack = false;
							timer_attack_cd.restart();

						}
						break;
					case 0x47:///����
						if (mp>=100) {
							on_attack_ex();
							can_attack = false;
							timer_attack_cd.restart();///Ҫ�������⣬��Ȼ��������ƽa��������

							mp = 0;
						}
						break;


					}
					break;
				case PlayerID::P2:
					switch (msg.vkcode) {
					case VK_LEFT:
						is_left_key_down = true;
						break;
					case VK_RIGHT:
						is_right_key_down = true;
						break;
					case VK_UP:
						on_jump();
						break;
					
					case VK_OEM_PERIOD:
						if (can_attack) {
							on_attack();
							can_attack = false;
							timer_attack_cd.restart();

						}
						break;

					case VK_OEM_2:
						if (mp >= 100) {
							on_attack_ex();
							
							can_attack = false;
							timer_attack_cd.restart();///Ҫ�������⣬��Ȼ��������ƽa��������

							mp = 0;
						}
						break;

					}



					break;

				}
 
			break;
			
			case WM_KEYUP:
				switch (player_id) {
				case PlayerID::P1:
					switch (msg.vkcode) {
					case 0x41:
						is_left_key_down = false;
						break;
					case 0x44:
						is_right_key_down = false;
						break;
					case 0x42:

						break;

					case 0x43:

						break;


					}

					break;
				case PlayerID::P2:

					switch (msg.vkcode) {
					case VK_LEFT:
						is_left_key_down = false;
						break;
					case VK_RIGHT:
						is_right_key_down = false;
						break;
					case VK_UP:

						break;

					case VK_DOWN:

						break;


					}

					break;

				}

			break;


		default:
			break;

		}



	}

	virtual void on_run(float distance) {
		if (is_attacking_ex) {
			return;
		}
		position.x += distance;
	}	

	virtual void on_jump() {

		if (velocity.y != 0|| is_attacking_ex)
			return;

		velocity.y += jump_v;
	}

	virtual void on_attack(){
		

	}

	virtual void on_attack_ex(){
		

	}
	Vector2 get_size() {
		return size;
	}
	Vector2 get_pos() {
		return position;
	}

	void setID(PlayerID id) {
		this->player_id = id;
	}

	void set_pos(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void move_and_collide(int delta){///// !!! 
		
		velocity.y += gravity * delta;///
		position += velocity * (float)delta;///
		if (velocity.y > 0) {
			for (const Platform& platform : platform_list) {
				const Platform::CollisionShape& shape = platform.shape;
				bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left) <= size.x + (shape.right - shape.left));
				bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);
				if (is_collide_x && is_collide_y) {
					float delta_pos_y = velocity.y * delta;
					float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;
					if (last_tick_foot_pos_y <= shape.y) {
						position.y = shape.y - size.y;
						velocity.y = 0;
						
 						break;
					}

				}

			}

		}
		if (!is_invulnerable)
		{///���õ���ɫ�������޵�״̬��ʱ���ִ����ײ�߼�
			for (Bullet* bullet : bullet_list) {
				if (!bullet->get_valid() || bullet->get_collide_target() != player_id) {////�ж��ӵ��Ƿ���Ч�Լ��Ƿ��뵱ǰ���idƥ��
					continue;
				}
				if (bullet->check_collision(position, size))
				{///��������Լ��ߴ磬�ж��Ƿ�����ײ
					make_invulnerable();
					bullet->on_collide();
					bullet->set_valid(false);
					hp -= (bullet->get_damage());
					std::cout << "hurt" << std::endl;
				}
			}
		}


	}

	void make_invulnerable() 
	{
		is_invulnerable = true;
		timer_invulnerable.restart();
	}

	const Vector2& get_size()const
	{
		return size;
	}

	int get_hp()const
	{
		return hp;
	}

	int get_mp()const
	{
		return mp;
	}


protected:
	int mp = 0;
	int hp = 100;///����ֵ

	const float run_v = 0.55f;
	const float gravity = 1.6e-3f;
	const float jump_v = -0.85f;

	Vector2 size;
	Vector2 velocity;
	Vector2 position;


	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	
	Animation animation_attack_ex_left;
	Animation animation_attack_ex_right;


	Animation* current_animation = nullptr;

	PlayerID player_id = PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;

	bool can_attack = true;///�Ƿ�����ͷ���ͨ������ʵ���չ���ȴ
	bool is_attacking_ex = false;//�Ƿ�����ͷŴ���

	Timer timer_attack_cd;///�չ���ȴ��ʱ��

	int attack_cd = 500;

	bool is_invulnerable = false;//��ɫ�Ƿ����޵�״̬
	bool is_showing_sketch_frame = false;///�Ƿ��ڼ�Ӱ֡
	Timer timer_invulnerable;//�޵�״̬��ʱ��
	Timer timer_invulnerable_blink;///�޵���˸��ʱ��

	IMAGE img_sketch;
	 
};




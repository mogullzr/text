#pragma once

#include"scene.h"
#include"scene_manager.h"
#include"atlas.h"
#include"animation.h"

extern IMAGE img_VS;// VS������ͼƬ
extern IMAGE img_1P;// 1P�ı�ͼƬ
extern IMAGE img_2P;//2P�ı�ͼƬ
extern IMAGE img_1P_desc;//1P��λ����ͼƬ
extern IMAGE img_2P_desc;//2P��λ����ͼƬ
extern IMAGE img_gravestone_left;// �������Ĺ��ͼƬ
extern IMAGE img_gravestone_right;//�����ҵ�Ĺ��ͼƬ
extern IMAGE img_selector_tip;//ѡ�ǽ�����ʾ��Ϣ�ı�ͼƬ
extern IMAGE img_selector_background;//ѡ�ǽ��汳��ͼ
extern IMAGE img_1P_selector_btn_idle_left;//1P����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_idle_right;// 1P����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_left;//1P����ѡ��ť����״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_right;//1P����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_left;//2P����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_right;//2P����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_left;//2P����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_right;// 2P����ѡ��ť����״̬ͼƬ
extern IMAGE img_peashooter_selector_background_left;//ѡ�ǽ��泯����������ֱ���ͼƬ
extern IMAGE img_peashooter_selector_background_right;//ѡ�ǽ��泯���ҵ������ֱ���ͼƬ
extern IMAGE img_sunflower_selector_background_left;//ѡ�ǽ��泯��������տ�����ͼƬ
extern IMAGE img_sunflower_selector_background_right;//ѡ�ǽ��泯���ҵ����տ�����ͼƬ

extern Atlas atlas_peashooter_idle_right;//�����ֳ����ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_idle_right;

extern IMAGE img_avatar_peashooter;//������ͷ��ͼƬ
extern IMAGE img_avatar_sunflower;//���տ�ͷ��ͼƬ

extern SceneManager scene_manager;

class SelectScene :public Scene {
public:
	SelectScene(){}
	~SelectScene(){}
	 

	void on_enter() {///�������ʱ�ĳ�ʼ���߼�


	}

	void on_update(int delta) {//��������

	}

	void on_draw(const Camera& camera) {//����

	}

	void on_input(const ExMessage& msg) {///�����������


	}

	void on_exit() {///�������˳�ʱ��ж���߼�

	}


private:
	POINT pos_img_VS = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1P = { 0 };
	POINT pos_img_2P = { 0 };
	POINT pos_img_1P_desc = { 0 };
	POINT pos_img_2P_desc = { 0 };
	POINT pos_img_1P_name = { 0 };
	POINT pos_img_2P_name = { 0 };
	POINT pos_animation_1P = { 0 };
	POINT pos_animation_2P = { 0 };
	POINT pos_img_1P_gravestone = { 0 };
	POINT pos_img_2P_gravestone = { 0 };
	POINT pos_1P_selector_btn_left = { 0 };
	POINT pos_1P_selector_btn_right = { 0 };
	POINT pos_2P_selector_btn_left = { 0 };
	POINT pos_2P_selector_btn_right = { 0 };
	
	
};
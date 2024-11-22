#pragma once

#include<iostream>
#include"scene_manager.h"
#include"scene.h"
#include"atlas.h"
#include"animation.h"
#include"camera.h"
#include"timer.h"


extern SceneManager scene_manager;
extern IMAGE img_menu_background;



class Menuscene :public Scene {
public:
	Menuscene() {

	}
	~Menuscene() {

	}

	void on_enter() {///�������ʱ�ĳ�ʼ���߼�
		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);

	
	}
	 
	void on_update(int delta) {//��������

	}

	void on_draw(const Camera& camera) {//����
		putimage(0, 0, &img_menu_background);

	}

	void on_input(const ExMessage& msg) {///�����������
		if (msg.message == WM_KEYUP) {
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager.switch_scene(SceneManager::SceneType::Select);
		}

	}

	void on_exit() {///�������˳�ʱ��ж���߼�

	}


private:
	Animation animation_peashooter_run_right;
	Camera camera;
	Timer timer;
};
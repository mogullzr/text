#pragma once

#include"scene_manager.h"
#include"scene.h"

extern SceneManager scene_manager;


class GameScene:public Scene{
public:
	GameScene() {

	}
	~GameScene() {
	}
	void on_enter() {///�������ʱ�ĳ�ʼ���߼�
		std::cout << " ������Ϸ�ڳ��� " << std::endl;
	}

	void on_update(int delta) {//��������
		std::cout << "��Ϸ��������" << std::endl;
	}

	void on_draw(const Camera& camera) {//����
		outtextxy(20, 20, _T("��Ϸ�������ڻ�������"));
	}

	void on_input(const ExMessage& msg) {///�����������
		if (msg.message == WM_KEYDOWN) {///������������� GameScene
			scene_manager.switch_scene(SceneManager::SceneType::Menu);
		}
	}
	void on_exit(){
		///�������˳�ʱ��ж���߼�
		std::cout << "��Ϸ���˳�" << std::endl;
	}



};


#pragma once

#include<graphics.h>
#include<iostream>
#include"camera.h"


class Scene {
public:
	Scene(){}
	~Scene(){}


	///  ���ù���/����--->>���ⲻ�Ϲ�����ɾ���µĶ���Ӷ��˷����� // �������ڶ����������ڳ��ڳ�����������-->ʹ���������������������Ϸ������������ͬ
	///����� ---�� ��new������Ϊrefresh initiate
	
	virtual void on_enter() {///�������ʱ�ĳ�ʼ���߼�
	}

	virtual void on_update(int delta) {//��������

		//SceneManager::switch_scene(arg);
	}

	virtual void on_draw(const Camera& camera){//����
	}

	virtual void on_input(const ExMessage& msg) {///�����������

	}

	virtual void on_exit() {///�������˳�ʱ��ж���߼�

	}


};




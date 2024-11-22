#include<iostream>
#include<easyx.h>
#include<graphics.h>

#include"atlas.h"///ͼ��

#include"tools.h"///���߼�

#include"scene.h"
#include"menu_scene.h"
#include"game_scene.h"
#include"select_scene.h"

#include"scene_manager.h"
#include"animation.h"

#include"Init_res.h"///����ͼ�����ֵ���Դ





 
Scene* menu_scene = nullptr;//�̳���Scene���ʿ���ֱ�Ӹ�Scene*�ı�������
Scene* game_scene = nullptr;//�̳���Scene���ʿ���ֱ�Ӹ�Scene*�ı�������
Scene* select_scene = nullptr;//�̳���Scene���ʿ���ֱ�Ӹ�Scene*�ı�������

Camera main_camera;
SceneManager scene_manager;






int main() {
	load_image_res();


	ExMessage msg;
	const int FPS = 60;
	initgraph(1280,720);

	BeginBatchDraw();

	menu_scene = new Menuscene();
	game_scene = new GameScene();
	select_scene = new SelectScene();

	scene_manager.set_current_scene(menu_scene);
	
	
	while (1) {
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg)) {
			scene_manager.on_input(msg);
		}


		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick_time = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick_time);
		last_tick_time = current_tick_time;


		cleardevice();
		
		scene_manager.on_draw(main_camera);

		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS) {
			Sleep(1000 /FPS - frame_delta_time);
		}

	}

	EndBatchDraw();


	return 0;
}
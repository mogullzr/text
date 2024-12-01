#pragma once

#include"tools.h"

class StatusBar 
{
public:
	StatusBar(){}
	~StatusBar(){}

	void set_avater(IMAGE* img) 
	{
		img_avater = img;
	}
	
	void set_position(int x, int y) 
	{
		position.x = x, position.y = y;
	}

	void set_hp(int val)
	{
		hp = val;
	}

	void set_mp(int val)
	{
		mp = val;
	}

	void on_draw()
	{
		putimage_Alpha(position.x, position.y, img_avater);
		
		setfillcolor(RGB(5, 5, 5));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3 * 2, position.y + 36, 8, 8);///����������ڻ��ޱ߿�����Բ�Ǿ��Ρ�
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3 * 2, position.y + 71, 8, 8);///����������ڻ��ޱ߿�����Բ�Ǿ��Ρ�
		
		setfillcolor(RGB(67, 47, 47));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3 , position.y + 33, 8, 8);///����������ڻ��ޱ߿�����Բ�Ǿ��Ρ�
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3 , position.y + 68, 8, 8);///����������ڻ��ޱ߿�����Բ�Ǿ��Ρ�

		float hp_bar_width = width * max(0, hp) / 100.0f;
		float mp_bar_width = width * min(100, mp) / 100.0f;
		setfillcolor(RGB(197, 61, 67));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + (int)hp_bar_width + 3, position.y + 33, 8, 8);
		setfillcolor(RGB(83, 131, 195));
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + (int)mp_bar_width + 3, position.y + 68, 8, 8);


	}
private:

	int hp = 0;
	int mp = 0;
	POINT position = { 0 };///��������ʾ��λ��
	IMAGE* img_avater = nullptr;//ͷ��

	const int width = 275;///״̬�����

};
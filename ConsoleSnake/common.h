#pragma once
/*
  ���ļ������궨�塢ȫ�ֳ�����ö������
*/
// ���峣������
const int ESC_KEY = 27;
const int UP_KEY = 72;
const int DOWN_KEY = 80;
const int LEFT_KEY = 75;
const int RIGHT_KEY = 77;
/*
ESC_KEY ��ֵΪ 27����Ӧ ASCII ����е� Esc ����
UP_KEY ��ֵΪ 72����Ӧ ASCII ����еķ�����ϡ�
DOWN_KEY ��ֵΪ 80����Ӧ ASCII ����еķ�����¡�
LEFT_KEY ��ֵΪ 75����Ӧ ASCII ����еķ������
RIGHT_KEY ��ֵΪ 77����Ӧ ASCII ����еķ�����ҡ�
*/

//ö������ Up ��ֵΪ 0��RIGHT ��ֵΪ1��Down ��ֵΪ 2��LEFT ��ֵΪ 3
enum Direction {
	UP ,
	RIGHT,
	DOWN,
	LEFT
};
enum Color
{
	BLACK = 0,
	GRAY = 8,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE
};

#define BOARD_X 1		 //��ʾ��Ϸ��������Ļ�ϵ����Ͻ�����
#define BOARD_Y 3		 //��ʾ��Ϸ��������Ļ�ϵ����Ͻ�����
#define WIDTH 30		 //��ʾ��Ϸ���ڵĿ��
#define HIGHT 23		 //��ʾ��Ϸ���ڵĸ߶�

//����һЩ�Ʊ��				  
const wchar_t CELL_V = L'|';						 //����
const wchar_t CELL_H = L'-';	 					 //����
const wchar_t CELL_TL = L'��';	 					 //����
const wchar_t CELL_TR = L'��';   					 //����
const wchar_t CELL_BL = L'��';   					 //����
const wchar_t CELL_BR = L'��';   					 //����
const wchar_t CELL_SQUARE =  L'��';					 //ʵ�ķ���




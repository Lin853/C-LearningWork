#pragma once
/*
  本文件包含宏定义、全局常量、枚举类型
*/
// 定义常量向量
const int ESC_KEY = 27;
const int UP_KEY = 72;
const int DOWN_KEY = 80;
const int LEFT_KEY = 75;
const int RIGHT_KEY = 77;
/*
ESC_KEY 的值为 27，对应 ASCII 码表中的 Esc 键。
UP_KEY 的值为 72，对应 ASCII 码表中的方向键上。
DOWN_KEY 的值为 80，对应 ASCII 码表中的方向键下。
LEFT_KEY 的值为 75，对应 ASCII 码表中的方向键左。
RIGHT_KEY 的值为 77，对应 ASCII 码表中的方向键右。
*/

//枚举类型 Up 的值为 0，RIGHT 的值为1，Down 的值为 2，LEFT 的值为 3
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

#define BOARD_X 1		 //表示游戏窗口在屏幕上的左上角坐标
#define BOARD_Y 3		 //表示游戏窗口在屏幕上的左上角坐标
#define WIDTH 30		 //表示游戏窗口的宽度
#define HIGHT 23		 //表示游戏窗口的高度

//定义一些制表符				  
const wchar_t CELL_V = L'|';						 //竖线
const wchar_t CELL_H = L'-';	 					 //横线
const wchar_t CELL_TL = L'┏';	 					 //左上
const wchar_t CELL_TR = L'┓';   					 //右上
const wchar_t CELL_BL = L'┗';   					 //左下
const wchar_t CELL_BR = L'┛';   					 //右上
const wchar_t CELL_SQUARE =  L'■';					 //实心方块




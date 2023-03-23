/*
  全局函数的定义
*/
#pragma once
#include <iostream> 
#include<Windows.h>
#include <deque>
#include <conio.h>
#include "common.h"
#include <algorithm>





//调用了Windows API函数GetStdHandle，该函数的作用是获取当前进程的标准输出设备的句柄
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

//在x,y坐标处输出一个格子
void PrintCell(int x, int y, Color color, wchar_t ch = CELL_SQUARE)			//wchar_t 宽字节字符类型
{
	COORD pos;
	/*
	COORD是Windows API中的一个结构体，表示一个字符在控制台屏幕上的坐标位置，包含如下两个值：
	X：表示字符在屏幕上的水平位置，从左到右从0开始计数。
	Y：表示字符在屏幕上的垂直位置，从上到下从0开始计数。
	*/
	ULONG unuse;		//ULONG是一种数据类型，用于表示无符号长整数（unsigned long）
	pos.X = x * 2;		//在默认情况下，控制台在水平方向上每个字符占据两个位置
	pos.Y = y;
	/*
		使用了Windows API函数WriteConsoleOutputCharacterW来将一个字符输出到控制台屏幕上的指定位置
		参数handle是一个表示已打开的控制台屏幕缓冲区的句柄
		&ch是一个指向要输出的字符的指针，
		1表示要输出的字符数，
		pos是一个COORD类型的变量，表示要输出字符的位置，
		&unuse是一个指向未使用的ULONG类型变量的指针，可以为NULL。
			&符号用于取变量的地址，不是引用。但在这个情况下，&unuse这个指针的实际作用是告诉函数WriteConsoleOutputCharacterW，
			我们并不需要使用这个指针所指向的变量的值，只是让编译器通过函数调用时传递一个无用的值
	*/
	WriteConsoleOutputCharacterW(handle, &ch, 1, pos, &unuse);	 //输出字符
	//调用了Windows API函数FillConsoleOutputAttribute，该函数用指定的颜色值填充控制台的字符格
	FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);   //设置颜色
}
//清除控制台的x,y处开始的length个字符
void ClearString(int x, int y, size_t length)  //size_t 一个无符号整数类型，通常用于表示对象大小或数量的值
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	FillConsoleOutputAttribute(handle, BLACK, static_cast<DWORD>(length),pos, &unuse);
}
//计算一个宽字节字符串的长度占用的半角字符数
size_t WcharStrHalfWidthLen(const wchar_t* str)
{
	size_t size{ 0 };
	const size_t length{ wcslen(str) };
	for (int i{ 0 }; i < length; i++)
	{
		if (str[i] >= 0 && str[i] < 128)
			size++;
		else
			size += 2;
	}
	return size;
}
//在x,y坐标处输一个字符串
void PrintString(const wchar_t* str, int x, int y,Color color)		
{
	COORD pos;					//COORD是Windows API中的一个结构体，表示一个字符在控制台屏幕上的坐标位置，包含如下两个值：
	ULONG unuse;				//定义整型变量，未被使用
	pos.X = x * 2;				//在默认情况下，控制台在水平方向上每个字符占据两个位置
	pos.Y = y;
	// 计算字符串长度
	size_t len{ wcslen(str) };	/*
								*len 是一个 size_t 类型的变量，
								*花括号 {} 标志着一个列表，将 wcslen(str) 的结果作为参数传递给变量 len 进行初始化
								*wcslen() 函数用于计算 Unicode 字符串中的字符数量，返回一个 size_t 类型的值
								*/
	size_t len_halfwidth{ WcharStrHalfWidthLen(str) };						// 计算字符串占用的半角字符数
	WriteConsoleOutputCharacterW(handle, str, static_cast<DWORD>(len), pos, &unuse);			//输出字符
	FillConsoleOutputAttribute(handle, color, static_cast<DWORD>(len_halfwidth), pos, &unuse);	//设置颜色
}

void PrintInt(int num,int x,short y ,Color color)
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	wchar_t str[20];
	str[19] = '\0';
	_itow_s(num, str, 10);
	size_t len{ wcslen(str) };
	WriteConsoleOutputCharacterW(handle, str, static_cast<DWORD>(len), pos, &unuse);			//输出字符
	FillConsoleOutputAttribute(handle, color, static_cast<DWORD>(len), pos, &unuse);	//设置颜色
}
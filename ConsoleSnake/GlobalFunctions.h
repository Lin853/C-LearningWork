/*
  ȫ�ֺ����Ķ���
*/
#pragma once
#include <iostream> 
#include<Windows.h>
#include <deque>
#include <conio.h>
#include "common.h"
#include <algorithm>





//������Windows API����GetStdHandle���ú����������ǻ�ȡ��ǰ���̵ı�׼����豸�ľ��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

//��x,y���괦���һ������
void PrintCell(int x, int y, Color color, wchar_t ch = CELL_SQUARE)			//wchar_t ���ֽ��ַ�����
{
	COORD pos;
	/*
	COORD��Windows API�е�һ���ṹ�壬��ʾһ���ַ��ڿ���̨��Ļ�ϵ�����λ�ã�������������ֵ��
	X����ʾ�ַ�����Ļ�ϵ�ˮƽλ�ã������Ҵ�0��ʼ������
	Y����ʾ�ַ�����Ļ�ϵĴ�ֱλ�ã����ϵ��´�0��ʼ������
	*/
	ULONG unuse;		//ULONG��һ���������ͣ����ڱ�ʾ�޷��ų�������unsigned long��
	pos.X = x * 2;		//��Ĭ������£�����̨��ˮƽ������ÿ���ַ�ռ������λ��
	pos.Y = y;
	/*
		ʹ����Windows API����WriteConsoleOutputCharacterW����һ���ַ����������̨��Ļ�ϵ�ָ��λ��
		����handle��һ����ʾ�Ѵ򿪵Ŀ���̨��Ļ�������ľ��
		&ch��һ��ָ��Ҫ������ַ���ָ�룬
		1��ʾҪ������ַ�����
		pos��һ��COORD���͵ı�������ʾҪ����ַ���λ�ã�
		&unuse��һ��ָ��δʹ�õ�ULONG���ͱ�����ָ�룬����ΪNULL��
			&��������ȡ�����ĵ�ַ���������á������������£�&unuse���ָ���ʵ�������Ǹ��ߺ���WriteConsoleOutputCharacterW��
			���ǲ�����Ҫʹ�����ָ����ָ��ı�����ֵ��ֻ���ñ�����ͨ����������ʱ����һ�����õ�ֵ
	*/
	WriteConsoleOutputCharacterW(handle, &ch, 1, pos, &unuse);	 //����ַ�
	//������Windows API����FillConsoleOutputAttribute���ú�����ָ������ɫֵ������̨���ַ���
	FillConsoleOutputAttribute(handle, color, 2, pos, &unuse);   //������ɫ
}
//�������̨��x,y����ʼ��length���ַ�
void ClearString(int x, int y, size_t length)  //size_t һ���޷����������ͣ�ͨ�����ڱ�ʾ�����С��������ֵ
{
	COORD pos;
	ULONG unuse;
	pos.X = x * 2;
	pos.Y = y;
	FillConsoleOutputAttribute(handle, BLACK, static_cast<DWORD>(length),pos, &unuse);
}
//����һ�����ֽ��ַ����ĳ���ռ�õİ���ַ���
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
//��x,y���괦��һ���ַ���
void PrintString(const wchar_t* str, int x, int y,Color color)		
{
	COORD pos;					//COORD��Windows API�е�һ���ṹ�壬��ʾһ���ַ��ڿ���̨��Ļ�ϵ�����λ�ã�������������ֵ��
	ULONG unuse;				//�������ͱ�����δ��ʹ��
	pos.X = x * 2;				//��Ĭ������£�����̨��ˮƽ������ÿ���ַ�ռ������λ��
	pos.Y = y;
	// �����ַ�������
	size_t len{ wcslen(str) };	/*
								*len ��һ�� size_t ���͵ı�����
								*������ {} ��־��һ���б��� wcslen(str) �Ľ����Ϊ�������ݸ����� len ���г�ʼ��
								*wcslen() �������ڼ��� Unicode �ַ����е��ַ�����������һ�� size_t ���͵�ֵ
								*/
	size_t len_halfwidth{ WcharStrHalfWidthLen(str) };						// �����ַ���ռ�õİ���ַ���
	WriteConsoleOutputCharacterW(handle, str, static_cast<DWORD>(len), pos, &unuse);			//����ַ�
	FillConsoleOutputAttribute(handle, color, static_cast<DWORD>(len_halfwidth), pos, &unuse);	//������ɫ
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
	WriteConsoleOutputCharacterW(handle, str, static_cast<DWORD>(len), pos, &unuse);			//����ַ�
	FillConsoleOutputAttribute(handle, color, static_cast<DWORD>(len), pos, &unuse);	//������ɫ
}
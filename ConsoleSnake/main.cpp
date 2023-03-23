#include "GlobalFunctions.h"
#include "Snake.h"
#include <iostream>
using namespace std;

int main() 
{
	Snake snake;													// ����Snake����
	snake.DramFram();												// ���Ʊ߿�
	snake.ShowInfo();												// ��ʾ��Ϸ��Ϣ
	snake.DrawSnake();												// ����̰����
	snake.DrawFood();												// ����ʳ��

	ULONGLONG temp_time = GetTickCount64();							// ��ȡ��ǰ����ʱ�䲢�洢�ڱ��� temp_time ��
	int ch = 72;
	while (ch != ESC_KEY)											// ���û�û�а��� ESC ��ʱ��ѭ����������
	{
		ULONGLONG current_time = GetTickCount64();					// ��ȡ��ǰ����ʱ�䣬��λ������
		if (current_time - temp_time >= snake.GetIntervalTime())	// ������ϴθ��µ�ʱ��������ָ����ʱ����
		{
			temp_time = current_time;								// ����ǰʱ�丳ֵ����һ�θ��µ�ʱ��
			snake.ClearSnake();										// ���������
			snake.SnakeForward();									// ��̰������ǰ�ƶ�һ��
			snake.DrawSnake();										// ����Ļ�����»���̰����
			snake.DrawFood();										// ����Ļ�ϻ����µ�ʳ��
		}
		if (snake.GameOver())										// ���̰�����Ѿ�����
		{
			PrintString(L"GAME OVER!!!", 6, 10, RED);				// ����Ļ�ϴ�ӡ "GAME OVER!!!"
			cin.get();												// �ȴ��û����������
			return 0;												// �˳�����
		}
		if (_kbhit())												// ����û������˼����ϵ�ĳ����
		{
			ch = _getch();											// ��ȡ�û�����
			snake.ClearSnake();										// ���������
			switch (ch)
			{
			case UP_KEY:											// ���������ƶ����߼�
				snake.MoveSnake(UP);
				break;
			case DOWN_KEY:											// ���������ƶ����߼�
				snake.MoveSnake(DOWN);
				break;
			case LEFT_KEY:											// ���������ƶ����߼�
				snake.MoveSnake(LEFT);
				break;
			case RIGHT_KEY:											// ���������ƶ����߼�
				snake.MoveSnake(RIGHT);
				break;
			default:												//����û���������������ִ���κβ���
				break;
			}
			snake.DrawSnake();										// ����̰����
		}
		if (snake.SnakeHitFood())
		{
			snake.SnakeEatFood();									// �������ӳ���
			snake.CreateFood();										// �����µ�ʳ��
			snake.DrawFood();										// �ڵ�ͼ�ϻ���ʳ��
			snake.DrawSnake();										// �ڵ�ͼ�ϻ�����
			snake.ShowInfo();										// �ڿ���̨����ߵĳ��Ⱥ͵÷���Ϣ
		}
	}
	return 0;
}


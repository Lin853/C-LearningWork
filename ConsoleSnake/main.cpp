#include "GlobalFunctions.h"
#include "Snake.h"
#include <iostream>
using namespace std;

int main() 
{
	Snake snake;													// 创建Snake对象
	snake.DramFram();												// 绘制边框
	snake.ShowInfo();												// 显示游戏信息
	snake.DrawSnake();												// 绘制贪吃蛇
	snake.DrawFood();												// 绘制食物

	ULONGLONG temp_time = GetTickCount64();							// 获取当前本地时间并存储在变量 temp_time 中
	int ch = 72;
	while (ch != ESC_KEY)											// 当用户没有按下 ESC 键时，循环处理输入
	{
		ULONGLONG current_time = GetTickCount64();					// 获取当前本地时间，单位：毫秒
		if (current_time - temp_time >= snake.GetIntervalTime())	// 如果与上次更新的时间间隔大于指定的时间间隔
		{
			temp_time = current_time;								// 将当前时间赋值给上一次更新的时间
			snake.ClearSnake();										// 清除蛇身体
			snake.SnakeForward();									// 将贪吃蛇向前移动一步
			snake.DrawSnake();										// 在屏幕上重新绘制贪吃蛇
			snake.DrawFood();										// 在屏幕上绘制新的食物
		}
		if (snake.GameOver())										// 如果贪吃蛇已经死亡
		{
			PrintString(L"GAME OVER!!!", 6, 10, RED);				// 在屏幕上打印 "GAME OVER!!!"
			cin.get();												// 等待用户按下任意键
			return 0;												// 退出程序
		}
		if (_kbhit())												// 如果用户按下了键盘上的某个键
		{
			ch = _getch();											// 获取用户输入
			snake.ClearSnake();										// 清除蛇身体
			switch (ch)
			{
			case UP_KEY:											// 处理向上移动的逻辑
				snake.MoveSnake(UP);
				break;
			case DOWN_KEY:											// 处理向下移动的逻辑
				snake.MoveSnake(DOWN);
				break;
			case LEFT_KEY:											// 处理向左移动的逻辑
				snake.MoveSnake(LEFT);
				break;
			case RIGHT_KEY:											// 处理向右移动的逻辑
				snake.MoveSnake(RIGHT);
				break;
			default:												//如果用户按下其他键，不执行任何操作
				break;
			}
			snake.DrawSnake();										// 绘制贪吃蛇
		}
		if (snake.SnakeHitFood())
		{
			snake.SnakeEatFood();									// 蛇身增加长度
			snake.CreateFood();										// 创建新的食物
			snake.DrawFood();										// 在地图上绘制食物
			snake.DrawSnake();										// 在地图上绘制蛇
			snake.ShowInfo();										// 在控制台输出蛇的长度和得分信息
		}
	}
	return 0;
}


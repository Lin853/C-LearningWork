#pragma once
/*
	定义蛇的参数
*/
#include "GlobalFunctions.h"


class Snake {
public:
	//定义了一个名为Point的类，它包含两个整型成员变量 x 和 y，用于表示一个平面上的点的横纵坐标
	class Point {
	public:
		int x;
		int y;
		//构造函数，初始化Point类型的对象
		Point(int _x, int _y) 
			:x(_x),y(_y)
		{}
		//构造函数，初始化Point类型的对象为0
		Point()
			:x(0),y(0)
		{}
		//成员函数，重载了"=="运算符，用于判断两个Point对象是否相等
		bool operator==(Point point) const
		{
			return x == point.x && y == point.y;
		}
	};
private:
	//定义了一个deque类型变量m_snake，其中存储了Point类型的元素。
	//deque是双端队列（double-ended queue）的缩写，是一种和vector类似的容器，可以在队列头和队列尾快速地添加和删除元素。
	std::deque<Point> m_snake;     //储存蛇身体的每个点的坐标
	Direction m_direction;         //蛇当前前进方向
	Point m_food;                  //食物坐标
	Point m_last_tail;             //蛇在上一个位置时尾部的坐标
	int m_score;				   //分数
	int m_level;				   //等级
public:
	Snake();
	void SnakeForward();            // 蛇前进
	bool GameOver()  const;               //游戏结束

	void DrawSnake() const;               //绘制蛇身体
	void ClearSnake() const;              //清除蛇身体
	void MoveSnake(Direction direction); //蛇移动

	bool CreateFood();               //生成食物
	void DrawFood();                //绘制食物
	void ClearFood();               //清除食物

	bool SnakeHitFood();            //判断蛇是否碰到食物
	void SnakeEatFood();            //蛇吃到食物
	int GetIntervalTime() const;    //根据当前等级计算间隔时间（单位：ms）

	void DramFram() const;	        //绘制边框
	void ShowInfo() const;	        //显示游戏信息

	static wchar_t CheckPointsShape(Point last, Point current, Point next); //判断三个点的形状,wchar_t 是一种C++中的字符类型，用于存储Unicode字符
	static wchar_t CheckPointShape(Point last, Point current);              //两个个点的形状
	bool IsPointInSnake(const Point& point, bool exculude_head = false) const;  //判断一个点是否位于蛇的身体中，exclude_head：是否排除头部
};	
//Snake::Snake() 构造函数的实现
Snake::Snake()
{
	system("mode con:cols = 64 lines = 27");     //函数将控制台的列数和行数分别设置为64和27
	m_snake.clear();							//清除蛇身开始时的所有坐标
	m_snake.emplace_back(10, 9);				//将新的蛇头和蛇身添加到 m_snake 向量中
	m_snake.emplace_back(10, 10);				
	m_snake.emplace_back(10, 11);
	m_direction = UP;							//设置蛇开始移动的方向为 UP
	CreateFood();								//调用类的一个方法 CreateFood(),用于在游戏画面上随机创建食物
}
//蛇前进
void Snake::SnakeForward()
{
	Point point;							//首先创建一个空的 Point 对象 point
	switch (m_direction)					//switch 语句根据当前方向指定 point 的新位置
	{	
	case UP:
		point.x = m_snake.front().x;
		point.y = m_snake.front().y - 1;
		break;
	case DOWN:
		point.x = m_snake.front().x;
		point.y = m_snake.front().y + 1;
		break;
	case RIGHT:
		point.x = m_snake.front().x + 1;
		point.y = m_snake.front().y;
		break;
	case LEFT:
		point.x = m_snake.front().x - 1;
		point.y = m_snake.front().y;
		break;
	default:
		break;
	}
	m_snake.push_front(point);				//把 point 对象添加到 m_snake 双端队列的头部，即成为新的蛇头。
	m_last_tail = m_snake.back();			//把当前双端队列的末尾元素，即原来的蛇尾的坐标值保存在 m_last_tail 变量
	m_snake.pop_back();						//删除队列的末尾元素，即原来的蛇尾，以保证蛇的长度不变
}
//游戏结束
bool Snake::GameOver() const
{
	if (m_snake.front().x >= WIDTH || m_snake.front().y >= HIGHT || m_snake.front().x < 0 || m_snake.front().y < 0) 
		//蛇的头碰到了边框，则游戏结束
		return true;
	if (IsPointInSnake(m_snake.front(), true)) 
		//蛇的头碰到了身体，则游戏结束
		return true;
	return false;
}
//绘制蛇身体
void Snake::DrawSnake() const
{
	// 用迭代器遍历蛇的每个点
	for (auto iter = m_snake.begin(); iter != m_snake.end(); iter++)
	{
		Point cur_point = *iter;
		if (cur_point == m_snake.front())    // 如果是蛇头
		{
			PrintCell(cur_point.x + BOARD_X, cur_point.y + BOARD_Y, RED);// 绘制为红色
		}
		else                                 // 如果是身体
		{
			Point last_point = *(iter - 1);		// 找到前一个点
			wchar_t ch = CELL_SQUARE;			// 初始为方块形状
			if (iter != m_snake.end() - 1)		// 如果不是最后一个点
			{
				Point next_point = *(iter + 1);  // 找到下一个点
				ch = CheckPointsShape(last_point, cur_point, next_point);//判断三个点的形状
			}
			else
			{
				ch = CheckPointShape(last_point, cur_point); //判断三个点的形状
			}
			PrintCell(cur_point.x + BOARD_X, cur_point.y + BOARD_Y , CYAN,ch); // 绘制该点
		}
	}
}
//清除蛇身体
void Snake::ClearSnake() const
{
	for (auto& point : m_snake)		//(循环变量 : 遍历对象),m_snake 容器中的每个元素
	{
		ClearString(point.x + BOARD_X, point.y + BOARD_Y, 2);
	}
}
//蛇移动
void Snake::MoveSnake(Direction direction)
{
	switch (direction)
		//如果新方向和当前方向相反，则返回并不执行移动操作
	{	
	case UP:
			if (m_direction  == DOWN) {return;}	//执行 return; 是跳出函数 MoveSnake()
			break;								//当执行 break; 时，会跳出当前的 switch 语句
	case DOWN:
			if (m_direction  == UP)   {return;}
			break;			
	case LEFT:
			if (m_direction  == RIGHT){return;}
			break;			
	case RIGHT:
			if (m_direction  == LEFT)  {return;}
			break;	
	}	
	m_direction = direction;
	SnakeForward();				//蛇前进
	//Sleep(Snake::GetIntervalTime());
}
//生成食物
bool Snake::CreateFood()
{
	if (m_snake.size() >= WIDTH * HIGHT)			//当蛇身体长度大于或等于界面格子数时无法生成食物，返回false
		return false;
	int cell_num = static_cast<int>(WIDTH * HIGHT - m_snake.size()); // 合理的食物位置数量
	//生成食物位置的索引
	SYSTEMTIME current_time;						//创建 SYSTEMTIME 类型的 current_time 变量，用于存储获取到的当前时间
	GetLocalTime(&current_time);					//获取当前时间
	srand(current_time.wMilliseconds);				//用当前时间的毫秒数设置产生随机数的种子
	int food_index = rand() % cell_num;				//生成介于0到(cell_num - 1)之间的随机整数

	int cur_index = -1;								//初始化当前索引为-1
	//计算可用的格子中第food_index个格子的位置
	for (int i = 0; i < WIDTH; i++)					//遍历游戏棋盘的每一行
	{
		for (int j = 0; j < HIGHT; j++)				//遍历游戏棋盘的每一列
		{
			if (!IsPointInSnake(Point(i, j)))		//如果当前探索到的这个格子不在蛇体内（即不是蛇的一部分）
				cur_index++;
			if (cur_index >= food_index)			//如果当前索引已经达到了随机生成的食物索引
			{
				m_food = Point(i, j);				//找到了对应的位置，将其记录到m_food中
				return true;						//返回true，表示成功生成了食物
			}
		}
	}
	return 0;
}
//绘制食物
void Snake::DrawFood() 
{
	PrintCell(m_food.x + BOARD_X, m_food.y + BOARD_Y, YELLOW);
}
//清除食物
void Snake::ClearFood()
{
	ClearString(m_food.x + BOARD_X, m_food.y + BOARD_Y, 2);
}
//判断蛇是否碰到食物
bool Snake::SnakeHitFood()
{
	return m_snake.front() == m_food;
}
//蛇吃到食物
void Snake::SnakeEatFood()
{
	m_snake.push_back(m_last_tail);
	m_score++;
	m_level = m_score / 20 + 1;
}
//根据当前等级计算间隔时间（单位：ms）
int  Snake::GetIntervalTime() const
{
	switch (m_level)
	{	
	case 1:return 1000;
	case 2:return 800;
	case 3:return 650;
	case 4:return 500;
	case 5:return 400;
	case 6:return 320;
	case 7:return 250;
	case 8:return 190;
	default:return 1000;

	}
}
//绘制边框
void Snake::DramFram() const
{
	//绘制上下边界
	for (int i{0}; i < (WIDTH + 1); i++)
	{
		PrintString(L"▓", i, BOARD_Y - 1, GRAY);
		PrintString(L"▓", i, BOARD_Y + HIGHT, GRAY);
	}
	//绘制左右边界
	for (int i{2 }; i < (HIGHT + 4); i++)
	{
		PrintString(L"▓", BOARD_X - 1, i, GRAY);
		PrintString(L"▓", BOARD_X + WIDTH, i, GRAY);
	}
}
//显示游戏信息
void Snake::ShowInfo() const
{
	PrintString(L"贪吃蛇 V0.1", 0, 0, WHITE);
	PrintString(L"得分：", 0, 1, WHITE);
	PrintInt(m_score, 3, 1, CYAN);
	PrintString(L"等级：", 6, 1, WHITE);
	PrintInt(m_level, 9, 1, CYAN);
}


//判断三个点的形状,wchar_t 是一种C++中的字符类型，用于存储Unicode字符
wchar_t Snake::CheckPointsShape(Point last, Point current, Point next)
{
	//计算3个点最小x和y坐标
	int min_x = min(min(last.x, current.x), next.x);
	int min_y = min(min(last.y, current.y), next.y);
	//将3个点移动到最靠近原点的位置
	last.x -= min_x;
	last.y -= min_y;
	current.x -= min_x;
	current.y -= min_y;
	next.x -= min_x;
	next.y -= min_y;
	//判断3个点的形状
	if (last.y == 0 && current.y == 0 && next.y == 0)
		return CELL_H;	
	else if (last.x == 0 && current.x == 0 && next.x == 0)
		return CELL_V;
	else if ((last == Point(1, 0) && current == Point(0, 0) && next == Point(0, 1)) || (next == Point(1, 0) && current == Point(0, 0) && last == Point(0, 1)))
		return CELL_TL;
	else if ((last == Point(0, 0) && current == Point(1, 0) && next == Point(1, 1)) || (next == Point(0, 0) && current == Point(1, 0) && last == Point(1, 1)))
		return CELL_TR;
	else if ((last == Point(0, 0) && current == Point(0, 1) && next == Point(1, 1)) || (next == Point(0, 0) && current == Point(0, 1) && last == Point(1, 1)))
		return CELL_BL;
	else if ((last == Point(1, 0) && current == Point(1, 1) && next == Point(0, 1)) || (next == Point(1, 0) && current == Point(1, 1) && last == Point(0, 1)))
		return CELL_BR;
	else return CELL_SQUARE;
}
//判断两个点的形状
wchar_t Snake::CheckPointShape(Point last, Point current)
{
	int min_x = min(last.x, current.x);
	int min_y = min(last.y, current.y);

	last.x -= min_x;
	last.y -= min_y;
	current.x -= min_x;
	current.y -= min_y;

	if (last.y == 0 && current.y == 0)
		return CELL_H;
	else if (last.x == 0 && current.x == 0)
		return CELL_V;
	else
		return CELL_SQUARE;
}

bool Snake::IsPointInSnake(const Point& point, bool exculude_head) const  //判断一个点是否位于蛇的身体中，exclude_head：是否排除头部
{
		auto iter = (exculude_head ? m_snake.begin() + 1 : m_snake.begin());
		for (; iter != m_snake.end(); ++iter)
		{
			if (*iter == point)
			{
				return true;
			}
		}
		return false;
}
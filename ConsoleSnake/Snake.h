#pragma once
/*
	�����ߵĲ���
*/
#include "GlobalFunctions.h"


class Snake {
public:
	//������һ����ΪPoint���࣬�������������ͳ�Ա���� x �� y�����ڱ�ʾһ��ƽ���ϵĵ�ĺ�������
	class Point {
	public:
		int x;
		int y;
		//���캯������ʼ��Point���͵Ķ���
		Point(int _x, int _y) 
			:x(_x),y(_y)
		{}
		//���캯������ʼ��Point���͵Ķ���Ϊ0
		Point()
			:x(0),y(0)
		{}
		//��Ա������������"=="������������ж�����Point�����Ƿ����
		bool operator==(Point point) const
		{
			return x == point.x && y == point.y;
		}
	};
private:
	//������һ��deque���ͱ���m_snake�����д洢��Point���͵�Ԫ�ء�
	//deque��˫�˶��У�double-ended queue������д����һ�ֺ�vector���Ƶ������������ڶ���ͷ�Ͷ���β���ٵ���Ӻ�ɾ��Ԫ�ء�
	std::deque<Point> m_snake;     //�����������ÿ���������
	Direction m_direction;         //�ߵ�ǰǰ������
	Point m_food;                  //ʳ������
	Point m_last_tail;             //������һ��λ��ʱβ��������
	int m_score;				   //����
	int m_level;				   //�ȼ�
public:
	Snake();
	void SnakeForward();            // ��ǰ��
	bool GameOver()  const;               //��Ϸ����

	void DrawSnake() const;               //����������
	void ClearSnake() const;              //���������
	void MoveSnake(Direction direction); //���ƶ�

	bool CreateFood();               //����ʳ��
	void DrawFood();                //����ʳ��
	void ClearFood();               //���ʳ��

	bool SnakeHitFood();            //�ж����Ƿ�����ʳ��
	void SnakeEatFood();            //�߳Ե�ʳ��
	int GetIntervalTime() const;    //���ݵ�ǰ�ȼ�������ʱ�䣨��λ��ms��

	void DramFram() const;	        //���Ʊ߿�
	void ShowInfo() const;	        //��ʾ��Ϸ��Ϣ

	static wchar_t CheckPointsShape(Point last, Point current, Point next); //�ж����������״,wchar_t ��һ��C++�е��ַ����ͣ����ڴ洢Unicode�ַ�
	static wchar_t CheckPointShape(Point last, Point current);              //�����������״
	bool IsPointInSnake(const Point& point, bool exculude_head = false) const;  //�ж�һ�����Ƿ�λ���ߵ������У�exclude_head���Ƿ��ų�ͷ��
};	
//Snake::Snake() ���캯����ʵ��
Snake::Snake()
{
	system("mode con:cols = 64 lines = 27");     //����������̨�������������ֱ�����Ϊ64��27
	m_snake.clear();							//�������ʼʱ����������
	m_snake.emplace_back(10, 9);				//���µ���ͷ��������ӵ� m_snake ������
	m_snake.emplace_back(10, 10);				
	m_snake.emplace_back(10, 11);
	m_direction = UP;							//�����߿�ʼ�ƶ��ķ���Ϊ UP
	CreateFood();								//�������һ������ CreateFood(),��������Ϸ�������������ʳ��
}
//��ǰ��
void Snake::SnakeForward()
{
	Point point;							//���ȴ���һ���յ� Point ���� point
	switch (m_direction)					//switch �����ݵ�ǰ����ָ�� point ����λ��
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
	m_snake.push_front(point);				//�� point ������ӵ� m_snake ˫�˶��е�ͷ��������Ϊ�µ���ͷ��
	m_last_tail = m_snake.back();			//�ѵ�ǰ˫�˶��е�ĩβԪ�أ���ԭ������β������ֵ������ m_last_tail ����
	m_snake.pop_back();						//ɾ�����е�ĩβԪ�أ���ԭ������β���Ա�֤�ߵĳ��Ȳ���
}
//��Ϸ����
bool Snake::GameOver() const
{
	if (m_snake.front().x >= WIDTH || m_snake.front().y >= HIGHT || m_snake.front().x < 0 || m_snake.front().y < 0) 
		//�ߵ�ͷ�����˱߿�����Ϸ����
		return true;
	if (IsPointInSnake(m_snake.front(), true)) 
		//�ߵ�ͷ���������壬����Ϸ����
		return true;
	return false;
}
//����������
void Snake::DrawSnake() const
{
	// �õ����������ߵ�ÿ����
	for (auto iter = m_snake.begin(); iter != m_snake.end(); iter++)
	{
		Point cur_point = *iter;
		if (cur_point == m_snake.front())    // �������ͷ
		{
			PrintCell(cur_point.x + BOARD_X, cur_point.y + BOARD_Y, RED);// ����Ϊ��ɫ
		}
		else                                 // ���������
		{
			Point last_point = *(iter - 1);		// �ҵ�ǰһ����
			wchar_t ch = CELL_SQUARE;			// ��ʼΪ������״
			if (iter != m_snake.end() - 1)		// ����������һ����
			{
				Point next_point = *(iter + 1);  // �ҵ���һ����
				ch = CheckPointsShape(last_point, cur_point, next_point);//�ж����������״
			}
			else
			{
				ch = CheckPointShape(last_point, cur_point); //�ж����������״
			}
			PrintCell(cur_point.x + BOARD_X, cur_point.y + BOARD_Y , CYAN,ch); // ���Ƹõ�
		}
	}
}
//���������
void Snake::ClearSnake() const
{
	for (auto& point : m_snake)		//(ѭ������ : ��������),m_snake �����е�ÿ��Ԫ��
	{
		ClearString(point.x + BOARD_X, point.y + BOARD_Y, 2);
	}
}
//���ƶ�
void Snake::MoveSnake(Direction direction)
{
	switch (direction)
		//����·���͵�ǰ�����෴���򷵻ز���ִ���ƶ�����
	{	
	case UP:
			if (m_direction  == DOWN) {return;}	//ִ�� return; ���������� MoveSnake()
			break;								//��ִ�� break; ʱ����������ǰ�� switch ���
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
	SnakeForward();				//��ǰ��
	//Sleep(Snake::GetIntervalTime());
}
//����ʳ��
bool Snake::CreateFood()
{
	if (m_snake.size() >= WIDTH * HIGHT)			//�������峤�ȴ��ڻ���ڽ��������ʱ�޷�����ʳ�����false
		return false;
	int cell_num = static_cast<int>(WIDTH * HIGHT - m_snake.size()); // �����ʳ��λ������
	//����ʳ��λ�õ�����
	SYSTEMTIME current_time;						//���� SYSTEMTIME ���͵� current_time ���������ڴ洢��ȡ���ĵ�ǰʱ��
	GetLocalTime(&current_time);					//��ȡ��ǰʱ��
	srand(current_time.wMilliseconds);				//�õ�ǰʱ��ĺ��������ò��������������
	int food_index = rand() % cell_num;				//���ɽ���0��(cell_num - 1)֮����������

	int cur_index = -1;								//��ʼ����ǰ����Ϊ-1
	//������õĸ����е�food_index�����ӵ�λ��
	for (int i = 0; i < WIDTH; i++)					//������Ϸ���̵�ÿһ��
	{
		for (int j = 0; j < HIGHT; j++)				//������Ϸ���̵�ÿһ��
		{
			if (!IsPointInSnake(Point(i, j)))		//�����ǰ̽������������Ӳ��������ڣ��������ߵ�һ���֣�
				cur_index++;
			if (cur_index >= food_index)			//�����ǰ�����Ѿ��ﵽ��������ɵ�ʳ������
			{
				m_food = Point(i, j);				//�ҵ��˶�Ӧ��λ�ã������¼��m_food��
				return true;						//����true����ʾ�ɹ�������ʳ��
			}
		}
	}
	return 0;
}
//����ʳ��
void Snake::DrawFood() 
{
	PrintCell(m_food.x + BOARD_X, m_food.y + BOARD_Y, YELLOW);
}
//���ʳ��
void Snake::ClearFood()
{
	ClearString(m_food.x + BOARD_X, m_food.y + BOARD_Y, 2);
}
//�ж����Ƿ�����ʳ��
bool Snake::SnakeHitFood()
{
	return m_snake.front() == m_food;
}
//�߳Ե�ʳ��
void Snake::SnakeEatFood()
{
	m_snake.push_back(m_last_tail);
	m_score++;
	m_level = m_score / 20 + 1;
}
//���ݵ�ǰ�ȼ�������ʱ�䣨��λ��ms��
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
//���Ʊ߿�
void Snake::DramFram() const
{
	//�������±߽�
	for (int i{0}; i < (WIDTH + 1); i++)
	{
		PrintString(L"��", i, BOARD_Y - 1, GRAY);
		PrintString(L"��", i, BOARD_Y + HIGHT, GRAY);
	}
	//�������ұ߽�
	for (int i{2 }; i < (HIGHT + 4); i++)
	{
		PrintString(L"��", BOARD_X - 1, i, GRAY);
		PrintString(L"��", BOARD_X + WIDTH, i, GRAY);
	}
}
//��ʾ��Ϸ��Ϣ
void Snake::ShowInfo() const
{
	PrintString(L"̰���� V0.1", 0, 0, WHITE);
	PrintString(L"�÷֣�", 0, 1, WHITE);
	PrintInt(m_score, 3, 1, CYAN);
	PrintString(L"�ȼ���", 6, 1, WHITE);
	PrintInt(m_level, 9, 1, CYAN);
}


//�ж����������״,wchar_t ��һ��C++�е��ַ����ͣ����ڴ洢Unicode�ַ�
wchar_t Snake::CheckPointsShape(Point last, Point current, Point next)
{
	//����3������Сx��y����
	int min_x = min(min(last.x, current.x), next.x);
	int min_y = min(min(last.y, current.y), next.y);
	//��3�����ƶ������ԭ���λ��
	last.x -= min_x;
	last.y -= min_y;
	current.x -= min_x;
	current.y -= min_y;
	next.x -= min_x;
	next.y -= min_y;
	//�ж�3�������״
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
//�ж����������״
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

bool Snake::IsPointInSnake(const Point& point, bool exculude_head) const  //�ж�һ�����Ƿ�λ���ߵ������У�exclude_head���Ƿ��ų�ͷ��
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
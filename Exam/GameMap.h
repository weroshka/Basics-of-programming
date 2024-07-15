#pragma once

#include <vector>
#include <algorithm>

struct Vector2
{
	int x, 
		y;
};

class GameMap
{
public:
	GameMap(); //конструктор
	GameMap(Vector2, int); //конструктор 
	GameMap(int, int, int); //конструктор
	~GameMap(); //деструктор

	bool SetPosition(Vector2, int); //задать позицию
	bool IsEmpty(Vector2); //проверка на свободную ячейку
	bool IsEmpty(int,int); //проверка на свободную ячейку
	void SetMap(Vector2, int);
	void SetMap(int, int,int);
	int GetValue(Vector2);
	int GetValue(int,int);
	int GetLength() { return length; };
	Vector2 GetSize() { return size; };
	int CheckList(std::vector<int> a);
	int CheckingWin();
	bool CanMove();
	Vector2 GetCenter();


private:
	int** map; //матрица предоставления карты в виде двумерного массива
	Vector2 size; //вектор, чтобы указать размерность матрицы
	int length; //необходимая длина выигрышной последовательности
};


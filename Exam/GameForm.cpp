#include "GameForm.h"
#include "StartForm.h"

enum GameMode
{
	PvP = 0, //игрок против игрока
	PvE //игрок против ПК
} gameMode;

//Общие данные 
GameMap map;
Gamer player1;
Gamer player2;
GamerStatus currentPlayer;
Vector2 selectedCellPlayer;

//Флажки 
bool canPlay;
bool endGame;
bool sound;
//Данные для ПК
std::vector<Vector2> allMoves; //все возможные ходы
int currentMoves; // текущий ход, с к-ого начинать

System::Void tictactoe::GameForm::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	auto senderGrid = (DataGridView^)sender; //преобразуем полученный лбъект в таблицу

	//Запоминаем индексы выбранной ячейки
	selectedCellPlayer.x = e->RowIndex;
	selectedCellPlayer.y = e->ColumnIndex;

	//Делаем ход
	SetPositionPlayer(selectedCellPlayer);
}

System::Void tictactoe::GameForm::GameForm_Load(System::Object^ sender, System::EventArgs^ e)
{ 
	//Инициализируем параметры
	if (selectedGameMode == 0)
	{
		gameMode = PvP;
	}
	else
		gameMode = PvE;

	//Инициализация звуков
	//soundClick = gcnew System::Media::SoundPlayer("..\\Resources\\1.wav");
	//soundEndGame = gcnew System::Media::SoundPlayer("..\\Resources\\2.wav");
	//sound = true;

	NewGame();
}

System::Void tictactoe::GameForm::новаяИграToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();
	if (MessageBox::Show("Продолжить?", "Внимание!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
		NewGame();
}

System::Void tictactoe::GameForm::вернутьсяToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	if (MessageBox::Show("Продолжить?", "Внимание!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
	{
		StartForm^ form = gcnew StartForm();
		form->Show();
		this->Hide();
	}
}

System::Void tictactoe::GameForm::вклВыклЗвукToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	//sound = !sound;
}

System::Void tictactoe::GameForm::оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	MessageBox::Show("Программа реализует игру Крестики-Нолики стандартного типа для 2 игроков и против компьютера");
}

System::Void tictactoe::GameForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	if (MessageBox::Show("Продолжить?", "Внимание!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
		Application::Exit();
}

void tictactoe::GameForm::GameLogic()
{
	//Проверяем режим игры
	if (gameMode == PvE)
	{
		if (currentPlayer == Computer)
		{
			//Делаем ход
			StepAI();
		}
		Update();
	}
}

void tictactoe::GameForm::Update()
{
	if (endGame)
		return;

	int state_game = map.CheckingWin();

	if (state_game == 1)
	{
		if (gameMode == PvP)
		{
			MessageBox::Show("Поздравляем Игрока1 с победой!!!", "Победа!!!");
		}
		else
			MessageBox::Show("Поздравляем Игрока1 с победой!!!", "Победа!!!");
		UpdateGameGrid();
		endGame = true;
	}

	if (state_game == 2)
	{
		if (gameMode == PvP)
		{
			MessageBox::Show("Поздравляем Игрока2 с победой!!!", "Победа!!!");
		}
		else
			MessageBox::Show("Поздравляем Компьютер с победой!!!", "Победа!!!");
		UpdateGameGrid();
		endGame = true;
	}

	if (state_game == 3)
	{
		MessageBox::Show("Победила дружба!!!", "Ничья!!!");
	
		UpdateGameGrid();
		endGame = true;
	}

	if (endGame)
	{
		//if (sound)
			//soundEndGame->Play();
		if (MessageBox::Show("Запустить новую игру?", "Внимание!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
		{
			NewGame();
		}
		return;
	}

	if (gameMode == PvE)
	{
		if (currentPlayer == Computer)
		{
			status->Text = "Ход: Игрока!";
			currentPlayer = Player;
			return;
		}
		else
		{
			status->Text = "Ход: Компьютера!";
			currentPlayer = Computer;

			GameLogic();
			UpdateGameGrid();
			return;
		}
	}

	else
	{
		if (currentPlayer == Player1)
		{
			status->Text = "Ход: 0!";
			currentPlayer = Player2;
		}
		else
		{
			status->Text = "Ход: Х!";
			currentPlayer = Player1;
		}
	}

	GameLogic();
	UpdateGameGrid();
}

void tictactoe::GameForm::NewGame()
{
	//Инициализация данных
	map.SetMap(rows, columns, lenghth);
	rand = gcnew Random();
	endGame = false;

	CreateGameGrid(map.GetSize()); //создаем игровое поле

	currentMoves = 0;
	allMoves.clear();
	Vector2 buf;

	//Инициализируем все возможные ходы для AI
	for (int i = 0; i < map.GetSize().x; i++)
	{
		for (int j = 0; j < map.GetSize().x; j++)
		{
			buf.x = i;
			buf.y = j;

			allMoves.push_back(buf);
		}
	}

	//Перемешиваем все возможные ходы несколько раз
	int num_mixing = rand->Next(1, 10);
	for (int i = 0; i < num_mixing; i++)
		std::random_shuffle(allMoves.begin(), allMoves.end());

	//Проверяем очередность и режим игры
	int state_gamer = rand->Next(1, 3);
	if (state_gamer == 1)
	{
		if (gameMode == PvE)
		{
			player1.SetField(Player, 1);
			player2.SetField(Computer, 2);

			status->Text = "Ход: Игрока!";

			currentPlayer = Player;
		}
		else
		{
			player1.SetField(Player1, 1);
			player2.SetField(Player2, 2);

			status->Text = "Ход: X!";

			currentPlayer = Player1;
		}
	}

	else if (state_gamer == 2)
	{
		if (gameMode == PvE)
		{
			player1.SetField(Player, 1);
			player2.SetField(Computer, 2);

			status->Text = "Ход: Компьютера!";

			currentPlayer = Computer;

			GameLogic();
			UpdateGameGrid();
		}

		else
		{
			player1.SetField(Player1, 1);
			player2.SetField(Player2, 2);

			status->Text = "Ход: 0!";

			currentPlayer = Player2;
		}
	}

	else
	{
		MessageBox::Show("Ошибка генерации первоначального выбора игрока!", "Ошибка!");
		return;
	}
}

void tictactoe::GameForm::StepAI()
{
	//Проверяем,есть ли еще ходы
	if (currentMoves < allMoves.size())
	{
		//Проверяем текущий ход
		if (map.IsEmpty(allMoves[currentMoves]))
		{
			//Если свободно, делаем ход
		
			map.SetPosition(allMoves[currentMoves], player2.GetMark());
			currentMoves++;
		}

		else
		{
			//если занята, перемещаемся на след ход
			// и вызываем рекурсивно данную функцию
			currentMoves++;
			StepAI();
		}
	}
}

void tictactoe::GameForm::UpdateGameGrid()
{
	for (int i = 0; i < map.GetSize().x; i++)
	{
		for (int j = 0; j < map.GetSize().y; j++)
		{
			if (!map.IsEmpty(i, j))
			{
				if (map.GetValue(i, j) == 1)
				{
					dataGridView->Rows[i]->Cells[j]->Value = "X";
				}
				else
					dataGridView->Rows[i]->Cells[j]->Value = "0";
			}
		}
	}
}

void tictactoe::GameForm::CreateGameGrid(Vector2 size)
{
	//Очищаем таблицу
	dataGridView->Rows->Clear();
	dataGridView->Columns->Clear();

	//Задаем стиль
	System::Drawing::Font^ font = gcnew System::Drawing::Font("Microsoft Sans Serif", 14);
	dataGridView->DefaultCellStyle->Font = font;
	dataGridView->ColumnHeadersDefaultCellStyle->Font = font;
	dataGridView->RowHeadersDefaultCellStyle->Font = font;

	//Создаем столбцы
	for (int i = 0; i < size.x; i++)
	{
		DataGridViewButtonColumn^ column = gcnew DataGridViewButtonColumn();
		column->HeaderCell->Value = Convert::ToString(i + 1);
		column->Name = "column" + i;
		column->Width = 50;

		dataGridView->Columns->Add(column);
	}

	//Создаем строки
	for (int i = 0; i < size.y; i++)
	{
		dataGridView->Rows->Add();
		dataGridView->Rows[i]->HeaderCell->Value = Convert::ToString(i + 1);
		dataGridView->Rows[i]->Height = 50;
	}
}

System::Void tictactoe::GameForm::SetPositionPlayer(Vector2 cell)
{
	//Проверяем режим игры
	if (gameMode == PvE)
	{
		//Проверяем очередность игрока
		if (currentPlayer == Player)
		{
			//Делаем ход
			if (!map.SetPosition(cell, player1.GetMark()))
			{
				MessageBox::Show("Данная позиция занята!", "Внимание!");
				return;
			}
		}
		else
		{
			MessageBox::Show("Еще не ваша очередь!", "Внимание!");
			return;
		}
	}
	else
	{
		//Проверяем очередь игрока
		if (currentPlayer == Player1)
		{
			//Делаем ход
			if (!map.SetPosition(cell, player1.GetMark()))
			{
				MessageBox::Show("Данная позиция занята!", "Внимание!");
				return;
			}
		}
		else
		{
			//Делаем ход
			if (!map.SetPosition(cell, player2.GetMark()))
			{
				MessageBox::Show("Данная позиция занята!", "Внимание!");
				return;
			}
		}
	}
	Update();
}

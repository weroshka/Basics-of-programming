#include "GameForm.h"
#include "StartForm.h"

enum GameMode
{
	PvP = 0, //����� ������ ������
	PvE //����� ������ ��
} gameMode;

//����� ������ 
GameMap map;
Gamer player1;
Gamer player2;
GamerStatus currentPlayer;
Vector2 selectedCellPlayer;

//������ 
bool canPlay;
bool endGame;
bool sound;
//������ ��� ��
std::vector<Vector2> allMoves; //��� ��������� ����
int currentMoves; // ������� ���, � �-��� ��������

System::Void tictactoe::GameForm::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	auto senderGrid = (DataGridView^)sender; //����������� ���������� ������ � �������

	//���������� ������� ��������� ������
	selectedCellPlayer.x = e->RowIndex;
	selectedCellPlayer.y = e->ColumnIndex;

	//������ ���
	SetPositionPlayer(selectedCellPlayer);
}

System::Void tictactoe::GameForm::GameForm_Load(System::Object^ sender, System::EventArgs^ e)
{ 
	//�������������� ���������
	if (selectedGameMode == 0)
	{
		gameMode = PvP;
	}
	else
		gameMode = PvE;

	//������������� ������
	//soundClick = gcnew System::Media::SoundPlayer("..\\Resources\\1.wav");
	//soundEndGame = gcnew System::Media::SoundPlayer("..\\Resources\\2.wav");
	//sound = true;

	NewGame();
}

System::Void tictactoe::GameForm::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();
	if (MessageBox::Show("����������?", "��������!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
		NewGame();
}

System::Void tictactoe::GameForm::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	if (MessageBox::Show("����������?", "��������!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
	{
		StartForm^ form = gcnew StartForm();
		form->Show();
		this->Hide();
	}
}

System::Void tictactoe::GameForm::�����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	//sound = !sound;
}

System::Void tictactoe::GameForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	MessageBox::Show("��������� ��������� ���� ��������-������ ������������ ���� ��� 2 ������� � ������ ����������");
}

System::Void tictactoe::GameForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	//if (sound)
		//soundClick->Play();

	if (MessageBox::Show("����������?", "��������!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
		Application::Exit();
}

void tictactoe::GameForm::GameLogic()
{
	//��������� ����� ����
	if (gameMode == PvE)
	{
		if (currentPlayer == Computer)
		{
			//������ ���
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
			MessageBox::Show("����������� ������1 � �������!!!", "������!!!");
		}
		else
			MessageBox::Show("����������� ������1 � �������!!!", "������!!!");
		UpdateGameGrid();
		endGame = true;
	}

	if (state_game == 2)
	{
		if (gameMode == PvP)
		{
			MessageBox::Show("����������� ������2 � �������!!!", "������!!!");
		}
		else
			MessageBox::Show("����������� ��������� � �������!!!", "������!!!");
		UpdateGameGrid();
		endGame = true;
	}

	if (state_game == 3)
	{
		MessageBox::Show("�������� ������!!!", "�����!!!");
	
		UpdateGameGrid();
		endGame = true;
	}

	if (endGame)
	{
		//if (sound)
			//soundEndGame->Play();
		if (MessageBox::Show("��������� ����� ����?", "��������!", MessageBoxButtons::YesNo) == Windows::Forms::DialogResult::Yes)
		{
			NewGame();
		}
		return;
	}

	if (gameMode == PvE)
	{
		if (currentPlayer == Computer)
		{
			status->Text = "���: ������!";
			currentPlayer = Player;
			return;
		}
		else
		{
			status->Text = "���: ����������!";
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
			status->Text = "���: 0!";
			currentPlayer = Player2;
		}
		else
		{
			status->Text = "���: �!";
			currentPlayer = Player1;
		}
	}

	GameLogic();
	UpdateGameGrid();
}

void tictactoe::GameForm::NewGame()
{
	//������������� ������
	map.SetMap(rows, columns, lenghth);
	rand = gcnew Random();
	endGame = false;

	CreateGameGrid(map.GetSize()); //������� ������� ����

	currentMoves = 0;
	allMoves.clear();
	Vector2 buf;

	//�������������� ��� ��������� ���� ��� AI
	for (int i = 0; i < map.GetSize().x; i++)
	{
		for (int j = 0; j < map.GetSize().x; j++)
		{
			buf.x = i;
			buf.y = j;

			allMoves.push_back(buf);
		}
	}

	//������������ ��� ��������� ���� ��������� ���
	int num_mixing = rand->Next(1, 10);
	for (int i = 0; i < num_mixing; i++)
		std::random_shuffle(allMoves.begin(), allMoves.end());

	//��������� ����������� � ����� ����
	int state_gamer = rand->Next(1, 3);
	if (state_gamer == 1)
	{
		if (gameMode == PvE)
		{
			player1.SetField(Player, 1);
			player2.SetField(Computer, 2);

			status->Text = "���: ������!";

			currentPlayer = Player;
		}
		else
		{
			player1.SetField(Player1, 1);
			player2.SetField(Player2, 2);

			status->Text = "���: X!";

			currentPlayer = Player1;
		}
	}

	else if (state_gamer == 2)
	{
		if (gameMode == PvE)
		{
			player1.SetField(Player, 1);
			player2.SetField(Computer, 2);

			status->Text = "���: ����������!";

			currentPlayer = Computer;

			GameLogic();
			UpdateGameGrid();
		}

		else
		{
			player1.SetField(Player1, 1);
			player2.SetField(Player2, 2);

			status->Text = "���: 0!";

			currentPlayer = Player2;
		}
	}

	else
	{
		MessageBox::Show("������ ��������� ��������������� ������ ������!", "������!");
		return;
	}
}

void tictactoe::GameForm::StepAI()
{
	//���������,���� �� ��� ����
	if (currentMoves < allMoves.size())
	{
		//��������� ������� ���
		if (map.IsEmpty(allMoves[currentMoves]))
		{
			//���� ��������, ������ ���
		
			map.SetPosition(allMoves[currentMoves], player2.GetMark());
			currentMoves++;
		}

		else
		{
			//���� ������, ������������ �� ���� ���
			// � �������� ���������� ������ �������
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
	//������� �������
	dataGridView->Rows->Clear();
	dataGridView->Columns->Clear();

	//������ �����
	System::Drawing::Font^ font = gcnew System::Drawing::Font("Microsoft Sans Serif", 14);
	dataGridView->DefaultCellStyle->Font = font;
	dataGridView->ColumnHeadersDefaultCellStyle->Font = font;
	dataGridView->RowHeadersDefaultCellStyle->Font = font;

	//������� �������
	for (int i = 0; i < size.x; i++)
	{
		DataGridViewButtonColumn^ column = gcnew DataGridViewButtonColumn();
		column->HeaderCell->Value = Convert::ToString(i + 1);
		column->Name = "column" + i;
		column->Width = 50;

		dataGridView->Columns->Add(column);
	}

	//������� ������
	for (int i = 0; i < size.y; i++)
	{
		dataGridView->Rows->Add();
		dataGridView->Rows[i]->HeaderCell->Value = Convert::ToString(i + 1);
		dataGridView->Rows[i]->Height = 50;
	}
}

System::Void tictactoe::GameForm::SetPositionPlayer(Vector2 cell)
{
	//��������� ����� ����
	if (gameMode == PvE)
	{
		//��������� ����������� ������
		if (currentPlayer == Player)
		{
			//������ ���
			if (!map.SetPosition(cell, player1.GetMark()))
			{
				MessageBox::Show("������ ������� ������!", "��������!");
				return;
			}
		}
		else
		{
			MessageBox::Show("��� �� ���� �������!", "��������!");
			return;
		}
	}
	else
	{
		//��������� ������� ������
		if (currentPlayer == Player1)
		{
			//������ ���
			if (!map.SetPosition(cell, player1.GetMark()))
			{
				MessageBox::Show("������ ������� ������!", "��������!");
				return;
			}
		}
		else
		{
			//������ ���
			if (!map.SetPosition(cell, player2.GetMark()))
			{
				MessageBox::Show("������ ������� ������!", "��������!");
				return;
			}
		}
	}
	Update();
}

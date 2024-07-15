#include "StartForm.h"
#include "GameForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args) 
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	tictactoe::StartForm form;
	Application::Run(% form);
}


System::Void tictactoe::StartForm::оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Игра крестики-нолики");
}

System::Void tictactoe::StartForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
  
	Application::Exit();
}

System::Void tictactoe::StartForm::buttonStartGame_Click(System::Object^ sender, System::EventArgs^ e)
{

	int indexGameMode = listBoxGameMode->SelectedIndex;
	if (indexGameMode == -1) 
	{
		return;
	}

	int size;
	size = Convert::ToInt32(numericUpDownSizeMap->Value);

	numericUpDownLength->Maximum = size;
	int length = Convert::ToInt32(numericUpDownLength->Value);

	GameForm^ form = gcnew GameForm();
	form->rows = size;
	form->columns = size;
	form->lenghth = length;
	form->selectedGameMode = indexGameMode;
	form->Show();
	this->Hide();

}



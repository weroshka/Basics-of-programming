#pragma once
#include"GameForm.h"

namespace tictactoe {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для StartForm
	/// </summary>
	public ref class StartForm : public System::Windows::Forms::Form
	{
	public:
		StartForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~StartForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выходToolStripMenuItem;
	private: System::Windows::Forms::ListBox^ listBoxGameMode;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownSizeMap;
	private: System::Windows::Forms::NumericUpDown^ numericUpDownLength;
	private: System::Windows::Forms::Button^ buttonStartGame;






	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->listBoxGameMode = (gcnew System::Windows::Forms::ListBox());
			this->numericUpDownSizeMap = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownLength = (gcnew System::Windows::Forms::NumericUpDown());
			this->buttonStartGame = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownSizeMap))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownLength))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(23, 50);
			this->label1->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(346, 31);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Выберите игровой режим:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(14, 148);
			this->label2->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(489, 31);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Укажите размерность игрового поля:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Tai Le", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(14, 206);
			this->label3->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(528, 31);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Укажите длину комбинации для победы:";
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->выходToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(13, 3, 0, 3);
			this->menuStrip1->Size = System::Drawing::Size(679, 30);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(118, 24);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &StartForm::оПрограммеToolStripMenuItem_Click);
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(67, 24);
			this->выходToolStripMenuItem->Text = L"Выход";
			this->выходToolStripMenuItem->Click += gcnew System::EventHandler(this, &StartForm::выходToolStripMenuItem_Click);
			// 
			// listBoxGameMode
			// 
			this->listBoxGameMode->FormattingEnabled = true;
			this->listBoxGameMode->ItemHeight = 26;
			this->listBoxGameMode->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Игрок vs Игрока ", L"Игрок vs Компьютера" });
			this->listBoxGameMode->Location = System::Drawing::Point(462, 50);
			this->listBoxGameMode->Margin = System::Windows::Forms::Padding(5);
			this->listBoxGameMode->Name = L"listBoxGameMode";
			this->listBoxGameMode->Size = System::Drawing::Size(205, 30);
			this->listBoxGameMode->TabIndex = 5;
			// 
			// numericUpDownSizeMap
			// 
			this->numericUpDownSizeMap->Location = System::Drawing::Point(547, 147);
			this->numericUpDownSizeMap->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->numericUpDownSizeMap->Name = L"numericUpDownSizeMap";
			this->numericUpDownSizeMap->Size = System::Drawing::Size(120, 34);
			this->numericUpDownSizeMap->TabIndex = 6;
			this->numericUpDownSizeMap->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			// 
			// numericUpDownLength
			// 
			this->numericUpDownLength->Location = System::Drawing::Point(547, 205);
			this->numericUpDownLength->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->numericUpDownLength->Name = L"numericUpDownLength";
			this->numericUpDownLength->Size = System::Drawing::Size(120, 34);
			this->numericUpDownLength->TabIndex = 7;
			this->numericUpDownLength->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			// 
			// buttonStartGame
			// 
			this->buttonStartGame->Font = (gcnew System::Drawing::Font(L"Times New Roman", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonStartGame->Location = System::Drawing::Point(249, 266);
			this->buttonStartGame->Name = L"buttonStartGame";
			this->buttonStartGame->Size = System::Drawing::Size(188, 50);
			this->buttonStartGame->TabIndex = 8;
			this->buttonStartGame->Text = L"Начать игру";
			this->buttonStartGame->UseVisualStyleBackColor = true;
			this->buttonStartGame->Click += gcnew System::EventHandler(this, &StartForm::buttonStartGame_Click);
			// 
			// StartForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 26);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(679, 333);
			this->Controls->Add(this->buttonStartGame);
			this->Controls->Add(this->numericUpDownLength);
			this->Controls->Add(this->numericUpDownSizeMap);
			this->Controls->Add(this->listBoxGameMode);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(5);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(697, 380);
			this->MinimumSize = System::Drawing::Size(697, 380);
			this->Name = L"StartForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Tag = L"Made FirePlanetStudio";
			this->Text = L"Новая игра";
			this->Load += gcnew System::EventHandler(this, &StartForm::StartForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownSizeMap))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownLength))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	//private: System::Media::SoundPlayer^ sound;
	private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonStartGame_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void StartForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}

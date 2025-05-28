#include "MainForm1.h"
#include "PostOpen.h"

using namespace QQ;

void MainForm::InitializeComponent(void)
{
	this->SuspendLayout();
	// 
	// MainForm
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
	this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->AutoValidate = System::Windows::Forms::AutoValidate::EnableAllowFocusChange;
	this->ClientSize = System::Drawing::Size(1540, 845);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->Margin = System::Windows::Forms::Padding(2);
	this->Name = L"MainForm";
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
	this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
	this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
	this->ResumeLayout(false);

}
#pragma endregion

void MainForm::MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		Application::Exit();
	}

void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {

			   myControl = gcnew QQ::MyUserControl();
			   myControl->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->Controls->Add(myControl);

			   try {
				   // Загружаем все посты из базы
				   List<QQ::Post^>^ posts = PostRepository::LoadAllPosts();

				   // Добавляем каждый пост как элемент управления
				   for each (QQ::Post ^ post in posts) {
					   QQ::PostOpen^ control = gcnew QQ::PostOpen(post);
					   control->Margin = System::Windows::Forms::Padding(10);
				   }
			   }
			   catch (Exception^ ex) {
				   MessageBox::Show("Ошибка при загрузке постов: " + ex->Message);
			   }
		   }
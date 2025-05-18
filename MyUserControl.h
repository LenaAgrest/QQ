#pragma once

#include "PostgresConnection.h"
#include "PostRepository.h"
#include "PostControl.h"
#include "Post.h"
#include "User.h"
#include "Session.h"
#include "UserPage.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;	
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Xml;

namespace QQ {

	public ref class MyUserControl : public System::Windows::Forms::UserControl
	{
	public:
		MyUserControl()
		{
			InitializeComponent();
			SetUser();
		}

	protected:
		~MyUserControl()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^ Panel;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBoxAvatar;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ user_post;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::FlowLayoutPanel^ mainflow;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Label^ labelUserName;
	private: System::ComponentModel::IContainer^ components;
	
	public: QQ::User^ user;
		  void SetUser()
		  {
			  if (QQ::Session::CurrentUser != nullptr) {
				  user = QQ::Session::CurrentUser;
				  labelUserName->Text = QQ::Session::CurrentUser->Username;
			  }
			  MainForm_Load();
		  }




#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyUserControl::typeid));
			this->Panel = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->labelUserName = (gcnew System::Windows::Forms::Label());
			this->pictureBoxAvatar = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->mainflow = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->Panel->SuspendLayout();
			this->panel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxAvatar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->flowLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// Panel
			// 
			this->Panel->BackColor = System::Drawing::Color::SlateBlue;
			this->Panel->Controls->Add(this->panel4);
			this->Panel->Controls->Add(this->pictureBox1);
			this->Panel->Controls->Add(this->flowLayoutPanel2);
			this->Panel->Dock = System::Windows::Forms::DockStyle::Top;
			this->Panel->Location = System::Drawing::Point(0, 0);
			this->Panel->Name = L"Panel";
			this->Panel->Size = System::Drawing::Size(1540, 80);
			this->Panel->TabIndex = 0;
			this->Panel->Resize += gcnew System::EventHandler(this, &MyUserControl::Panel_Resize);
			// 
			// panel4
			// 
			this->panel4->AutoSize = true;
			this->panel4->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panel4->Controls->Add(this->labelUserName);
			this->panel4->Controls->Add(this->pictureBoxAvatar);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel4->Location = System::Drawing::Point(1310, 0);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(230, 80);
			this->panel4->TabIndex = 5;
			// 
			// labelUserName
			// 
			this->labelUserName->AutoSize = true;
			this->labelUserName->Cursor = System::Windows::Forms::Cursors::Hand;
			this->labelUserName->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 18, System::Drawing::FontStyle::Bold));
			this->labelUserName->ForeColor = System::Drawing::Color::White;
			this->labelUserName->Location = System::Drawing::Point(111, 20);
			this->labelUserName->Name = L"labelUserName";
			this->labelUserName->Size = System::Drawing::Size(116, 41);
			this->labelUserName->TabIndex = 2;
			this->labelUserName->TabStop = true;
			this->labelUserName->Text = L"Войти";
			this->labelUserName->Click += gcnew System::EventHandler(this, &MyUserControl::labelUserName_Click);
			// 
			// pictureBoxAvatar
			// 
			this->pictureBoxAvatar->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxAvatar.BackgroundImage")));
			this->pictureBoxAvatar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBoxAvatar->ErrorImage = nullptr;
			this->pictureBoxAvatar->InitialImage = nullptr;
			this->pictureBoxAvatar->Location = System::Drawing::Point(43, 8);
			this->pictureBoxAvatar->Name = L"pictureBoxAvatar";
			this->pictureBoxAvatar->Size = System::Drawing::Size(62, 62);
			this->pictureBoxAvatar->TabIndex = 0;
			this->pictureBoxAvatar->TabStop = false;
			this->pictureBoxAvatar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyUserControl::pictureBoxAvatar_Paint);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(3, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(126, 77);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyUserControl::pictureBox1_Click);
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->BackColor = System::Drawing::Color::White;
			this->flowLayoutPanel2->Controls->Add(this->pictureBox2);
			this->flowLayoutPanel2->Controls->Add(this->textBox1);
			this->flowLayoutPanel2->Location = System::Drawing::Point(432, 10);
			this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(300, 10, 3, 0);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(649, 60);
			this->flowLayoutPanel2->TabIndex = 3;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox2->Location = System::Drawing::Point(3, 3);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(42, 57);
			this->pictureBox2->TabIndex = 0;
			this->pictureBox2->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Montserrat", 20, System::Drawing::FontStyle::Bold));
			this->textBox1->Location = System::Drawing::Point(49, 13);
			this->textBox1->Margin = System::Windows::Forms::Padding(1, 13, 1, 0);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(583, 41);
			this->textBox1->TabIndex = 3;
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->Controls->Add(this->mainflow);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 80);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1540, 720);
			this->panel1->TabIndex = 1;
			this->panel1->Resize += gcnew System::EventHandler(this, &MyUserControl::panel1_Resize);
			// 
			// mainflow
			// 
			this->mainflow->AutoSize = true;
			this->mainflow->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->mainflow->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->mainflow->Location = System::Drawing::Point(300, 0);
			this->mainflow->Name = L"mainflow";
			this->mainflow->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->mainflow->Size = System::Drawing::Size(0, 0);
			this->mainflow->TabIndex = 0;
			this->mainflow->WrapContents = false;
			this->mainflow->SizeChanged += gcnew System::EventHandler(this, &MyUserControl::panel1_Resize);
			// 
			// MyUserControl
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoSize = true;
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->Panel);
			this->Name = L"MyUserControl";
			this->Size = System::Drawing::Size(1540, 800);
			this->Panel->ResumeLayout(false);
			this->Panel->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxAvatar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void flowLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}

	private:
		void pictureBoxAvatar_Paint(Object^ sender, PaintEventArgs^ e)
		{
			auto path = gcnew Drawing2D::GraphicsPath();
			path->AddEllipse(0, 0, pictureBoxAvatar->Width - 1, pictureBoxAvatar->Height - 1);
			this->pictureBoxAvatar->Region = gcnew System::Drawing::Region(path);
		}

		void labelUserName_Click(Object^ sender, EventArgs^ e)
		{
			if (user != nullptr) {
				QQ::UserPage^ userpage = gcnew QQ::UserPage(user);
				this->mainflow->Controls->Clear();
				this->mainflow->Controls->Add(userpage);
			}
			this->panel1->ResumeLayout(false);
			this->panel1->Resize += gcnew System::EventHandler(this, &MyUserControl::panel1_Resize);
			this->panel1->PerformLayout();
		}

		void MainForm_Load() {
			try {
				// Загружаем все посты из базы
				List<QQ::Post^>^ posts = PostRepository::LoadAllPosts();

				// Добавляем каждый пост как элемент управления
				for each (QQ::Post ^ post in posts) {
					QQ::PostControl^ control = gcnew QQ::PostControl(post);
					control->Margin = System::Windows::Forms::Padding(10);
					this->mainflow->Controls->Add(control);
				}
				
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка при загрузке постов: " + ex->Message);
			}
		}

		void MyUserControl::panel1_Resize(Object^ sender, EventArgs^ e)
		{
			   int centerX = (this->panel1->ClientSize.Width - this->mainflow->Width) / 2;
			   if (centerX < 0) {centerX = 0;}
			   this->mainflow->Location = Point(centerX, this->mainflow->Location.Y);
		}
		void MyUserControl::Panel_Resize(Object^ sender, EventArgs^ e)
		{
			int centerX = (this->Panel->ClientSize.Width - this->flowLayoutPanel2->Width) / 2;
			this->flowLayoutPanel2->Location = Point(centerX, this->flowLayoutPanel2->Location.Y);
		}


private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	this->mainflow->Controls->Clear();
	MainForm_Load();
}
};
}
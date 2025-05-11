#pragma once

#include "PostgresConnection.h"
#include "PostRepository.h"
#include "PostControl.h"
#include "Post.h"
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
		MyUserControl(void)
		{
			InitializeComponent();
			this->Load += gcnew System::EventHandler(this, &MyUserControl::MainForm_Load);

		}

	protected:

		~MyUserControl()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ textBox1;

	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel3;
	private: System::Windows::Forms::PictureBox^ pictureBoxAvatar;

	private: System::Windows::Forms::ContextMenuStrip^ contextMenu;
	private: System::Windows::Forms::Label^ labelUserName;
	private: System::Windows::Forms::Panel^ panel1;

	private: System::Windows::Forms::Label^ user_post;

	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ title_post;
	private: System::Windows::Forms::Label^ text_post;
	private: System::Windows::Forms::Label^ date_post;



	private: System::Windows::Forms::PictureBox^ image_post;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ContextMenuStrip^ svoistva_post;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ comm_info;
	private: System::Windows::Forms::FlowLayoutPanel^ mainflow;





	private: System::ComponentModel::IContainer^ components;


	protected:

	private:



#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyUserControl::typeid));
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pictureBoxAvatar = (gcnew System::Windows::Forms::PictureBox());
			this->labelUserName = (gcnew System::Windows::Forms::Label());
			this->contextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->mainflow = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->flowLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->flowLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->flowLayoutPanel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxAvatar))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->BackColor = System::Drawing::Color::SlateBlue;
			this->flowLayoutPanel1->Controls->Add(this->pictureBox1);
			this->flowLayoutPanel1->Controls->Add(this->flowLayoutPanel2);
			this->flowLayoutPanel1->Controls->Add(this->flowLayoutPanel3);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(1540, 80);
			this->flowLayoutPanel1->TabIndex = 0;
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
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->AutoSize = true;
			this->flowLayoutPanel3->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->flowLayoutPanel3->Controls->Add(this->pictureBoxAvatar);
			this->flowLayoutPanel3->Controls->Add(this->labelUserName);
			this->flowLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Right;
			this->flowLayoutPanel3->Location = System::Drawing::Point(100, 90);
			this->flowLayoutPanel3->Margin = System::Windows::Forms::Padding(100, 7, 3, 0);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(390, 68);
			this->flowLayoutPanel3->TabIndex = 4;
			// 
			// pictureBoxAvatar
			// 
			this->pictureBoxAvatar->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxAvatar.BackgroundImage")));
			this->pictureBoxAvatar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBoxAvatar->ErrorImage = nullptr;
			this->pictureBoxAvatar->InitialImage = nullptr;
			this->pictureBoxAvatar->Location = System::Drawing::Point(3, 3);
			this->pictureBoxAvatar->Name = L"pictureBoxAvatar";
			this->pictureBoxAvatar->Size = System::Drawing::Size(62, 62);
			this->pictureBoxAvatar->TabIndex = 0;
			this->pictureBoxAvatar->TabStop = false;
			this->pictureBoxAvatar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyUserControl::pictureBoxAvatar_Paint);
			// 
			// labelUserName
			// 
			this->labelUserName->AutoSize = true;
			this->labelUserName->Cursor = System::Windows::Forms::Cursors::Hand;
			this->labelUserName->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelUserName->ForeColor = System::Drawing::Color::White;
			this->labelUserName->Location = System::Drawing::Point(71, 12);
			this->labelUserName->Margin = System::Windows::Forms::Padding(3, 12, 3, 0);
			this->labelUserName->Name = L"labelUserName";
			this->labelUserName->Size = System::Drawing::Size(316, 41);
			this->labelUserName->TabIndex = 1;
			this->labelUserName->TabStop = true;
			this->labelUserName->Text = L"Имя пользователя";
			this->labelUserName->Click += gcnew System::EventHandler(this, &MyUserControl::labelUserName_Click);
			// 
			// contextMenu
			// 
			this->contextMenu->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenu->Name = L"contextMenu";
			this->contextMenu->ShowImageMargin = false;
			this->contextMenu->Size = System::Drawing::Size(36, 4);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->mainflow);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 80);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1540, 765);
			this->panel1->TabIndex = 1;
			// 
			// mainflow
			// 
			this->mainflow->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			//this->mainflow->AutoScroll = true;
			this->mainflow->AutoSize = true;
			this->mainflow->Location = System::Drawing::Point(320, 0);
			this->mainflow->Name = L"mainflow";
			//this->mainflow->Size = System::Drawing::Size(1026, 749);
			this->mainflow->TabIndex = 0;
			// 
			// MyUserControl
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoSize = true;
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Name = L"MyUserControl";
			this->Size = System::Drawing::Size(1540, 800);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->flowLayoutPanel3->ResumeLayout(false);
			this->flowLayoutPanel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxAvatar))->EndInit();
			this->panel1->ResumeLayout(false);
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
			this->contextMenu->Show(this->labelUserName, Drawing::Point(0, this->labelUserName->Height));
		}

		void MenuMyBlog_Click(Object^ sender, EventArgs^ e)
		{
			// TODO: переход в блог
		}

		void MenuEditProfile_Click(Object^ sender, EventArgs^ e)
		{
			// TODO: открыть форму редактирования профиля
		}

		void MenuLogout_Click(Object^ sender, EventArgs^ e)
		{
			DialogResult result = MessageBox::Show("Вы уверены, что хотите выйти?", "Подтверждение", MessageBoxButtons::YesNo);
			if (result == DialogResult::Yes)
			{
				Application::Exit();
			}
		}

		private: void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
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

};
}
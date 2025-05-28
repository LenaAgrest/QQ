#pragma once

#include "Post.h"
#include "User.h"

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
	public:	MyUserControl();

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
		  

	private:
		void InitializeComponent(void);

		void labelUserName_Click(Object^ sender, EventArgs^ e);

		void OpenEditProfile(User^ user);
		void pictureBoxAvatar_Paint(Object^ sender, PaintEventArgs^ e);
		void OpenPost(QQ::Post^ post);
		void SetUser();

		void MainForm_Load();

		void RefreshHomeAfterDeletion();

		void panel1_Resize(Object^ sender, EventArgs^ e);

		void Panel_Resize(Object^ sender, EventArgs^ e);

		void panel1_Resize2(Object^ sender, EventArgs^ e);
		void OpenCreatePost(User^ user);
		void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e);
		void ReturnToUserPage(User^ updatedUser);

	};
}
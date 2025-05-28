#pragma once

#include "MyUserControl.h"
#include "PostRepository.h"

namespace QQ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class MainForm : public System::Windows::Forms::Form
	{
	//private: QQ::User^ currentUser;
	public:
		MainForm()
		{
			//currentUser = user;
			InitializeComponent();
		}

	protected:

		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::ComponentModel::Container ^components;

	private: QQ::MyUserControl^ myControl;
		
		   void InitializeComponent(void);

		   void MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);

		   void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
		
	};
}

#pragma once

#include <msclr/marshal_cppstd.h>
#include <string>
#include "reg.h"
#include "MainForm1.h"
int Check_ñredentials(std::string username, std::string password);

namespace QQ {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	public ref class aurorise : public System::Windows::Forms::Form
	{
	public:
		aurorise(void)
		{
			InitializeComponent();
		}
	protected:

		~aurorise()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ name;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ vxod;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::TextBox^ password;
	private: System::Windows::Forms::Button^ exit;
	private:
		void InitializeComponent(void);
		void exit_Click(System::Object^ sender, System::EventArgs^ e);
		void vxod_Click(System::Object^ sender, System::EventArgs^ e);
		void button3_Click(System::Object^ sender, System::EventArgs^ e);
		System::ComponentModel::Container ^components;
		
};

}

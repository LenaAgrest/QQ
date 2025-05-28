#pragma once

#include <msclr/marshal_cppstd.h>
#include <string>

int reg_people(std::string username, std::string password, std::string interests, std::string date, std::string about, std::string contacts);

namespace QQ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::TextBox^ pswd;

	private: System::Windows::Forms::Panel^ panel3;

	private: System::Windows::Forms::Button^ vxod;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ name;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ exit2;

	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::TextBox^ born;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Panel^ panel6;
	private: System::Windows::Forms::TextBox^ contacts;

	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ about_me;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Panel^ panel7;
	private: System::Windows::Forms::TextBox^ interes;
	private: System::Windows::Forms::Label^ label7;

	protected:

	private:
		System::ComponentModel::Container^ components;
		void InitializeComponent(void);

	private: System::Void exit2_Click(System::Object^ sender, System::EventArgs^ e);
	
	private: System::Void reg_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
#pragma once

#include "MyUserControl.h"

namespace QQ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
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
	private: System::Windows::Forms::Integration::ElementHost^ elementHost1;
	private: QQ::MyUserControl^ myControl;

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		myControl = gcnew QQ::MyUserControl();
		myControl->Location = System::Drawing::Point(10, 10);
		myControl->Size = System::Drawing::Size(300, 200);
		this->Controls->Add(myControl);
	}

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->elementHost1 = (gcnew System::Windows::Forms::Integration::ElementHost());
			this->SuspendLayout();
			// 
			// elementHost1
			// 
			this->elementHost1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->elementHost1->Location = System::Drawing::Point(0, 0);
			this->elementHost1->Name = L"elementHost1";
			this->elementHost1->Size = System::Drawing::Size(1902, 1033);
			this->elementHost1->TabIndex = 0;
			this->elementHost1->Text = L"elementHost1";
			this->elementHost1->Child = nullptr;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1902, 1033);
			this->Controls->Add(this->elementHost1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}

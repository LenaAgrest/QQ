#pragma once

#include "MyUserControl.h"

using namespace QQ;

namespace QQ {

	public ref class MainForm : public System::Windows::Forms::Form
	{
	private: MyUserControl^ myUserControl;

	public:
		MainForm(void)
		{
			InitializeComponent();
			MyUserControl^ myUserControl = gcnew MyUserControl();
			this->Controls->Add(myUserControl);
		}
	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1920, 1080);
			this->Name = L"MainForm";
			this->Text = L"";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->ResumeLayout(false);
			// 
			// myUserControl
			// 
			this->myUserControl = (gcnew MyUserControl());
			this->SuspendLayout();
			this->myUserControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->myUserControl->Location = System::Drawing::Point(0, 0);
			this->myUserControl->Name = L"myUserControl";
			this->myUserControl->Size = System::Drawing::Size(1920, 1080);
			this->myUserControl->TabIndex = 0;
		}
#pragma endregion
	};
}

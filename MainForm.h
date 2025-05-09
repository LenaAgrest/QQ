#pragma once
#include "MyUserControl.h"

namespace QQ {

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
				delete components;
		}

	private: MyUserControl^ myUserControl;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->myUserControl = (gcnew MyUserControl());
			this->SuspendLayout();

			// 
			// myUserControl
			// 
			this->myUserControl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->myUserControl->Location = System::Drawing::Point(0, 0);
			this->myUserControl->Name = L"myUserControl";
			this->myUserControl->Size = System::Drawing::Size(1920, 1080);
			this->myUserControl->TabIndex = 0;

			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1920, 1080);
			this->Controls->Add(this->myUserControl);
			this->Name = L"MainForm";
			this->Text = L"Главная страница";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->ResumeLayout(false);
		}
#pragma endregion
	};
}

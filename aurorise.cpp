#include "aurorise.h"
#include "Session.h"
#include "PostgresConnection.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <libpq-fe.h>
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
#include <string>
#include "User.h"
using namespace System::IO;

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::SqlClient;
using namespace System::Drawing;
using namespace msclr::interop;
using namespace System::Runtime::InteropServices;


int Check_сredentials(std::string username, std::string password) {
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    if (!dbConnection.connect()) {
        std::cerr << "Ошибка подключения: " << dbConnection.getLastError() << std::endl;
        return 3;
    }
    std::string query = "SELECT (SELECT COUNT(*) FROM people WHERE name = '" + username + "' AND pswd = '" + password + "') AS match_count, p.id, p.name, p.pswd, p.interests, p.date_of_birth, p.about_me, p.photo, p.contacts FROM people p WHERE name = '" + username + "' AND pswd = '" + password + "';";

    // Выполняем запрос
    PGconn* conn = dbConnection.get();
    PGresult* res = PQexec(conn, query.c_str());

    int rows = PQntuples(res);
    if (rows != 1) {
        std::cerr << "Ошибка при выполнении запроса: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        dbConnection.disconnect();
        return 0;
    }
    for (int i = 0; i < rows; ++i) {
        int userCount = std::stoi(PQgetvalue(res, 0, 0));
        int id = std::stoi(PQgetvalue(res, i, 1));
        std::string Name = PQgetvalue(res, i, 2);
        std::string Password = PQgetvalue(res, i, 3);
        std::string Interests = PQgetvalue(res, i, 4);
        std::string Date_of_birth = PQgetvalue(res, i, 5);
        std::string About_me = PQgetvalue(res, i, 6);
        std::string Contacts = PQgetvalue(res, i, 8);
        Image^ img = nullptr;


        if (!PQgetisnull(res, i, 7)) {
            size_t unescapedLength = 0;
            const char* escaped = PQgetvalue(res, i, 7);
            unsigned char* unescaped = PQunescapeBytea((const unsigned char*)escaped, &unescapedLength);

            if (unescaped && unescapedLength > 0) {
                array<Byte>^ imageData = gcnew array<Byte>((int)unescapedLength);
                Marshal::Copy((IntPtr)(void*)unescaped, imageData, 0, (int)unescapedLength);

                try {
                    MemoryStream^ ms = gcnew MemoryStream(imageData);
                    img = Image::FromStream(ms);
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Ошибка при чтении изображения: " + ex->Message);
                    img = nullptr;
                }

                PQfreemem(unescaped);
            }
        }
        

        String^ name = marshal_as<String^>(Name);
        String^ pswd = marshal_as<String^>(Password);
        String^ interests = marshal_as<String^>(Interests);
        String^ about_me = marshal_as<String^>(About_me);
        String^ contacts = marshal_as<String^>(Contacts);

        //DateTime date_of_birth = DateTime::Parse(marshal_as<String^>(Date_of_birth));
        DateTime date_of_birth = DateTime::MinValue;
        if (!PQgetisnull(res, i, 5)) {
            try {
                date_of_birth = DateTime::Parse(marshal_as<String^>(PQgetvalue(res, i, 5)));
            }
            catch (...) {
                date_of_birth = DateTime::MinValue; // или логирование ошибки
            }
        }

            if (userCount != 1) {
                std::cerr << "Ошибка при выполнении запроса: " << PQerrorMessage(conn) << std::endl;
                PQclear(res);
                dbConnection.disconnect();
                return 0;
            }
            else
            {
                QQ::User^ user = gcnew QQ::User(id, name, pswd, interests, date_of_birth, about_me, img, contacts);
                QQ::Session::CurrentUser = user;
                MyUserControl^ control = gcnew MyUserControl();
                QQ::MainForm^ mainForm = gcnew QQ::MainForm();
                mainForm->Show();

                PQclear(res);
                dbConnection.disconnect();
                return 1;
            }
    }
}
void aurorise::InitializeComponent(void)
{
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(aurorise::typeid));
	this->panel1 = (gcnew System::Windows::Forms::Panel());
	this->panel2 = (gcnew System::Windows::Forms::Panel());
	this->password = (gcnew System::Windows::Forms::TextBox());
	this->panel3 = (gcnew System::Windows::Forms::Panel());
	this->button3 = (gcnew System::Windows::Forms::Button());
	this->vxod = (gcnew System::Windows::Forms::Button());
	this->label3 = (gcnew System::Windows::Forms::Label());
	this->name = (gcnew System::Windows::Forms::TextBox());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->exit = (gcnew System::Windows::Forms::Button());
	this->panel1->SuspendLayout();
	this->SuspendLayout();
	// 
	// panel1
	// 
	this->panel1->BackColor = System::Drawing::Color::Transparent;
	this->panel1->Controls->Add(this->panel2);
	this->panel1->Controls->Add(this->password);
	this->panel1->Controls->Add(this->panel3);
	this->panel1->Controls->Add(this->button3);
	this->panel1->Controls->Add(this->vxod);
	this->panel1->Controls->Add(this->label3);
	this->panel1->Controls->Add(this->name);
	this->panel1->Controls->Add(this->label2);
	this->panel1->Controls->Add(this->label1);
	this->panel1->Location = System::Drawing::Point(25, 20);
	this->panel1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
	this->panel1->Name = L"panel1";
	this->panel1->Size = System::Drawing::Size(305, 363);
	this->panel1->TabIndex = 4;
	// 
	// panel2
	// 
	this->panel2->BackColor = System::Drawing::Color::SlateBlue;
	this->panel2->Location = System::Drawing::Point(8, 266);
	this->panel2->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
	this->panel2->Name = L"panel2";
	this->panel2->Size = System::Drawing::Size(271, 2);
	this->panel2->TabIndex = 9;
	// 
	// password
	// 
	this->password->BackColor = System::Drawing::Color::White;
	this->password->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->password->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->password->ForeColor = System::Drawing::Color::MediumSlateBlue;
	this->password->Location = System::Drawing::Point(8, 240);
	this->password->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
	this->password->Name = L"password";
	this->password->Size = System::Drawing::Size(271, 23);
	this->password->TabIndex = 2;
	this->password->UseSystemPasswordChar = true;
	// 
	// panel3
	// 
	this->panel3->BackColor = System::Drawing::Color::SlateBlue;
	this->panel3->Location = System::Drawing::Point(8, 186);
	this->panel3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
	this->panel3->Name = L"panel3";
	this->panel3->Size = System::Drawing::Size(271, 2);
	this->panel3->TabIndex = 7;
	// 
	// button3
	// 
	this->button3->BackColor = System::Drawing::Color::SlateBlue;
	this->button3->FlatAppearance->BorderSize = 0;
	this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->button3->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->button3->ForeColor = System::Drawing::Color::White;
	this->button3->Location = System::Drawing::Point(142, 288);
	this->button3->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
	this->button3->Name = L"button3";
	this->button3->Size = System::Drawing::Size(136, 35);
	this->button3->TabIndex = 4;
	this->button3->Text = L"Нет аккаунта\?";
	this->button3->UseVisualStyleBackColor = true;
	this->button3->Click += gcnew System::EventHandler(this, &aurorise::button3_Click);
	// 
	// vxod
	// 
	this->vxod->BackColor = System::Drawing::Color::SlateBlue;
	this->vxod->FlatAppearance->BorderSize = 0;
	this->vxod->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->vxod->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->vxod->ForeColor = System::Drawing::Color::White;
	this->vxod->Location = System::Drawing::Point(8, 288);
	this->vxod->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
	this->vxod->Name = L"vxod";
	this->vxod->Size = System::Drawing::Size(121, 35);
	this->vxod->TabIndex = 3;
	this->vxod->Text = L"Войти";
	this->vxod->UseVisualStyleBackColor = true;
	this->vxod->Click += gcnew System::EventHandler(this, &aurorise::vxod_Click);
	// 
	// label3
	// 
	this->label3->AutoSize = true;
	this->label3->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label3->ForeColor = System::Drawing::Color::SlateBlue;
	this->label3->Location = System::Drawing::Point(2, 202);
	this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
	this->label3->Name = L"label3";
	this->label3->Size = System::Drawing::Size(100, 30);
	this->label3->TabIndex = 3;
	this->label3->Text = L"Пароль";
	// 
	// name
	// 
	this->name->BackColor = System::Drawing::Color::White;
	this->name->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->name->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->name->ForeColor = System::Drawing::Color::MediumSlateBlue;
	this->name->Location = System::Drawing::Point(8, 160);
	this->name->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
	this->name->Name = L"name";
	this->name->Size = System::Drawing::Size(271, 23);
	this->name->TabIndex = 1;
	// 
	// label2
	// 
	this->label2->AutoSize = true;
	this->label2->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label2->ForeColor = System::Drawing::Color::SlateBlue;
	this->label2->Location = System::Drawing::Point(2, 122);
	this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
	this->label2->Name = L"label2";
	this->label2->Size = System::Drawing::Size(63, 30);
	this->label2->TabIndex = 1;
	this->label2->Text = L"Имя";
	// 
	// label1
	// 
	this->label1->AutoSize = true;
	this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label1->ForeColor = System::Drawing::Color::SlateBlue;
	this->label1->Location = System::Drawing::Point(2, 54);
	this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(124, 52);
	this->label1->TabIndex = 0;
	this->label1->Text = L"Вход";
	// 
	// exit
	// 
	this->exit->AutoSize = true;
	this->exit->BackColor = System::Drawing::Color::Transparent;
	this->exit->FlatAppearance->BorderSize = 0;
	this->exit->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
	this->exit->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
	this->exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->exit->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->exit->Location = System::Drawing::Point(685, -2);
	this->exit->Margin = System::Windows::Forms::Padding(0);
	this->exit->Name = L"exit";
	this->exit->Size = System::Drawing::Size(38, 40);
	this->exit->TabIndex = 5;
	this->exit->Text = L"X";
	this->exit->UseVisualStyleBackColor = false;
	this->exit->Click += gcnew System::EventHandler(this, &aurorise::exit_Click);
	// 
	// aurorise
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->BackColor = System::Drawing::Color::White;
	this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
	this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
	this->ClientSize = System::Drawing::Size(720, 410);
	this->Controls->Add(this->exit);
	this->Controls->Add(this->panel1);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
	this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
	this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
	this->Name = L"aurorise";
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	this->Text = L"aurorise";
	this->panel1->ResumeLayout(false);
	this->panel1->PerformLayout();
	this->ResumeLayout(false);
	this->PerformLayout();

}

void aurorise::exit_Click(System::Object^ sender, System::EventArgs^ e) {
	Form::Close();
}

void aurorise::vxod_Click(System::Object^ sender, System::EventArgs^ e) {
	std::string username = marshal_as<std::string>(name->Text);
	std::string pswd = marshal_as<std::string>(password->Text);

	int isAuthenticated = Check_сredentials(username, pswd);

	if (name->Text->Length == 0 || password->Text->Length == 0) {
		MessageBox::Show("Введите имя пользователя и пароль", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	if (isAuthenticated == 1) {
		//MessageBox::Show("Успешный вход!", "Добро пожаловать", MessageBoxButtons::OK, MessageBoxIcon::Information);
		//QQ::MainForm^ mainForm = gcnew QQ::MainForm(name);
		//mainForm->Show();
		this->Hide();
	}
	else if (isAuthenticated == 0) {
		MessageBox::Show("Неверное имя пользователя или пароль", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else if (isAuthenticated == 3) {
		MessageBox::Show("Ошибка подключения к базе данных", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else {
		MessageBox::Show("Что-то пошло не так", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
void aurorise::button3_Click(System::Object^ sender, System::EventArgs^ e) {
	Form^ f2 = gcnew MyForm();
	this->Hide();
	if (f2->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		this->Show();
	}
	else {
		this->Close();
	}

}
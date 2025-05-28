#include "reg.h"
#include "aurorise.h"
#include "PostgresConnection.h"
#include <iostream>
#include <libpq-fe.h>
#include <string>
#include <msclr/marshal_cppstd.h>

int reg_people(std::string username, std::string password, std::string interests, std::string date, std::string about, std::string contacts) {
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    if (!dbConnection.connect()) {
        std::cerr << "Ошибка подключения: " << dbConnection.getLastError() << std::endl;
        return 3;
    }

    // Экранируем данные
    PGconn* conn = dbConnection.get();
    char* esc_username = PQescapeLiteral(conn, username.c_str(), username.length());
    char* esc_password = PQescapeLiteral(conn, password.c_str(), password.length());
    char* esc_interests = interests.empty() ? nullptr : PQescapeLiteral(conn, interests.c_str(), interests.length());
    char* esc_date = date.empty() ? nullptr : PQescapeLiteral(conn, date.c_str(), date.length());
    char* esc_about = about.empty() ? nullptr : PQescapeLiteral(conn, about.c_str(), about.length());
    char* esc_contacts = contacts.empty() ? nullptr : PQescapeLiteral(conn, contacts.c_str(), contacts.length());

    std::string query = "SELECT COUNT(*) FROM people WHERE name=" + std::string(esc_username) + " AND pswd=" + std::string(esc_password) + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        int count = atoi(PQgetvalue(res, 0, 0));
        if (count > 0) {
            PQclear(res);
            PQfreemem(esc_username);
            PQfreemem(esc_password);
            return 2;
        }
        else {
            std::string query = "INSERT INTO people (name, pswd, interests, date_of_birth, about_me, contacts) VALUES (" +
                std::string(esc_username) + ", " +
                std::string(esc_password) + ", " +
                std::string(esc_interests ? esc_interests : "NULL") + ", " +
                std::string(esc_date ? esc_date : "NULL") + ", " +
                std::string(esc_about ? esc_about : "NULL") + ", " +
                std::string(esc_contacts ? esc_contacts : "NULL") + ")";

            PGresult* res = PQexec(conn, query.c_str());

            if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                std::cerr << "Ошибка запроса: " << PQerrorMessage(conn) << std::endl;
                PQclear(res);
                dbConnection.disconnect();
                return 0;
            }
            else { return 1; }
        }
    }
    

    // Очистка
    PQclear(res);
    PQfreemem(esc_username);
    PQfreemem(esc_password);
    PQfreemem(esc_interests);
    PQfreemem(esc_date);
    PQfreemem(esc_about);
    PQfreemem(esc_contacts);
    dbConnection.disconnect();
}


void MyForm::InitializeComponent(void)
{
	this->panel1 = (gcnew System::Windows::Forms::Panel());
	this->panel7 = (gcnew System::Windows::Forms::Panel());
	this->interes = (gcnew System::Windows::Forms::TextBox());
	this->panel6 = (gcnew System::Windows::Forms::Panel());
	this->label7 = (gcnew System::Windows::Forms::Label());
	this->contacts = (gcnew System::Windows::Forms::TextBox());
	this->panel5 = (gcnew System::Windows::Forms::Panel());
	this->label6 = (gcnew System::Windows::Forms::Label());
	this->about_me = (gcnew System::Windows::Forms::TextBox());
	this->panel4 = (gcnew System::Windows::Forms::Panel());
	this->label5 = (gcnew System::Windows::Forms::Label());
	this->panel2 = (gcnew System::Windows::Forms::Panel());
	this->born = (gcnew System::Windows::Forms::TextBox());
	this->label4 = (gcnew System::Windows::Forms::Label());
	this->pswd = (gcnew System::Windows::Forms::TextBox());
	this->panel3 = (gcnew System::Windows::Forms::Panel());
	this->vxod = (gcnew System::Windows::Forms::Button());
	this->label3 = (gcnew System::Windows::Forms::Label());
	this->name = (gcnew System::Windows::Forms::TextBox());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->exit2 = (gcnew System::Windows::Forms::Button());
	this->panel1->SuspendLayout();
	this->SuspendLayout();
	// 
	// panel1
	// 
	this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
		| System::Windows::Forms::AnchorStyles::Left));
	this->panel1->BackColor = System::Drawing::Color::Transparent;
	this->panel1->Controls->Add(this->panel7);
	this->panel1->Controls->Add(this->interes);
	this->panel1->Controls->Add(this->panel6);
	this->panel1->Controls->Add(this->label7);
	this->panel1->Controls->Add(this->contacts);
	this->panel1->Controls->Add(this->panel5);
	this->panel1->Controls->Add(this->label6);
	this->panel1->Controls->Add(this->about_me);
	this->panel1->Controls->Add(this->panel4);
	this->panel1->Controls->Add(this->label5);
	this->panel1->Controls->Add(this->panel2);
	this->panel1->Controls->Add(this->born);
	this->panel1->Controls->Add(this->label4);
	this->panel1->Controls->Add(this->pswd);
	this->panel1->Controls->Add(this->panel3);
	this->panel1->Controls->Add(this->vxod);
	this->panel1->Controls->Add(this->label3);
	this->panel1->Controls->Add(this->name);
	this->panel1->Controls->Add(this->label2);
	this->panel1->Controls->Add(this->label1);
	this->panel1->Location = System::Drawing::Point(22, 12);
	this->panel1->Name = L"panel1";
	this->panel1->Size = System::Drawing::Size(890, 469);
	this->panel1->TabIndex = 6;
	// 
	// panel7
	// 
	this->panel7->BackColor = System::Drawing::Color::SlateBlue;
	this->panel7->Location = System::Drawing::Point(504, 371);
	this->panel7->Name = L"panel7";
	this->panel7->Size = System::Drawing::Size(361, 2);
	this->panel7->TabIndex = 16;
	// 
	// interes
	// 
	this->interes->BackColor = System::Drawing::Color::White;
	this->interes->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->interes->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->interes->ForeColor = System::Drawing::Color::MediumSlateBlue;
	this->interes->Location = System::Drawing::Point(504, 339);
	this->interes->Name = L"interes";
	this->interes->Size = System::Drawing::Size(361, 29);
	this->interes->TabIndex = 6;
	// 
	// panel6
	// 
	this->panel6->BackColor = System::Drawing::Color::SlateBlue;
	this->panel6->Location = System::Drawing::Point(504, 271);
	this->panel6->Name = L"panel6";
	this->panel6->Size = System::Drawing::Size(361, 2);
	this->panel6->TabIndex = 13;
	// 
	// label7
	// 
	this->label7->AutoSize = true;
	this->label7->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label7->ForeColor = System::Drawing::Color::SlateBlue;
	this->label7->Location = System::Drawing::Point(497, 292);
	this->label7->Name = L"label7";
	this->label7->Size = System::Drawing::Size(166, 39);
	this->label7->TabIndex = 15;
	this->label7->Text = L"Интересы";
	// 
	// contacts
	// 
	this->contacts->BackColor = System::Drawing::Color::White;
	this->contacts->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->contacts->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->contacts->ForeColor = System::Drawing::Color::MediumSlateBlue;
	this->contacts->Location = System::Drawing::Point(504, 239);
	this->contacts->Name = L"contacts";
	this->contacts->Size = System::Drawing::Size(361, 29);
	this->contacts->TabIndex = 5;
	// 
	// panel5
	// 
	this->panel5->BackColor = System::Drawing::Color::SlateBlue;
	this->panel5->Location = System::Drawing::Point(504, 177);
	this->panel5->Name = L"panel5";
	this->panel5->Size = System::Drawing::Size(361, 2);
	this->panel5->TabIndex = 10;
	// 
	// label6
	// 
	this->label6->AutoSize = true;
	this->label6->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label6->ForeColor = System::Drawing::Color::SlateBlue;
	this->label6->Location = System::Drawing::Point(497, 192);
	this->label6->Name = L"label6";
	this->label6->Size = System::Drawing::Size(158, 39);
	this->label6->TabIndex = 12;
	this->label6->Text = L"Контакты";
	// 
	// about_me
	// 
	this->about_me->BackColor = System::Drawing::Color::White;
	this->about_me->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->about_me->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->about_me->ForeColor = System::Drawing::Color::MediumSlateBlue;
	this->about_me->Location = System::Drawing::Point(504, 145);
	this->about_me->Name = L"about_me";
	this->about_me->Size = System::Drawing::Size(361, 29);
	this->about_me->TabIndex = 4;
	// 
	// panel4
	// 
	this->panel4->BackColor = System::Drawing::Color::SlateBlue;
	this->panel4->Location = System::Drawing::Point(11, 371);
	this->panel4->Name = L"panel4";
	this->panel4->Size = System::Drawing::Size(361, 2);
	this->panel4->TabIndex = 10;
	// 
	// label5
	// 
	this->label5->AutoSize = true;
	this->label5->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label5->ForeColor = System::Drawing::Color::SlateBlue;
	this->label5->Location = System::Drawing::Point(497, 98);
	this->label5->Name = L"label5";
	this->label5->Size = System::Drawing::Size(120, 39);
	this->label5->TabIndex = 9;
	this->label5->Text = L"О себе";
	// 
	// panel2
	// 
	this->panel2->BackColor = System::Drawing::Color::SlateBlue;
	this->panel2->Location = System::Drawing::Point(10, 271);
	this->panel2->Name = L"panel2";
	this->panel2->Size = System::Drawing::Size(361, 2);
	this->panel2->TabIndex = 9;
	// 
	// born
	// 
	this->born->BackColor = System::Drawing::Color::White;
	this->born->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->born->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->born->ForeColor = System::Drawing::Color::MediumSlateBlue;
	this->born->Location = System::Drawing::Point(11, 339);
	this->born->Name = L"born";
	this->born->Size = System::Drawing::Size(361, 29);
	this->born->TabIndex = 3;
	// 
	// label4
	// 
	this->label4->AutoSize = true;
	this->label4->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label4->ForeColor = System::Drawing::Color::SlateBlue;
	this->label4->Location = System::Drawing::Point(4, 292);
	this->label4->Name = L"label4";
	this->label4->Size = System::Drawing::Size(250, 39);
	this->label4->TabIndex = 9;
	this->label4->Text = L"Дата рождения";
	// 
	// pswd
	// 
	this->pswd->BackColor = System::Drawing::Color::White;
	this->pswd->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->pswd->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->pswd->ForeColor = System::Drawing::Color::MediumSlateBlue;
	this->pswd->Location = System::Drawing::Point(10, 239);
	this->pswd->Name = L"pswd";
	this->pswd->Size = System::Drawing::Size(361, 29);
	this->pswd->TabIndex = 2;
	this->pswd->UseSystemPasswordChar = true;
	// 
	// panel3
	// 
	this->panel3->BackColor = System::Drawing::Color::SlateBlue;
	this->panel3->Location = System::Drawing::Point(10, 177);
	this->panel3->Name = L"panel3";
	this->panel3->Size = System::Drawing::Size(361, 2);
	this->panel3->TabIndex = 7;
	// 
	// vxod
	// 
	this->vxod->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
		| System::Windows::Forms::AnchorStyles::Right));
	this->vxod->AutoSize = true;
	this->vxod->BackColor = System::Drawing::Color::SlateBlue;
	this->vxod->FlatAppearance->BorderSize = 0;
	this->vxod->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->vxod->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->vxod->ForeColor = System::Drawing::Color::White;
	this->vxod->Location = System::Drawing::Point(321, 423);
	this->vxod->Name = L"vxod";
	this->vxod->Size = System::Drawing::Size(251, 43);
	this->vxod->TabIndex = 7;
	this->vxod->Text = L"Зарегистрироваться";
	this->vxod->UseVisualStyleBackColor = true;
	this->vxod->Click += gcnew System::EventHandler(this, &MyForm::reg_Click);
	// 
	// label3
	// 
	this->label3->AutoSize = true;
	this->label3->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label3->ForeColor = System::Drawing::Color::SlateBlue;
	this->label3->Location = System::Drawing::Point(3, 192);
	this->label3->Name = L"label3";
	this->label3->Size = System::Drawing::Size(128, 39);
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
	this->name->Location = System::Drawing::Point(10, 145);
	this->name->Name = L"name";
	this->name->Size = System::Drawing::Size(361, 29);
	this->name->TabIndex = 1;
	// 
	// label2
	// 
	this->label2->AutoSize = true;
	this->label2->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label2->ForeColor = System::Drawing::Color::SlateBlue;
	this->label2->Location = System::Drawing::Point(3, 98);
	this->label2->Name = L"label2";
	this->label2->Size = System::Drawing::Size(80, 39);
	this->label2->TabIndex = 1;
	this->label2->Text = L"Имя";
	// 
	// label1
	// 
	this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
		| System::Windows::Forms::AnchorStyles::Right));
	this->label1->AutoSize = true;
	this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat", 28.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label1->ForeColor = System::Drawing::Color::SlateBlue;
	this->label1->Location = System::Drawing::Point(281, 3);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(358, 65);
	this->label1->TabIndex = 0;
	this->label1->Text = L"Регистрация";
	// 
	// exit2
	// 
	this->exit2->AutoSize = true;
	this->exit2->BackColor = System::Drawing::Color::Transparent;
	this->exit2->FlatAppearance->BorderSize = 0;
	this->exit2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
	this->exit2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
	this->exit2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->exit2->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->exit2->Location = System::Drawing::Point(902, -3);
	this->exit2->Margin = System::Windows::Forms::Padding(0);
	this->exit2->Name = L"exit2";
	this->exit2->Size = System::Drawing::Size(50, 49);
	this->exit2->TabIndex = 7;
	this->exit2->Text = L"X";
	this->exit2->UseVisualStyleBackColor = false;
	this->exit2->Click += gcnew System::EventHandler(this, &MyForm::exit2_Click);
	// 
	// MyForm
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->BackgroundImage = System::Drawing::Image::FromFile("рег.png");
	this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
	this->ClientSize = System::Drawing::Size(942, 493);
	this->Controls->Add(this->panel1);
	this->Controls->Add(this->exit2);
	this->DoubleBuffered = true;
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
	this->Name = L"MyForm";
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	this->Text = L"MyForm";
	this->panel1->ResumeLayout(false);
	this->panel1->PerformLayout();
	this->ResumeLayout(false);
	this->PerformLayout();

}

void QQ::MyForm::exit2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->DialogResult = System::Windows::Forms::DialogResult::OK;
	this->Close();

}
void QQ::MyForm::reg_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string username = marshal_as<std::string>(name->Text);
		std::string pass = marshal_as<std::string>(pswd->Text);
		std::string date = marshal_as<std::string>(born->Text);
		std::string interesi = marshal_as<std::string>(interes->Text);
		std::string call = marshal_as<std::string>(contacts->Text);
		std::string about = marshal_as<std::string>(about_me->Text);

		if (name->Text->Length == 0 || pswd->Text->Length == 0 || born->Text->Length == 0 || interes->Text->Length == 0 || contacts->Text->Length == 0 || about_me->TextLength == 0) {
			MessageBox::Show("Пожалуйста, заполните все поля", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		int result = reg_people(username, pass, interesi, date, about, call);

		if (result == 1) {
			MessageBox::Show("Регистрация успешна!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
			this->Hide();
			aurorise^ loginForm = gcnew aurorise();
			loginForm->ShowDialog();
			this->Close();
		}
		else if (result == 2) {
			MessageBox::Show("Имя или пароль уже заняты. Пожалуйста, выберите другие.",
				"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else if (result == 3) {
			MessageBox::Show("Ошибка подключения к базе данных.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			MessageBox::Show("Ошибка при регистрации", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
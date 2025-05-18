#pragma once

#include "User.h"
#include <string>
#include <ctime>


using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;
using namespace System;


namespace QQ {
    public ref class UserPage : public UserControl
    {
    public: UserPage(User^ user);
    public:

    protected:
        ~UserPage();

    private:
        void InitializeComponent(void); // ← вот объявление

    private: System::ComponentModel::IContainer^ components;
    private:
        Label^ user_name;
        TextBox^ title_post;
        PictureBox^ pictureBoxAvatar;
        Panel^ panel;
        Panel^ panel4;
        TableLayoutPanel^ about_user;
        Label^ o_sebe;
        Label^ o_sebe_text;
        Label^ interesi;
        Label^ interesi_text;
        Label^ contacts;
        Label^ contacts_text;
        Label^ birthday;
        Label^ birthday_text;
        TableLayoutPanel^ user_table;
        Button^ user_red;
        Button^ reveal;
        int user_Id;


        void pictureBoxAvatar_Paint(Object^ sender, PaintEventArgs^ e);
        void QQ::UserPage::red_Click(System::Object^ sender, System::EventArgs^ e);
        void QQ::UserPage::user_name_Click(System::Object^ sender, System::EventArgs^ e);
    };
}
#pragma once

#include "User.h"
#include <string>
#include <ctime>

using namespace System::Windows::Forms;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::IO;
using namespace System;


namespace QQ {
    public ref class UserPageRed : public UserControl
    {
    public: UserPageRed(User^ user);
    public: User^ user_izm;

    protected:

        ~UserPageRed();

    private:
        void InitializeComponent(void);

    private: System::ComponentModel::IContainer^ components;

    private:
        Label^ user_name;
        PictureBox^ pictureBoxAvatar;
        Panel^ panel;
        Panel^ panel4;
        Panel^ buttonsPanel;
        TableLayoutPanel^ about_user;
        Label^ o_sebe;
        TextBox^ o_sebe_text;
        Label^ interesi;
        TextBox^ interesi_text;
        Label^ contacts;
        TextBox^ contacts_text;
        Label^ birthday;
        TextBox^ birthday_text;
        Label^ pswd;
        Label^ now_pswd;
        Label^ new_pswd;
        TextBox^ now_pswd_text;
        TextBox^ new_pswd_text;
        TableLayoutPanel^ user_table;
        Button^ upd_photo;
        Button^ save;
        FlowLayoutPanel^ flowLayoutPanel4;
        OpenFileDialog^ openFileDialog1;
        int user_Id;
        MemoryStream^ ms;
        Image^ img;

    private: 
        bool isExpanded2 = true;
    private: array<Byte>^ imageBytes;
    public: delegate void ProfileSavedHandler(User^ updatedUser);
    public: event ProfileSavedHandler^ OnProfileSaved;
        
    public: bool UpdateUserData(User^ user, array<Byte>^ imageData);
          bool UpdateUserFull(QQ::User^ user);


        void pictureBoxAvatar_Paint(Object^ sender, PaintEventArgs^ e);
        void QQ::UserPageRed::username(System::Object^ sender, System::EventArgs^ e);
        void QQ::UserPageRed::save_Click(System::Object^ sender, System::EventArgs^ e);
        void QQ::UserPageRed::UpdatePhoto_Click(System::Object^ sender, System::EventArgs^ e);
        void QQ::UserPageRed::update_pswd_Click(System::Object^ sender, System::EventArgs^ e);
    };
}
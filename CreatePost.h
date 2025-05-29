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
    public ref class CreatePost : public UserControl
    {
    public: CreatePost(User^ user);
    public: User^ user_izm;

    protected:

        ~CreatePost();

    private:
        void InitializeComponent(void);

    private: System::ComponentModel::IContainer^ components;

    private:
        Label^ user_name;
        PictureBox^ testBox;
        Panel^ panel;
        TableLayoutPanel^ post_table;
        Label^ header;
        TextBox^ header_text;
        Label^ text_post;
        TextBox^ text_post_text;
        Label^ add_photo;
        TableLayoutPanel^ main_table;
        Button^ upd_photo;
        Button^ save;
        OpenFileDialog^ openFileDialog1;
        int user_Id;
        MemoryStream^ ms;
        Image^ img;


    private:
        bool isExpanded2 = true;
    private: array<Byte>^ imageBytes;
    //public: delegate void ProfileSavedHandler(User^ updatedUser);
    //public: event ProfileSavedHandler^ OnProfileSaved;

    public:
        //bool UpdateUserFull(QQ::User^ user);
    public:
        delegate void PostSavedHandler(QQ::User^ user);
        PostSavedHandler^ OnPostCreated;


        //void QQ::CreatePost::username(System::Object^ sender, System::EventArgs^ e);
        void QQ::CreatePost::save_Click(System::Object^ sender, System::EventArgs^ e);
        void QQ::CreatePost::UpdatePhoto_Click(System::Object^ sender, System::EventArgs^ e);
    };
}
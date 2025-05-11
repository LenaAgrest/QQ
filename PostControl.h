#pragma once

#include "Post.h"
#include <string>
#include <ctime>


using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;

using namespace System;

namespace QQ {
    public ref class PostControl : public UserControl
    {
    private: System::ComponentModel::IContainer^ components;
    private:
        Label^ user_post;
        Label^ title_post;
        Label^ text_post;
        Label^ date_post;
        PictureBox^ image_post;
        ToolStripMenuItem^ editItem;
        ToolStripMenuItem^ deleteItem;
        System::Windows::Forms::ContextMenuStrip^ svoistva_post;
        Label^ label1;
        Label^ comm_info;
        Label^ label2;
        Panel^ panel2;
        GroupBox^ groupBox1;
        TableLayoutPanel^ tableLayoutPanel1;

    public:
        PostControl(Post^ post)
        {
            this->user_post = gcnew Label();
            this->user_post->Text = post->Author;
            this->user_post->AutoSize = true;
            this->user_post->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->user_post->Location = System::Drawing::Point(3, 3);
            this->user_post->Name = L"user_post";
            this->user_post->Size = System::Drawing::Size(100, 39);

            this->title_post = gcnew Label();
            this->title_post->AutoSize = true;
            this->title_post->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->title_post->Location = System::Drawing::Point(3, 44);
            this->title_post->Name = L"title_post";
            this->title_post->Size = System::Drawing::Size(202, 46);
            this->title_post->Text = post->Title;


            this->text_post = gcnew Label();
            this->text_post->Text = post->Content;
            this->text_post->AutoSize = true;
            this->text_post->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->text_post->Location = System::Drawing::Point(4, 90);
            this->text_post->Name = L"this->text_post";
            this->text_post->Size = System::Drawing::Size(188, 39);


            this->date_post = gcnew Label();
            this->date_post->Text = post->Date->ToString("dd.MM.yyyy hh:mm:ss");
            this->date_post->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
            this->date_post->AutoSize = true;
            this->date_post->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->date_post->Location = System::Drawing::Point(586, 262);
            this->date_post->Name = L"date_post";
            this->date_post->Size = System::Drawing::Size(163, 35);



            this->image_post = gcnew PictureBox();
            this->image_post->InitialImage = nullptr;
            this->image_post->Location = System::Drawing::Point(11, 133);
            this->image_post->Name = L"image_post";
            this->image_post->Size = System::Drawing::Size(100, 50);
            this->image_post->TabIndex = 6;
            this->image_post->TabStop = false;
            this->image_post->SizeMode = PictureBoxSizeMode::Zoom;

            if (post->ImageData != nullptr)
            {
                MemoryStream^ ms = gcnew MemoryStream(post->ImageData);
                this->image_post->Image = Image::FromStream(ms);
            }
            else
            {
                this->image_post->Visible = false;
            }

            this->editItem = gcnew ToolStripMenuItem(L"Редактировать");
            this->deleteItem = gcnew ToolStripMenuItem(L"Удалить");
            this->editItem->Click += gcnew EventHandler(this, &PostControl::Edit_Click);
            this->deleteItem->Click += gcnew EventHandler(this, &PostControl::Delete_Click);

            this->svoistva_post = gcnew System::Windows::Forms::ContextMenuStrip();
            this->svoistva_post->ImageScalingSize = System::Drawing::Size(20, 20);
            this->svoistva_post->Name = L"contextMenuStrip1";
            this->svoistva_post->Size = System::Drawing::Size(61, 4);
            this->svoistva_post->Items->Add(this->editItem);
            this->svoistva_post->Items->Add(this->deleteItem);
            this->svoistva_post->Items->Add(L"Редактировать", nullptr, gcnew EventHandler(this, &PostControl::Edit_Click));
            this->svoistva_post->Items->Add(L"Удалить", nullptr, gcnew EventHandler(this, &PostControl::Delete_Click));



            this->label1 = gcnew Label();
            this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
            this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat ExtraBold", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(709, 3);
            this->label1->Margin = System::Windows::Forms::Padding(0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(40, 23);
            this->label1->TabIndex = 8;
            this->label1->Text = L"...";
            this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
            this->label1->UseCompatibleTextRendering = true;
            this->label1->ContextMenuStrip = this->svoistva_post;



            this->comm_info = gcnew Label();
            this->comm_info->AutoSize = true;
            this->comm_info->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 14.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->comm_info->ForeColor = System::Drawing::SystemColors::ControlDark;
            this->comm_info->Location = System::Drawing::Point(35, 133);
            this->comm_info->Name = L"comm_info";
            this->comm_info->Size = System::Drawing::Size(183, 35);
            this->comm_info->TabIndex = 9;
            this->comm_info->Text = L"Отсутствуют";



            this->label2 = gcnew Label();
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(0, 5);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(227, 39);
            this->label2->TabIndex = 9;
            this->label2->Text = L"Комментарии";



            this->panel2 = gcnew Panel();
            this->panel2->Controls->Add(this->label1);
            this->panel2->Controls->Add(this->date_post);
            this->panel2->Controls->Add(this->image_post);
            this->panel2->Controls->Add(this->text_post);
            this->panel2->Controls->Add(this->title_post);
            this->panel2->Controls->Add(this->user_post);
            this->panel2->Location = System::Drawing::Point(3, 3);
            this->panel2->Name = L"panel2";
            this->panel2->Size = System::Drawing::Size(752, 297);
            this->panel2->TabIndex = 4;



            this->groupBox1 = gcnew GroupBox();
            this->groupBox1->Controls->Add(this->comm_info);
            this->groupBox1->Controls->Add(this->label2);
            this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
            this->groupBox1->Location = System::Drawing::Point(761, 3);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(259, 297);
            this->groupBox1->TabIndex = 5;
            this->groupBox1->TabStop = false;



            this->tableLayoutPanel1 = gcnew TableLayoutPanel();
            this->tableLayoutPanel1->ColumnCount = 2;
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                74.09579F)));
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                25.9042F)));
            this->tableLayoutPanel1->Controls->Add(this->panel2, 0, 0);
            this->tableLayoutPanel1->Controls->Add(this->groupBox1, 1, 0);
            this->tableLayoutPanel1->Location = System::Drawing::Point(3, 3);
            this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
            this->tableLayoutPanel1->RowCount = 1;
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel1->Size = System::Drawing::Size(1023, 303);

            this->Controls->Add(tableLayoutPanel1);
        }

        void Edit_Click(Object^ sender, EventArgs^ e)
        {
            // TODO: переход в блог
        }

        void Delete_Click(Object^ sender, EventArgs^ e)
        {
            // TODO: переход в блог
        }
    };
}
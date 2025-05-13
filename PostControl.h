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
    public: PostControl(Post^ post);
    protected:
        ~PostControl();

    private:
        void InitializeComponent(void); // ← вот объявление

    private: System::ComponentModel::IContainer^ components;
    private:
        Label^ user_post;
        TextBox^ title_post;
        Label^ title_post_l;
        Label^ text_post;
        TextBox^ text_post_t;
        Label^ date_post;
        PictureBox^ image_post;
        ToolStripMenuItem^ editItem;
        ToolStripMenuItem^ deleteItem;
        System::Windows::Forms::ContextMenuStrip^ svoistva_post;
        Label^ label1;
        Label^ comm_info;
        Label^ label2;
        Panel^ panel2;
        Panel^ panel3;
        Button^ save;
        Button^ otmena;
        GroupBox^ groupBox1;
        TableLayoutPanel^ tableLayoutPanel1;
        TableLayoutPanel^ tableLayoutPanel2;

        void Delete_Click(Object^ sender, EventArgs^ e);
        void Label1_Click(Object^ sender, EventArgs^ e);
        void save_Click(System::Object^ sender, System::EventArgs^ e);
        void otmena_Click(System::Object^ sender, System::EventArgs^ e);
        void Edit_Click(Object^ sender, EventArgs^ e);
    };
}
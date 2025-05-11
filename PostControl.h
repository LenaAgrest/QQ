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

    //public: PostControl(Post^ post);
        void Delete_Click(Object^ sender, EventArgs^ e);
        void Edit_Click(Object^ sender, EventArgs^ e);
    };
}
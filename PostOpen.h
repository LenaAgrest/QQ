#pragma once

#include "Post.h"
#include <string>
#include <ctime>


using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;
using namespace System;

int update_post(System::String^ title_post, System::String^ text_post, const int id);

namespace QQ {
    public ref class PostOpen : public UserControl
    {
    public: PostOpen(Post^ post);
    public:

    protected:
        ~PostOpen();

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
        Panel^ panel1;
        Button^ save;
        Button^ otmena;
        TextBox^ comm_tb;
        Button^ comm_send;
        TableLayoutPanel^ tableLayoutPanel1;
        TableLayoutPanel^ tableLayoutPanel2;
        TableLayoutPanel^ tableLayoutPanel3;
        int postId;

    public: delegate void PostOpenHandler(Post^ SelectPost);
    public: event PostOpenHandler^ OpenPost;


        void Delete_Click(Object^ sender, EventArgs^ e);
        void Label1_Click(Object^ sender, EventArgs^ e);
        void save_Click(System::Object^ sender, System::EventArgs^ e);
        void otmena_Click(System::Object^ sender, System::EventArgs^ e);
        void Edit_Click(Object^ sender, EventArgs^ e);
    };
}
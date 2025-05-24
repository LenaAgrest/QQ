#pragma once

#include "Post.h"
#include "Comm.h"
#include <string>
#include <ctime>


using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;
using namespace System;

int update_post(System::String^ title_post, System::String^ text_post, const int id);

namespace QQ {
    public ref class Comment : public UserControl
    {
    public: Comment(Post^ post, Comm^ comm);
    public:

    protected:
        ~Comment();

    private:
        
        void InitializeComponent(void);

    private: System::ComponentModel::IContainer^ components;
    private:
        Label^ user_comm;
        Label^ text_comm;
        Label^ date_post;
        Label^ otvet_user_name;
        ToolStripMenuItem^ deleteItem;
        System::Windows::Forms::ContextMenuStrip^ svoistva_post;
        Label^ label1;
        Label^ comm_info;
        Label^ label2;
        Panel^ panel2;
        Panel^ panel3;
        Panel^ panel1;
        Button^ otvet;
        TextBox^ comm_tb;
        Button^ comm_send;
        TableLayoutPanel^ tableLayoutPanel1;
        TableLayoutPanel^ tableLayoutPanel2;
        TableLayoutPanel^ tableLayoutPanel3;
        int postId;
        int commId;
        Boolean^ its_otvet;
        int serial_otvet;

           void Delete_Click(Object^ sender, EventArgs^ e);
           void Label1_Click(Object^ sender, EventArgs^ e);
           void Comment::otvet_Click(Object^ sender, EventArgs^ e);

    };
}
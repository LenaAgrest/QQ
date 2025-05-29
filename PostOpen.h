#pragma once

#include "Post.h"
#include "Comm.h"
#include <string>
#include <ctime>
#include "Comment.h"


using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;
using namespace System;

namespace QQ {
    public ref class PostOpen : public UserControl
    {
    public: PostOpen(Post^ post);
    public:
        Post^ PostData;
        delegate void PostDeletedHandler();
        PostDeletedHandler^ OnPostDeleted;


    protected:
        ~PostOpen();

    private:
        void InitializeComponent(void);

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
        ToolStripMenuItem^ toggleCommentsItem;
        String^ comm_en;
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
        TableLayoutPanel^ commentsLayout;
        int postId;
    public: bool isPostAuthor;
    private: FlowLayoutPanel^ repliesPanel;

        void Delete_Click(Object^ sender, EventArgs^ e);
        void Label1_Click(Object^ sender, EventArgs^ e);
        void save_Click(System::Object^ sender, System::EventArgs^ e);
        void otmena_Click(System::Object^ sender, System::EventArgs^ e);
        void Edit_Click(Object^ sender, EventArgs^ e);
        void RenderComments();
        void RenderCommentNode(QQ::Comm^ comm, Dictionary<int, Comment^>^ idToUI);
        void RefreshComments(Object^ sender, EventArgs^ e);
        void comm_send_Click(System::Object^ sender, System::EventArgs^ e);

        void ToggleComments_Click(Object^ sender, EventArgs^ e);
        void AuthorLabel_Click(System::Object^ sender, System::EventArgs^ e);

    };
}
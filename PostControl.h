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

    public ref class PostControl : public UserControl
    {
    public:
        PostControl(Post^ post);
        void QQ::PostControl::AttachClickHandlers(Control^ parent);

        ~PostControl();

        Post^ PostData;

        delegate void PostSelectedHandler(Post^ post);
        PostSelectedHandler^ OnPostSelected; 

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
        Label^ label1;
        Label^ label2;
        Panel^ panel2;
        TableLayoutPanel^ tableLayoutPanel1;
        TableLayoutPanel^ tableLayoutPanel2;
        int postId;
        System::Void HandleClick(System::Object^ sender, System::EventArgs^ e);
    };
}
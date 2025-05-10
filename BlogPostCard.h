#pragma once

#include "Post.h"
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::IO;

namespace QQ {
    public ref class BlogPostCard : public UserControl {
    public:
        BlogPostCard(Post^ post) {
            this->Size = Drawing::Size(500, 200);
            //this->BorderStyle = BorderStyle::FixedSingle;

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = post->Title;
            lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
            lblTitle->Location = Point(10, 10);
            lblTitle->AutoSize = true;

            Label^ lblAuthor = gcnew Label();
            lblAuthor->Text = "Автор: " + post->Author;
            lblAuthor->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Italic);
            lblAuthor->Location = Point(10, 40);
            lblAuthor->AutoSize = true;

            Label^ lblContent = gcnew Label();
            lblContent->Text = post->Content;
            lblContent->Location = Point(10, 70);
            lblContent->Size = Drawing::Size(350, 100);

            PictureBox^ imgPreview = gcnew PictureBox();
            imgPreview->SizeMode = PictureBoxSizeMode::Zoom;
            imgPreview->Location = Point(370, 10);
            imgPreview->Size = Drawing::Size(100, 100);

            if (post->ImageData != nullptr && post->ImageData->Length > 0) {
                MemoryStream^ ms = gcnew MemoryStream(post->ImageData);
                imgPreview->Image = Image::FromStream(ms);
            }

            this->Controls->Add(lblTitle);
            this->Controls->Add(lblAuthor);
            this->Controls->Add(lblContent);
            this->Controls->Add(imgPreview);
        }
    };
}
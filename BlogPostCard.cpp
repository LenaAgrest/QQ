#include "BlogPostCard.h"

BlogPostCard::BlogPostCard(String^ title, String^ author, DateTime date, String^ previewText, Image^ image)
{
    this->Width = 400;
    this->Height = 150;
    //this->BorderStyle = BorderStyle::FixedSingle;

    Label^ titleLabel = gcnew Label();
    titleLabel->Text = title;
    titleLabel->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
    titleLabel->Location = Point(10, 10);
    titleLabel->AutoSize = true;

    Label^ authorLabel = gcnew Label();
    authorLabel->Text = "Автор: " + author;
    authorLabel->Location = Point(10, 35);
    authorLabel->AutoSize = true;

    Label^ dateLabel = gcnew Label();
    dateLabel->Text = "Дата: " + date.ToShortDateString();
    dateLabel->Location = Point(10, 55);
    dateLabel->AutoSize = true;

    Label^ previewLabel = gcnew Label();
    previewLabel->Text = previewText;
    previewLabel->Location = Point(10, 75);
    previewLabel->Size = Drawing::Size(380, 40);

    Button^ readButton = gcnew Button();
    readButton->Text = "Читать";
    readButton->Location = Point(300, 120);
    readButton->Click += gcnew EventHandler(this, &BlogPostCard::ReadMore);

    this->Controls->Add(titleLabel);
    this->Controls->Add(authorLabel);
    this->Controls->Add(dateLabel);
    this->Controls->Add(previewLabel);
    this->Controls->Add(readButton);

    if (image != nullptr)
    {
        PictureBox^ pic = gcnew PictureBox();
        pic->Image = image;
        pic->Size = Drawing::Size(100, 100);
        pic->Location = Point(290, 10);
        pic->SizeMode = PictureBoxSizeMode::Zoom;
        this->Controls->Add(pic);
    }
}

void BlogPostCard::ReadMore(Object^ sender, EventArgs^ e)
{
    MessageBox::Show("Открыть подробности поста...");
}

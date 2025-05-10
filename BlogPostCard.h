#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class BlogPostCard : public UserControl
{
public:
    BlogPostCard(String^ title, String^ author, DateTime date, String^ previewText, Image^ image);

private:
    void ReadMore(Object^ sender, EventArgs^ e);
};

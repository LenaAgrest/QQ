#include "PostControl.h"
#include "Post.h"
#include <ctime>
#include <string>

using namespace QQ;

    PostControl::PostControl(Post^ post) {

        InitializeComponent();
        PostData = post;
        postId = post->ID;
        user_post->Text = post->Author;
        title_post_l->Text = post->Title;
        title_post->Text = post->Title;
        text_post->Text = post->Content;
        text_post_t->Text = post->Content;
        date_post->Text = post->Date->ToString("dd.MM.yyyy hh:mm:ss");
        
        if (post->ImageData != nullptr)
        {
            MemoryStream^ ms = gcnew MemoryStream(post->ImageData);
            image_post->Image = Image::FromStream(ms);
            this->image_post->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        }
        else
        {
            this->tableLayoutPanel2->Controls->Remove(this->image_post);
            this->image_post = nullptr;
        }    
        this->tableLayoutPanel2->Click += gcnew EventHandler(this, &PostControl::HandleClick);
        for each (Control ^ ctrl in this->Controls) {
            ctrl->Click += gcnew EventHandler(this, &PostControl::HandleClick);
        }
        AttachClickHandlers(this); // Рекурсивно добавляем обработчик клика на всё содержимое
    }

    void PostControl::InitializeComponent(void)
    {
        this->AutoSize = true;

        this->user_post = gcnew Label();
        this->user_post->AutoSize = true;
        this->user_post->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point));
        this->user_post->Location = System::Drawing::Point(3, 3);
        this->user_post->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left));


        this->title_post_l = gcnew Label();
        this->title_post_l->AutoSize = true;
        this->title_post_l->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
        this->title_post_l->Location = System::Drawing::Point(4, 90);
        this->title_post_l->Dock = DockStyle::Fill;

        this->title_post = gcnew TextBox();
        this->text_post_t = gcnew TextBox();

        this->text_post = gcnew Label();
        this->text_post->AutoSize = true;
        this->text_post->Font = (gcnew System::Drawing::Font(L"Montserrat", 13.8F, System::Drawing::FontStyle::Regular));
        this->text_post->Location = System::Drawing::Point(4, 90);
        this->text_post->Name = L"this->text_post";
        this->text_post->Dock = DockStyle::Fill;
        this->text_post->MaximumSize = System::Drawing::Size(1010, 0);


        this->image_post = gcnew PictureBox();
        this->image_post->InitialImage = nullptr;
        this->image_post->Location = System::Drawing::Point(11, 133);
        this->image_post->Name = L"image_post";
        this->image_post->Size = System::Drawing::Size(200, 200);
        this->image_post->TabIndex = 6;
        this->image_post->TabStop = false;
        this->image_post->SizeMode = PictureBoxSizeMode::Zoom;


        this->panel2 = gcnew Panel();
        this->panel2->AutoSize = true;
        this->panel2->Dock = DockStyle::Top;
        this->panel2->TabIndex = 4;
        this->panel2->Controls->Add(label1);
        this->panel2->Controls->Add(user_post);


        this->date_post = gcnew Label();
        this->date_post->Font = (gcnew System::Drawing::Font(L"Montserrat", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point));
        this->date_post->TextAlign = ContentAlignment::BottomRight;
        this->date_post->Dock = DockStyle::Top;
        this->date_post->AutoSize = true;


        this->tableLayoutPanel2 = gcnew TableLayoutPanel();
        this->tableLayoutPanel2->Dock = DockStyle::Fill;
        this->tableLayoutPanel2->AutoSize = true;
        this->tableLayoutPanel2->AutoSizeMode = Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->tableLayoutPanel2->ColumnCount = 1;
        this->tableLayoutPanel2->BackColor = System::Drawing::Color::White;
        this->tableLayoutPanel2->RowCount = 0;
        this->tableLayoutPanel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->tableLayoutPanel2->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
        this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
        this->tableLayoutPanel2->Controls->Add(this->panel2);
        this->tableLayoutPanel2->Controls->Add(this->title_post_l);
        this->tableLayoutPanel2->Controls->Add(this->text_post);
        this->tableLayoutPanel2->Controls->Add(this->image_post);
        this->tableLayoutPanel2->Controls->Add(this->date_post);
        this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
        this->tableLayoutPanel2->Size = System::Drawing::Size(1018, 402);
        this->tableLayoutPanel2->MaximumSize = System::Drawing::Size(1018, 0);
        this->Controls->Add(tableLayoutPanel2);

        /*
        this->tableLayoutPanel1 = gcnew TableLayoutPanel();
        this->tableLayoutPanel1->ColumnCount = 1;
        this->tableLayoutPanel1->BackColor = System::Drawing::Color::White;
        this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
        this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::AutoSize)));
        this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 0);
        this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
        this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
        this->tableLayoutPanel1->RowCount = 1;
        this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
        this->tableLayoutPanel1->AutoSize = true;
        this->tableLayoutPanel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->tableLayoutPanel1->Size = System::Drawing::Size(1018, 410);
        */
        
        
        //this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
        //this->tableLayoutPanel1->Location = System::Drawing::Point(3, 255);
        // */
    }
    void QQ::PostControl::AttachClickHandlers(Control^ parent)
    {
        parent->Click += gcnew EventHandler(this, &PostControl::HandleClick);
        for each (Control ^ child in parent->Controls)
        {
            AttachClickHandlers(child);
        }
    }


    void QQ::PostControl::HandleClick(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->OnPostSelected != nullptr) {
            this->OnPostSelected(PostData);
        }
    }
    

    PostControl::~PostControl()
    {
    }
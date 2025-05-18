#include "UserPage.h"
#include "User.h"
#include <ctime>
#include <string>

using namespace QQ;

UserPage::UserPage(User^ user) {

    InitializeComponent();
    user_Id = user->ID;
    user_name->Text = user->Username;
	o_sebe_text->Text = user->About;
	interesi_text->Text = user->Interests;
	contacts_text->Text = user->Contacts;
	birthday_text->Text = user->Date->ToString("dd.MM.yyyy hh:mm:ss");
    /*title_post_l->Text = post->Title;
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

    comm_info->Text = post->CommentsAllowed ? L"Разрешены" : L"Запрещены";*/
}

void UserPage::InitializeComponent(void)
{
    this->AutoSize = true;


    this->user_name->AutoSize = true;
    this->user_name->Font = (gcnew System::Drawing::Font(L"Montserrat", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
        static_cast<System::Byte>(204)));
    this->user_name->ForeColor = System::Drawing::Color::White;
    this->user_name->Location = System::Drawing::Point(166, 36);
    this->user_name->Size = System::Drawing::Size(188, 69);
    this->user_name->TabIndex = 1;
    // 
    // reveal
    // 
	this->about_user->AutoSize = true;
	this->about_user->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->about_user->BackColor = System::Drawing::Color::SlateBlue;
	this->about_user->ColumnCount = 1;
	this->about_user->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
		100)));
	this->about_user->Controls->Add(this->birthday_text, 0, 7);
	this->about_user->Controls->Add(this->birthday, 0, 6);
	this->about_user->Controls->Add(this->contacts_text, 0, 5);
	this->about_user->Controls->Add(this->contacts, 0, 4);
	this->about_user->Controls->Add(this->interesi_text, 0, 3);
	this->about_user->Controls->Add(this->interesi, 0, 2);
	this->about_user->Controls->Add(this->o_sebe_text, 0, 1);
	this->about_user->Controls->Add(this->o_sebe, 0, 0);
	this->about_user->Dock = System::Windows::Forms::DockStyle::Fill;
	this->about_user->Location = System::Drawing::Point(0, 140);
	this->about_user->Margin = System::Windows::Forms::Padding(0);
	this->about_user->Name = L"about_user";
	this->about_user->RowCount = 8;
	this->about_user->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->about_user->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->about_user->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->about_user->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->about_user->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->about_user->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->about_user->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->about_user->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->about_user->Size = System::Drawing::Size(1200, 434);
	this->about_user->TabIndex = 5;



	this->birthday_text->AutoSize = true;
	this->birthday_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->birthday_text->ForeColor = System::Drawing::Color::White;
	this->birthday_text->Location = System::Drawing::Point(3, 398);
	this->birthday_text->Margin = System::Windows::Forms::Padding(3);
	this->birthday_text->MaximumSize = System::Drawing::Size(1200, 0);
	this->birthday_text->Name = L"birthday_text";
	this->birthday_text->Size = System::Drawing::Size(221, 33);
	this->birthday_text->TabIndex = 10;
	this->birthday_text->Text = L"хуйней страдать";
	// 
	// birthday
	// 
	this->birthday->AutoSize = true;
	this->birthday->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->birthday->ForeColor = System::Drawing::Color::White;
	this->birthday->Location = System::Drawing::Point(3, 345);
	this->birthday->Margin = System::Windows::Forms::Padding(3);
	this->birthday->Name = L"birthday";
	this->birthday->Size = System::Drawing::Size(310, 47);
	this->birthday->TabIndex = 9;
	this->birthday->Text = L"День рождения";
	// 
	// contacts_text
	// 
	this->contacts_text->AutoSize = true;
	this->contacts_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->contacts_text->ForeColor = System::Drawing::Color::White;
	this->contacts_text->Location = System::Drawing::Point(3, 306);
	this->contacts_text->Margin = System::Windows::Forms::Padding(3);
	this->contacts_text->MaximumSize = System::Drawing::Size(1200, 0);
	this->contacts_text->Name = L"contacts_text";
	this->contacts_text->Size = System::Drawing::Size(221, 33);
	this->contacts_text->TabIndex = 8;
	this->contacts_text->Text = L"хуйней страдать";
	// 
	// contacts
	// 
	this->contacts->AutoSize = true;
	this->contacts->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->contacts->ForeColor = System::Drawing::Color::White;
	this->contacts->Location = System::Drawing::Point(3, 253);
	this->contacts->Margin = System::Windows::Forms::Padding(3);
	this->contacts->Name = L"contacts";
	this->contacts->Size = System::Drawing::Size(192, 47);
	this->contacts->TabIndex = 7;
	this->contacts->Text = L"Контакты";
	// 
	// interesi_text
	// 
	this->interesi_text->AutoSize = true;
	this->interesi_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->interesi_text->ForeColor = System::Drawing::Color::White;
	this->interesi_text->Location = System::Drawing::Point(3, 214);
	this->interesi_text->Margin = System::Windows::Forms::Padding(3);
	this->interesi_text->MaximumSize = System::Drawing::Size(1200, 0);
	this->interesi_text->Name = L"interesi_text";
	this->interesi_text->Size = System::Drawing::Size(221, 33);
	this->interesi_text->TabIndex = 6;
	this->interesi_text->Text = L"хуйней страдать";
	// 
	// interesi
	// 
	this->interesi->AutoSize = true;
	this->interesi->Dock = System::Windows::Forms::DockStyle::Fill;
	this->interesi->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->interesi->ForeColor = System::Drawing::Color::White;
	this->interesi->Location = System::Drawing::Point(3, 161);
	this->interesi->Margin = System::Windows::Forms::Padding(3);
	this->interesi->Name = L"interesi";
	this->interesi->Size = System::Drawing::Size(1194, 47);
	this->interesi->TabIndex = 5;
	this->interesi->Text = L"Интересы";
	// 
	// o_sebe_text
	// 
	this->o_sebe_text->AutoSize = true;
	this->o_sebe_text->Dock = System::Windows::Forms::DockStyle::Fill;
	this->o_sebe_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->o_sebe_text->ForeColor = System::Drawing::Color::White;
	this->o_sebe_text->Location = System::Drawing::Point(3, 56);
	this->o_sebe_text->Margin = System::Windows::Forms::Padding(3);
	this->o_sebe_text->MaximumSize = System::Drawing::Size(1200, 0);
	this->o_sebe_text->Name = L"o_sebe_text";
	this->o_sebe_text->Size = System::Drawing::Size(1194, 99);
	this->o_sebe_text->TabIndex = 4;
	// 
	// o_sebe
	// 
	this->o_sebe->AutoSize = true;
	this->o_sebe->Dock = System::Windows::Forms::DockStyle::Fill;
	this->o_sebe->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->o_sebe->ForeColor = System::Drawing::Color::White;
	this->o_sebe->Location = System::Drawing::Point(3, 3);
	this->o_sebe->Margin = System::Windows::Forms::Padding(3);
	this->o_sebe->Name = L"o_sebe";
	this->o_sebe->Size = System::Drawing::Size(1194, 47);
	this->o_sebe->TabIndex = 1;
	this->o_sebe->Text = L"О себе";
	// 
	// user_table
	// 
	this->user_table->AutoSize = true;
	this->user_table->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->user_table->ColumnCount = 1;
	this->user_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
		100)));
	this->user_table->Controls->Add(this->panel4, 0, 0);
	this->user_table->Controls->Add(this->about_user, 0, 1);
	//this->user_table->Controls->Add(this->tableLayoutPanel1, 0, 2);
	this->user_table->Location = System::Drawing::Point(14, 13);
	this->user_table->Name = L"user_table";
	this->user_table->RowCount = 3;
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->user_table->Size = System::Drawing::Size(1200, 968);
	this->user_table->TabIndex = 4;
	// 
	// panel4
	// 
	this->panel4->BackColor = System::Drawing::Color::SlateBlue;
	this->panel4->Controls->Add(this->reveal);
	this->panel4->Controls->Add(this->user_red);
	this->panel4->Controls->Add(this->user_name);
	this->panel4->Controls->Add(this->pictureBoxAvatar);
	this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
	this->panel4->Location = System::Drawing::Point(0, 0);
	this->panel4->Margin = System::Windows::Forms::Padding(0);
	this->panel4->Name = L"panel4";
	this->panel4->Size = System::Drawing::Size(1200, 140);
	this->panel4->TabIndex = 0;
	// 
	// reveal
	// 
	this->reveal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
	this->reveal->AutoSize = true;
	this->reveal->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->reveal->BackColor = System::Drawing::Color::SlateBlue;
	this->reveal->FlatAppearance->BorderSize = 0;
	this->reveal->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->reveal->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 26, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->reveal->ForeColor = System::Drawing::Color::White;
	this->reveal->Location = System::Drawing::Point(1122, 26);
	this->reveal->Margin = System::Windows::Forms::Padding(3, 53, 10, 53);
	this->reveal->Name = L"reveal";
	this->reveal->Size = System::Drawing::Size(68, 71);
	this->reveal->TabIndex = 3;
	this->reveal->Text = L"V";
	this->reveal->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
	this->reveal->UseVisualStyleBackColor = false;
	// 
	// user_red
	// 
	this->user_red = gcnew Button();
	this->user_red->Click += gcnew System::EventHandler(this, &UserPage::red_Click);
	this->user_red->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
	this->user_red->AutoSize = true;
	this->user_red->BackColor = System::Drawing::Color::MediumSlateBlue;
	this->user_red->FlatAppearance->BorderSize = 0;
	this->user_red->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->user_red->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 14, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->user_red->ForeColor = System::Drawing::Color::White;
	this->user_red->Location = System::Drawing::Point(907, 44);
	this->user_red->Margin = System::Windows::Forms::Padding(3, 53, 10, 53);
	this->user_red->Name = L"user_red";
	this->user_red->Size = System::Drawing::Size(219, 43);
	this->user_red->TabIndex = 2;
	this->user_red->Text = L"Редактировать";
	this->user_red->UseVisualStyleBackColor = false;
	// 
	// label3
	// 
	this->user_name->AutoSize = true;
	this->user_name->Font = (gcnew System::Drawing::Font(L"Montserrat", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->user_name->ForeColor = System::Drawing::Color::White;
	this->user_name->Location = System::Drawing::Point(166, 36);
	this->user_name->Margin = System::Windows::Forms::Padding(3, 34, 3, 34);
	this->user_name->Name = L"label3";
	this->user_name->Size = System::Drawing::Size(188, 69);
	this->user_name->TabIndex = 1;
	this->user_name->Text = L"label3";
	this->user_name->Click += gcnew System::EventHandler(this, &UserPage::user_name_Click);
	// 
	// pictureBoxAvatar
	// 
	this->pictureBoxAvatar->Anchor = System::Windows::Forms::AnchorStyles::Left;
	this->pictureBoxAvatar->Location = System::Drawing::Point(40, 10);
	this->pictureBoxAvatar->Margin = System::Windows::Forms::Padding(50, 10, 3, 10);
	this->pictureBoxAvatar->Size = System::Drawing::Size(120, 120);
	this->pictureBoxAvatar->TabIndex = 0;
	this->pictureBoxAvatar->TabStop = false;
	this->pictureBoxAvatar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
	this->pictureBoxAvatar->ErrorImage = nullptr;
	this->pictureBoxAvatar->InitialImage = nullptr;
	this->pictureBoxAvatar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &UserPage::pictureBoxAvatar_Paint);

    this->Controls->Add(user_table);
}

void QQ::UserPage::pictureBoxAvatar_Paint(Object^ sender, PaintEventArgs^ e)
{
    auto path = gcnew Drawing2D::GraphicsPath();
    path->AddEllipse(0, 0, pictureBoxAvatar->Width - 1, pictureBoxAvatar->Height - 1);
    this->pictureBoxAvatar->Region = gcnew System::Drawing::Region(path);
}

void QQ::UserPage::red_Click(System::Object^ sender, System::EventArgs^ e)
{
}

void QQ::UserPage::user_name_Click(System::Object^ sender, System::EventArgs^ e)
{
}

UserPage::~UserPage()
{
}


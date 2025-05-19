#include "UserPage.h"
#include "User.h"
#include "PostControl.h"
#include "PostRepository.h"
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

	post_Load(user);
}

void UserPage::InitializeComponent(void)
{
	resources = (gcnew System::ComponentModel::ComponentResourceManager(UserPage::typeid));

    this->AutoSize = true;
    

	this->birthday_text = gcnew Label();
	this->birthday_text->AutoSize = true;
	this->birthday_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->birthday_text->ForeColor = System::Drawing::Color::White;
	this->birthday_text->Location = System::Drawing::Point(3, 3);
	this->birthday_text->Margin = System::Windows::Forms::Padding(3);
	this->birthday_text->MaximumSize = System::Drawing::Size(1004, 0);
	this->birthday_text->Size = System::Drawing::Size(1004, 33);
	//this->birthday_text->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// birthday
	// 
	this->birthday = gcnew Label();
	this->birthday->Text = L"День рождения";
	this->birthday->AutoSize = true;
	this->birthday->Dock = System::Windows::Forms::DockStyle::Fill;
	this->birthday->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold));
	this->birthday->ForeColor = System::Drawing::Color::White;
	this->birthday->Location = System::Drawing::Point(3, 3);
	this->birthday->Margin = System::Windows::Forms::Padding(3);
	this->birthday->Size = System::Drawing::Size(1004, 47);
	//this->birthday->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// contacts_text
	// 
	this->contacts_text = gcnew Label();
	this->contacts_text->AutoSize = true;
	this->contacts_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->contacts_text->ForeColor = System::Drawing::Color::White;
	this->contacts_text->Location = System::Drawing::Point(3, 3);
	this->contacts_text->Margin = System::Windows::Forms::Padding(3);
	this->contacts_text->MaximumSize = System::Drawing::Size(1004, 0);
	this->contacts_text->Size = System::Drawing::Size(1004, 33);
	//this->contacts_text->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// contacts
	// 
	this->contacts = gcnew Label();
	this->contacts->Text = L"Контакты";
	this->contacts->AutoSize = true;
	this->contacts->Dock = System::Windows::Forms::DockStyle::Fill;
	this->contacts->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold));
	this->contacts->ForeColor = System::Drawing::Color::White;
	this->contacts->Location = System::Drawing::Point(3, 3);
	this->contacts->Margin = System::Windows::Forms::Padding(3);
	this->contacts->Size = System::Drawing::Size(1004, 47);
	//this->contacts->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// interesi_text
	// 
	this->interesi_text = gcnew Label();
	this->interesi_text->AutoSize = true;
	this->interesi_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->interesi_text->ForeColor = System::Drawing::Color::White;
	this->interesi_text->Margin = System::Windows::Forms::Padding(3);
	this->interesi_text->Location = System::Drawing::Point(0, 0); //3, 214
	this->interesi_text->MaximumSize = System::Drawing::Size(1004, 0);
	this->interesi_text->Size = System::Drawing::Size(1000, 200);
	//this->interesi_text->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// interesi
	// 
	this->interesi = gcnew Label();
	this->interesi->Text = L"Интересы";
	this->interesi->AutoSize = true;
	this->interesi->Dock = System::Windows::Forms::DockStyle::Fill;
	this->interesi->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold));
	this->interesi->ForeColor = System::Drawing::Color::White;
	this->interesi->Location = System::Drawing::Point(3, 3); //3, 161
	this->interesi->Margin = System::Windows::Forms::Padding(3);
	this->interesi->Size = System::Drawing::Size(1004, 47);
	//this->interesi->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// o_sebe_text
	// 
	this->o_sebe_text = gcnew Label();
	this->o_sebe_text->AutoSize = true;
	//this->o_sebe_text->Dock = System::Windows::Forms::DockStyle::Fill;
	this->o_sebe_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->o_sebe_text->ForeColor = System::Drawing::Color::White;
	this->o_sebe_text->Location = System::Drawing::Point(3, 56);
	this->o_sebe_text->Margin = System::Windows::Forms::Padding(3);
	this->o_sebe_text->MaximumSize = System::Drawing::Size(1010, 0);
	this->o_sebe_text->Size = System::Drawing::Size(1000, 99);
	//this->o_sebe_text->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// o_sebe
	// 
	this->o_sebe = gcnew Label();
	this->o_sebe->Text = L"О себе";
	this->o_sebe->Dock = DockStyle::Fill;
	this->o_sebe->Margin = System::Windows::Forms::Padding(3);
	this->o_sebe->Font = gcnew System::Drawing::Font(L"Montserrat", 20, FontStyle::Bold);
	this->o_sebe->ForeColor = Color::White;
	this->o_sebe->AutoSize = true;
	this->o_sebe->Location = System::Drawing::Point(3, 3);
	this->o_sebe->Size = System::Drawing::Size(1004, 47);
	//this->o_sebe->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;


	// Редактировать
	this->user_red = gcnew Button();
	this->user_red->Click += gcnew System::EventHandler(this, &UserPage::red_Click);
	this->user_red->BackColor = System::Drawing::Color::MediumSlateBlue;
	this->user_red->FlatAppearance->BorderSize = 0;
	this->user_red->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->user_red->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 14, System::Drawing::FontStyle::Bold));
	this->user_red->ForeColor = System::Drawing::Color::White;
	this->user_red->Size = System::Drawing::Size(190, 45);
	this->user_red->Location = System::Drawing::Point(15, 45); // внутри buttonsPanel
	this->user_red->Text = L"Редактировать";


	// V
	this->reveal = gcnew Button();
	this->reveal->Click += gcnew System::EventHandler(this, &UserPage::open_Click);
	this->reveal->BackColor = System::Drawing::Color::SlateBlue;
	this->reveal->FlatAppearance->BorderSize = 0;
	this->reveal->BackgroundImage = Image::FromFile("info_down.png");
	this->reveal->BackgroundImageLayout = ImageLayout::Zoom;
	this->reveal->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	//this->reveal->Font = (gcnew System::Drawing::Font(L"Montserrat Medium", 22));
	this->reveal->ForeColor = System::Drawing::Color::White;
	this->reveal->Size = System::Drawing::Size(50, 45);
	this->reveal->Location = System::Drawing::Point(210, 45);


	this->buttonsPanel = gcnew Panel();
	this->buttonsPanel->Size = System::Drawing::Size(270, 120); // фиксированная ширина
	this->buttonsPanel->Dock = DockStyle::Right;
	//this->buttonsPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->buttonsPanel->BackColor = System::Drawing::Color::SlateBlue;
	this->buttonsPanel->Controls->Add(this->user_red);
	this->buttonsPanel->Controls->Add(this->reveal);
	// 
	// label3
	// 
	this->user_name = gcnew Label();
	this->user_name->AutoSize = true;
	//this->user_name->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->user_name->Font = (gcnew System::Drawing::Font(L"Montserrat", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->user_name->ForeColor = System::Drawing::Color::White;
	this->user_name->Location = System::Drawing::Point(166, 36);
	this->user_name->Margin = System::Windows::Forms::Padding(3, 34, 3, 34);
	this->user_name->Size = System::Drawing::Size(188, 69);
	this->user_name->TabIndex = 1;
	this->user_name->Text = L"label3";
	this->user_name->Click += gcnew System::EventHandler(this, &UserPage::user_name_Click);
	// 
	// pictureBoxAvatar
	// 
	this->pictureBoxAvatar = gcnew PictureBox();
	//this->pictureBoxAvatar->Anchor = System::Windows::Forms::AnchorStyles::Left;
	this->pictureBoxAvatar->BackgroundImage = Image::FromFile("ava.png");
	this->pictureBoxAvatar->Location = System::Drawing::Point(40, 10);
	this->pictureBoxAvatar->Margin = System::Windows::Forms::Padding(50, 10, 3, 10);
	this->pictureBoxAvatar->Size = System::Drawing::Size(120, 120);
	this->pictureBoxAvatar->TabIndex = 0;
	//this->pictureBoxAvatar->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->pictureBoxAvatar->TabStop = false;
	this->pictureBoxAvatar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
	this->pictureBoxAvatar->ErrorImage = nullptr;
	this->pictureBoxAvatar->InitialImage = nullptr;
	this->pictureBoxAvatar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &UserPage::pictureBoxAvatar_Paint);
	


	this->create_post = gcnew Button();
	this->create_post->Click += gcnew System::EventHandler(this, &UserPage::createPost_Click);
	this->create_post->BackColor = System::Drawing::Color::MediumSlateBlue;
	this->create_post->FlatAppearance->BorderSize = 0;
	this->create_post->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->create_post->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold));
	this->create_post->ForeColor = System::Drawing::Color::White;
	this->create_post->Size = System::Drawing::Size(190, 50);
	this->create_post->Dock = DockStyle::Fill;
	this->create_post->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
	this->create_post->Text = L"Создать пост";
	
	// 
	// panel4
	// 
	this->panel4 = gcnew Panel();
	this->panel4->BackColor = System::Drawing::Color::SlateBlue;
	this->panel4->Controls->Add(this->pictureBoxAvatar);
	this->panel4->Controls->Add(this->user_name);
	this->panel4->Controls->Add(this->buttonsPanel);
	this->panel4->Dock = System::Windows::Forms::DockStyle::Top;
	this->panel4->Location = System::Drawing::Point(0, 0);
	this->panel4->Margin = System::Windows::Forms::Padding(2);
	this->panel4->Name = L"panel4";
	this->panel4->Size = System::Drawing::Size(1010, 140);



	this->about_user = gcnew TableLayoutPanel();
	this->about_user->AutoSize = true;
	this->about_user->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
	this->about_user->BackColor = System::Drawing::Color::SlateBlue;
	this->about_user->Dock = System::Windows::Forms::DockStyle::Fill;
	this->about_user->ColumnCount = 1;
	this->about_user->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 100));
	this->about_user->Location = System::Drawing::Point(0, 0);
	this->about_user->Margin = System::Windows::Forms::Padding(2, 0, 2, 2);
	this->about_user->RowCount = 8; // будет нарастать динамически
	this->about_user->Size = System::Drawing::Size(1010, 434);
	this->about_user->MaximumSize = System::Drawing::Size(1010, 0);
	//this->about_user->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// user_table
	// 
	this->user_table = gcnew TableLayoutPanel();
	this->user_table->AutoSize = true;
	this->user_table->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
	this->user_table->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->user_table->ColumnCount = 1;
	this->user_table->Dock = DockStyle::Fill;
	this->user_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,100)));
	this->user_table->Controls->Add(this->panel4, 0, 0);
	this->user_table->Controls->Add(this->about_user, 0, 1);
	this->user_table->Controls->Add(this->create_post, 0, 2);
	this->user_table->Location = System::Drawing::Point(0, 0);
	this->user_table->RowCount = 4;
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->user_table->Size = System::Drawing::Size(1018, 720);
	this->Controls->Add(this->user_table);
}

void QQ::UserPage::pictureBoxAvatar_Paint(Object^ sender, PaintEventArgs^ e)
{
    auto path = gcnew Drawing2D::GraphicsPath();
    path->AddEllipse(0, 0, pictureBoxAvatar->Width - 1, pictureBoxAvatar->Height - 1);
    this->pictureBoxAvatar->Region = gcnew System::Drawing::Region(path);
}

void QQ::UserPage::post_Load(User^ user)
{
	try {
		List<QQ::Post^>^ posts = PostRepository::LoadPostsUser(user);

		// Добавляем каждый пост как элемент управления
		for each (QQ::Post ^ post in posts) {
			QQ::PostControl^ control = gcnew QQ::PostControl(post);
			//control->Margin = System::Windows::Forms::Padding(0,10,0,0);
			this->user_table->Controls->Add(control, 0, 3);
			control->Dock = DockStyle::Left;
		}

	}
	catch (Exception^ ex) {
		MessageBox::Show("Ошибка при загрузке постов: " + ex->Message);
	}
}

void QQ::UserPage::red_Click(System::Object^ sender, System::EventArgs^ e)
{
}

void QQ::UserPage::open_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (isExpanded) {
		// Добавляем только если этих контролов ещё нет в таблице
		if (o_sebe_text->Text != "" && !about_user->Controls->Contains(o_sebe))
		{
			about_user->Controls->Add(o_sebe);
			about_user->Controls->Add(o_sebe_text);
		}
		if (interesi_text->Text != "" && !about_user->Controls->Contains(interesi))
		{
			about_user->Controls->Add(interesi);
			about_user->Controls->Add(interesi_text);
		}
		if (contacts_text->Text != "" && !about_user->Controls->Contains(contacts))
		{
			about_user->Controls->Add(contacts);
			about_user->Controls->Add(contacts_text);
		}
		if (birthday_text->Text != "" && !about_user->Controls->Contains(birthday))
		{
			about_user->Controls->Add(birthday);
			about_user->Controls->Add(birthday_text);
		}

		this->user_table->Controls->Add(about_user, 0, 1);
		this->reveal->BackgroundImage = Image::FromFile("info_up.png");
	}
	else {
		this->user_table->Controls->Remove(about_user);
		this->reveal->BackgroundImage = Image::FromFile("info_down.png");
	}
	isExpanded = !isExpanded;
}

void QQ::UserPage::createPost_Click(System::Object^ sender, System::EventArgs^ e)
{

}

void QQ::UserPage::user_name_Click(System::Object^ sender, System::EventArgs^ e)
{
}

UserPage::~UserPage()
{
}


#include "PostOpen.h"
#include <ctime>
#include <string>

using namespace QQ;

PostOpen::PostOpen(Post^ post) {

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
	this->tableLayoutPanel2->Click += gcnew EventHandler(this, &PostOpen::HandleClick);
	for each(Control ^ ctrl in this->Controls) {
		ctrl->Click += gcnew EventHandler(this, &PostOpen::HandleClick);
	}
	AttachClickHandlers(this);

	//comm_info->Text = post->CommentsAllowed ? L"Отсутствуют" : L"Запрещены";
}

void PostOpen::InitializeComponent(void)
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
	this->title_post_l->MaximumSize = System::Drawing::Size(1010, 0);


	this->title_post = gcnew TextBox();
	this->text_post_t = gcnew TextBox();

	this->text_post = gcnew Label();
	this->text_post->AutoSize = true;
	this->text_post->Font = (gcnew System::Drawing::Font(L"Montserrat", 13.8F, System::Drawing::FontStyle::Regular));
	this->text_post->Location = System::Drawing::Point(4, 90);
	this->text_post->Dock = DockStyle::Fill;
	this->text_post->MaximumSize = System::Drawing::Size(1010, 0);



	this->image_post = gcnew PictureBox();
	this->image_post->InitialImage = nullptr;
	this->image_post->Location = System::Drawing::Point(11, 133);
	this->image_post->Size = System::Drawing::Size(200, 200);
	this->image_post->TabIndex = 6;
	this->image_post->TabStop = false;
	this->image_post->SizeMode = PictureBoxSizeMode::Zoom;



	this->svoistva_post = gcnew System::Windows::Forms::ContextMenuStrip();
	this->svoistva_post->ImageScalingSize = System::Drawing::Size(20, 20);
	this->svoistva_post->ShowImageMargin = false;
	this->svoistva_post->Name = L"contextMenuStrip1";
	this->svoistva_post->Size = System::Drawing::Size(61, 4);
	this->svoistva_post->Items->Add(L"Редактировать", nullptr, gcnew EventHandler(this, &PostOpen::Edit_Click));
	this->svoistva_post->Items->Add(L"Удалить", nullptr, gcnew EventHandler(this, &PostOpen::Delete_Click));


	this->label1 = gcnew Label();
	this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
	this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat ExtraBold", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(40, 20);
	this->label1->TabIndex = 8;
	this->label1->Text = L"...";
	this->label1->Dock = DockStyle::Right;
	this->label1->UseCompatibleTextRendering = true;
	this->label1->ContextMenuStrip = this->svoistva_post;
	this->label1->Click += gcnew System::EventHandler(this, &PostOpen::Label1_Click);


	/*this->comm_info = gcnew Label();
	this->comm_info->AutoSize = true;
	this->comm_info->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 14.8F, System::Drawing::FontStyle::Bold));
	this->comm_info->ForeColor = System::Drawing::SystemColors::ControlDark;
	this->comm_info->Location = System::Drawing::Point(35, 133);
	this->comm_info->Name = L"comm_info";
	this->comm_info->Size = System::Drawing::Size(183, 35);
	this->comm_info->TabIndex = 9;


	this->label2 = gcnew Label();
	this->label2->AutoSize = true;
	this->label2->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point));
	this->label2->Location = System::Drawing::Point(0, 5);
	this->label2->TabIndex = 9;
	this->label2->Text = L"Комментарии";*/


	this->panel2 = gcnew Panel();
	this->panel2->AutoSize = true;
	this->panel2->Dock = DockStyle::Top;
	this->panel2->TabIndex = 4;
	this->panel2->Controls->Add(label1);
	this->panel2->Controls->Add(user_post);


	this->save = gcnew Button();
	this->otmena = gcnew Button();
	this->date_post = gcnew Label();

	this->panel3 = gcnew Panel();
	this->panel3->Size = System::Drawing::Size(730, 30);
	this->panel3->Dock = DockStyle::Top;
	this->panel3->TabIndex = 4;
	this->panel3->Controls->Add(this->date_post);


	this->date_post->Font = (gcnew System::Drawing::Font(L"Montserrat", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point));
	this->date_post->TextAlign = ContentAlignment::BottomRight;
	this->date_post->Dock = DockStyle::Right;
	this->date_post->AutoSize = true;

	











	/*
	// 
	// comm_send
	// 
	this->comm_send = gcnew Button();
	this->comm_send->AutoSize = true;
	this->comm_send->BackColor = System::Drawing::Color::MediumSlateBlue;
	this->comm_send->Dock = System::Windows::Forms::DockStyle::Right;
	this->comm_send->FlatAppearance->BorderSize = 0;
	this->comm_send->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->comm_send->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 10, System::Drawing::FontStyle::Bold));
	this->comm_send->ForeColor = System::Drawing::Color::White;
	this->comm_send->Location = System::Drawing::Point(438, 0);
	this->comm_send->Margin = System::Windows::Forms::Padding(30, 7, 3, 3);
	this->comm_send->Name = L"comm_send";
	this->comm_send->Size = System::Drawing::Size(30, 34);
	this->comm_send->TabIndex = 6;
	this->comm_send->Text = L">";
	this->comm_send->UseVisualStyleBackColor = false;
	// 
	// comm_tb
	// 
	this->comm_tb = gcnew TextBox();
	this->comm_tb->Dock = System::Windows::Forms::DockStyle::Fill;
	this->comm_tb->Location = System::Drawing::Point(0, 0);
	this->comm_tb->Margin = System::Windows::Forms::Padding(3);
	this->comm_tb->MaximumSize = System::Drawing::Size(1000 - comm_send->Width, 0);
	this->comm_tb->Multiline = true;
	this->comm_tb->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 14.8F, System::Drawing::FontStyle::Bold));
	this->comm_tb->Size = System::Drawing::Size(435, 34);
	this->comm_tb->TabIndex = 0;


	this->panel1 = gcnew Panel();
	this->panel1->Controls->Add(this->comm_send);
	this->panel1->Controls->Add(this->comm_tb);
	this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
	this->panel1->Location = System::Drawing::Point(3, 115);
	this->panel1->Size = System::Drawing::Size(468, 34);
	this->panel1->TabIndex = 1;*/
	
	this->tableLayoutPanel2 = gcnew TableLayoutPanel();
	this->tableLayoutPanel2->Dock = DockStyle::Fill;
	this->tableLayoutPanel2->AutoSize = true;
	this->tableLayoutPanel2->AutoSizeMode = Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->tableLayoutPanel2->ColumnCount = 1;
	this->tableLayoutPanel2->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
	this->tableLayoutPanel2->BackColor = System::Drawing::Color::White;
	this->tableLayoutPanel2->RowCount = 5;
	this->tableLayoutPanel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize)); // Автор + ...
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize)); // Фото
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize)); // Заголовок
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize)); // Контент
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize)); // Дата
	this->tableLayoutPanel2->Controls->Add(this->panel2, 0, 0);
	this->tableLayoutPanel2->Controls->Add(this->panel3, 0, 4);
	this->tableLayoutPanel2->Controls->Add(this->image_post, 0, 3);
	this->tableLayoutPanel2->Controls->Add(this->text_post, 0, 2);
	this->tableLayoutPanel2->Controls->Add(this->title_post_l,0, 1);
	this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
	this->tableLayoutPanel2->Size = System::Drawing::Size(1018, 402);
	this->tableLayoutPanel2->MaximumSize = System::Drawing::Size(1018, 0);
	this->Controls->Add(tableLayoutPanel2);


	/*
	this->tableLayoutPanel2 = gcnew TableLayoutPanel();
	this->tableLayoutPanel2->Dock = DockStyle::Fill;
	this->tableLayoutPanel2->AutoSize = true;
	this->tableLayoutPanel2->AutoSizeMode = Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->tableLayoutPanel2->ColumnCount = 1;
	this->tableLayoutPanel2->RowCount = 0;
	//this->tableLayoutPanel2->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
	this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(SizeType::AutoSize)));
	this->tableLayoutPanel2->Controls->Add(this->panel2);
	this->tableLayoutPanel2->Controls->Add(this->title_post_l);
	this->tableLayoutPanel2->Controls->Add(this->text_post);
	this->tableLayoutPanel2->Controls->Add(this->image_post);
	this->tableLayoutPanel2->Controls->Add(this->date_post);
	//this->tableLayoutPanel2->Location = System::Drawing::Point(3, 3);
	//this->tableLayoutPanel2->Size = System::Drawing::Size(1018, 402);



	this->tableLayoutPanel3 = gcnew TableLayoutPanel();
	this->tableLayoutPanel3->Dock = DockStyle::Fill;
	this->tableLayoutPanel3->AutoSize = true;
	this->tableLayoutPanel3->AutoSizeMode = Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->tableLayoutPanel3->ColumnCount = 1;
	this->tableLayoutPanel3->RowCount = 0;
	this->tableLayoutPanel3->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	this->tableLayoutPanel3->Controls->Add(this->label2);
	this->tableLayoutPanel3->Controls->Add(this->comm_info);
	this->tableLayoutPanel3->Controls->Add(this->panel1);


	this->tableLayoutPanel1 = gcnew TableLayoutPanel();
	this->tableLayoutPanel1->ColumnCount = 1;
	this->tableLayoutPanel1->BackColor = System::Drawing::Color::White;
	this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
	this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 0);
	this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 0, 1);
	this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
	this->tableLayoutPanel1->RowCount = 1;
	this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
	this->tableLayoutPanel1->AutoSize = true;
	this->tableLayoutPanel1->MaximumSize = System::Drawing::Size(1018, 0);
	this->tableLayoutPanel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->Controls->Add(tableLayoutPanel1);*/
}

void PostOpen::Edit_Click(Object^ sender, EventArgs^ e)

{
	this->title_post->Multiline = true;
	this->title_post->BackColor = System::Drawing::Color::White;
	this->title_post->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold));
	this->title_post->WordWrap = true;
	this->title_post->Dock = DockStyle::Top;
	this->title_post->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left));
	this->title_post->Size = System::Drawing::Size(1010, 40);
	//this->title_post->MaximumSize = System::Drawing::Size(1010, 0);
	this->tableLayoutPanel2->Controls->Remove(this->title_post_l);
	this->tableLayoutPanel2->Controls->Add(this->title_post);



	this->text_post_t->Multiline = true;
	this->text_post_t->BackColor = System::Drawing::Color::White;
	this->text_post_t->Font = (gcnew System::Drawing::Font(L"Montserrat", 13.8F, System::Drawing::FontStyle::Regular));
	this->text_post_t->Location = System::Drawing::Point(3, 90);
	this->text_post_t->WordWrap = true;
	this->text_post_t->Dock = DockStyle::Fill;
	this->text_post_t->Size = System::Drawing::Size(1010, 100);
	//this->text_post_t->MaximumSize = System::Drawing::Size(1010, 0);
	this->text_post_t->ScrollBars = ScrollBars::None;
	this->tableLayoutPanel2->Controls->Remove(this->text_post);
	this->tableLayoutPanel2->Controls->Add(this->text_post_t);



	this->save->BackColor = System::Drawing::Color::SlateBlue;
	this->save->FlatAppearance->BorderSize = 0;
	this->save->Font = (gcnew System::Drawing::Font(L"Montserrat", 10.8F, System::Drawing::FontStyle::Bold));
	this->save->ForeColor = System::Drawing::Color::White;
	this->save->Location = System::Drawing::Point(3, 0);
	this->save->AutoSize = true;
	this->save->TabIndex = 10;
	this->save->Text = L"Сохранить";
	this->save->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->save->UseVisualStyleBackColor = false;
	this->save->Click += gcnew System::EventHandler(this, &PostOpen::save_Click);



	this->otmena->BackColor = System::Drawing::Color::SlateBlue;
	this->otmena->FlatAppearance->BorderSize = 0;
	this->otmena->Font = (gcnew System::Drawing::Font(L"Montserrat", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point));
	this->otmena->ForeColor = System::Drawing::Color::White;
	this->otmena->Location = System::Drawing::Point(save->Width + 50, 0);
	this->otmena->AutoSize = true;
	this->otmena->TabIndex = 10;
	this->otmena->Text = L"Отменить";
	this->otmena->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->otmena->UseVisualStyleBackColor = false;
	this->otmena->Click += gcnew System::EventHandler(this, &PostOpen::otmena_Click);



	this->panel3->Controls->Add(this->save);
	this->panel3->Controls->Add(this->otmena);

}

void PostOpen::Delete_Click(Object^ sender, EventArgs^ e)
{
	// TODO: переход в блог
}

void PostOpen::Label1_Click(Object^ sender, EventArgs^ e)
{
	MouseEventArgs^ me = dynamic_cast<MouseEventArgs^>(e);
	if (me != nullptr && me->Button == Windows::Forms::MouseButtons::Left) {
		this->svoistva_post->Show(this->label1, Point(0, this->label1->Height));
	}
}

void QQ::PostOpen::AttachClickHandlers(Control^ parent)
{
	parent->Click += gcnew EventHandler(this, &PostOpen::HandleClick);
	for each(Control ^ child in parent->Controls)
	{
		AttachClickHandlers(child);
	}
}


void QQ::PostOpen::HandleClick(System::Object^ sender, System::EventArgs^ e)
{
	if (this->OnPostSelected != nullptr) {
		this->OnPostSelected(PostData);
	}
}

void PostOpen::save_Click(System::Object^ sender, System::EventArgs^ e) {
	int post_id = postId;
	System::String^ newTitle = title_post->Text;
	System::String^ newContent = text_post_t->Text;

	int result = update_post(newTitle, newContent, post_id);

	if (result == 0) {
		MessageBox::Show("Ошибка при обновлении поста.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	this->text_post->Text = this->text_post_t->Text;
	this->title_post_l->Text = this->title_post->Text;
	this->tableLayoutPanel2->Controls->Remove(this->text_post_t);
	this->tableLayoutPanel2->Controls->Add(this->text_post);
	this->tableLayoutPanel2->Controls->Remove(this->title_post);
	this->tableLayoutPanel2->Controls->Add(this->title_post_l);
	this->panel3->Controls->Remove(this->save);
	this->panel3->Controls->Remove(this->otmena);

}

void PostOpen::otmena_Click(System::Object^ sender, System::EventArgs^ e) {
	this->tableLayoutPanel2->Controls->Remove(this->text_post_t);
	this->tableLayoutPanel2->Controls->Add(this->text_post);
	this->tableLayoutPanel2->Controls->Remove(this->title_post);
	this->tableLayoutPanel2->Controls->Add(this->title_post_l);
	this->panel3->Controls->Remove(this->save);
	this->panel3->Controls->Remove(this->otmena);
}

PostOpen::~PostOpen()
{
}
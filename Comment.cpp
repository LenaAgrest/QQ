#include "Comment.h"
#include <ctime>
#include <string>
#include "Comm.h"

using namespace QQ;

Comment::Comment(Post^ post, Comm^ comm) {

	InitializeComponent();
	postId = post->ID;
	commId = comm->ID;
	user_comm->Text = comm->Author;
	otvet_user_name->Text = comm->ReplyTo != "" ? "(в ответ " + comm->ReplyTo + ")" : "";
	text_comm->Text = comm->Text;
	date_post->Text = comm->Date.ToString("dd.MM.yyyy HH:mm");
}

void Comment::InitializeComponent(void)
{
	this->AutoSize = true;

	this->user_comm = gcnew Label();
	this->user_comm->AutoSize = true;
	this->user_comm->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point));
	this->user_comm->Location = System::Drawing::Point(0, 0);
	this->user_comm->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left));


	this->otvet_user_name = gcnew Label();
	this->otvet_user_name->AutoSize = true;
	this->otvet_user_name->Font = (gcnew System::Drawing::Font(L"Montserrat", 12, System::Drawing::FontStyle::Regular));
	this->otvet_user_name->ForeColor = System::Drawing::SystemColors::ControlDark;
	this->otvet_user_name->Location = System::Drawing::Point(35, 0);
	this->otvet_user_name->Size = System::Drawing::Size(183, 35);


	this->text_comm = gcnew Label();
	this->text_comm->AutoSize = true;
	this->text_comm->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->text_comm->Location = System::Drawing::Point(0, 0);
	this->text_comm->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->text_comm->Dock = DockStyle::Fill;
	this->text_comm->MaximumSize = System::Drawing::Size(1010, 0);


	this->svoistva_post = gcnew System::Windows::Forms::ContextMenuStrip();
	this->svoistva_post->ImageScalingSize = System::Drawing::Size(20, 20);
	this->svoistva_post->ShowImageMargin = false;
	this->svoistva_post->Name = L"contextMenuStrip1";
	this->svoistva_post->Size = System::Drawing::Size(61, 4);
	this->svoistva_post->Items->Add(L"Удалить", nullptr, gcnew EventHandler(this, &Comment::Delete_Click));


	this->label1 = gcnew Label();
	this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
	this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat ExtraBold", 19.8F, System::Drawing::FontStyle::Bold));
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(40, 20);
	this->label1->TabIndex = 8;
	this->label1->Text = L"...";
	this->label1->Dock = DockStyle::Right;
	this->label1->UseCompatibleTextRendering = true;
	this->label1->ContextMenuStrip = this->svoistva_post;
	this->label1->Click += gcnew System::EventHandler(this, &Comment::Label1_Click);


	this->panel2 = gcnew Panel();
	this->panel2->AutoSize = true;
	this->panel2->Dock = DockStyle::Top;
	this->panel2->Location = System::Drawing::Point(0, 0);
	this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->panel2->Controls->Add(user_comm);
	this->panel2->Controls->Add(otvet_user_name);
	this->panel2->Controls->Add(label1);


	this->date_post = gcnew Label();
	this->date_post->Font = (gcnew System::Drawing::Font(L"Montserrat", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point));
	this->date_post->TextAlign = ContentAlignment::BottomRight;
	this->date_post->Dock = DockStyle::Right;
	this->date_post->AutoSize = true;
	this->date_post->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

	this->otvet = gcnew Button();
	this->otvet->Click += gcnew System::EventHandler(this, &Comment::otvet_Click);
	//this->otvet->BackColor = System::Drawing::Color::SlateBlue;
	this->otvet->Dock = DockStyle::Left;
	this->otvet->FlatAppearance->BorderSize = 0;
	this->otvet->BackgroundImage = Image::FromFile("ответить.png");
	this->otvet->BackgroundImageLayout = ImageLayout::Zoom;
	this->otvet->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->otvet->Size = System::Drawing::Size(30, 30);
	this->otvet->Location = System::Drawing::Point(0, 0);


	this->panel3 = gcnew Panel();
	this->panel3->Size = System::Drawing::Size(988, 30);
	this->panel3->Dock = DockStyle::Fill;
	this->panel3->Location = System::Drawing::Point(0, 0);
	this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->panel3->Controls->Add(this->date_post);
	this->panel3->Controls->Add(this->otvet);


	this->repliesPanel = gcnew FlowLayoutPanel();
	this->repliesPanel->FlowDirection = FlowDirection::TopDown;
	this->repliesPanel->WrapContents = false;
	this->repliesPanel->AutoSize = true;
	this->repliesPanel->AutoSizeMode = Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->repliesPanel->Dock = DockStyle::Fill;
	//this->repliesPanel->MaximumSize = System::Drawing::Size(988, 0);
	this->repliesPanel->Margin = System::Windows::Forms::Padding(30, 0, 0, 0); // отступ слева


	this->tableLayoutPanel2 = gcnew TableLayoutPanel();
	this->tableLayoutPanel2->Dock = DockStyle::Fill;
	this->tableLayoutPanel2->AutoSize = true;
	this->tableLayoutPanel2->AutoSizeMode = Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->tableLayoutPanel2->ColumnCount = 1;
	this->tableLayoutPanel2->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100));
	this->tableLayoutPanel2->BackColor = System::Drawing::Color::White;
	this->tableLayoutPanel2->RowCount = 4;
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize)); 
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	this->tableLayoutPanel2->Controls->Add(this->panel2, 0, 0);
	this->tableLayoutPanel2->Controls->Add(this->text_comm, 0, 1);
	this->tableLayoutPanel2->Controls->Add(this->panel3, 0, 2);
	this->tableLayoutPanel2->Controls->Add(this->repliesPanel, 0, 3);
	this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
	//this->tableLayoutPanel2->Size = System::Drawing::Size(1018, 402);
	//this->tableLayoutPanel2->MaximumSize = System::Drawing::Size(1018, 0);
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


void Comment::Delete_Click(Object^ sender, EventArgs^ e)
{
	// TODO: переход в блог
}

void Comment::otvet_Click(Object^ sender, EventArgs^ e)
{
	// TODO: переход в блог
}

void Comment::Label1_Click(Object^ sender, EventArgs^ e)
{
	MouseEventArgs^ me = dynamic_cast<MouseEventArgs^>(e);
	if (me != nullptr && me->Button == Windows::Forms::MouseButtons::Left) {
		this->svoistva_post->Show(this->label1, Point(0, this->label1->Height));
	}
}

/*void Comment::AddReply(Comment^ child) {
	if (Replies == nullptr) Replies = gcnew List<Comment^>();
	Replies->Add(child);
}*/


Comment::~Comment()
{
}
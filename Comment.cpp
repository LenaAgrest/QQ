#include "Comment.h"
#include <ctime>
#include <string>
#include "Comm.h"
#include "Session.h"
#include "CommRepository.h"

using namespace QQ;

Comment::Comment(Post^ post, Comm^ comm) {

	InitializeComponent();
	postId = post->ID;
	comm_allowed = post->CommentsAllowed;
	commId = comm->ID;
	ID_user = comm->ID_user;
	idReplyUser = comm->IdReplyUser;
	parentId = comm->ParentID;
	if (comm->Text == "Комментарий был удалён")
	{
		this->BackColor = Color::LightGray;
		user_comm->Text = "@" + comm->Author;
		otvet_user_name->Text = comm->ReplyTo != "" ? "(в ответ " + comm->ReplyTo + ")" : "";
		otvet_user_name->Location = System::Drawing::Point(user_comm->PreferredSize.Width + 10, 0);
		text_comm->Text = "Комментарий был удалён";
		otvet->Visible = false;
		label1->Visible = false; // скрываем кнопку удаления тоже
	}
	else
	{
		user_comm->Text = "@" + comm->Author;
		otvet_user_name->Text = comm->ReplyTo != "" ? "(в ответ @" + comm->ReplyTo + ")" : "";
		otvet_user_name->Location = System::Drawing::Point(user_comm->PreferredSize.Width + 10, 0);
		text_comm->Text = comm->Text;
	}

	date_post->Text = comm->Date.ToString("dd.MM.yyyy HH:mm");

	// ограничение по ширине и поведение
	this->MaximumSize = System::Drawing::Size(1018, 0);
	this->Dock = DockStyle::Top;
	this->Margin = System::Windows::Forms::Padding(0, 0, 0, 0);
	this->BackColor = System::Drawing::Color::White;

	if (!comm_allowed)
	{
		this->otvet->BackgroundImage = Image::FromFile("answer_disable.png");
		this->otvet->Enabled = false;
	}
}

void Comment::InitializeComponent(void)
{
	this->AutoSize = true;

	this->user_comm = gcnew Label();
	this->user_comm->AutoSize = true;
	this->user_comm->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 16.8F, System::Drawing::FontStyle::Bold));
	this->user_comm->Location = System::Drawing::Point(0, 0);

	this->otvet_user_name = gcnew Label();
	this->otvet_user_name->AutoSize = true;
	this->otvet_user_name->Font = (gcnew System::Drawing::Font(L"Montserrat", 12));
	this->otvet_user_name->ForeColor = System::Drawing::SystemColors::ControlDark;

	this->text_comm = gcnew Label();
	this->text_comm->AutoSize = true;
	this->text_comm->Font = (gcnew System::Drawing::Font(L"Montserrat", 14));
	this->text_comm->Location = System::Drawing::Point(0, 0);
	this->text_comm->MaximumSize = System::Drawing::Size(960, 0);

	this->svoistva_post = gcnew System::Windows::Forms::ContextMenuStrip();
	this->svoistva_post->ImageScalingSize = System::Drawing::Size(20, 20);
	this->svoistva_post->ShowImageMargin = false;
	this->svoistva_post->Items->Add(L"Удалить", nullptr, gcnew EventHandler(this, &Comment::Delete_Click));

	this->label1 = gcnew Label();
	this->label1->Font = (gcnew System::Drawing::Font(L"Montserrat ExtraBold", 19.8F, System::Drawing::FontStyle::Bold));
	this->label1->Text = L"...";
	this->label1->Dock = DockStyle::Right;
	this->label1->UseCompatibleTextRendering = true;
	this->label1->ContextMenuStrip = this->svoistva_post;
	this->label1->Click += gcnew System::EventHandler(this, &Comment::Label1_Click);

	this->panel2 = gcnew Panel();
	this->panel2->AutoSize = true;
	this->panel2->Dock = DockStyle::Top;
	this->panel2->Controls->Add(user_comm);
	this->panel2->Controls->Add(otvet_user_name);
	this->panel2->Controls->Add(label1);

	this->date_post = gcnew Label();
	this->date_post->Font = (gcnew System::Drawing::Font(L"Montserrat", 12));
	this->date_post->TextAlign = ContentAlignment::BottomRight;
	this->date_post->Dock = DockStyle::Right;
	this->date_post->AutoSize = true;


	this->otvet = gcnew Button();
	this->otvet->Click += gcnew System::EventHandler(this, &Comment::otvet_Click);
	this->otvet->FlatAppearance->BorderSize = 0;
	this->otvet->BackgroundImage = Image::FromFile("answer.png");
	this->otvet->BackgroundImageLayout = ImageLayout::Zoom;
	this->otvet->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->otvet->Size = System::Drawing::Size(date_post->Height, date_post->Height);

	this->panel3 = gcnew Panel();
	this->panel3->AutoSize = true;
	this->panel3->Dock = DockStyle::Top;
	this->panel3->Controls->Add(this->date_post);
	this->panel3->Controls->Add(this->otvet);


	this->comm_send = gcnew Button();
	this->comm_tb = gcnew TextBox();
	this->panel1 = gcnew Panel();

	this->comm_send->AutoSize = true;
	this->comm_send->BackColor = System::Drawing::Color::MediumSlateBlue;
	this->comm_send->Dock = System::Windows::Forms::DockStyle::Right;
	this->comm_send->FlatAppearance->BorderSize = 0;
	this->comm_send->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->comm_send->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 10, System::Drawing::FontStyle::Bold));
	this->comm_send->ForeColor = System::Drawing::Color::White;
	this->comm_send->Location = System::Drawing::Point(438, 0);
	this->comm_send->Margin = System::Windows::Forms::Padding(30, 7, 3, 3);
	this->comm_send->Click += gcnew System::EventHandler(this, &Comment::comm_send_Click);
	this->comm_send->Size = System::Drawing::Size(30, 34);
	this->comm_send->Text = L">";
	this->comm_send->UseVisualStyleBackColor = false;
	// 
	// comm_tb
	// 
	this->comm_tb->Dock = System::Windows::Forms::DockStyle::Fill;
	this->comm_tb->Location = System::Drawing::Point(0, 0);
	this->comm_tb->Margin = System::Windows::Forms::Padding(3);
	this->comm_tb->MaximumSize = System::Drawing::Size(980 - comm_send->Width, 0);
	this->comm_tb->Multiline = true;
	this->comm_tb->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 14.8F, System::Drawing::FontStyle::Bold));
	this->comm_tb->Size = System::Drawing::Size(435, 34);


	this->panel1->Controls->Add(this->comm_send);
	this->panel1->Controls->Add(this->comm_tb);
	this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
	//this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->panel1->Location = System::Drawing::Point(0, 0);
	this->panel1->MaximumSize = System::Drawing::Size(980, 34);

	this->tableLayoutPanel2 = gcnew TableLayoutPanel();
	this->tableLayoutPanel2->Dock = DockStyle::Fill;
	this->tableLayoutPanel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->tableLayoutPanel2->AutoSize = true;
	this->tableLayoutPanel2->ColumnCount = 2;
	this->tableLayoutPanel2->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 1));
	this->tableLayoutPanel2->ColumnStyles->Add(gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 99));
	this->tableLayoutPanel2->RowCount = 3;
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	this->tableLayoutPanel2->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	this->tableLayoutPanel2->Controls->Add(this->panel2, 1, 0);
	this->tableLayoutPanel2->Controls->Add(this->text_comm, 1, 1);
	this->tableLayoutPanel2->Controls->Add(this->panel3, 1, 2);
	this->Controls->Add(tableLayoutPanel2);
}

void Comment::Delete_Click(Object^ sender, EventArgs^ e)
{
	auto result = MessageBox::Show("Удалить комментарий?", "Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

	if (result == DialogResult::Yes)
	{
		bool success = CommRepository::MarkAsDeleted(this->commId);

		if (this->parentId == -1)
			success = success && CommRepository::DeleteReplies(this->commId);

		if (success)
		{
			if (OnCommentsUpdated != nullptr)
				OnCommentsUpdated();
		}
		else
		{
			MessageBox::Show("Ошибка при удалении комментария.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

void Comment::otvet_Click(Object^ sender, EventArgs^ e)
{
	if (isExpanded && comm_allowed)
	{
		this->tableLayoutPanel2->Controls->Add(this->panel1);
		this->otvet->BackgroundImage = Image::FromFile("answer_enable.png");
	}
	else
	{
		this->tableLayoutPanel2->Controls->Remove(this->panel1);
		this->otvet->BackgroundImage = Image::FromFile("answer.png");
	}
	isExpanded = !isExpanded;
}

void Comment::Label1_Click(Object^ sender, EventArgs^ e)
{
	MouseEventArgs^ me = dynamic_cast<MouseEventArgs^>(e);
	if(me != nullptr && me->Button == Windows::Forms::MouseButtons::Left) {
		this->svoistva_post->Show(this->label1, Point(0, this->label1->Height));
		
	}
}

void Comment::comm_send_Click(Object^ sender, EventArgs^ e)
{
	String^ text = comm_tb->Text->Trim();
	if (String::IsNullOrWhiteSpace(text)) {
		MessageBox::Show("Комментарий не может быть пустым.");
		return;
	}

	bool success = CommRepository::AddComment(
		this->postId,
		Session::CurrentUser->ID,
		this->ID_user,  // <-- передаём ID автора комментария, на который отвечаем
		text,
		DateTime::Now,
		true,
		this->commId
	);

	if (success) {
		comm_tb->Clear();

		if (OnReplySent != nullptr)
			OnReplySent(this, EventArgs::Empty);
	}

	else {
		MessageBox::Show("Ошибка при добавлении ответа.");
	}

}

Comment::~Comment()
{
}
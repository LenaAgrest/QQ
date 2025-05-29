#include "MyUserControl.h"
#include "PostgresConnection.h"
#include "CreatePost.h"
#include "PostRepository.h"
#include "PostControl.h"
#include "Session.h"
#include "UserPage.h"
#include "red_user.h"
#include <ctime>
#include "PostOpen.h"

using namespace QQ;

MyUserControl::MyUserControl()
{
	InitializeComponent();
	SetUser();
}

void MyUserControl::InitializeComponent(void)
{
	System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyUserControl::typeid));
	this->Panel = (gcnew System::Windows::Forms::Panel());
	this->panel4 = (gcnew System::Windows::Forms::Panel());
	this->labelUserName = (gcnew System::Windows::Forms::Label());
	this->pictureBoxAvatar = (gcnew System::Windows::Forms::PictureBox());
	this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
	this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
	this->contextMenuStrip1 = gcnew System::Windows::Forms::ContextMenuStrip();
	this->panel1 = (gcnew System::Windows::Forms::Panel());
	this->mainflow = (gcnew System::Windows::Forms::FlowLayoutPanel());
	this->Panel->SuspendLayout();
	this->panel4->SuspendLayout();
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxAvatar))->BeginInit();
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
	this->flowLayoutPanel2->SuspendLayout();
	this->panel1->SuspendLayout();
	this->SuspendLayout();
	// 
	// Panel
	// 
	this->Panel->BackColor = System::Drawing::Color::SlateBlue;
	this->Panel->Controls->Add(this->panel4);
	this->Panel->Controls->Add(this->pictureBox1);
	this->Panel->Controls->Add(this->flowLayoutPanel2);
	this->Panel->Dock = System::Windows::Forms::DockStyle::Top;
	this->Panel->Location = System::Drawing::Point(0, 0);
	this->Panel->Name = L"Panel";
	this->Panel->Size = System::Drawing::Size(1540, 80);
	this->Panel->Resize += gcnew System::EventHandler(this, &MyUserControl::Panel_Resize);
	// 
	// panel4
	// 
	this->panel4->AutoSize = true;
	this->panel4->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->panel4->Controls->Add(this->labelUserName);
	this->panel4->Controls->Add(this->pictureBoxAvatar);
	this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
	this->panel4->Location = System::Drawing::Point(1310, 0);
	this->panel4->Name = L"panel4";
	this->panel4->Size = System::Drawing::Size(230, 80);
	//this->panel4->Click += gcnew System::EventHandler(this, &MyUserControl::panel4_Click);
	// 
	// labelUserName
	// 
	this->labelUserName->AutoSize = true;
	this->labelUserName->Cursor = System::Windows::Forms::Cursors::Hand;
	this->labelUserName->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 18, System::Drawing::FontStyle::Bold));
	this->labelUserName->ForeColor = System::Drawing::Color::White;
	this->labelUserName->Location = System::Drawing::Point(111, 20);
	this->labelUserName->Name = L"labelUserName";
	this->labelUserName->Size = System::Drawing::Size(116, 41);
	this->labelUserName->TabStop = true;
	this->labelUserName->Text = L"Войти";
	this->labelUserName->ContextMenuStrip = contextMenuStrip1;
	this->labelUserName->Click += gcnew System::EventHandler(this, &MyUserControl::labelUserName_Click);
	
	this->menuItemLogout = gcnew ToolStripMenuItem("Выйти из аккаунта");
	this->menuItemDeleteAccount = gcnew ToolStripMenuItem("Удалить аккаунт");
	this->contextMenuStrip1->Items->AddRange(gcnew array<ToolStripItem^>{ menuItemLogout, menuItemDeleteAccount });
	this->menuItemLogout->Click += gcnew EventHandler(this, &MyUserControl::Logout_Click);
	this->menuItemDeleteAccount->Click += gcnew EventHandler(this, &MyUserControl::DeleteAccount_Click);


	// 
	// pictureBoxAvatar
	// 
	this->pictureBoxAvatar->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxAvatar.BackgroundImage")));
	this->pictureBoxAvatar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
	this->pictureBoxAvatar->ErrorImage = nullptr;
	this->pictureBoxAvatar->InitialImage = nullptr;
	this->pictureBoxAvatar->Location = System::Drawing::Point(43, 8);
	this->pictureBoxAvatar->Name = L"pictureBoxAvatar";
	this->pictureBoxAvatar->Size = System::Drawing::Size(62, 62);
	this->pictureBoxAvatar->TabStop = false;
	this->pictureBoxAvatar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyUserControl::pictureBoxAvatar_Paint);
	this->pictureBoxAvatar->Click += gcnew System::EventHandler(this, &MyUserControl::panel4_Click);
	// 
	// pictureBox1
	// 
	this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
	this->pictureBox1->Location = System::Drawing::Point(3, 3);
	this->pictureBox1->Name = L"pictureBox1";
	this->pictureBox1->Size = System::Drawing::Size(126, 77);
	this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
	this->pictureBox1->TabStop = false;
	this->pictureBox1->Click += gcnew System::EventHandler(this, &MyUserControl::pictureBox1_Click);
	


	this->pageButton = gcnew Button();
	this->pageButton->Text = "Следующая страница";
	this->pageButton->Font = gcnew System::Drawing::Font(L"Montserrat", 12, FontStyle::Bold);
	this->pageButton->BackColor = Color::SlateBlue;
	this->pageButton->ForeColor = Color::White;
	this->pageButton->AutoSize = true;
	this->pageButton->FlatStyle = FlatStyle::Flat;
	this->pageButton->Click += gcnew System::EventHandler(this, &MyUserControl::pageButton_Click);
	this->pageButton->Visible = false;

	this->prevPageButton = gcnew Button();
	this->prevPageButton->Text = "Предыдущая страница";
	this->prevPageButton->Font = gcnew System::Drawing::Font(L"Montserrat", 12, FontStyle::Bold);
	this->prevPageButton->BackColor = Color::SlateBlue;
	this->prevPageButton->ForeColor = Color::White;
	this->prevPageButton->AutoSize = true;
	this->prevPageButton->FlatStyle = FlatStyle::Flat;
	this->prevPageButton->Click += gcnew System::EventHandler(this, &MyUserControl::prevPageButton_Click);
	this->prevPageButton->Visible = false;



	this->pageLabel = gcnew Label();
	this->pageLabel->Text = "Страница 1";
	this->pageLabel->Font = gcnew System::Drawing::Font(L"Montserrat", 12, FontStyle::Bold);
	this->pageLabel->AutoSize = true;
	this->pageLabel->ForeColor = Color::White;
	this->pageLabel->TextAlign = ContentAlignment::MiddleCenter;
	this->pageLabel->Margin = System::Windows::Forms::Padding(20, 10, 20, 10);

	// 
	// flowLayoutPanel2
	// 
	this->flowLayoutPanel2->Controls->Add(this->prevPageButton);
	this->flowLayoutPanel2->Controls->Add(this->pageLabel);
	this->flowLayoutPanel2->Controls->Add(this->pageButton);
	//this->flowLayoutPanel2->Size = System::Drawing::Size(649, 60);
	this->flowLayoutPanel2->FlowDirection = FlowDirection::LeftToRight;
	this->flowLayoutPanel2->WrapContents = false;
	this->flowLayoutPanel2->AutoSize = true;
	this->flowLayoutPanel2->Anchor = AnchorStyles::Top;
	//this->flowLayoutPanel2->Padding = System::Windows::Forms::Padding(10);
	this->flowLayoutPanel2->Dock = DockStyle::Top;
	this->flowLayoutPanel2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(0, 20, 0, 10);
	this->flowLayoutPanel2->Anchor = AnchorStyles::None;
	this->flowLayoutPanel2->Location = System::Drawing::Point((this->Width - flowLayoutPanel2->Width) / 2, 20);

	// 
	// panel1
	// 
	this->panel1->AutoScroll = true;
	this->panel1->Controls->Add(this->mainflow);
	this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
	this->panel1->Location = System::Drawing::Point(0, 80);
	this->panel1->Name = L"panel1";
	this->panel1->Size = System::Drawing::Size(1540, 720);
	// 
	// mainflow
	// 
	this->mainflow->AutoSize = true;
	this->mainflow->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->mainflow->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
	this->mainflow->Location = System::Drawing::Point(300, 0);
	this->mainflow->Name = L"mainflow";
	this->mainflow->Size = System::Drawing::Size(0, 0);
	this->mainflow->WrapContents = false;
	this->mainflow->SizeChanged += gcnew System::EventHandler(this, &MyUserControl::panel1_Resize2);
	// 
	// MyUserControl
	// 
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
	this->AutoSize = true;
	this->Controls->Add(this->panel1);
	this->Controls->Add(this->Panel);
	this->Name = L"MyUserControl";
	this->Size = System::Drawing::Size(1540, 800);
	this->Panel->ResumeLayout(false);
	this->Panel->PerformLayout();
	this->panel4->ResumeLayout(false);
	this->panel4->PerformLayout();
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxAvatar))->EndInit();
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
	this->flowLayoutPanel2->ResumeLayout(false);
	this->flowLayoutPanel2->PerformLayout();
	this->panel1->ResumeLayout(false);
	this->panel1->PerformLayout();
	this->ResumeLayout(false);

}
#pragma endregion

void MyUserControl::SetUser()
{
	if (QQ::Session::CurrentUser != nullptr) {
		user = QQ::Session::CurrentUser;
		labelUserName->Text = user->Username;

		if (user->Photo != nullptr)
			pictureBoxAvatar->BackgroundImage = user->Photo;
		else
			pictureBoxAvatar->BackgroundImage = Image::FromFile("ava.png");
	}
	MainForm_Load();
}

void MyUserControl::pictureBoxAvatar_Paint(Object^ sender, PaintEventArgs^ e)
		{
			if (this->pictureBoxAvatar->BackgroundImage == nullptr)
				return;

			Graphics^ g = e->Graphics;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			Image^ img = this->pictureBoxAvatar->BackgroundImage;

			float boxWidth = static_cast<float>(this->pictureBoxAvatar->Width);
			float boxHeight = static_cast<float>(this->pictureBoxAvatar->Height);
			float imgWidth = static_cast<float>(img->Width);
			float imgHeight = static_cast<float>(img->Height);

			// Масштабирование как cover
			float scale = Math::Max(boxWidth / imgWidth, boxHeight / imgHeight);
			SizeF scaledSize(imgWidth * scale, imgHeight * scale);
			PointF offset((boxWidth - scaledSize.Width) / 2, (boxHeight - scaledSize.Height) / 2);

			auto path = gcnew Drawing2D::GraphicsPath();
			path->AddEllipse(0, 0, pictureBoxAvatar->Width - 1, pictureBoxAvatar->Height - 1);
			this->pictureBoxAvatar->Region = gcnew System::Drawing::Region(path);

			// Обрезаем всё по кругу
			g->SetClip(path);

			// Отрисовка
			g->DrawImage(img, RectangleF(offset, scaledSize));
		}

void MyUserControl::panel4_Click(Object^ sender, EventArgs^ e)
		{
			if (user != nullptr) {
				QQ::UserPage^ userpage = gcnew QQ::UserPage(user);
				QQ::CreatePost^ cr_post = gcnew QQ::CreatePost(user);
				userpage->OnEditRequested += gcnew QQ::UserPage::EditRequestedHandler(this, &MyUserControl::OpenEditProfile);
				userpage->OnCreatePost += gcnew UserPage::CreatePostRequestedHandler(this, &MyUserControl::OpenCreatePost);

				this->mainflow->Controls->Clear();
				this->mainflow->Controls->Add(userpage);
			}
			this->panel1->ResumeLayout(false);
			//this->panel1->Resize += gcnew System::EventHandler(this, &MyUserControl::panel1_Resize);
			this->panel1->PerformLayout();
		}

void MyUserControl::OpenEditProfile(User^ user)
{
	this->mainflow->Controls->Clear();
	this->flowLayoutPanel2->Visible = false;

	UserPageRed^ red = gcnew UserPageRed(user);
	this->mainflow->Controls->Add(red);
}


void MyUserControl::OpenPost(Post^ post)
{
	this->mainflow->Controls->Clear();
	this->flowLayoutPanel2->Visible = false;

	PostOpen^ postOpen = gcnew PostOpen(post);
	this->mainflow->Controls->Add(postOpen);
}


void MyUserControl::OpenCreatePost(User^ user)
{
	this->mainflow->Controls->Clear();
	this->flowLayoutPanel2->Visible = false;

	CreatePost^ create = gcnew CreatePost(user);
	this->mainflow->Controls->Add(create);
}



void MyUserControl::ReturnToUserPage(User^ updatedUser)
		{
			this->user = updatedUser;
			QQ::Session::CurrentUser = updatedUser;

			this->labelUserName->Text = updatedUser->Username;

			if (updatedUser->Photo != nullptr) {
				this->pictureBoxAvatar->BackgroundImage = updatedUser->Photo;
			}
			else {
				this->pictureBoxAvatar->BackgroundImage = Image::FromFile("ava.png");
			}

			this->mainflow->Controls->Clear();
			UserPage^ page = gcnew UserPage(updatedUser);
			page->OnEditRequested += gcnew UserPage::EditRequestedHandler(this, &MyUserControl::OpenEditProfile);
			this->mainflow->Controls->Add(page);

		}
void MyUserControl::labelUserName_Click(System::Object^ sender, System::EventArgs^ e)
{
	MouseEventArgs^ me = dynamic_cast<MouseEventArgs^>(e);
	if (me != nullptr && me->Button == Windows::Forms::MouseButtons::Left) {
		this->contextMenuStrip1->Show(this->labelUserName, Point(0, this->labelUserName->Height));

	}
}

void MyUserControl::prevPageButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (currentPage > 1) {
		currentPage--;
		MainForm_Load();
	}
}


void MyUserControl::Logout_Click(System::Object^ sender, System::EventArgs^ e)
{
	Session::CurrentUser = nullptr;
	Application::Restart(); // Или переход на форму авторизации
}

void MyUserControl::DeleteAccount_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (MessageBox::Show("Вы уверены, что хотите удалить аккаунт? Это действие необратимо.",
		"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes)
	{
		PostgresConnection& db = PostgresConnection::getInstance();
		if (!db.connect()) {
			MessageBox::Show("Ошибка подключения к БД при удалении аккаунта.");
			return;
		}

		PGconn* conn = db.get();
		int id = user->ID;

		std::string idStr = std::to_string(id);
		std::string q1 = "DELETE FROM posts WHERE blog_id = " + idStr + ";";
		std::string q2 = "UPDATE commenti SET text = 'Пользователь удалён' WHERE id_user = " + idStr + ";";
		std::string q3 = "DELETE FROM people WHERE id = " + idStr + ";";

		PGresult* r1 = PQexec(conn, q1.c_str());
		PQclear(r1);
		PGresult* r2 = PQexec(conn, q2.c_str());
		PQclear(r2);
		PGresult* r3 = PQexec(conn, q3.c_str());
		PQclear(r3);

		db.disconnect();
		MessageBox::Show("Аккаунт успешно удалён.");
		Session::CurrentUser = nullptr;
		Application::Restart(); // или переход на форму авторизации
	}
}


void MyUserControl::MainForm_Load() {
	this->mainflow->Controls->Clear();

	List<QQ::Post^>^ posts = PostRepository::LoadAllPosts();
	int totalPosts = posts->Count;
	int startIndex = (currentPage - 1) * postsPerPage;
	int endIndex = Math::Min(startIndex + postsPerPage, totalPosts);

	for (int i = startIndex; i < endIndex; ++i)
	{
		QQ::PostControl^ control = gcnew QQ::PostControl(posts[i]);
		control->Margin = System::Windows::Forms::Padding(10);
		control->OnPostSelected += gcnew PostControl::PostSelectedHandler(this, &MyUserControl::OpenPost);
		this->mainflow->Controls->Add(control);
	}

	// Показывать/прятать кнопку
	pageButton->Visible = (totalPosts > currentPage * postsPerPage);
	prevPageButton->Visible = (currentPage > 1);

		}

		void MyUserControl::RefreshHomeAfterDeletion()
		{
			this->mainflow->Controls->Clear();
			MainForm_Load();
		}

		void MyUserControl::pageButton_Click(System::Object^ sender, System::EventArgs^ e)
		{
			currentPage++;
			MainForm_Load();
		}

		void MyUserControl::panel1_Resize(Object^ sender, EventArgs^ e)
		{
			int centerX = (this->panel1->ClientSize.Width - this->mainflow->Width) / 2;
			if (centerX < 0) { centerX = 0; }
			this->mainflow->Location = Point(centerX, this->mainflow->Location.Y);
		}
		void MyUserControl::Panel_Resize(Object^ sender, EventArgs^ e)
		{
			int centerX = (this->Panel->ClientSize.Width - this->flowLayoutPanel2->Width) / 2;
			this->flowLayoutPanel2->Location = Point(centerX, this->flowLayoutPanel2->Location.Y);
		}
		void MyUserControl::panel1_Resize2(Object^ sender, EventArgs^ e)
		{
			int i = panel1->Width;
			if (mainflow->Height >= panel1->Height)
			{
				i = panel1->Width;
				return;
			}
			else if (mainflow->Height > panel1->Height || panel1->Width > i)
			{
				this->mainflow->Location = Point(this->mainflow->Location.X + SystemInformation::VerticalScrollBarWidth, this->mainflow->Location.Y);
			}

		}

		void MyUserControl::pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
			this->mainflow->Controls->Clear();
			currentPage = 1;
			MainForm_Load();

	}
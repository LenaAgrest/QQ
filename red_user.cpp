#include "User.h"
#include "red_user.h"
#include <ctime>
#include <string>

using namespace QQ;

UserPageRed::UserPageRed(User^ user) {

	InitializeComponent();
	user_Id = user->ID;
	user_name->Text = user->Username;
	o_sebe_text->Text = user->About;
	interesi_text->Text = user->Interests;
	contacts_text->Text = user->Contacts;
	birthday_text->Text = user->Date->ToString("dd.MM.yyyy hh:mm:ss");
}

void UserPageRed::InitializeComponent(void)
{
	this->AutoSize = true;


	this->birthday_text = gcnew TextBox();
	this->birthday_text->AutoSize = true;
	this->birthday_text->TabIndex = 5;
	this->birthday_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->birthday_text->ForeColor = System::Drawing::Color::Black;
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
	this->contacts_text = gcnew TextBox();
	this->contacts_text->AutoSize = true;
	this->contacts_text->TabIndex = 4;
	this->contacts_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->contacts_text->ForeColor = System::Drawing::Color::Black;
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
	this->interesi_text = gcnew TextBox();
	this->interesi_text->AutoSize = true;
	this->interesi_text->WordWrap = true;
	this->interesi_text->TabIndex = 3;
	this->interesi_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->interesi_text->ForeColor = System::Drawing::Color::Black;
	this->interesi_text->Margin = System::Windows::Forms::Padding(3);
	this->interesi_text->Location = System::Drawing::Point(0, 0); //3, 214
	this->interesi_text->Size = System::Drawing::Size(1004, 100);
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
	this->interesi->Location = System::Drawing::Point(0, 0); //3, 161
	this->interesi->Margin = System::Windows::Forms::Padding(3);
	this->interesi->Size = System::Drawing::Size(1004, 47);
	//this->interesi->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// o_sebe_text
	// 
	this->o_sebe_text = gcnew TextBox();
	this->o_sebe_text->AutoSize = true;
	this->o_sebe_text->Multiline = true;
	this->o_sebe_text->TabIndex = 2;
	this->o_sebe_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->o_sebe_text->ForeColor = System::Drawing::Color::Black;
	this->o_sebe_text->Location = System::Drawing::Point(3, 56);
	this->o_sebe_text->Margin = System::Windows::Forms::Padding(3);
	this->o_sebe_text->Size = System::Drawing::Size(1004, 100);
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
	// 
	//имя юзера в панели
	// 
	this->user_name = gcnew Label();
	this->user_name->AutoSize = true;
	//this->user_name->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->user_name->Font = (gcnew System::Drawing::Font(L"Montserrat", 30, System::Drawing::FontStyle::Bold));
	this->user_name->ForeColor = System::Drawing::Color::White;
	this->user_name->Location = System::Drawing::Point(213, 44);
	this->user_name->Margin = System::Windows::Forms::Padding(3, 34, 3, 34);
	this->user_name->Size = System::Drawing::Size(188, 69);
	this->user_name->TabIndex = 1;
	this->user_name->Text = L"label3";



	this->pswd = gcnew Label();
	this->pswd->AutoSize = true;
	this->pswd->Font = gcnew System::Drawing::Font(L"Montserrat", 20, FontStyle::Bold | System::Drawing::FontStyle::Underline);
	this->pswd->ForeColor = System::Drawing::Color::White;
	this->pswd->Location = System::Drawing::Point(3, 3);
	this->pswd->Margin = System::Windows::Forms::Padding(0);
	this->pswd->Size = System::Drawing::Size(188, 69);
	this->pswd->TabIndex = 1;
	this->pswd->Text = L"Изменить пароль?";
	this->pswd->Click += gcnew System::EventHandler(this, &UserPageRed::update_pswd_Click);




	this->now_pswd = gcnew Label();
	this->now_pswd->AutoSize = true;
	this->now_pswd->Visible = false;
	this->now_pswd->Font = gcnew System::Drawing::Font(L"Montserrat", 20, FontStyle::Bold);
	this->now_pswd->ForeColor = System::Drawing::Color::White;
	this->now_pswd->Location = System::Drawing::Point(3, 3);
	this->now_pswd->Margin = System::Windows::Forms::Padding(0);
	this->now_pswd->Size = System::Drawing::Size(188, 69);
	this->now_pswd->TabIndex = 1;
	this->now_pswd->Text = L"Текущий пароль";



	this->now_pswd_text = gcnew TextBox();
	this->now_pswd_text->AutoSize = true;
	this->now_pswd_text->Visible = false;
	this->now_pswd_text->UseSystemPasswordChar = true;
	this->now_pswd_text->Font = gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular);
	this->now_pswd_text->ForeColor = System::Drawing::Color::Black;
	this->now_pswd_text->Location = System::Drawing::Point(3, 3);
	this->now_pswd_text->Margin = System::Windows::Forms::Padding(3);
	this->now_pswd_text->MaximumSize = System::Drawing::Size(1004, 0);
	this->now_pswd_text->Size = System::Drawing::Size(1004, 33);



	this->new_pswd = gcnew Label();
	this->new_pswd->AutoSize = true;
	this->new_pswd->Visible = false;
	this->new_pswd->Font = gcnew System::Drawing::Font(L"Montserrat", 20, FontStyle::Bold);
	this->new_pswd->ForeColor = System::Drawing::Color::White;
	this->new_pswd->Location = System::Drawing::Point(3, 3);
	this->new_pswd->Margin = System::Windows::Forms::Padding(0);
	this->new_pswd->Size = System::Drawing::Size(188, 69);
	this->new_pswd->TabIndex = 1;
	this->new_pswd->Text = L"Новый пароль";



	this->new_pswd_text = gcnew TextBox();
	this->new_pswd_text->AutoSize = true;
	this->new_pswd_text->Visible = false;
	this->new_pswd_text->UseSystemPasswordChar = true;
	this->new_pswd_text->Font = gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular);
	this->new_pswd_text->ForeColor = System::Drawing::Color::Black;
	this->new_pswd_text->Location = System::Drawing::Point(3, 3);
	this->new_pswd_text->Margin = System::Windows::Forms::Padding(3);
	this->new_pswd_text->MaximumSize = System::Drawing::Size(1004, 0);
	this->new_pswd_text->Size = System::Drawing::Size(1004, 33);
	// 
	// pictureBoxAvatar
	// 
	this->pictureBoxAvatar = gcnew PictureBox();
	//this->pictureBoxAvatar->Anchor = System::Windows::Forms::AnchorStyles::Left;
	this->pictureBoxAvatar->BackgroundImage = Image::FromFile("ava.png");
	//this->pictureBoxAvatar->Location = System::Drawing::Point(65, 5);
	this->pictureBoxAvatar->Margin = System::Windows::Forms::Padding(33, 10, 3, 5);
	this->pictureBoxAvatar->Size = System::Drawing::Size(95, 95);
	this->pictureBoxAvatar->TabIndex = 0;
	//this->pictureBoxAvatar->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->pictureBoxAvatar->TabStop = false;
	this->pictureBoxAvatar->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
	this->pictureBoxAvatar->ErrorImage = nullptr;
	this->pictureBoxAvatar->InitialImage = nullptr;
	this->pictureBoxAvatar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &UserPageRed::pictureBoxAvatar_Paint);

	this->openFileDialog1 = gcnew OpenFileDialog();
	this->openFileDialog1->Title = "Выберите изображение";
	this->openFileDialog1->Filter = "Файлы изображений (*.png;*.jpg)|*.png;*.jpg";


	this->save = gcnew Button();
	this->save->Click += gcnew System::EventHandler(this, &UserPageRed::save_Click);
	this->save->BackColor = System::Drawing::Color::MediumSlateBlue;
	this->save->FlatAppearance->BorderSize = 0;
	this->save->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->save->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold));
	this->save->ForeColor = System::Drawing::Color::White;
	this->save->Size = System::Drawing::Size(190, 50);
	this->save->Dock = DockStyle::Fill;
	this->save->TabIndex = 6;
	this->save->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
	this->save->Text = L"Сохранить";

	this->upd_photo = gcnew Button();
	this->upd_photo->Click += gcnew System::EventHandler(this, &UserPageRed::UpdatePhoto_Click);
	this->upd_photo->BackColor = System::Drawing::Color::MediumSlateBlue;
	this->upd_photo->FlatAppearance->BorderSize = 0;
	this->upd_photo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	this->upd_photo->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 14, System::Drawing::FontStyle::Bold));
	this->upd_photo->ForeColor = System::Drawing::Color::White;
	this->upd_photo->Size = System::Drawing::Size(151, 33);
	this->upd_photo->AutoSize = true;
	this->upd_photo->TabIndex = 0;
	//this->upd_photo->Location = System::Drawing::Point(30, 102);
	this->upd_photo->Margin = System::Windows::Forms::Padding(3, 3, 3, 3);
	this->upd_photo->Text = L"Изменить";


	this->flowLayoutPanel4 = gcnew FlowLayoutPanel();
	this->flowLayoutPanel4->AutoSize = true;
	this->flowLayoutPanel4->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->flowLayoutPanel4->Controls->Add(this->pictureBoxAvatar);
	this->flowLayoutPanel4->Controls->Add(this->upd_photo);
	this->flowLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Left;
	this->flowLayoutPanel4->Location = System::Drawing::Point(30, 0);
	this->flowLayoutPanel4->Margin = System::Windows::Forms::Padding(0, 0, 0, 0);
	this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
	//this->flowLayoutPanel4->Size = System::Drawing::Size(184, 158);
	this->flowLayoutPanel4->TabIndex = 4;

	// 
	// panel4
	// 
	this->panel4 = gcnew Panel();
	this->panel4->BackColor = System::Drawing::Color::SlateBlue;
	this->panel4->Controls->Add(this->flowLayoutPanel4);
	this->panel4->Controls->Add(this->user_name);
	this->panel4->Dock = System::Windows::Forms::DockStyle::Top;
	this->panel4->Location = System::Drawing::Point(0, 0);
	this->panel4->Margin = System::Windows::Forms::Padding(2);
	this->panel4->Padding = System::Windows::Forms::Padding(30, 0, 0, 0);
	this->panel4->Name = L"panel4";
	this->panel4->Size = System::Drawing::Size(1010, 160);



	this->about_user = gcnew TableLayoutPanel();
	this->about_user->AutoSize = true;
	this->about_user->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
	this->about_user->BackColor = System::Drawing::Color::SlateBlue;
	this->about_user->Dock = System::Windows::Forms::DockStyle::Fill;
	this->about_user->ColumnCount = 1;
	this->about_user->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 100));
	this->about_user->Location = System::Drawing::Point(0, 0);
	this->about_user->Margin = System::Windows::Forms::Padding(2, 0, 2, 2);
	this->about_user->RowCount = 0; // будет нарастать динамически
	this->about_user->Controls->Add(this->o_sebe);
	this->about_user->Controls->Add(this->o_sebe_text);
	this->about_user->Controls->Add(this->interesi);
	this->about_user->Controls->Add(this->interesi_text);
	this->about_user->Controls->Add(this->contacts);
	this->about_user->Controls->Add(this->contacts_text);
	this->about_user->Controls->Add(this->birthday);
	this->about_user->Controls->Add(this->birthday_text);
	this->about_user->Controls->Add(this->pswd);
	this->about_user->Controls->Add(this->now_pswd);
	this->about_user->Controls->Add(this->now_pswd_text);
	this->about_user->Controls->Add(this->new_pswd);
	this->about_user->Controls->Add(this->new_pswd_text);
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
	this->user_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
	this->user_table->Controls->Add(this->panel4, 0, 0);
	this->user_table->Controls->Add(this->about_user, 0, 1);
	this->user_table->Controls->Add(this->save, 0, 2);
	this->user_table->Location = System::Drawing::Point(0, 0);
	this->user_table->RowCount = 4;
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->user_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->user_table->Size = System::Drawing::Size(1018, 720);
	this->Controls->Add(this->user_table);
}

void QQ::UserPageRed::pictureBoxAvatar_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
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

void QQ::UserPageRed::username(System::Object^ sender, System::EventArgs^ e)
{

}

void QQ::UserPageRed::save_Click(System::Object^ sender, System::EventArgs^ e)
{

}

void QQ::UserPageRed::UpdatePhoto_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		try
		{
			// Без блокировки файла — делаем копию сразу
			MemoryStream^ ms = gcnew MemoryStream(File::ReadAllBytes(openFileDialog1->FileName));
			Image^ img = Image::FromStream(ms);

			// Проверяем наличие свойства ориентации (ID 0x0112)
			const int OrientationId = 0x0112;
			if (Array::IndexOf(img->PropertyIdList, OrientationId) >= 0)
			{
				System::Drawing::Imaging::PropertyItem^ prop = img->GetPropertyItem(OrientationId);
				int orientationValue = prop->Value[0];

				switch (orientationValue)
				{
				case 1: break; // Normal
				case 2: img->RotateFlip(RotateFlipType::RotateNoneFlipX); break;
				case 3: img->RotateFlip(RotateFlipType::Rotate180FlipNone); break;
				case 4: img->RotateFlip(RotateFlipType::RotateNoneFlipY); break;
				case 5: img->RotateFlip(RotateFlipType::Rotate90FlipX); break;
				case 6: img->RotateFlip(RotateFlipType::Rotate90FlipNone); break;
				case 7: img->RotateFlip(RotateFlipType::Rotate270FlipX); break;
				case 8: img->RotateFlip(RotateFlipType::Rotate270FlipNone); break;
				default: break; // нераспознанное значение
				}

			}
			// Показываем картинку в PictureBox
			this->pictureBoxAvatar->BackgroundImage = img;
			this->pictureBoxAvatar->BackgroundImageLayout = ImageLayout::None;

			// Сохраняем байты (для отправки в БД)
			MemoryStream^ saveStream = gcnew MemoryStream();
			img->Save(saveStream, System::Drawing::Imaging::ImageFormat::Png); // или .Jpeg
			this->imageBytes = saveStream->ToArray();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Ошибка загрузки изображения: " + ex->Message);
		}
	}
}

void QQ::UserPageRed::update_pswd_Click(System::Object^ sender, System::EventArgs^ e) {
	if (isExpanded2) {
		now_pswd->Visible = true;
		now_pswd_text->Visible = true;
		new_pswd->Visible = true;
		new_pswd_text->Visible = true;
	}
	else
	{
		now_pswd->Visible = false;
		now_pswd_text->Visible = false;
		new_pswd->Visible = false;
		new_pswd_text->Visible = false;
	}
	isExpanded2 = !isExpanded2;
}


UserPageRed::~UserPageRed()
{
}


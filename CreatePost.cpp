
#include "User.h"
#include "CreatePost.h"
#include "PostRepository.h"
#include <ctime>
#include <string>

using namespace QQ;

CreatePost::CreatePost(User^ user) {

	InitializeComponent();
	user_Id = user->ID;
}

void CreatePost::InitializeComponent(void)
{
	this->AutoSize = true;

	// 
	// text_post_text
	// 
	this->text_post_text = gcnew TextBox();
	this->text_post_text->AutoSize = true;
	this->text_post_text->Multiline = true;
	this->text_post_text->TabIndex = 3;
	this->text_post_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->text_post_text->ForeColor = System::Drawing::Color::Black;
	this->text_post_text->Margin = System::Windows::Forms::Padding(3);
	this->text_post_text->Location = System::Drawing::Point(0, 0); //3, 214
	this->text_post_text->Size = System::Drawing::Size(1004, 100);
	//this->text_post_text->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// text_post
	// 
	this->text_post = gcnew Label();
	this->text_post->Text = L"Текст";
	this->text_post->AutoSize = true;
	this->text_post->Dock = System::Windows::Forms::DockStyle::Fill;
	this->text_post->Font = (gcnew System::Drawing::Font(L"Montserrat SemiBold", 20, System::Drawing::FontStyle::Bold));
	this->text_post->ForeColor = System::Drawing::Color::White;
	this->text_post->Location = System::Drawing::Point(0, 0); //3, 161
	this->text_post->Margin = System::Windows::Forms::Padding(3);
	this->text_post->Size = System::Drawing::Size(1004, 47);
	//this->text_post->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// header_text
	// 
	this->header_text = gcnew TextBox();
	this->header_text->AutoSize = true;
	this->header_text->WordWrap = true;
	this->header_text->TabIndex = 2;
	this->header_text->Font = (gcnew System::Drawing::Font(L"Montserrat", 14, System::Drawing::FontStyle::Regular));
	this->header_text->ForeColor = System::Drawing::Color::Black;
	this->header_text->Location = System::Drawing::Point(3, 56);
	this->header_text->Margin = System::Windows::Forms::Padding(3);
	this->header_text->Size = System::Drawing::Size(1004, 100);
	//this->header_text->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// header
	// 
	this->header = gcnew Label();
	this->header->Text = L"Заголовок";
	this->header->Dock = DockStyle::Fill;
	this->header->Margin = System::Windows::Forms::Padding(3);
	this->header->Font = gcnew System::Drawing::Font(L"Montserrat", 20, FontStyle::Bold);
	this->header->ForeColor = Color::White;
	this->header->AutoSize = true;
	this->header->Location = System::Drawing::Point(3, 3);
	this->header->Size = System::Drawing::Size(1004, 47);
	//this->header->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	
	this->add_photo = gcnew Label();
	this->add_photo->Text = L"Добавить фотографию";
	this->add_photo->Dock = DockStyle::Fill;
	this->add_photo->Margin = System::Windows::Forms::Padding(3);
	this->add_photo->Font = gcnew System::Drawing::Font(L"Montserrat", 20, FontStyle::Bold);
	this->add_photo->ForeColor = Color::White;
	this->add_photo->AutoSize = true;
	this->add_photo->Location = System::Drawing::Point(3, 3);
	this->add_photo->Size = System::Drawing::Size(1004, 47);
	// 
	// pictureBox
	// 

	this->testBox = gcnew PictureBox();
	this->testBox->Image = Image::FromFile("ava.png"); // файл рядом
	this->testBox->SizeMode = PictureBoxSizeMode::Zoom;
	this->testBox->Size = System::Drawing::Size(400, 300);
	this->testBox->Visible = false;


	this->openFileDialog1 = gcnew OpenFileDialog();
	this->openFileDialog1->Title = "Выберите изображение";
	this->openFileDialog1->Filter = "Файлы изображений (*.png;*.jpg)|*.png;*.jpg";


	this->save = gcnew Button();
	this->save->Click += gcnew System::EventHandler(this, &CreatePost::save_Click);
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
	this->upd_photo->Click += gcnew System::EventHandler(this, &CreatePost::UpdatePhoto_Click);
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
	this->upd_photo->Text = L"Добавить";


	
	


	this->post_table = gcnew TableLayoutPanel();
	this->post_table->AutoSize = true;
	this->post_table->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
	this->post_table->BackColor = System::Drawing::Color::SlateBlue;
	this->post_table->Dock = System::Windows::Forms::DockStyle::Fill;
	this->post_table->ColumnCount = 1;
	this->post_table->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 100));
	this->post_table->Location = System::Drawing::Point(0, 0);
	this->post_table->Margin = System::Windows::Forms::Padding(2, 0, 2, 2);
	this->post_table->RowCount = 0; // будет нарастать динамически
	this->post_table->Controls->Add(this->header);
	this->post_table->Controls->Add(this->header_text);
	this->post_table->Controls->Add(this->text_post);
	this->post_table->Controls->Add(this->text_post_text);
	this->post_table->Controls->Add(this->add_photo);
	this->post_table->Controls->Add(this->upd_photo);
	//this->post_table->Controls->Add(this->pictureBox);
	this->post_table->Controls->Add(this->testBox);
	this->post_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->post_table->Size = System::Drawing::Size(1010, 434);
	this->post_table->MaximumSize = System::Drawing::Size(1010, 0);
	//this->post_table->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	// 
	// main_table
	// 
	this->main_table = gcnew TableLayoutPanel();
	this->main_table->AutoSize = true;
	this->main_table->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
	this->main_table->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->main_table->ColumnCount = 1;
	this->main_table->Dock = DockStyle::Fill;
	this->main_table->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
	this->main_table->Controls->Add(this->post_table, 0, 0);
	this->main_table->Controls->Add(this->save, 0, 1);
	this->main_table->Location = System::Drawing::Point(0, 0);
	this->main_table->RowCount = 4;
	this->main_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->main_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->main_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->main_table->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize)));
	this->main_table->Size = System::Drawing::Size(1018, 720);
	this->Controls->Add(this->main_table);
}


void QQ::CreatePost::UpdatePhoto_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		try
		{
			// Загружаем изображение во временный файл
			String^ filePath = openFileDialog1->FileName;
			img = Image::FromFile(filePath);

			// Корректируем ориентацию если нужно
			const int OrientationId = 0x0112;
			if (Array::IndexOf(img->PropertyIdList, OrientationId) >= 0)
			{
				System::Drawing::Imaging::PropertyItem^ prop = img->GetPropertyItem(OrientationId);
				int orientationValue = prop->Value[0];

				// Применяем корректировку ориентации
				RotateFlipType rotateType = RotateFlipType::RotateNoneFlipNone;
				switch (orientationValue)
				{
				case 2: rotateType = RotateFlipType::RotateNoneFlipX; break;
				case 3: rotateType = RotateFlipType::Rotate180FlipNone; break;
				case 4: rotateType = RotateFlipType::RotateNoneFlipY; break;
				case 5: rotateType = RotateFlipType::Rotate90FlipX; break;
				case 6: rotateType = RotateFlipType::Rotate90FlipNone; break;
				case 7: rotateType = RotateFlipType::Rotate270FlipX; break;
				case 8: rotateType = RotateFlipType::Rotate270FlipNone; break;
				}
				if (rotateType != RotateFlipType::RotateNoneFlipNone)
					img->RotateFlip(rotateType);
			}

			// Конвертируем в PNG и сохраняем в imageBytes
			
			try {
				MemoryStream^ ms = gcnew MemoryStream();
				img->Save(ms, System::Drawing::Imaging::ImageFormat::Png);
				imageBytes = ms->ToArray();
				ms->Close(); // на всякий случай
			}
			catch (Exception^ ex) {
				MessageBox::Show("Ошибка при сохранении изображения: " + ex->Message);
				return;
			}

			System::Text::StringBuilder^ hexOutput = gcnew System::Text::StringBuilder();

			int limit = Math::Min(32, imageBytes->Length);
			for (int i = 0; i < limit; ++i) {
				hexOutput->Append(imageBytes[i].ToString("X2"));
				hexOutput->Append(" ");
			}

			MessageBox::Show("imageBytes (" + imageBytes->Length + " байт):\n" + hexOutput->ToString());


			// Показываем в PictureBox
			this->testBox->Image = img;
			this->testBox->Visible = true;
			this->testBox->Refresh();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Ошибка загрузки изображения: " + ex->Message);
			img = nullptr;
			imageBytes = nullptr;
		}
	}
}

void QQ::CreatePost::save_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ title = header_text->Text->Trim();
	String^ content = text_post_text->Text->Trim();

	/*if (String::IsNullOrWhiteSpace(title) || String::IsNullOrWhiteSpace(content))
	{
		MessageBox::Show("Поля заголовка и текста не должны быть пустыми.");
		return;
	}*/
	DateTime^ s = DateTime::Now;
	// сохранение
	bool success = PostRepository::AddPost(
		this->user_Id,
		this->header_text->Text,
		this->text_post_text->Text,
		DateTime::Now,
		this->imageBytes // массив байтов PNG-фото
	);



	if (success) {
		MessageBox::Show("Пост успешно создан!");
	}
	else {
		MessageBox::Show("Ошибка при создании поста.");
	}
}

CreatePost::~CreatePost()
{
}

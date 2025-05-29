#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define IDataObject IDataObject_WINAPI

#include "PostRepository.h"
#include "Post.h"
#include "Session.h"
#include "PostControl.h"
#include <iostream>
#include <msclr/marshal_cppstd.h>
#include <string>
#include <vcclr.h>

extern "C" {
#include <libpq-fe.h>
#include "MyUserControl.h"
#include "UserPage.h"
using namespace System::IO;
}

#undef IDataObject


using namespace System::Runtime::InteropServices;
using namespace msclr::interop;
using namespace System;
using namespace QQ;


List<QQ::Post^>^ PostRepository::LoadAllPosts()
{
    List<QQ::Post^>^ posts = gcnew List<QQ::Post^>();

    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) return posts;

    PGconn* conn = db.get();
    std::string query = "SELECT posts.*, people.name FROM posts INNER JOIN people ON people.id=posts.blog_id ORDER BY posts.post_date DESC;";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        db.disconnect();
        return posts;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; ++i) {
        int id = std::stoi(PQgetvalue(res, i, 0));
        std::string titleStr = PQgetvalue(res, i, 2);
        std::string contentStr = PQgetvalue(res, i, 3);
        std::string dateStr = PQgetvalue(res, i, 5);
        std::string authorNameStr = "@" + std::string(PQgetvalue(res, i, 7));
        bool commentsEnabled = std::string(PQgetvalue(res, i, 6)) == "t";

        String^ title = marshal_as<String^>(titleStr);
        String^ content = marshal_as<String^>(contentStr);
        String^ authorName = marshal_as<String^>(authorNameStr);
        DateTime postDate = DateTime::Parse(marshal_as<String^>(dateStr));

        array<Byte>^ imageData = nullptr;
        System::Drawing::Image^ image = nullptr;

        if (!PQgetisnull(res, i, 4)) {
            size_t unescapedLength = 0;
            const char* escaped = PQgetvalue(res, i, 4);  // column 'photo'
            unsigned char* unescaped = PQunescapeBytea((const unsigned char*)escaped, &unescapedLength);

            if (unescaped && unescapedLength > 0) {
                imageData = gcnew array<Byte>((int)unescapedLength);
                Marshal::Copy((IntPtr)(void*)unescaped, imageData, 0, (int)unescapedLength);

                try {
                    MemoryStream^ ms = gcnew MemoryStream(imageData);
                    image = Image::FromStream(ms);
                }
                catch (...) {
                    image = nullptr;
                }

                PQfreemem(unescaped);
            }
        }

        QQ::Post^ post = gcnew QQ::Post(id, title, content, authorName, image, postDate);
        post->Image = image;
        post->Date = postDate;
        post->CommentsAllowed = commentsEnabled;

        posts->Add(post);
    }

    PQclear(res);
    db.disconnect();
    return posts;
}


List<QQ::Post^>^ PostRepository::LoadPostsUser(User^ user)
{
    List<QQ::Post^>^ posts = gcnew List<QQ::Post^>();

    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        return posts;
    }
    PGconn* conn = db.get(); // Нативный указатель

    std::string query = "SELECT posts.*, people.name FROM posts INNER JOIN people ON people.id=posts.blog_id WHERE posts.blog_id="+ std::to_string(user->ID) +" ORDER BY posts.post_date DESC;";
    PGresult* res = PQexec(conn, query.c_str()); // Нативный указатель

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);  // Очищаем результат запроса
        db.disconnect();
        return posts;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; ++i) {
        int id = std::stoi(PQgetvalue(res, i, 0));                     // posts.id
        std::string titleStr = PQgetvalue(res, i, 2);                   // posts.title
        std::string contentStr = PQgetvalue(res, i, 3);                 // posts.content
        std::string dateStr = PQgetvalue(res, i, 5);                    // posts.post_date
        std::string authorNameStr = "@" + std::string(PQgetvalue(res, i, 7));
        bool commentsEnabled = std::string(PQgetvalue(res, i, 6)) == "t";

        // Преобразования из std::string в String^
        String^ title = marshal_as<String^>(titleStr);
        String^ content = marshal_as<String^>(contentStr);
        String^ authorName = marshal_as<String^>(authorNameStr);
        DateTime postDate = DateTime::Parse(marshal_as<String^>(dateStr));

        array<Byte>^ imageData = nullptr;
        System::Drawing::Image^ image = nullptr;

        // Обработка изображения из базы данных
        if (!PQgetisnull(res, i, 4)) {
            size_t unescapedLength = 0;
            const char* escaped = PQgetvalue(res, i, 4);  // column 'photo'
            unsigned char* unescaped = PQunescapeBytea((const unsigned char*)escaped, &unescapedLength);

            if (unescaped && unescapedLength > 0) {
                imageData = gcnew array<Byte>((int)unescapedLength);
                Marshal::Copy((IntPtr)(void*)unescaped, imageData, 0, (int)unescapedLength);

                try {
                    MemoryStream^ ms = gcnew MemoryStream(imageData);
                    image = Image::FromStream(ms);
                }
                catch (...) {
                    image = nullptr;
                }

                PQfreemem(unescaped);
            }
        }

        // Создание поста и добавление в список
        QQ::Post^ post = gcnew QQ::Post(id, title, content, authorName, image, postDate);
        post->Image = image;
        post->Date = postDate;
        post->CommentsAllowed = commentsEnabled;

        posts->Add(post);
    }

    PQclear(res);  // Очищаем результат запроса
    db.disconnect();  // Отключаемся от базы данных
    return posts;
}

bool PostRepository::AddPost(int user_id, String^ title, String^ content, DateTime date, array<Byte>^ imageData)
{
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) return false;

    PGconn* conn = db.get();

    std::string query = "INSERT INTO public.posts (blog_id, title, content, post_date, photo, comment_enable) VALUES ($1, $2, $3, $4, $5, $6);";

    // Преобразуем параметры
    std::string blog_id_str = std::to_string(user_id);
    std::string title_str = marshal_as<std::string>(title);
    std::string content_str = marshal_as<std::string>(content);
    std::string date_str = marshal_as<std::string>(date.ToString("yyyy-MM-dd HH:mm:ss"));

    // Подготовим параметры
    const char* paramValues[6];
    int paramLengths[6] = { 0 };
    int paramFormats[6] = { 0, 0, 0, 0, 1, 0 }; // Последний параметр (фото) в бинарном, последний — текст

    paramValues[0] = blog_id_str.c_str();
    paramValues[1] = title_str.c_str();
    paramValues[2] = content_str.c_str();
    paramValues[3] = date_str.c_str();

    pin_ptr<unsigned char> pinnedData = nullptr;

    if (imageData != nullptr && imageData->Length > 0) {
        pinnedData = &imageData[0];
        paramValues[4] = reinterpret_cast<const char*>(pinnedData);
        paramLengths[4] = imageData->Length;
    }
    else {
        paramValues[4] = nullptr;
        paramLengths[4] = 0;
    }

    paramValues[5] = "true"; // Включаем комментарии по умолчанию

    // Выполняем запрос
    PGresult* res = PQexecParams(
        conn,
        query.c_str(),
        6,             // параметров 6
        nullptr,       // типы не указываем
        paramValues,
        paramLengths,
        paramFormats,
        0              // текстовый результат
    );

    bool success = PQresultStatus(res) == PGRES_COMMAND_OK;

    if (!success) {
        String^ error = gcnew String(PQerrorMessage(conn));
    }

    PQclear(res);
    db.disconnect();
    return success;
}



bool PostRepository::DeletePost(int postId)
{
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) return false;

    PGconn* conn = db.get();

    // Удалим сначала комментарии к посту, если есть (если нужна такая логика)
    std::string deleteComments = "DELETE FROM public.commenti WHERE post_id = " + std::to_string(postId) + ";";
    PQexec(conn, deleteComments.c_str());

    // Удаляем сам пост
    std::string query = "DELETE FROM public.posts WHERE id = " + std::to_string(postId) + ";";
    PGresult* res = PQexec(conn, query.c_str());

    bool success = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    db.disconnect();
    return success;
}

bool PostRepository::UpdateCommentsAllowed(int postId, bool allowed)
{
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) return false;

    PGconn* conn = db.get();
    const char* paramValues[2];
    int paramFormats[2] = { 0, 0 };
    int paramLengths[2] = { 0, 0 };

    std::string idStr = std::to_string(postId);
    std::string allowedStr = allowed ? "true" : "false";
    paramValues[0] = idStr.c_str();
    paramValues[1] = allowedStr.c_str();

    PGresult* res = PQexecParams(
        conn,
        "UPDATE public.posts SET comment_enable = $2 WHERE id = $1",
        2, nullptr, paramValues, paramLengths, paramFormats, 0
    );

    bool ok = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    db.disconnect();
    return ok;
}

void PostControl::OnAuthorClick(System::Object^ sender, System::EventArgs^ e)
{
    System::String^ name = this->user_post->Text->TrimStart('@'); // убираем @

    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        MessageBox::Show("Не удалось подключиться к базе данных.");
        return;
    }

    PGconn* conn = db.get();
    std::string nameStr = marshal_as<std::string>(name);
    std::string query = "SELECT * FROM people WHERE name = '" + nameStr + "' LIMIT 1;";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        MessageBox::Show("Пользователь не найден.");
        PQclear(res);
        db.disconnect();
        return;
    }

    QQ::User^ u = QQ::User::CreateEmpty();

    u->ID = Convert::ToInt32(gcnew String(PQgetvalue(res, 0, 0)));
    u->Username = gcnew String(PQgetvalue(res, 0, 1));
    u->Password = gcnew String(PQgetvalue(res, 0, 2));
    u->Interests = gcnew String(PQgetvalue(res, 0, 3));
    u->Date = DateTime::ParseExact(gcnew String(PQgetvalue(res, 0, 4)), "yyyy-MM-dd", System::Globalization::CultureInfo::InvariantCulture);
    u->About = gcnew String(PQgetvalue(res, 0, 5));
    u->Contacts = gcnew String(PQgetvalue(res, 0, 7));

    if (!PQgetisnull(res, 0, 6)) {
        size_t unescapedLength = 0;
        const char* escaped = PQgetvalue(res, 0, 6);
        unsigned char* unescaped = PQunescapeBytea((const unsigned char*)escaped, &unescapedLength);

        if (unescaped && unescapedLength > 0) {
            array<Byte>^ bytes = gcnew array<Byte>((int)unescapedLength);
            Marshal::Copy((IntPtr)(void*)unescaped, bytes, 0, (int)unescapedLength);
            try {
                MemoryStream^ ms = gcnew MemoryStream(bytes);
                u->Photo = Image::FromStream(ms);
            }
            catch (...) {
                u->Photo = nullptr;
            }
            PQfreemem(unescaped);
        }
    }


    PQclear(res);
    db.disconnect();

    Session::SelectUser = u;

    // вызываем переход на UserPage
    Control^ parent = this->Parent;
    while (parent != nullptr && parent->GetType()->Name != "MyUserControl") {
        parent = parent->Parent;
    }

    if (parent != nullptr) {
        QQ::MyUserControl^ main = safe_cast<QQ::MyUserControl^>(parent);
        UserPage^ page = gcnew UserPage(u);
        page->OnEditRequested += gcnew UserPage::EditRequestedHandler(main, &MyUserControl::OpenEditProfile);
        page->OnCreatePost += gcnew UserPage::CreatePostRequestedHandler(main, &MyUserControl::OpenCreatePost);
        main->Controls->Find("mainflow", true)[0]->Controls->Clear();
        main->Controls->Find("mainflow", true)[0]->Controls->Add(page);
    }
}
void QQ::PostOpen::AuthorLabel_Click(System::Object^ sender, System::EventArgs^ e)
{
    System::String^ name = this->user_post->Text->TrimStart('@');

    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        MessageBox::Show("Не удалось подключиться к базе данных.");
        return;
    }

    PGconn* conn = db.get();
    std::string nameStr = marshal_as<std::string>(name);
    std::string query = "SELECT * FROM people WHERE name = '" + nameStr + "' LIMIT 1;";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        MessageBox::Show("Пользователь не найден.");
        PQclear(res);
        db.disconnect();
        return;
    }

    QQ::User^ u = QQ::User::CreateEmpty();
    u->ID = Convert::ToInt32(gcnew String(PQgetvalue(res, 0, 0)));
    u->Username = gcnew String(PQgetvalue(res, 0, 1));
    u->Password = gcnew String(PQgetvalue(res, 0, 2));
    u->Interests = gcnew String(PQgetvalue(res, 0, 3));
    u->Date = DateTime::ParseExact(gcnew String(PQgetvalue(res, 0, 4)), "yyyy-MM-dd", System::Globalization::CultureInfo::InvariantCulture);
    u->About = gcnew String(PQgetvalue(res, 0, 5));
    u->Contacts = gcnew String(PQgetvalue(res, 0, 7));

    if (!PQgetisnull(res, 0, 6)) {
        size_t unescapedLength = 0;
        const char* escaped = PQgetvalue(res, 0, 6);
        unsigned char* unescaped = PQunescapeBytea((const unsigned char*)escaped, &unescapedLength);

        if (unescaped && unescapedLength > 0) {
            array<Byte>^ bytes = gcnew array<Byte>((int)unescapedLength);
            System::Runtime::InteropServices::Marshal::Copy(IntPtr((void*)unescaped), bytes, 0, (int)unescapedLength);
            try {
                MemoryStream^ ms = gcnew MemoryStream(bytes);
                u->Photo = Image::FromStream(ms);
            }
            catch (...) {
                u->Photo = nullptr;
            }
            PQfreemem(unescaped);
        }
    }

    PQclear(res);
    db.disconnect();

    Session::SelectUser = u;

    // Переход к UserPage
    Control^ parent = this->Parent;
    while (parent != nullptr && parent->GetType()->Name != "MyUserControl") {
        parent = parent->Parent;
    }

    if (parent != nullptr) {
        QQ::MyUserControl^ main = safe_cast<QQ::MyUserControl^>(parent);
        UserPage^ page = gcnew UserPage(u);
        page->OnEditRequested += gcnew UserPage::EditRequestedHandler(main, &MyUserControl::OpenEditProfile);
        page->OnCreatePost += gcnew UserPage::CreatePostRequestedHandler(main, &MyUserControl::OpenCreatePost);
        main->Controls->Find("mainflow", true)[0]->Controls->Clear();
        main->Controls->Find("mainflow", true)[0]->Controls->Add(page);
    }
}

void QQ::Comment::AuthorLabel_Click(System::Object^ sender, System::EventArgs^ e)
{
    System::String^ name = this->user_comm->Text->TrimStart('@');

    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        MessageBox::Show("Не удалось подключиться к базе данных.");
        return;
    }

    PGconn* conn = db.get();
    std::string nameStr = marshal_as<std::string>(name);
    std::string query = "SELECT * FROM people WHERE name = '" + nameStr + "' LIMIT 1;";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK || PQntuples(res) == 0) {
        MessageBox::Show("Пользователь не найден.");
        PQclear(res);
        db.disconnect();
        return;
    }

    QQ::User^ u = QQ::User::CreateEmpty();
    u->ID = Convert::ToInt32(gcnew String(PQgetvalue(res, 0, 0)));
    u->Username = gcnew String(PQgetvalue(res, 0, 1));
    u->Password = gcnew String(PQgetvalue(res, 0, 2));
    u->Interests = gcnew String(PQgetvalue(res, 0, 3));
    u->Date = DateTime::ParseExact(gcnew String(PQgetvalue(res, 0, 4)), "yyyy-MM-dd", System::Globalization::CultureInfo::InvariantCulture);
    u->About = gcnew String(PQgetvalue(res, 0, 5));
    u->Contacts = gcnew String(PQgetvalue(res, 0, 7));

    if (!PQgetisnull(res, 0, 6)) {
        size_t unescapedLength = 0;
        const char* escaped = PQgetvalue(res, 0, 6);
        unsigned char* unescaped = PQunescapeBytea((const unsigned char*)escaped, &unescapedLength);

        if (unescaped && unescapedLength > 0) {
            array<Byte>^ bytes = gcnew array<Byte>((int)unescapedLength);
            System::Runtime::InteropServices::Marshal::Copy(IntPtr((void*)unescaped), bytes, 0, (int)unescapedLength);
            try {
                MemoryStream^ ms = gcnew MemoryStream(bytes);
                u->Photo = Image::FromStream(ms);
            }
            catch (...) {
                u->Photo = nullptr;
            }
            PQfreemem(unescaped);
        }
    }

    PQclear(res);
    db.disconnect();

    Session::SelectUser = u;

    // Переход к UserPage
    Control^ parent = this->Parent;
    while (parent != nullptr && parent->GetType()->Name != "MyUserControl") {
        parent = parent->Parent;
    }

    if (parent != nullptr) {
        QQ::MyUserControl^ main = safe_cast<QQ::MyUserControl^>(parent);
        UserPage^ page = gcnew UserPage(u);
        page->OnEditRequested += gcnew UserPage::EditRequestedHandler(main, &MyUserControl::OpenEditProfile);
        page->OnCreatePost += gcnew UserPage::CreatePostRequestedHandler(main, &MyUserControl::OpenCreatePost);
        main->Controls->Find("mainflow", true)[0]->Controls->Clear();
        main->Controls->Find("mainflow", true)[0]->Controls->Add(page);
    }
}

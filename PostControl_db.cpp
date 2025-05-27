#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define IDataObject IDataObject_WINAPI

#include "PostRepository.h"
#include "Post.h"
#include <iostream>
#include <msclr/marshal_cppstd.h>
#include <string>
#include <vcclr.h>

extern "C" {
#include <libpq-fe.h>
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

    std::string query = "INSERT INTO public.posts (blog_id, title, content, post_date, photo) VALUES ($1, $2, $3, $4, $5);";

    // Преобразуем параметры
    std::string blog_id_str = std::to_string(user_id);
    std::string title_str = marshal_as<std::string>(title);
    std::string content_str = marshal_as<std::string>(content);
    std::string date_str = marshal_as<std::string>(date.ToString("yyyy-MM-dd HH:mm:ss"));

    // Подготовим параметры
    const char* paramValues[5];
    int paramLengths[5] = { 0 };
    int paramFormats[5] = { 0, 0, 0, 0, 1 }; // Последний параметр (фото) в бинарном формате

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

    // Выполняем запрос
    PGresult* res = PQexecParams(
        conn,
        query.c_str(),
        5,             // параметров 5
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


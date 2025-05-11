#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define IDataObject IDataObject_WINAPI

#include "PostRepository.h"
#include "Post.h"
#include <msclr/marshal_cppstd.h>
#include <string>

extern "C" {
#include <libpq-fe.h>
}

#undef IDataObject


using namespace msclr::interop;
using namespace System;
using namespace QQ;


List<QQ::Post^>^ PostRepository::LoadAllPosts()
{
    List<QQ::Post^>^ posts = gcnew List<QQ::Post^>();

    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        return posts;
    }

    PGconn* conn = db.get(); // Нативный указатель
    std::string query = "SELECT id, blog_id, title, content, photo, post_date, comments_enabled FROM posts ORDER BY post_date DESC";
    PGresult* res = PQexec(conn, query.c_str()); // Нативный указатель

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);  // Очищаем результат запроса
        db.disconnect();
        return posts;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; ++i) {
        int id = std::stoi(PQgetvalue(res, i, 0));
        std::string titleStr = PQgetvalue(res, i, 2);
        std::string contentStr = PQgetvalue(res, i, 3);
        std::string dateStr = PQgetvalue(res, i, 5);
        std::string author = "Автор #" + std::to_string(std::stoi(PQgetvalue(res, i, 1))); // blog_id = user id
        bool commentsEnabled = std::string(PQgetvalue(res, i, 6)) == "t";

        // Преобразования из std::string в String^
        String^ title = marshal_as<String^>(titleStr);
        String^ content = marshal_as<String^>(contentStr);
        String^ authorName = marshal_as<String^>(author);
        DateTime postDate = DateTime::Parse(marshal_as<String^>(dateStr));

        // Обработка изображения из базы данных
        array<Byte>^ imageData = nullptr;
        int photoLength = PQgetlength(res, i, 4);
        if (photoLength > 0) {
            const char* photoData = PQgetvalue(res, i, 4);
            imageData = gcnew array<Byte>(photoLength);
            for (int j = 0; j < photoLength; ++j) {
                imageData[j] = photoData[j];
            }
        }

        // Создание поста и добавление в список
        QQ::Post^ post = gcnew QQ::Post(title, content, authorName, imageData, postDate);
        post->Date = postDate;
        post->CommentsAllowed = commentsEnabled;

        posts->Add(post);
    }

    PQclear(res);  // Очищаем результат запроса
    db.disconnect();  // Отключаемся от базы данных
    return posts;
}


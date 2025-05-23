#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define IDataObject IDataObject_WINAPI

#include "PostRepository.h"
#include "PostgresConnection.h"
#include "Post.h"
#include "red_user.h"
#include <msclr/marshal_cppstd.h>
#include <string>
#include <iostream>

extern "C" {
#include <libpq-fe.h>
}

#undef IDataObject


using namespace msclr::interop;
using namespace System;
using namespace System::Drawing::Imaging;
using namespace QQ;

int update_post(System::String^ title_post, System::String^ text_post, const int id) { 
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        return 0;
    }
    PGconn* conn = db.get(); // Нативный указатель

    std::string title = marshal_as<std::string>(title_post);
    std::string content = marshal_as<std::string>(text_post);
    std::string idStr = std::to_string(id);

    // Экранирование всех полей
    char* title_new = PQescapeLiteral(conn, title.c_str(), title.length());
    char* content_new = PQescapeLiteral(conn, content.c_str(), content.length());
    char* escapedId = PQescapeLiteral(conn, idStr.c_str(), idStr.length());
    //char* photo = PQescapeLiteral(conn, photo_data.c_str(), photo_data.length());

    // Проверка успешности экранирования
    if (!title_new || !content_new || !escapedId) {
        std::cerr << "Ошибка экранирования." << std::endl;
        if (title_new) PQfreemem(title_new);
        if (content_new) PQfreemem(content_new);
        if (escapedId) PQfreemem(escapedId);
        //if (photo) PQfreemem(photo);
        return 3;
    }

    // Формирование запроса
    std::string query = "UPDATE posts SET title = " + std::string(title_new) +
        ", content = " + std::string(content_new) +
        //", photo = " + std::string(photo) +
        " WHERE posts.id = " + std::string(escapedId) + ";";

    // Выполнение запроса
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Ошибка выполнения запроса: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        PQfreemem(title_new);
        PQfreemem(content_new);
        PQfreemem(escapedId);
        //PQfreemem(photo);
        db.disconnect();
        return 0;
    }

    // Очистка ресурсов
    PQclear(res);
    PQfreemem(title_new);
    PQfreemem(content_new);
    PQfreemem(escapedId);
    //PQfreemem(photo);

    db.disconnect();
    return 1;
}

bool QQ::UserPageRed::UpdateUserFull(QQ::User^ user)
{
    if (user->Photo == nullptr) {
        MessageBox::Show("user->Photo == nullptr");
    }
    else {
        MemoryStream^ testStream = gcnew MemoryStream();
        try {
            user->Photo->Save(testStream, System::Drawing::Imaging::ImageFormat::Png);
            MessageBox::Show("user->Photo успешно сериализуется");
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка сериализации photo: " + ex->Message);
        }
    }


    PostgresConnection& dbConnection = PostgresConnection::getInstance();
    if (!dbConnection.connect()) {
        MessageBox::Show("Ошибка подключения к базе данных");
        return false;
    }

    PGconn* conn = dbConnection.get();

    String^ interests1 = user->Interests;
    String^ about1 = user->About;
    String^ contacts1 = user->Contacts;
    DateTime^ date = user->Date;
    String^ dateStr = date->ToString("yyyy-MM-dd");

    std::string interests = marshal_as<std::string>(interests1);
    std::string about = marshal_as<std::string>(about1);
    std::string contacts = marshal_as<std::string>(contacts1);
    std::string born = marshal_as<std::string>(dateStr);

    const char* photoPtr = nullptr;
    int photoLength = 0;
    int hasPhoto = 0;

    if (user->Photo != nullptr) {
        try {
            MemoryStream^ ms = gcnew MemoryStream();
            user->Photo->Save(ms, System::Drawing::Imaging::ImageFormat::Png);
            ms->Position = 0;
            array<Byte>^ bytes = ms->ToArray();

            photoLength = bytes->Length;
            photoPtr = (const char*)(void*)System::Runtime::InteropServices::Marshal::UnsafeAddrOfPinnedArrayElement(bytes, 0);
            hasPhoto = 1;
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка обработки изображения: " + ex->Message);
            dbConnection.disconnect();
            return false;
        }
    }

    const Oid TEXTOID = 25;     // text
    const Oid BYTEAOID = 17;    // bytea
    const Oid DATEOID = 1082;

    const char* paramValues[5];
    int paramLengths[5];
    int paramFormats[5] = { 0, 0, 0, hasPhoto ? 1 : 0, 0 };
    Oid paramTypes[5] = { TEXTOID, DATEOID, TEXTOID, BYTEAOID, TEXTOID };

    paramValues[0] = interests.c_str();
    paramLengths[0] = interests.length();
    paramValues[1] = born.c_str();
    paramLengths[1] = born.length();
    paramValues[2] = about.c_str();
    paramLengths[2] = about.length();
    paramValues[3] = hasPhoto ? photoPtr : nullptr;
    paramLengths[3] = photoLength;
    paramValues[4] = contacts.c_str();
    paramLengths[4] = contacts.length();

    std::string query = "UPDATE people SET interests = $1, date_of_birth = $2, about_me = $3, photo = $4, contacts = $5 WHERE id = " + std::to_string(user->ID);

    PGresult* res = PQexecParams(
        conn,
        query.c_str(),
        5,
        paramTypes,
        paramValues,
        paramLengths,
        paramFormats,
        0
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        MessageBox::Show("Ошибка при обновлении данных: " + gcnew String(PQerrorMessage(conn)));
        PQclear(res);
        dbConnection.disconnect();
        return false;
    }

    PQclear(res);
    dbConnection.disconnect();
    return true;
}
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

bool QQ::UserPageRed::UpdateUserData(User^ user, array<Byte>^ imageData)
{
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
            ms->Position = 0;  // 🔥 обязательно
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


/*bool QQ::UserPageRed::UpdateUserData(User^ user, array<Byte>^ imageData)
{
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    if (!dbConnection.connect()) {
        MessageBox::Show("Ошибка подключения к БД");
        return false;
    }

    PGconn* conn = dbConnection.get();

    String^ pswd_st = user->Password;
    String^ interests1 = user->Interests;
    String^ about1 = user->About;
    String^ contacts1 = user->Contacts;
    DateTime^ date = user->Date;
    String^ dateStr = date->ToString("yyyy-MM-dd");

    // Подготавливаем параметры
    const char* paramValues[7];
    int paramLengths[7] = { 0 };
    int paramFormats[7] = { 0 };

    // Конвертируем строки в UTF-8
    //std::string password = msclr::interop::marshal_as<std::string>(pswd_st);
    std::string about = msclr::interop::marshal_as<std::string>(about1);
    std::string interests = msclr::interop::marshal_as<std::string>(interests1);
    std::string contacts = msclr::interop::marshal_as<std::string>(contacts1);
    std::string born = msclr::interop::marshal_as<std::string>(dateStr);

    paramValues[0] = about.c_str();
    paramValues[1] = interests.c_str();
    paramValues[2] = contacts.c_str();
    paramValues[3] = born.c_str();

    // Обрабатываем изображение
    if (imageData != nullptr && imageData->Length > 0)
    {
        pin_ptr<unsigned char> pinnedData = &imageData[0];
        paramValues[4] = (const char*)pinnedData;
        paramLengths[4] = imageData->Length;
        paramFormats[4] = 1; // binary format
    }
    else
    {
        paramValues[4] = NULL;
    }

    // ID пользователя
    std::string idStr = std::to_string(user->ID);
    paramValues[5] = idStr.c_str();

    // Пароль (если изменен)
    if (!String::IsNullOrEmpty(user->Password))
    {
        std::string pswd = msclr::interop::marshal_as<std::string>(pswd_st);
        paramValues[6] = pswd.c_str();
    }
    else
    {
        paramValues[6] = NULL;
    }

    // Выполняем запрос
    std::string query = "UPDATE people SET about_me = $1, interests = $2, "
        "contacts = $3, date_of_birth = $4, photo = $5 "
        "WHERE id = $6";

    if (paramValues[6] != NULL)
    {
        query += " RETURNING pswd = $7";
    }

    PGresult* res = PQexecParams(conn, query.c_str(),
        6 + (paramValues[6] != NULL ? 1 : 0),
        NULL, paramValues, paramLengths, paramFormats, 0);

    bool success = (PQresultStatus(res) == PGRES_COMMAND_OK ||
        PQresultStatus(res) == PGRES_TUPLES_OK);

    PQclear(res);
    dbConnection.disconnect();

    return success;
}*/

bool UpdateUserPhoto(QQ::User^ user) {
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        MessageBox::Show("Ошибка подключения к базе");
        return false;
    }

    PGconn* conn = db.get();

    array<Byte>^ imageBytes = nullptr;
    if (user->Photo != nullptr) {
        try {
            MemoryStream^ ms = gcnew MemoryStream();
            user->Photo->Save(ms, System::Drawing::Imaging::ImageFormat::Png);
            imageBytes = ms->ToArray();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при сохранении изображения: " + ex->Message);
            return false;
        }
    }

    const char* photoPtr = nullptr;
    int photoLength = 0;
    int paramFormat = 0;

    if (imageBytes != nullptr && imageBytes->Length > 0) {
        photoLength = imageBytes->Length;
        photoPtr = (const char*)(void*)System::Runtime::InteropServices::Marshal::UnsafeAddrOfPinnedArrayElement(imageBytes, 0);
        paramFormat = 1; // Передача как бинарный
    }

    const char* values[1] = { photoPtr };
    int lengths[1] = { photoLength };
    int formats[1] = { paramFormat };
    Oid types[1] = { 17 }; // 17 = BYTEAOID

    std::string query = "UPDATE people SET photo = $1 WHERE id = " + std::to_string(user->ID);

    PGresult* res = PQexecParams(
        conn,
        query.c_str(),
        1,
        types,
        values,
        lengths,
        formats,
        0 // text encoding result
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        MessageBox::Show("Ошибка обновления фото: " + gcnew String(PQerrorMessage(conn)));
        PQclear(res);
        db.disconnect();
        return false;
    }

    PQclear(res);
    db.disconnect();
    return true;
}


bool QQ::UserPageRed::UpdateUserFull(QQ::User^ user)
{
    if (user->Photo == nullptr) {
        MessageBox::Show("⚠️ user->Photo == nullptr");
    }
    else {
        MemoryStream^ testStream = gcnew MemoryStream();
        try {
            user->Photo->Save(testStream, System::Drawing::Imaging::ImageFormat::Png);
            MessageBox::Show("✅ user->Photo успешно сериализуется");
        }
        catch (Exception^ ex) {
            MessageBox::Show("❌ Ошибка сериализации photo: " + ex->Message);
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
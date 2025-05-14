#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define IDataObject IDataObject_WINAPI

#include "PostRepository.h"
#include "PostgresConnection.h"
#include "Post.h"
#include <msclr/marshal_cppstd.h>
#include <string>
#include <iostream>

extern "C" {
#include <libpq-fe.h>
}

#undef IDataObject


using namespace msclr::interop;
using namespace System;
using namespace QQ;

int update_post(System::String^ title_post, System::String^ text_post, const int id) { 
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        return 0;
    }
    PGconn* conn = db.get(); // �������� ���������

    std::string title = marshal_as<std::string>(title_post);
    std::string content = marshal_as<std::string>(text_post);
    std::string idStr = std::to_string(id);

    // ������������� ���� �����
    char* title_new = PQescapeLiteral(conn, title.c_str(), title.length());
    char* content_new = PQescapeLiteral(conn, content.c_str(), content.length());
    char* escapedId = PQescapeLiteral(conn, idStr.c_str(), idStr.length());
    //char* photo = PQescapeLiteral(conn, photo_data.c_str(), photo_data.length());

    // �������� ���������� �������������
    if (!title_new || !content_new || !escapedId) {
        std::cerr << "������ �������������." << std::endl;
        if (title_new) PQfreemem(title_new);
        if (content_new) PQfreemem(content_new);
        if (escapedId) PQfreemem(escapedId);
        //if (photo) PQfreemem(photo);
        return 3;
    }

    // ������������ �������
    std::string query = "UPDATE posts SET title = " + std::string(title_new) +
        ", content = " + std::string(content_new) +
        //", photo = " + std::string(photo) +
        " WHERE posts.id = " + std::string(escapedId) + ";";

    // ���������� �������
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "������ ���������� �������: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        PQfreemem(title_new);
        PQfreemem(content_new);
        PQfreemem(escapedId);
        //PQfreemem(photo);
        db.disconnect();
        return 0;
    }

    // ������� ��������
    PQclear(res);
    PQfreemem(title_new);
    PQfreemem(content_new);
    PQfreemem(escapedId);
    //PQfreemem(photo);

    db.disconnect();
    return 1;
}

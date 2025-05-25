#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define IDataObject IDataObject_WINAPI

#include "CommRepository.h"
#include <msclr/marshal_cppstd.h>
#include <string>

extern "C" {
#include <libpq-fe.h>

}

#undef IDataObject

using namespace msclr::interop;
using namespace System;
using namespace System::Windows::Forms;
using namespace QQ;


List<QQ::Comm^>^ CommRepository::LoadTree(QQ::Post^ post)
{
    List<QQ::Comm^>^ flatList = gcnew List<QQ::Comm^>();
    Dictionary<int, QQ::Comm^>^ commentMap = gcnew Dictionary<int, QQ::Comm^>();

    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) {
        MessageBox::Show("Не удалось подключиться к БД.");
        return flatList;
    }

    PGconn* conn = db.get();
    std::string query = "SELECT c.id, c.id_post, u1.name, COALESCE(u2.name, '') AS reply_to, c.text, c.date, COALESCE(c.parent_comm, -1)"
        "FROM public.commenti c JOIN people u1 ON c.id_user = u1.id LEFT JOIN people u2 ON c.id_otvet_user = u2.id WHERE c.id_post = " + std::to_string(post->ID) + " "
        "ORDER BY c.date DESC;";


    PGresult* res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        MessageBox::Show("Ошибка запроса комментариев.");
        PQclear(res);
        db.disconnect();
        return flatList;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; ++i) {
        int id = std::stoi(PQgetvalue(res, i, 0));
        int id_post = std::stoi(PQgetvalue(res, i, 1));
        String^ author = marshal_as<String^>(PQgetvalue(res, i, 2));
        String^ replyTo = marshal_as<String^>(PQgetvalue(res, i, 3));
        String^ text = marshal_as<String^>(PQgetvalue(res, i, 4));
        DateTime date = DateTime::Parse(marshal_as<String^>(PQgetvalue(res, i, 5)));
        int parentId = std::stoi(PQgetvalue(res, i, 6));

        QQ::Comm^ comm = gcnew QQ::Comm(id, id_post, author, replyTo, text, date, parentId);
        commentMap->Add(id, comm);
    }

    // Строим дерево
    for each (KeyValuePair<int, QQ::Comm^> kvp in commentMap) {
        int parentId = kvp.Value->ParentID;
        if (parentId == -1) {
            flatList->Add(kvp.Value);
        }
        else if (commentMap->ContainsKey(parentId)) {
            commentMap[parentId]->Children->Add(kvp.Value);
        }
    }

    PQclear(res);
    db.disconnect();
    return flatList;
}

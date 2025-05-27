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
    std::string query =
        "SELECT c.id, c.id_post, u1.name, COALESCE(u2.name, '') AS reply_to, "
        "c.text, c.date, COALESCE(c.parent_comm, -1), "
        "COALESCE(c.id_otvet_user, -1), c.id_user "
        "FROM public.commenti c "
        "JOIN public.people u1 ON c.id_user = u1.id "
        "LEFT JOIN public.people u2 ON c.id_otvet_user = u2.id "
        "WHERE c.id_post = " + std::to_string(post->ID) + " "
        "ORDER BY c.date ASC;";

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
        int postId = std::stoi(PQgetvalue(res, i, 1));
        String^ author = marshal_as<String^>(PQgetvalue(res, i, 2));
        String^ replyTo = marshal_as<String^>(PQgetvalue(res, i, 3));
        String^ text = marshal_as<String^>(PQgetvalue(res, i, 4));
        DateTime date = DateTime::Parse(marshal_as<String^>(PQgetvalue(res, i, 5)));
        int parentId = std::stoi(PQgetvalue(res, i, 6));
        int idReplyUser = std::stoi(PQgetvalue(res, i, 7));
        int id_user = std::stoi(PQgetvalue(res, i, 8));

        Comm^ comm = gcnew Comm(id, postId, author, replyTo, text, date, parentId, idReplyUser);
        comm->ID_user = id_user;  // сохраняем ID автора
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


bool CommRepository::AddComment(int id_post, int id_user, int id_otvet_user,
    System::String^ text, System::DateTime date,
    bool its_otvet, int parent_comm)
{
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) return false;

    PGconn* conn = db.get();
    std::string query = "INSERT INTO public.commenti (id_post, id_user, id_otvet_user, text, date, its_otvet, parent_comm) VALUES (";

    query += std::to_string(id_post) + ",";
    query += std::to_string(id_user) + ",";

    query += (id_otvet_user == 0 ? "NULL" : std::to_string(id_otvet_user)) + ",";
    query += "'" + marshal_as<std::string>(text) + "',";
    query += "'" + marshal_as<std::string>(date.ToString("yyyy-MM-dd HH:mm:ss")) + "',";
    query += its_otvet ? "true," : "false,";
    query += (parent_comm == 0 ? "NULL" : std::to_string(parent_comm)) + ");";

    PGresult* res = PQexec(conn, query.c_str());

    bool success = PQresultStatus(res) == PGRES_COMMAND_OK;
    PQclear(res);
    db.disconnect();
    return success;
}

bool CommRepository::MarkAsDeleted(int commentId)
{
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) return false;

    PGconn* conn = db.get();
    std::string query = "UPDATE public.commenti SET text = 'Комментарий был удалён' WHERE id = " + std::to_string(commentId) + ";";

    PGresult* res = PQexec(conn, query.c_str());
    bool success = PQresultStatus(res) == PGRES_COMMAND_OK;

    PQclear(res);
    db.disconnect();
    return success;
}

bool CommRepository::DeleteReplies(int parentId)
{
    PostgresConnection& db = PostgresConnection::getInstance();
    if (!db.connect()) return false;

    PGconn* conn = db.get();

    // 1. Получаем id всех комментариев, у которых parent_comm = parentId
    std::string query = "SELECT id FROM public.commenti WHERE parent_comm = " + std::to_string(parentId) + ";";
    PGresult* res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        db.disconnect();
        return false;
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; ++i) {
        int childId = std::stoi(PQgetvalue(res, i, 0));
        DeleteReplies(childId);  // рекурсивно удаляем вложенные ответы
    }
    PQclear(res);

    // 2. Удаляем все комментарии, где parent_comm = parentId
    std::string deleteQuery = "DELETE FROM public.commenti WHERE parent_comm = " + std::to_string(parentId) + ";";
    PGresult* delRes = PQexec(conn, deleteQuery.c_str());
    bool success = PQresultStatus(delRes) == PGRES_COMMAND_OK;
    PQclear(delRes);

    db.disconnect();
    return success;
}

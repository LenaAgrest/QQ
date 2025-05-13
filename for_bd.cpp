#include "Post.h"
#include "PostgresConnection.h"
#include <iostream>
#include <libpq-fe.h>
#include <string>
#include <msclr/marshal_cppstd.h>

int update_post(std::string title_post, std::string text_post_t, std::string id) {
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    PGconn* conn = dbConnection.get();
    char* title = PQescapeLiteral(conn, title_post.c_str(), title_post.length());
    char* content = PQescapeLiteral(conn, text_post_t.c_str(), text_post_t.length());
    //char* id = PQescapeLiteral(conn, id.c_str(), id.length());
    //char* photo = PQescapeLiteral(conn, text_post_t.c_str(), text_post_t.length());

    std::string query = "UPDATE posts SET title = '" + std::string(title) + "', content = '" + std::string(content) + "' WHERE posts.id = '" + std::string(id) + "';";
    PGresult* res = PQexec(conn, query.c_str());


    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Ошибка запроса: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        dbConnection.disconnect();
        return 0;
    }
    else {
        return 1;
    }

    // Очистка
    PQclear(res);
    PQfreemem(title);
    PQfreemem(content);

    dbConnection.disconnect();
}
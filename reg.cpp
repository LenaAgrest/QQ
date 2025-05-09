#include "reg.h"
#include "PostgresConnection.h"
#include <iostream>
#include <libpq-fe.h>
#include <string>
#include <msclr/marshal_cppstd.h>

int reg_people(std::string username, std::string password, std::string interests, std::string date, std::string about, std::string contacts) {
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    if (!dbConnection.connect()) {
        std::cerr << "ќшибка подключени€: " << dbConnection.getLastError() << std::endl;
        return 3;
    }

    // Ёкранируем данные
    PGconn* conn = dbConnection.get();
    char* esc_username = PQescapeLiteral(conn, username.c_str(), username.length());
    char* esc_password = PQescapeLiteral(conn, password.c_str(), password.length());
    char* esc_interests = interests.empty() ? nullptr : PQescapeLiteral(conn, interests.c_str(), interests.length());
    char* esc_date = date.empty() ? nullptr : PQescapeLiteral(conn, date.c_str(), date.length());
    char* esc_about = about.empty() ? nullptr : PQescapeLiteral(conn, about.c_str(), about.length());
    char* esc_contacts = contacts.empty() ? nullptr : PQescapeLiteral(conn, contacts.c_str(), contacts.length());

    std::string query = "SELECT COUNT(*) FROM people WHERE name=" + std::string(esc_username) + " AND pswd=" + std::string(esc_password) + ";";
    PGresult* res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        int count = atoi(PQgetvalue(res, 0, 0));
        if (count > 0) {
            PQclear(res);
            PQfreemem(esc_username);
            PQfreemem(esc_password);
            return 2;
        }
        else {
            std::string query = "INSERT INTO people (name, pswd, interests, date_of_birth, about_me, contacts) VALUES (" +
                std::string(esc_username) + ", " +
                std::string(esc_password) + ", " +
                std::string(esc_interests ? esc_interests : "NULL") + ", " +
                std::string(esc_date ? esc_date : "NULL") + ", " +
                std::string(esc_about ? esc_about : "NULL") + ", " +
                std::string(esc_contacts ? esc_contacts : "NULL") + ")";

            PGresult* res = PQexec(conn, query.c_str());

            if (PQresultStatus(res) != PGRES_COMMAND_OK) {
                std::cerr << "ќшибка запроса: " << PQerrorMessage(conn) << std::endl;
                PQclear(res);
                dbConnection.disconnect();
                return 0;
            }
            else { return 1; }
        }
    }
    

    // ќчистка
    PQclear(res);
    PQfreemem(esc_username);
    PQfreemem(esc_password);
    PQfreemem(esc_interests);
    PQfreemem(esc_date);
    PQfreemem(esc_about);
    PQfreemem(esc_contacts);
    dbConnection.disconnect();
}
#include "aurorise.h"
#include "PostgresConnection.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <libpq-fe.h>
#include <msclr/marshal_cppstd.h>
#include <string>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::SqlClient;

int Check_сredentials(std::string username, std::string password) {
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    if (!dbConnection.connect()) {
        std::cerr << "Ошибка подключения: " << dbConnection.getLastError() << std::endl;
        return 3;
    }
    std::string query = "SELECT COUNT(*) FROM uchetki.people WHERE name='" + username + "' AND pswd='" + password + "';";

    // Выполняем запрос
    PGconn* conn = dbConnection.get();
    PGresult* res = PQexec(conn, query.c_str());

    // Проверка результата
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Ошибка при выполнении запроса: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        dbConnection.disconnect();
        return 0;
    }
    // Проверяем, найден ли пользователь
    int userCount = std::stoi(PQgetvalue(res, 0, 0));

    PQclear(res);  // Освобождаем ресурсы результата запроса
    dbConnection.disconnect();

    return 1;  // Если пользователь найден — успешная авторизация
}
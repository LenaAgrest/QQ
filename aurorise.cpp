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

int Check_�redentials(std::string username, std::string password) {
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    if (!dbConnection.connect()) {
        std::cerr << "������ �����������: " << dbConnection.getLastError() << std::endl;
        return 3;
    }
    std::string query = "SELECT COUNT(*) FROM people WHERE name='" + username + "' AND pswd='" + password + "';";

    // ��������� ������
    PGconn* conn = dbConnection.get();
    PGresult* res = PQexec(conn, query.c_str());

    int userCount = std::stoi(PQgetvalue(res, 0, 0));

    // �������� ����������
    if (userCount != 1) {
        std::cerr << "������ ��� ���������� �������: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        dbConnection.disconnect();
        return 0;
    }
    else {
        PQclear(res); 
        dbConnection.disconnect();
        return 1;
    } 
}
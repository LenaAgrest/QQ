#include "aurorise.h"
#include "Session.h"
#include "PostgresConnection.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <libpq-fe.h>
#include <msclr/marshal_cppstd.h>
#include <string>
#include "User.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::SqlClient;

int Check_сredentials(std::string username, std::string password) {
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    if (!dbConnection.connect()) {
        std::cerr << "Ошибка подключения: " << dbConnection.getLastError() << std::endl;
        return 3;
    }
    std::string query = "SELECT (SELECT COUNT(*) FROM people WHERE name = '" + username + "' AND pswd = '" + password + "') AS match_count, p.id, p.name, p.interests, p.date_of_birth, p.about_me, p.photo, p.contacts FROM people p WHERE name = '" + username + "' AND pswd = '" + password + "';";

    // Выполняем запрос
    PGconn* conn = dbConnection.get();
    PGresult* res = PQexec(conn, query.c_str());

    int rows = PQntuples(res);
    if (rows != 1) {
        std::cerr << "Ошибка при выполнении запроса: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        dbConnection.disconnect();
        return 0;
    }
    for (int i = 0; i < rows; ++i) {
        int userCount = std::stoi(PQgetvalue(res, 0, 0));
        int id = std::stoi(PQgetvalue(res, i, 1));
        std::string Name = PQgetvalue(res, i, 2);
        std::string Interests = PQgetvalue(res, i, 3);
        std::string Date_of_birth = PQgetvalue(res, i, 4);
        std::string About_me = PQgetvalue(res, i, 5);
        //std::string photo = PQgetvalue(res, i, 4);
        std::string Contacts = PQgetvalue(res, i, 7);


        String^ name = marshal_as<String^>(Name);
        String^ interests = PQgetisnull(res, i, 3) ? "" : marshal_as<String^>(PQgetvalue(res, i, 3));
        String^ about_me = PQgetisnull(res, i, 5) ? "" : marshal_as<String^>(PQgetvalue(res, i, 5));
        String^ contacts = PQgetisnull(res, i, 7) ? "" : marshal_as<String^>(PQgetvalue(res, i, 7));

        //DateTime date_of_birth = DateTime::Parse(marshal_as<String^>(Date_of_birth));
        DateTime date_of_birth = DateTime::MinValue;
        if (!PQgetisnull(res, i, 4)) {
            try {
                date_of_birth = DateTime::Parse(marshal_as<String^>(PQgetvalue(res, i, 4)));
            }
            catch (...) {
                date_of_birth = DateTime::MinValue; // или логирование ошибки
            }
        }


        // Обработка изображения из базы данных
        /*array<Byte>^ imageData = nullptr;
        int photoLength = PQgetlength(res, i, 4);
        if (photoLength > 0) {
            const char* photoData = PQgetvalue(res, i, 4);
            imageData = gcnew array<Byte>(photoLength);
            for (int j = 0; j < photoLength; ++j) {
                imageData[j] = photoData[j];
            }
        }*/

            if (userCount != 1) {
                std::cerr << "Ошибка при выполнении запроса: " << PQerrorMessage(conn) << std::endl;
                PQclear(res);
                dbConnection.disconnect();
                return 0;
            }
            else
            {
                QQ::User^ user = gcnew QQ::User(id, name, interests, date_of_birth, about_me, contacts);
                QQ::Session::CurrentUser = user;
                MyUserControl^ control = gcnew MyUserControl();
                //control->SetUser(user); // вот это передаёт данные!
                QQ::MainForm^ mainForm = gcnew QQ::MainForm();
                mainForm->Show();

                PQclear(res);
                dbConnection.disconnect();
                return 1;
            }
    }
}
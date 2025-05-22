#include "aurorise.h"
#include "Session.h"
#include "PostgresConnection.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <libpq-fe.h>
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>
#include <string>
#include "User.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::SqlClient;
using namespace System::Drawing;
using namespace msclr::interop;
using namespace System::Runtime::InteropServices;


int Check_сredentials(std::string username, std::string password) {
    PostgresConnection& dbConnection = PostgresConnection::getInstance();

    if (!dbConnection.connect()) {
        std::cerr << "Ошибка подключения: " << dbConnection.getLastError() << std::endl;
        return 3;
    }
    std::string query = "SELECT (SELECT COUNT(*) FROM people WHERE name = '" + username + "' AND pswd = '" + password + "') AS match_count, p.id, p.name, p.pswd, p.interests, p.date_of_birth, p.about_me, p.photo, p.contacts FROM people p WHERE name = '" + username + "' AND pswd = '" + password + "';";

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
        std::string Password = PQgetvalue(res, i, 3);
        std::string Interests = PQgetvalue(res, i, 4);
        std::string Date_of_birth = PQgetvalue(res, i, 5);
        std::string About_me = PQgetvalue(res, i, 6);
        std::string Contacts = PQgetvalue(res, i, 8);
        Image^ img = nullptr;


        if (!PQgetisnull(res, i, 7)) {
            size_t unescapedLength = 0;
            const char* escaped = PQgetvalue(res, i, 7);
            unsigned char* unescaped = PQunescapeBytea((const unsigned char*)escaped, &unescapedLength);

            if (unescaped && unescapedLength > 0) {
                array<Byte>^ imageData = gcnew array<Byte>((int)unescapedLength);
                Marshal::Copy((IntPtr)(void*)unescaped, imageData, 0, (int)unescapedLength);

                try {
                    MemoryStream^ ms = gcnew MemoryStream(imageData);
                    img = Image::FromStream(ms);
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Ошибка при чтении изображения: " + ex->Message);
                    img = nullptr;
                }

                PQfreemem(unescaped);
            }
        }
        

        String^ name = marshal_as<String^>(Name);
        String^ pswd = marshal_as<String^>(Password);
        String^ interests = marshal_as<String^>(Interests);
        String^ about_me = marshal_as<String^>(About_me);
        String^ contacts = marshal_as<String^>(Contacts);

        //DateTime date_of_birth = DateTime::Parse(marshal_as<String^>(Date_of_birth));
        DateTime date_of_birth = DateTime::MinValue;
        if (!PQgetisnull(res, i, 5)) {
            try {
                date_of_birth = DateTime::Parse(marshal_as<String^>(PQgetvalue(res, i, 5)));
            }
            catch (...) {
                date_of_birth = DateTime::MinValue; // или логирование ошибки
            }
        }

            if (userCount != 1) {
                std::cerr << "Ошибка при выполнении запроса: " << PQerrorMessage(conn) << std::endl;
                PQclear(res);
                dbConnection.disconnect();
                return 0;
            }
            else
            {
                QQ::User^ user = gcnew QQ::User(id, name, pswd, interests, date_of_birth, about_me, img, contacts);
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
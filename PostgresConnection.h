#ifndef POSTGRESCONNECTION_H
#define POSTGRESCONNECTION_H
#pragma once

#include <libpq-fe.h>
#include <string>

class PostgresConnection {
private:
    PGconn* conn;

    // Встроенная строка подключения
    const std::string connStr =
        "host=pnlqb.h.filess.io "
        "port=5433 "
        "dbname=qqdb_slabsdoes "
        "user=qqdb_slabsdoes "
        "password= а это секрет";

    PostgresConnection() : conn(nullptr) {}

public:
    // Запрещаем копирование
    PostgresConnection(const PostgresConnection&) = delete;
    PostgresConnection& operator=(const PostgresConnection&) = delete;

    static PostgresConnection& getInstance() {
        static PostgresConnection instance;
        return instance;
    }

    bool connect() {
        conn = PQconnectdb(connStr.c_str());
        return PQstatus(conn) == CONNECTION_OK;
    }

    PGconn* get() const {
        return conn;
    }

    void disconnect() {
        if (conn) {
            PQfinish(conn);
            conn = nullptr;
        }
    }

    std::string getLastError() const {
        if (conn) return PQerrorMessage(conn);
        return "Соединение не установлено.";
    }

    ~PostgresConnection() {
        disconnect();
    }
};
#endif // POSTGRESCONNECTION_H
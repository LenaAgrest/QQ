#pragma once

using namespace System;

namespace QQ {
    public ref class User {
    public:
        User(int id, String^ name, String^ interests, DateTime^ born, String^ about, String^ contacts) {    //array<Byte>^ photo,
            ID = id;
            Username = name;
            Interests = interests;
            Date = born;
            About = about;
            //Photo = photo;
            Contacts = contacts;
        }

        int ID;
        String^ Username;
        String^ Interests;
        DateTime^ Date;
        String^ About;
        //array<Byte>^ Photo;  // Массив байтов для изображения
        String^ Contacts;
    };
}
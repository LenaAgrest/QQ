#pragma once

using namespace System;
using namespace System::Drawing;

namespace QQ {
    public ref class User {
    public:
        User(int id, String^ name, String^ password, String^ interests, DateTime^ born, String^ about, Image^ photo, String^ contacts) {    //
            ID = id;
            Username = name;
            Password = password;
            Interests = interests;
            Date = born;
            About = about;
            Photo = photo;
            Contacts = contacts;
        }

        int ID;
        String^ Username;
        String^ Password;
        String^ Interests;
        DateTime^ Date;
        String^ About;
        Image^ Photo;
        String^ Contacts;
    };
}
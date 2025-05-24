#pragma once

using namespace System;
using namespace System::Drawing;

namespace QQ {
    public ref class Comm {
    public:
        Comm(int id, int id_post, String^ user, String^ otv_user, String^ text, DateTime^ date, Boolean^ its_otvet, int serial_otvet) {    //
            ID = id;
            ID_post = id_post;
            User = user;
            Otv_user = otv_user;
            Text_comm = text;
            Date = date;
            Its_otvet = its_otvet;
            Serial_otvet = serial_otvet;
        }

        int ID;
        int ID_post;
        String^ User;
        String^ Otv_user;
        String^ Text_comm;
        DateTime^ Date;
        Boolean^ Its_otvet;
        int Serial_otvet;
    };
}

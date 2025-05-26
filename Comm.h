#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace QQ {
    public ref class Comm {
    public:
        Comm(int id, int postId, String^ author, String^ replyTo, String^ text, DateTime date, int parentId, int idReplyUser)
        {
            ID = id;
            PostID = postId;
            Author = author;
            ReplyTo = replyTo;
            Text = text;
            Date = date;
            ParentID = parentId;
            IdReplyUser = idReplyUser;
            Children = gcnew List<Comm^>();
        }


        int ID;
        int PostID;
        String^ Author;
        String^ ReplyTo;
        String^ Text;
        DateTime Date;
        int ParentID; // -1 если корневой
        int IdReplyUser;
        List<Comm^>^ Children;

        int ID_user; // ID автора этого комментария

    };
}

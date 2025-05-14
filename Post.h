#pragma once

using namespace System;

namespace QQ {
    public ref class Post {
    public:
        Post(int id, String^ title, String^ content, String^ author, array<Byte>^ imageData, DateTime^ datetime) {
            ID = id;
            Title = title;
            Content = content;
            Author = author;
            Date = datetime;
            ImageData = imageData;
            CommentsAllowed = true;
        }

        int ID;
        String^ Title;
        String^ Content;
        String^ Author;
        array<Byte>^ ImageData;  // Массив байтов для изображения
        DateTime^ Date;
        bool CommentsAllowed;
    };
}

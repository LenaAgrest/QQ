#pragma once

using namespace System;

namespace QQ {
    public ref class Post {
    public:
        Post(String^ title, String^ content, String^ author, array<Byte>^ imageData, DateTime^ datetime) {
            Title = title;
            Content = content;
            Author = author;
            Date = datetime;
            ImageData = imageData;  // “еперь храним данные изображени€ как массив байтов
        }

        String^ Title;
        String^ Content;
        String^ Author;
        array<Byte>^ ImageData;  // ћассив байтов дл€ изображени€
        DateTime^ Date;
        bool CommentsAllowed;
    };
}

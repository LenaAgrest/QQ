#pragma once

using namespace System;

namespace QQ {
    public ref class Post {
    public:
        Post(String^ title, String^ content, String^ author, array<Byte>^ imageData) {
            Title = title;
            Content = content;
            Author = author;
            ImageData = imageData;  // ������ ������ ������ ����������� ��� ������ ������
        }

        String^ Title;
        String^ Content;
        String^ Author;
        array<Byte>^ ImageData;  // ������ ������ ��� �����������
        DateTime Date;
        bool CommentsAllowed;
    };
}

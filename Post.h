#pragma once

using namespace System;

public ref class Post {
public:
    int id;
    String^ title;
    String^ text;
    DateTime date;
    String^ authorName;
    bool commentsAllowed;
    String^ imagePath;

    Post(int id, String^ title, String^ text, DateTime date, String^ authorName, bool commentsAllowed, String^ imagePath) {
        this->id = id;
        this->title = title;
        this->text = text;
        this->date = date;
        this->authorName = authorName;
        this->commentsAllowed = commentsAllowed;
        this->imagePath = imagePath;
    }
};

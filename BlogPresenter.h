#pragma once

#include "IMainView.h"
#include "Post.h"

public ref class BlogPresenter {
private:
    IMainView^ view;
    String^ currentUser;

public:
    BlogPresenter(IMainView^ view, String^ currentUser) {
        this->view = view;
        this->currentUser = currentUser;
    }

    void LoadPostsForPage(int page) {
        // Тут будет запрос в БД
        List<Post^>^ posts = gcnew List<Post^>();
        // например, заглушки:
        posts->Add(gcnew Post(1, "Заголовок 1", "Текст поста 1", DateTime::Now, "Пользователь", true, ""));
        posts->Add(gcnew Post(2, "Заголовок 2", "Текст поста 2", DateTime::Now.AddMinutes(-10), "Пользователь", true, ""));

        view->ShowPosts(posts);
        view->SetPageInfo(page, 1); // пока только 1 страница
        view->EnablePostCreation(true); // если это его блог
        view->ShowAuthorName(currentUser);
    }
};

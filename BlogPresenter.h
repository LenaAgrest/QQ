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
        // ��� ����� ������ � ��
        List<Post^>^ posts = gcnew List<Post^>();
        // ��������, ��������:
        posts->Add(gcnew Post(1, "��������� 1", "����� ����� 1", DateTime::Now, "������������", true, ""));
        posts->Add(gcnew Post(2, "��������� 2", "����� ����� 2", DateTime::Now.AddMinutes(-10), "������������", true, ""));

        view->ShowPosts(posts);
        view->SetPageInfo(page, 1); // ���� ������ 1 ��������
        view->EnablePostCreation(true); // ���� ��� ��� ����
        view->ShowAuthorName(currentUser);
    }
};

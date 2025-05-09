#pragma once

#include "Post.h"
using namespace System;
using namespace System::Collections::Generic;

public interface class IMainView {
    void ShowPosts(List<Post^>^ posts);
    void SetPageInfo(int currentPage, int totalPages);
    void ShowAuthorName(String^ name);
    void EnablePostCreation(bool enable);
};

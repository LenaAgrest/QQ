#pragma once

#include "Post.h"
#include "User.h"
#include "PostgresConnection.h"
#include <list>

using namespace System;
using namespace QQ;
using namespace System::Collections::Generic;

public ref class PostRepository
{
public:
    static List<QQ::Post^>^ LoadAllPosts();
    static List<QQ::Post^>^ LoadPostsUser(User^ user);
};

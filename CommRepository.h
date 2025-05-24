#pragma once

#include "Post.h"
#include "User.h"
#include "PostgresConnection.h"
#include <list>
#include "Comm.h"

using namespace System;
using namespace QQ;
using namespace System::Collections::Generic;

public ref class CommRepository
{
public:
    static List<QQ::Comm^>^ PostsComm(Post^ post);
};

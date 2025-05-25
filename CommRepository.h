#pragma once

#include "Comm.h"
#include "PostgresConnection.h"
#include "Post.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class CommRepository
{
public:
    static List<QQ::Comm^>^ LoadTree(QQ::Post^ post);
public:
    static bool AddComment(int id_post, int id_user, int id_otvet_user,
        System::String^ text, System::DateTime date,
        bool its_otvet, int parent_comm);

    static bool MarkAsDeleted(int commentId);
    static bool DeleteReplies(int parentId);

};


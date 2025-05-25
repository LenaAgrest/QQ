#pragma once

#include "Post.h"
#include "User.h"
#include "Comm.h"

using namespace System;
using namespace System::Collections::Generic;
namespace QQ {
    ref class CommService {
    public:
        static bool AddNewComment(
            Post^ post,
            User^ author,
            String^ text,
            DateTime date,
            bool isReply,
            int serialOtvet,
            int idOtvUser,
            int parentCommId
        );
    };
}
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
};

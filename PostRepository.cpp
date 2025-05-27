#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define IDataObject IDataObject_WINAPI

#include "PostRepository.h"
#include "Post.h"
#include <msclr/marshal_cppstd.h>
#include <string>
#include <vcclr.h>

extern "C" {
#include <libpq-fe.h>
}

#undef IDataObject


using namespace msclr::interop;
using namespace System;
using namespace QQ;


static bool AddPost(int user_id, String^ title, String^ content, DateTime date, array<Byte>^ imageData)
{
	
}

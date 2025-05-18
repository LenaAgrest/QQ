#pragma once

#include "User.h"

namespace QQ {
	public ref class Session abstract sealed {
	public:
		static QQ::User^ CurrentUser = nullptr;
		static QQ::User^ SelectUser = nullptr;
	};
}

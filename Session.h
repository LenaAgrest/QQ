#pragma once

#include "User.h"

namespace QQ {
	public ref class Session abstract sealed {
	public:
		// Просто открытое static поле — этого достаточно
		static QQ::User^ CurrentUser = nullptr;
	};
}

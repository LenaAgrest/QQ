#pragma once

#include "User.h"

namespace QQ {
	public ref class Session abstract sealed {
	public:
		// ������ �������� static ���� � ����� ����������
		static QQ::User^ CurrentUser = nullptr;
	};
}

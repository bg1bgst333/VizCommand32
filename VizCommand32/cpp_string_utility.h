// 二重インクルード防止
#ifndef __CPP_STRING_UTILITY_H__
#define __CPP_STRING_UTILITY_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <string>		// std::string
#include <locale.h>		// ロケール

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// C++文字列ユーティリティクラスclass_cpp_string_utility
class class_cpp_string_utility{

	// publicメンバ
	public:

		// publicメンバ関数
		// staticメンバ関数
		static std::string encode_wstring_to_string(const std::wstring& wstr);	// wstringからstringへの変換.
		static std::wstring decode_string_to_wstring(const std::string& str);	// stringからwstringへの変換.
		static void replace(tstring &target, const tstring &before, const tstring &after);	// tstringの置換.

};

#endif
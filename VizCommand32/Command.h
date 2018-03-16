// 二重インクルード防止
#ifndef __COMMAND_H__
#define __COMMAND_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <string>	// std::string
#include <vector>	// std::vector
#include <sstream>	// std::stringstream
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#define tstringstream std::wstringstream
#else
#define tstring std::string
#define tstringstream std::stringstream
#endif

// コマンドクラスCCommand
class CCommand{

	// privateメンバ
	private:

		// privateメンバ変数
		tstring m_tstrCommandString;	// コマンド文字列m_tstrCommandString.
		tstring m_tstrCommandName;	// コマンド名m_tstrCommandName.

	// publicメンバ
	public:

		// publicメンバ変数
		std::vector<tstring> m_vectstrCommandToken;	// コマンド文字列のトークンリストm_vectstrCommandToken.
		// publicメンバ関数
		void Set(tstring tstrCommandString);	// コマンド文字列のセット.
		void Clear();	// コマンドのクリア.
		tstring GetCommandName();	// コマンド名の取得.
		tstring GetCommandString();	// コマンド文字列の取得.

};

#endif
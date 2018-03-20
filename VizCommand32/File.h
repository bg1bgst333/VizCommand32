// 二重インクルード防止
#ifndef __FILE_H__
#define __FILE_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <tchar.h>		// TCHAR型
#include <windows.h>	// 標準WindowsAPI
#include <string>	// std::string

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// ファイルクラスCFile
class CFile {

	// publicメンバ
	public:
		
		// publicメンバ変数
		HANDLE m_hFile;	// ファイルハンドル
		tstring m_tstrFileName;	// ファイル名(フルパス)

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CFile();	// コンストラクタCFile
		virtual ~CFile();	// デストラクタ~CFile
		// メンバ関数
		virtual BOOL Open(LPCTSTR lpctszFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition);	// ファイルを開くOpen.
		virtual void Close();	// ファイルを閉じるClose.
		virtual DWORD Read(LPVOID lpBuf, DWORD dwBytes);	// ファイル内容の読み込みRead.
		virtual DWORD Write(LPVOID lpBuf, DWORD dwBytes);	// ファイル内容の書き込みWrite.

};

#endif
// ヘッダのインクルード
// 独自のヘッダ
#include "File.h"	// CFile

// コンストラクタCFile
CFile::CFile() {

	// メンバの初期化
	m_hFile = NULL;	// m_hFileにNULLをセット.
	m_tstrFileName.clear();	// m_tstrFileName.clearでクリア.

}

// デストラクタ~CFile
CFile::~CFile() {

	// メンバの終了処理
	Close();	// Closeで閉じる.

}

// ファイルを開くOpen.
BOOL CFile::Open(LPCTSTR lpctszFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition) {

	// メンバのセット.
	m_tstrFileName = lpctszFileName;	// m_tstrFileNameにlpctszFileNameをセット.

	// ファイルハンドルの取得.
	m_hFile = CreateFile(m_tstrFileName.c_str(), dwDesiredAccess, FILE_SHARE_READ, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);	// CreateFileでm_tstrFileNameのファイルハンドルを取得し, m_hFileに格納.
	if (m_hFile == INVALID_HANDLE_VALUE) {	// 失敗なら.
		m_hFile = NULL;	// m_hFileにNULLをセット.
		m_tstrFileName.clear();	// m_tstrFileName.clearでクリア.
		return FALSE;	// FALSEを返す.
	}

	// 成功ならTRUE.
	return TRUE;	// 成功ならTRUEを返す.

}

// ファイルを閉じるClose.
void CFile::Close() {

	// ファイルハンドルを閉じる.
	if (m_hFile != NULL) {	// ハンドルが残っていたら.
		CloseHandle(m_hFile);	// CloseHandleでm_hFileを閉じる.
		m_hFile = NULL;	// m_hFileにNULLをセット.
	}

	// ファイル名などの情報もクリア.
	m_tstrFileName.clear();	// m_tstrFileName.clearでクリア.

}

// ファイル内容の読み込みRead.
DWORD CFile::Read(LPVOID lpBuf, DWORD dwBytes) {

	// 変数の初期化.
	DWORD dwReadBytes = 0;	// 読み込んだバイト数dwReadBytesを0に初期化.

	// ファイルを読み込む.
	ReadFile(m_hFile, lpBuf, dwBytes, &dwReadBytes, NULL);	// ReadFileで読み込み.

	// 読み込んだバイト数を返す.
	return dwReadBytes;	// dwReadBytesを返す.

}

// ファイル内容の書き込みWrite.
DWORD CFile::Write(LPVOID lpBuf, DWORD dwBytes) {

	// 変数の初期化.
	DWORD dwWrittenBytes = 0;	// 書き込んだバイト数dwWrittenBytesを0に初期化.

	// ファイルを書き込む.
	WriteFile(m_hFile, lpBuf, dwBytes, &dwWrittenBytes, NULL);	// WriteFileで書き込み.

	// 書き込んだバイト数を返す.
	return dwWrittenBytes;	// dwWrittenBytesを返す.

}
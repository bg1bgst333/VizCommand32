// ヘッダのインクルード
// 既定のヘッダ
#include <shlwapi.h>	// シェルAPI
// 独自のヘッダ
#include "FileInfoList.h"	// CFileListControlPanel

// コンストラクタCFileInfoList
CFileInfoList::CFileInfoList(){

	// メンバの初期化.
	m_tstrScanPath = _T("");	// m_tstrScanPathを""で初期化.
	m_vecpFileInfo.clear();	// m_vecpFileInfo.clearでクリア.

}

// デストラクタ~CFileInfoList
CFileInfoList::~CFileInfoList(){

	// 終了処理.
	RemoveAllInfo();	// すべてのアイテムを削除.

}

// ファイル情報の追加.
void CFileInfoList::AddInfo(tstring tstrFileName, HICON hIcon){

	// ファイル名とアイコンからファイル情報の生成.
	CFileInfo *pFileInfo = new CFileInfo();	// CFileInfoオブジェクトを生成し, ポインタをpFileInfoに格納.
	
	// ファイルフルパス.
	pFileInfo->m_tstrFileName = tstrFileName;	// pFileInfo->m_tstrFileNameにtstrFileNameをセット.

	// ファイルタイトル.
	TCHAR tszFileNameTitle[_MAX_PATH] = {0};	// ファイル名の部分だけを格納するtszFileNameTitleを{0}で初期化.
	GetFileTitle(tstrFileName.c_str(), tszFileNameTitle, _MAX_PATH);	// GetFileTitleでファイルタイトル取得.
	pFileInfo->m_tstrFileTitle = tszFileNameTitle;	// m_tstrCurrentFileNameTitleにtszFileNameTitleをセット.

	// ファイル拡張子.
	pFileInfo->m_tstrFileExt = PathFindExtension(pFileInfo->m_tstrFileName.c_str());	// PathFindExtensionで取得した拡張子をpFileInfo->m_tstrFileExtに格納.

	// ファイルアイコン.
	pFileInfo->m_hIcon = hIcon;	// pFileInfo->m_hIconにhIconをセット.

	// ファイル情報リストに追加.
	m_vecpFileInfo.push_back(pFileInfo);	// m_vecpFileInfo.push_backにpFileInfoを追加.

}

// ファイル情報の削除.
void CFileInfoList::RemoveInfo(){

}

// ファイルの探索.
void CFileInfoList::Scan(tstring tstrScanPath){

	// 変数の初期化.
	tstring tstrPattern = _T("");	// 検索パターンtstrPatternを""で初期化.
	WIN32_FIND_DATA wfdFindData = {0};	// 検索データwfdFindDataを{0}で初期化.
	HANDLE hFind = NULL;	// 検索ハンドルhFindをNULLで初期化.
	tstring tstrFileName = _T("");	// tstrFileNameを""で初期化.
	SHFILEINFO sfi = {0};	// シェルファイル情報sfiを{0}で初期化.

	// メンバにセット.
	m_tstrScanPath = tstrScanPath;	// m_tstrScanPathにtstrScanPathをセット.

	// 検索するパスと'*'を連結.
	tstrPattern = m_tstrScanPath;	// tstrPatternにm_tstrScanPathをセット.
	tstrPattern = tstrPattern + _T("\\*");	// tstrPatternに"\\*"を連結.

	// 最初の検索.
	hFind = FindFirstFile(tstrPattern.c_str(), &wfdFindData);	// FindFirstFileでhFindを取得.
	if (hFind != INVALID_HANDLE_VALUE){	// 不正な値でなければ.
		if (!((_tcscmp(wfdFindData.cFileName, _T(".")) == 0) || (_tcscmp(wfdFindData.cFileName, _T("..")) == 0))){	// "."または".."でない時.
			tstrFileName = tstrScanPath;	// tstrFileNameにtstrScanPathを代入.
			tstrFileName = tstrFileName + _T("\\");	// "\"を連結.
			tstrFileName = tstrFileName + wfdFindData.cFileName;	// wfdFindData.cFileNameを連結.
			SHGetFileInfo(tstrFileName.c_str(), 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_LARGEICON);	// SHGetFileInfoでファイル情報を取得.
			AddInfo(tstrFileName.c_str(), sfi.hIcon);	// AddInfoでファイル情報を追加.
		}
	}
	else{
		return;	// 異常終了.
	}

	// 以降の検索.
	while (FindNextFile(hFind, &wfdFindData)){	// FindNextFileで次のファイル情報を取得.
		tstrFileName = _T("");	// tstrFileNameに""をセット.
		ZeroMemory(&sfi, sizeof(SHFILEINFO));	// ZeroMemoryでsfiをクリア.
		if (!((_tcscmp(wfdFindData.cFileName, _T(".")) == 0) || (_tcscmp(wfdFindData.cFileName, _T("..")) == 0))){	// "."または".."でない時.
			tstrFileName = tstrScanPath;	// tstrFileNameにtstrScanPathを代入.
			tstrFileName = tstrFileName + _T("\\");	// "\"を連結.
			tstrFileName = tstrFileName + wfdFindData.cFileName;	// wfdFindData.cFileNameを連結.
			SHGetFileInfo(tstrFileName.c_str(), 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_LARGEICON);	// SHGetFileInfoでファイル情報を取得.
			AddInfo(tstrFileName.c_str(), sfi.hIcon);	// AddInfoでファイル情報を追加.
			MessageBox(NULL, tstrFileName.c_str(), _T("VizCommand"), MB_OK);	// MessageBoxでtstrFileNameを表示.
		}
	}

	// 終了処理.
	FindClose(hFind);	// FindCloseでhFindを閉じる.

}

// すべてのファイル情報を削除.
void CFileInfoList::RemoveAllInfo(){

	// 全て削除.
	for (std::vector<CFileInfo *>::iterator itor = m_vecpFileInfo.begin(); itor != m_vecpFileInfo.end(); itor++){	// begin()からend()まで.
		delete (*itor);	// deleteで削除.
		(*itor) = NULL;	// NULLをセット.
	}
	m_vecpFileInfo.clear();	// クリア.
	m_tstrScanPath = _T("");	// m_tstrScanPathに""をセット.

}
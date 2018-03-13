// 二重インクルード防止
#ifndef __FILE_INFO_LIST_H__
#define __FILE_INFO_LIST_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <vector>	// std::vector
// 独自のヘッダ
#include "FileInfo.h"	// CFileInfo

// ファイル情報リストを格納するクラスCFileInfoList
class CFileInfoList{

	// publicメンバ
	public:

		// publicメンバ変数
		tstring m_tstrScanPath;	// スキャン対象パスm_tstrScanPath.
		std::vector<CFileInfo *> m_vecpFileInfo;	// ファイル情報ポインタリストm_vecpFileInfo.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CFileInfoList();	// コンストラクタCFileInfoList
		virtual ~CFileInfoList();	// デストラクタ~CFileInfoList
		// メンバ関数
		virtual void AddInfo(tstring tstrFileName, HICON hIcon);	// ファイル情報の追加.
		virtual void RemoveInfo();	// ファイル情報の削除.
		virtual void Scan(tstring tstrScanPath);	// ファイルの探索.
		virtual void RemoveAllInfo();	// すべてのファイル情報を削除.

};

#endif
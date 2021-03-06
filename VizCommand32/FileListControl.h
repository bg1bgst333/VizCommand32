// 二重インクルード防止
#ifndef __FILE_LIST_CONTROL_H__
#define __FILE_LIST_CONTROL_H__

// ヘッダのインクルード
// 独自のヘッダ
#include "ListControl.h"	// CListControl
#include "FileInfoList.h"	// CFileInfoList

// ファイルリストコントロールクラスCFileListControl
class CFileListControl : public CListControl{

	// publicメンバ
	public:

		// publicメンバ変数
		CFileInfoList *m_pFileInfoList;	// ファイル情報リストm_pFileInfoList.
		tstring m_tstrPath;	// 探索しているパスm_tstrPath.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CFileListControl();	// コンストラクタCFileListControl
		virtual ~CFileListControl();	// デストラクタCFileListControl
		// メンバ関数
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
		void ScanFile(tstring tstrPath);	// ファイルの探索ScanFile.
		void ShowFileList();	// ファイルリストの表示ShowFileList.
		virtual void Destroy();	// ウィンドウの破棄と終了処理関数Destroy.

};

#endif

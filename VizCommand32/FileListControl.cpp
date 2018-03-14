// ヘッダのインクルード
// 独自のヘッダ
#include "FileListControl.h"	// CFileListControl

// コンストラクタCFileListControl
CFileListControl::CFileListControl() : CListControl(){

	// メンバの初期化.
	m_pFileInfoList = NULL;	// m_pFileInfoListをNULLで初期化.
	m_tstrPath = _T("");	// m_tstrPathを""で初期化.

}

// デストラクタ~CFileListControl
CFileListControl::~CFileListControl(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ファイルの探索ScanFile.
void CFileListControl::ScanFile(tstring tstrPath){

	// メンバにセット.
	m_tstrPath = tstrPath;	// m_tstrPathにtstrPathをセット.

	// ファイル情報リストを作成.
	if (m_pFileInfoList == NULL){	// m_pFileInfoListがNULLなら.
		m_pFileInfoList = new CFileInfoList();	// CFileInfoListオブジェクトを生成し, ポインタはm_pFileInfoListに格納.
	}

	// ファイルスキャン.
	m_pFileInfoList->Scan(m_tstrPath);	// m_pFileInfoList->Scanでスキャン.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CFileListControl::Destroy(){

	// ファイル情報リストを削除.
	if (m_pFileInfoList != NULL){	// m_pFileInfoListがNULLでない時.
		m_pFileInfoList->RemoveAllInfo();	// m_pFileInfoList->RemoveAllInfoで全て削除.
		delete m_pFileInfoList;	// deleteでm_pFileInfoListを解放.
		m_pFileInfoList = NULL;	// m_pFileInfoListにNULLをセット.
	}

	// 親クラスのDestroyを呼ぶ.
	CListControl::Destroy();	// CListControl::Destroyを呼ぶ.

}
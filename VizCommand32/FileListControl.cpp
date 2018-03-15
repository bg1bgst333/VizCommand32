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

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CFileListControl::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// 親ウィンドウのCreateで作成.
	BOOL bRet = CListControl::Create(lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CListControl::Createで作成.

	// ファイル情報リストの作成.
	m_pFileInfoList = new CFileInfoList();	// CFileInfoListオブジェクトを生成し, ポインタはm_pFileInfoListに格納.

	// 作成結果を返す.
	return bRet;	// bRetを返す.

}

// ファイルの探索ScanFile.
void CFileListControl::ScanFile(tstring tstrPath){

	// メンバにセット.
	m_tstrPath = tstrPath;	// m_tstrPathにtstrPathをセット.

	// ファイルスキャン.
	m_pFileInfoList->Scan(m_tstrPath);	// m_pFileInfoList->Scanでスキャン.

}

// ファイルリストの表示ShowFileList.
void CFileListControl::ShowFileList(){

	// イメージリストのセット.
	SetImageList(LVSIL_NORMAL);	// SetImageListでノーマルのイメージリストをセット.

	// ファイル情報の追加.
	int i = 0;	// iを0に初期化.
	for (std::vector<CFileInfo *>::iterator itor = m_pFileInfoList->m_vecpFileInfo.begin(); itor !=  m_pFileInfoList->m_vecpFileInfo.end(); itor++){	// ファイル情報リスト全て.
		int icon = AddIcon((*itor)->m_hIcon);	// AddIconでアイコンハンドルを追加.
		//SetImageList(LVSIL_NORMAL);	// SetImageListでノーマルのイメージリストをセット.(これがないとダメかとおもったが, コメントしても今のところ正常に表示されている.)
		LV_ITEM item = {0};	// itemを{0}で初期化.
		item.mask = LVIF_TEXT | LVIF_IMAGE;	// マスクはテキストとイメージ.		T
		TCHAR tszTitleText[1024] = {0};	// tszTitleTextを{0}で初期化.
		_tcscpy(tszTitleText, (*itor)->m_tstrFileTitle.c_str());	// _tcscpyで(*itor)->m_tstrFileTitleをtszTitleTextにコピー.
		item.pszText = tszTitleText;	// テキストはtszTitleText.
		item.iItem = i;	// インデックスはi.
		item.iSubItem = 0;	// サブアイテムはなし.
		item.iImage = icon;	// アイコンはicon.
		InsertItem(&item);	// InsertItemでitemを追加.
		i++;	// iをインクリメント.
	}

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
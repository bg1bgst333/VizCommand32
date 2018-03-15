// ヘッダのインクルード
// 独自のヘッダ
#include "ListControl.h"	// CListControl

// コンストラクタCListControl
CListControl::CListControl() : CCustomControl(){

	// メンバの初期化.
	m_hImageList = NULL;	// m_hImageListをNULLで初期化.

}

// デストラクタ~CListControl
CListControl::~CListControl(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウ作成関数Create.(ウィンドウクラス名省略バージョン.)
BOOL CListControl::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウクラス名が"SysListView32"なカスタムコントロールを作成.
	BOOL bRet = CCustomControl::Create(_T("SysListView32"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Createでリストコントロールを作成.

	// イメージリストの作成.
	m_hImageList = ImageList_Create(32, 32, ILC_COLOR24, 24, 0);	// ImageList_Createで作成.

	// 生成成功か失敗かを返す.
	return bRet;	// bRetを返す.

}

// イメージリストのセットSetImageList.
void CListControl::SetImageList(int nImageListType){

	// イメージリストのセット.
	ListView_SetImageList(m_hWnd, m_hImageList, nImageListType);	// ListView_SetImageListでイメージリストをセット.

}

// イメージリストにアイコンを追加するAddIcon.
int CListControl::AddIcon(HICON hIcon){

	// アイコンの追加.
	return ImageList_AddIcon(m_hImageList, hIcon);	// ImageList_AddIconでアイコンを追加.

}

// リストコントロールにアイテムを追加InsertItem.
int CListControl::InsertItem(LPLVITEM pItem){

	// アイテムの追加.
	return ListView_InsertItem(m_hWnd, pItem);	// ListView_InsertItemでpItemを追加.

}

// ウィンドウの作成が開始された時.
int CListControl::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(hwnd), UM_SIZECHILD, wParam, (LPARAM)hwnd);	// SendMessageでUM_SIZECHILDを送信.

	// 常にウィンドウ作成に成功するものとする.
	return CCustomControl::OnCreate(hwnd, lpCreateStruct);	// CCustomControl::OnCreateを呼ぶ.

}

// ウィンドウのサイズが変更された時.
void CListControl::OnSize(UINT nType, int cx, int cy){

	// 親クラスのOnSize.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSizeを呼ぶ.

	// UM_SIZECHILDで子ウィンドウのサイズに合わせる.
	WPARAM wParam;	// WPARAM型wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAMでwParamをセット.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessageでUM_SIZECHILDを送信.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CListControl::Destroy(){

	// イメージリストの破棄.
	if (m_hImageList != NULL){	// m_hImageListがNULLでない時.
		ImageList_Destroy(m_hImageList);	// ImageList_Destroyで破棄.
		m_hImageList = NULL;	// m_hImageListにNULLをセット.
	}

	// 親クラスのDestroy.
	CCustomControl::Destroy();	// CCustomControl::Destroyを呼ぶ.

}
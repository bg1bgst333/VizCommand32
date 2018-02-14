// ヘッダのインクルード
// 独自のヘッダ
#include "WindowListItemsPanel.h"	// CWindowListItemsPanel

// コンストラクタCWindowListItemsPanel
CWindowListItemsPanel::CWindowListItemsPanel() : CUserControl(){

	// メンバの初期化.
	m_vecWindowListItem.clear();	// m_vecWindowListItem.clearでクリア.
	m_nNextId = 0;	// m_nNextIdを0で初期化.

}

// デストラクタ~CWindowListItemsPanel
CWindowListItemsPanel::~CWindowListItemsPanel(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CWindowListItemsPanel::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CWindowListItemsPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CWindowListItemsPanel"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CWindowListItemsPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	return CUserControl::Create(_T("CWindowListItemsPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CWindowListItemsPanel::Destroy(){

	// ウィンドウリストアイテムリストの終了処理.
	m_vecWindowListItem.clear();	// m_vecWindowListItem.clearでクリア.
	m_nNextId = 0;	// m_nNextIdに0をセット.

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// アイテムを末尾から追加する関数Add.
void CWindowListItemsPanel::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// ウィンドウリストアイテムの追加.
	CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItemオブジェクトを生成し, ポインタをpWindowListItemに格納.
	pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Createでアイテム作成.
	m_vecWindowListItem.push_back(pWindowListItem);	// m_vecWindowListItem.push_backで末尾に追加.
	m_nNextId++;	// m_nNextIdをインクリメント.

}

// アイテムを末尾から削除する関数Remove.
void CWindowListItemsPanel::Remove(){

	// ウィンドウリストアイテムの削除.
	CWindowListItem *pWindowListItem = m_vecWindowListItem[m_vecWindowListItem.size() - 1];	// 末尾要素を取得.
	delete pWindowListItem;	// deleteでpWindowListItemの削除.
	m_vecWindowListItem.pop_back();	// m_vecWindowListItem.pop_backでリストを1つ減らす.
	m_nNextId--;

}

// アイテムを取得する関数Get.
CWindowListItem * CWindowListItemsPanel::Get(int iIndex){

	// iIndex番目の要素を返す.
	return m_vecWindowListItem[iIndex];	// m_vecWindowListItem[iIndex]を返す.

}

// 全てのアイテムを削除する関数RemoveAll.
void CWindowListItemsPanel::RemoveAll(){

	// アイテムの数だけ繰り返す.
	size_t n = GetSize();	// GetSizeでサイズを取得し, nに格納.
	for (size_t i = 0; i < n; i++){	// nの数だけ繰り返す.
		Remove();	// Removeで末尾を削除.
	}

}

// アイテムの数を返す関数GetSize.
size_t CWindowListItemsPanel::GetSize(){

	// アイテムの要素数を返す.
	return m_vecWindowListItem.size();	// m_vecWindowListItem.sizeで要素数を返す.

}

// ウィンドウの作成が開始された時.
int CWindowListItemsPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CWindowListItemsPanel::OnDestroy(){

	// メンバの終了処理
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 親クラスのOnDestroyを呼ぶ.
	CUserControl::OnDestroy();	// CUserControl::OnDestroyを呼ぶ.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CWindowListItemsPanel::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HPEN hPen = NULL;	// hPenをNULLで初期化.
	HBRUSH hBrush = NULL;	// hBrushをNULLで初期化.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

	// ペンとブラシの生成.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0));	// CreatePenで赤(淡)のペンを作成.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0x7f, 0, 0));		// CreateSolidBrushで赤(濃)のブラシを作成.

	// ペンとブラシの選択.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// 赤のペンを選択.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// 赤のブラシを選択.

	// 矩形描画.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangleで矩形を描画.
	
	// ペンとブラシの復元
	SelectObject(hDC, hOldBrush);		// 古いブラシを選択.
	SelectObject(hDC, hOldPen);		// 古いペンを選択.

	// ペンとブラシの破棄.
	DeleteObject(hBrush);	// ブラシの破棄.
	DeleteObject(hPen);	// ペンの破棄.

	// 描画終了.
	EndPaint(m_hWnd, &ps);	// EndPaintで描画終了.

}

// ウィンドウのサイズが変更された時.
void CWindowListItemsPanel::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウの既定処理.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

}

// 子から親へウィンドウサイズ変更の要求が発生した時.
void CWindowListItemsPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// サイズ取り出し.
	int iWidth = LOWORD(wParam);	// LOWORDはiWidth.
	int iHeight = HIWORD(wParam);	// HIWORDはiHeight.
	HWND hSrc = (HWND)lParam;	// lParamをHWNDにキャストして, hSrcに格納.

	// ウィンドウマップからウィンドウオブジェクト取得.
	CWindow *pWindow = m_mapWindowMap[hSrc];	// m_mapWindowMap[hSrc]からpWindowを取得.
	
	// 右端, 下端を取得.
	int w = pWindow->m_x + pWindow->m_iWidth;	// 取得したウィンドウの右端を取得.
	int h = pWindow->m_y + pWindow->m_iHeight;	// 取得したウィンドウの下端を取得.

	// パネルが小さかったら拡大.
	if (m_iWidth < w){	// wが大きい.
		MoveWindow(m_hWnd, m_x, m_y, w, m_iHeight, TRUE);	// MoveWindowで横をwの大きさに拡大.
	}
	if (m_iHeight < h){	// hが大きい.
		MoveWindow(m_hWnd, m_x, m_y, m_iWidth, h, TRUE);	// MoveWindowで縦をhの大きさに拡大.
	}

}
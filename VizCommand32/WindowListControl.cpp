// ヘッダのインクルード
// 独自のヘッダ
#include "WindowListControl.h"	// CWindowListControl

// コンストラクタCWindowListControl
CWindowListControl::CWindowListControl() : CUserControl(){

	// メンバ変数の初期化.
	m_pWindowListItemsPanel = NULL;	// m_pWindowListItemsPanelをNULLで初期化.
	m_iHScrollPos = 0;	// m_iHScrollPosを0で初期化.
	m_iVScrollPos = 0;	// m_iVScrollPosを0で初期化.

}

// デストラクタ~CWindowListControl
CWindowListControl::~CWindowListControl(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CWindowListControl::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CWindowListControl::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CWindowListControl"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CWindowListControl::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	return CUserControl::Create(_T("CWindowListControl"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createで作成.

}

// ウィンドウの破棄と終了処理関数Destroy.
void CWindowListControl::Destroy(){

	// ウィンドウリストアイテムズパネルの破棄.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでない時.
		m_pWindowListItemsPanel->Destroy();	// m_pWindowListItemsPanel->Destroyで破棄.
		delete m_pWindowListItemsPanel;	// deleteでm_pWindowListItemsPanelを解放.
		m_pWindowListItemsPanel = NULL;	// m_pWindowListItemsPanelにNULLをセット.
	}

	// 親ウィンドウのDestroyを呼ぶ.
	CUserControl::Destroy();	// CUserControl::Destroyを呼ぶ.

}

// アイテムを末尾から追加する関数Add.
void CWindowListControl::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// アイテムズパネルに追加.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでなければ.
		m_pWindowListItemsPanel->Add(lpctszWindowName, x, y, iWidth, iHeight, hInstance);	// Addで末尾に追加.
	}

}

// アイテムを末尾から追加する関数Add.
void CWindowListControl::Add(LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance){

	// アイテムズパネルに追加.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでなければ.
		m_pWindowListItemsPanel->Add(lpctszWindowName, iHeight, hInstance);	// Addで末尾に追加.
	}

}

// アイテムを指定の場所に挿入する関数Insert.
void CWindowListControl::Insert(int iIndex, LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance){

	// アイテムズパネルに追加.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでなければ.
		m_pWindowListItemsPanel->Insert(iIndex, lpctszWindowName, iHeight, hInstance);	// m_pWindowListItemsPanel->InsertでiIndex番目に挿入.
	}

}

// アイテムを末尾から削除する関数Remove.
void CWindowListControl::Remove(){

	// アイテムズパネルから削除.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでなければ.
		m_pWindowListItemsPanel->Remove();	// Removeで末尾から削除.
	}

}

// 指定の場所のアイテムを削除する関数Delete.
void CWindowListControl::Delete(int iIndex){

	// アイテムズパネルから削除.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでなければ.
		m_pWindowListItemsPanel->Delete(iIndex);	// DeleteでiIndex番目を削除.
	}

}

// アイテムを取得する関数Get.
CWindowListItem * CWindowListControl::Get(int iIndex){

	// アイテムズパネルから取得.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでなければ.
		return m_pWindowListItemsPanel->Get(iIndex);	// 
	}

	// なければNULL.
	return NULL;	// NULLを返す.

}

// 全てのアイテムを削除する関数RemoveAll.
void CWindowListControl::RemoveAll(){

	// アイテムズパネルから全て削除.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでなければ.
		m_pWindowListItemsPanel->RemoveAll();
	}

}

// ウィンドウの作成が開始された時.
int CWindowListControl::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// クライアント領域のサイズを取得.
	RECT rc = {0};	// rcを{0}で初期化.
	GetClientRect(hwnd, &rc);	// GetClientRectでクライアント領域のRECTを取得.
	m_iClientAreaWidth = rc.right - rc.left;	// 幅.
	m_iClientAreaHeight = rc.bottom - rc.top;	// 高さ.

	// 常にウィンドウ作成に成功するものとする.
	return 0;	// 0を返すと, ウィンドウ作成に成功したということになる.

}

// ウィンドウが破棄された時.
void CWindowListControl::OnDestroy(){

	// メンバの終了処理
	//Destroy();	// Destroyでこのウィンドウの終了処理をする.

	// 親クラスのOnDestroyを呼ぶ.
	CUserControl::OnDestroy();	// CUserControl::OnDestroyを呼ぶ.

}

// ウィンドウの描画を要求された時のハンドラOnPaint.
void CWindowListControl::OnPaint(){

	// 変数の初期化.
	HDC hDC = NULL;	// hDCをNULLで初期化.
	PAINTSTRUCT ps = {0};	// psを{0}で初期化.
	HPEN hPen = NULL;	// hPenをNULLで初期化.
	HBRUSH hBrush = NULL;	// hBrushをNULLで初期化.

	// 描画開始.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaintで描画開始.

#if 0
	// ペンとブラシの生成.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0xff));	// CreatePenで青(淡)のペンを作成.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0x7f));		// CreateSolidBrushで青(濃)のブラシを作成.

	// ペンとブラシの選択.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// 青のペンを選択.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// 青のブラシを選択.

	// 矩形描画.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangleで矩形を描画.
	
	// ペンとブラシの復元
	SelectObject(hDC, hOldBrush);		// 古いブラシを選択.
	SelectObject(hDC, hOldPen);		// 古いペンを選択.

	// ペンとブラシの破棄.
	DeleteObject(hBrush);	// ブラシの破棄.
	DeleteObject(hPen);	// ペンの破棄.

#if 0
	// スクロールバー設定.
	// 水平方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaWidth;	// ページ幅
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iWidth;	//最大値
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)
	// 垂直方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// ページ高さ
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iHeight;	//最大値
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)
#endif
#endif

  	// 描画終了.
	EndPaint(m_hWnd, &ps);	// EndPaintで描画終了.

}

// ウィンドウのサイズが変更された時.
void CWindowListControl::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウの既定処理.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSizeを呼ぶ.

	// ウィンドウリストアイテムズパネルの幅はウィンドウリストコントロールの幅にぴったり合わせる.
	if (m_pWindowListItemsPanel != NULL){	// NULLでなければ.
		MoveWindow(m_pWindowListItemsPanel->m_hWnd, m_pWindowListItemsPanel->m_x, m_pWindowListItemsPanel->m_y, cx, m_pWindowListItemsPanel->m_iHeight, TRUE);	// MoveWindowでm_pWindowListControl->m_hWndのサイズを幅だけ変更.
	}

	// 画面更新.
	//InvalidateRect(m_hWnd, NULL, FALSE);	// InvalidateRectで更新.

#if 1
	// スクロールバー設定.
#if 0
	// 水平方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaWidth;	// ページ幅
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iWidth;	//最大値
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)
#endif
	// 垂直方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// ページ高さ
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iHeight;	//最大値
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)
#endif

}

// 水平方向スクロールバーイベント時.
void CWindowListControl::OnHScroll(UINT nSBCode, UINT nPos){

	// スクロール情報取得.
	m_ScrollInfo.fMask = SIF_POS;	// 位置だけ変更モード(これがないと, スクロールバーが元の位置に戻ってしまうので注意!こっちが前!)
	GetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo);	// マスクを設定してからGetScrollInfo.(こっちが後!)

	// スクロールバー処理.
	switch (nSBCode) {	// nSBCodeごとに振り分け.

		// 一番左
		case SB_LEFT:

			// 位置を最小値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// 一番右
		case SB_RIGHT:

			// 位置を最大値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1列左
		case SB_LINELEFT:

			// nPosが0でなければデクリメント.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1列右
		case SB_LINERIGHT:

			// nPosが最大値-1でなければインクリメント.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1ページ左
		case SB_PAGELEFT:

			// nPage分減らす.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1ページ右
		case SB_PAGERIGHT:

			// nPage分増やす.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// つまみをドラッグ中.
		case SB_THUMBTRACK:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// つまみをドラッグ後.
		case SB_THUMBPOSITION:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// それ以外.
		default:

			break;

	}

	// スクロール情報設定.
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);
	// メンバにもセット.
	m_iHScrollPos = m_ScrollInfo.nPos;
	// アイテムズパネルの移動.
	MoveWindow(m_pWindowListItemsPanel->m_hWnd, 0 - m_iHScrollPos, 0 - m_iVScrollPos, m_pWindowListItemsPanel->m_iWidth, m_pWindowListItemsPanel->m_iHeight, TRUE);	// MoveWindowで移動.
	// 無効領域を作成して画面の更新.
	//InvalidateRect(m_hWnd, NULL, FALSE);	// InvalidateRectで無効領域作成.

}

// 垂直方向スクロールバーイベント時.
void CWindowListControl::OnVScroll(UINT nSBCode, UINT nPos){

	// スクロール情報取得.
	m_ScrollInfo.fMask = SIF_POS;	// 位置だけ変更モード(これがないと, スクロールバーが元の位置に戻ってしまうので注意!こっちが前!)
	GetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo);	// マスクを設定してからGetScrollInfo.(こっちが後!)

	// スクロールバー処理.
	switch (nSBCode) {	// nSBCodeごとに振り分け.

		// 一番上
		case SB_TOP:

			// 位置を最小値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// 一番下
		case SB_BOTTOM:

			// 位置を最大値に.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1行上
		case SB_LINEUP:

			// nPosが0でなければデクリメント.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1行下
		case SB_LINEDOWN:

			// nPosが最大値-1でなければインクリメント.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1ページ上
		case SB_PAGEUP:

			// nPage分減らす.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1ページ下
		case SB_PAGEDOWN:

			// nPage分増やす.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// つまみをドラッグ中.
		case SB_THUMBTRACK:
	
			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// つまみをドラッグ後.
		case SB_THUMBPOSITION:

			// 引数のnPosをセット
			m_ScrollInfo.nPos = nPos;
			break;

		// それ以外.
		default:

			break;

	}

	// スクロール情報設定.
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);
	// メンバにもセット.
	m_iVScrollPos = m_ScrollInfo.nPos;
	// アイテムズパネルの移動.
	MoveWindow(m_pWindowListItemsPanel->m_hWnd, 0 - m_iHScrollPos, 0 - m_iVScrollPos, m_pWindowListItemsPanel->m_iWidth, m_pWindowListItemsPanel->m_iHeight, TRUE);	// MoveWindowで移動.
	// 無効領域を作成して画面の更新.
	//InvalidateRect(m_hWnd, NULL, FALSE);	// InvalidateRectで無効領域作成.

}

// 子から親へウィンドウサイズ変更の要求が発生した時.
void CWindowListControl::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// 垂直方向.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemoryでm_ScrollInfoをクリア.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// サイズ
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// フラグ
	m_ScrollInfo.nPage = m_iClientAreaHeight;	// ページ高さ
	m_ScrollInfo.nMin = 0;	// 最小値
	m_ScrollInfo.nMax = m_pWindowListItemsPanel->m_iHeight;	//最大値
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfoでセット.(SetImageのInvalidateRectと第4引数のTRUEがないとスクロールバーつまみが即座に更新されない.)

}
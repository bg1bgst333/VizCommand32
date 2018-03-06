// ヘッダのインクルード
// 独自のヘッダ
#include "StreamConsole.h"	// ストリームコンソールクラス
#include "ConsoleCore.h"	// コンソールコアクラス

// コンストラクタCStreamConsole
CStreamConsole::CStreamConsole() : CWindowListControl(){

	// メンバの初期化.
	m_nId = 0;	// m_nIdを0で初期化.

}

// デストラクタ~CStreamConsole
CStreamConsole::~CStreamConsole(){

	// メンバの終了処理
	Destroy();	// Destroyでこのウィンドウの終了処理をする.

}

// ウィンドウクラス登録関数RegisterClass.
BOOL CStreamConsole::RegisterClass(HINSTANCE hInstance){

	// ウィンドウクラスの登録.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClassで登録.

}

// ウィンドウクラス登録関数RegisterClass.(hbrBackground指定.)
BOOL CStreamConsole::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackgroundを指定.
	return CUserControl::RegisterClass(hInstance, _T("CStreamConsole"), hbrBackground);	// CUserControl::RegisterClassで登録.

}

// ウィンドウ作成関数Create.
BOOL CStreamConsole::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// ウィンドウの作成.
	return CUserControl::Create(_T("CStreamConsole"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Createで作成.

}

// ウィンドウ作成時のハンドラOnCreate.
int CStreamConsole::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// 親ウィンドウのOnCreateを呼ぶ.
	int iRet = CWindowListControl::OnCreate(hwnd, lpCreateStruct);	// CWindowListControl::OnCreateを返す.
	
	// 初回更新タイマーをセット.
	SetTimer(hwnd, 1, 100, NULL);	// SetTimerで更新タイマーをセット.(100ミリ秒==0.1秒)

	// 戻り値を返す.
	return iRet;	// iRetを返す.

}

// ウィンドウのサイズが変更された時.
void CStreamConsole::OnSize(UINT nType, int cx, int cy){

	// 親ウィンドウのOnSize.
	CWindowListControl::OnSize(nType, cx, cy);	// CWindowListControlのOnSize.

	// すべてのコンソールコアのサイズを右にぴったしあわせる.
	if (m_pWindowListItemsPanel != NULL){	// m_pWindowListItemsPanelがNULLでない時.
		size_t n = m_pWindowListItemsPanel->GetSize();	// m_pWindowListItemsPanel->GetSizeでサイズを取得.
		for (int i = n - 1; i >= 0; i--){	// iがn - 1から0まで.
			CWindowListItem *pItem = Get(i);	// Get(i)でpItemを取得.
			if (pItem != NULL){	// pItemがNULLでない時.
				if (pItem->m_mapChildMap.find(_T("ConsoleCore")) != pItem->m_mapChildMap.end()){	// "ConsoleCore"が見つかったら.
					CWindow *pWindow = pItem->m_mapChildMap[_T("ConsoleCore")];	// pItem->m_mapChildMap[_T("ConsoleCore")]で取り出す.(この時, CWindowポインタでいい.)
					MoveWindow(pWindow->m_hWnd, pWindow->m_x, pWindow->m_y, m_iWidth/* cx */, pWindow->m_iHeight, TRUE);	// MoveWindowで横幅をcxとする.
				}
			}
		}
	}

}

// タイマーイベントが発生した時.
void CStreamConsole::OnTimer(UINT_PTR nIDEvent){

	// 初回更新タイマーの時.
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);	// GetWindowLongでhInstanceを取得.
	if (nIDEvent == 1){	// 1の時.

		// デフォルトアイテムの挿入.
		Insert(0, _T("0"), 80, hInstance);	// Insertで0番目のアイテムを挿入.
		CWindowListItem *pItem = Get(0);	// Getで0番目を取得し, pItemに格納.
		CConsoleCore *pConsoleCore = new CConsoleCore();	// CConsoleCoreオブジェクトを作成し, pConsoleCoreに格納.
		pConsoleCore->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, pItem->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pConsoleCore->Createでウィンドウ作成.
		pItem->m_mapChildMap.insert(std::make_pair(_T("ConsoleCore"), pConsoleCore));	// pItem->m_mapChildMap.insertで"ConsoleCore"をキーとして, pConsoleCoreを追加.
	
		// 無効領域を作成して画面の更新.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRectで無効領域作成.

		// タイマーを終了.
		KillTimer(m_hWnd, 1);	// 初回更新タイマーを終了.

	}

}
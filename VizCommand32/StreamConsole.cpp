// ヘッダのインクルード
// 独自のヘッダ
#include "StreamConsole.h"	// ストリームコンソールクラス
#include "StreamConsoleItemsPanel.h"	// ストリームコンソールアイテムズパネルクラス

// コンストラクタCStreamConsole
CStreamConsole::CStreamConsole() : CWindowListControl(){

	// メンバの初期化.
	m_nId = 0;	// m_nIdを0で初期化.
	m_iNext = 0;	// m_iNextを0で初期化.

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
	
	// ウィンドウリストアイテムズパネルの生成.
	//m_pWindowListItemsPanel = new CWindowListItemsPanel();	// CWindowListItemsPanelの作成.
	m_pWindowListItemsPanel = new CStreamConsoleItemsPanel();	// CStreamConsoleItemsPanelの作成.

	// ウィンドウリストアイテムズパネルのウィンドウ生成.
	m_pWindowListItemsPanel->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, (HMENU)(WM_APP + 2), lpCreateStruct->hInstance);	// m_pWindowListItemsPanel->Createでウィンドウ生成.
	
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
				if (pItem->m_mapChildMap.find(_T("Console")) != pItem->m_mapChildMap.end()){	// "Console"が見つかったら.
					CWindow *pWindow = pItem->m_mapChildMap[_T("Console")];	// pItem->m_mapChildMap[_T("Console")]で取り出す.(この時, CWindowポインタでいい.)
					MoveWindow(pWindow->m_hWnd, pWindow->m_x, pWindow->m_y, m_iWidth/* cx */, pWindow->m_iHeight, TRUE);	// MoveWindowで横幅をcxとする.
				}
				if (pItem->m_mapChildMap.find(_T("StaticPanel")) != pItem->m_mapChildMap.end()){	// "StaticPanel"が見つかったら.
					CWindow *pWindow = pItem->m_mapChildMap[_T("StaticPanel")];	// pItem->m_mapChildMap[_T("StaticPanel")]で取り出す.(このとき, CWindowポインタでいい.)
					MoveWindow(pWindow->m_hWnd, pWindow->m_x, pWindow->m_y, m_iWidth, pWindow->m_iHeight, TRUE);	// MoveWindowで横幅をcxとする.
				}
				if (pItem->m_mapChildMap.find(_T("FileListControlPanel")) != pItem->m_mapChildMap.end()){	// "ListControlPanel"が見つかったら.
					CWindow *pWindow = pItem->m_mapChildMap[_T("FileListControlPanel")];	// pItem->m_mapChildMap[_T("ListControlPanel")]で取り出す.(このとき, CWindowポインタでいい.)
					MoveWindow(pWindow->m_hWnd, pWindow->m_x, pWindow->m_y, cx, pWindow->m_iHeight, TRUE);	// MoveWindowで横幅をcxとする.
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
		TCHAR tszNext[16] = {0};	// tszNextを{0}で初期化.
		_stprintf(tszNext, _T("%d"), m_iNext);	// m_iNextをtszNextに変換. 
		Insert(m_iNext, tszNext, 80, hInstance);	// Insertでm_iNext番目のアイテムを挿入.
		CWindowListItem *pItem = Get(m_iNext);	// Getでm_iNext番目を取得し, pItemに格納.
		//CConsoleCore *pConsoleCore = new CConsoleCore();	// CConsoleCoreオブジェクトを作成し, pConsoleCoreに格納.
		//pConsoleCore->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, pItem->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pConsoleCore->Createでウィンドウ作成.
		//pItem->m_mapChildMap.insert(std::make_pair(_T("ConsoleCore"), pConsoleCore));	// pItem->m_mapChildMap.insertで"ConsoleCore"をキーとして, pConsoleCoreを追加.
		CConsole *pConsole = new CConsole();	// CConsoleオブジェクトを作成し, pConsoleに格納.
		pConsole->SetProcWindow(m_hWnd);	// pConsole->SetProcWindowでストリームコマンドならここに投げるようにする.
		pConsole->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, pItem->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pConsole->Createでウィンドウ作成.
		pConsole->ShowInputForm();	// 入力フォームを出力.
		pItem->m_mapChildMap.insert(std::make_pair(_T("Console"), pConsole));	// pItem->m_mapChildMap.insertで"Console"をキーとして, pConsoleを追加.
		m_nId++;	// m_nIdをインクリメント.
		m_iNext++;	// m_iNextをインクリメント.

		// 無効領域を作成して画面の更新.
		//InvalidateRect(m_hWnd, NULL, FALSE);	// InvalidateRectで無効領域作成.

		// タイマーを終了.
		KillTimer(m_hWnd, 1);	// 初回更新タイマーを終了.

	}

}

// ユーザ定義メッセージが発生した時.
void CStreamConsole::OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

	// switch-case文で振り分ける.
	switch (uMsg) {

		// 子から親へウィンドウサイズ変更の要求が発生した時.
		case UM_SIZECHILD:

			// UM_SIZECHILDブロック
			{

				// OnSizeChildに任せる.
				OnSizeChild(wParam, lParam);	// OnSizeChildに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// 下へのスクロールが要求された時.
		case UM_REQUESTSCROLLBOTTOM:

			// UM_REQUESTSCROLLBOTTOMブロック
			{

				// OnRequestScrollBottomに任せる.
				OnRequestScrollBottom(wParam, lParam);	// OnRequestScrollBottomに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// コンソールからストリームコンソールへのメッセージが送られた時.
		case UM_STREAMCOMMAND:

			// UM_STREAMCOMMANDブロック
			{

				// OnStreamCommandに任せる.
				OnStreamCommand(wParam, lParam);	// OnStreamCommandに任せる.

			}

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

		// それ以外.
		default:

			// 既定の処理へ向かう.
			break;	// 抜けてDefWindowProcに向かう.

	};

}

// 下へのスクロールが要求された時.
void CStreamConsole::OnRequestScrollBottom(WPARAM wParam, LPARAM lParam){

	// スクロール情報を取得する.
	ZeroMemory(&m_ScrollInfo, sizeof(m_ScrollInfo));	// ZeroMemoryで0で初期化.
	m_ScrollInfo.fMask = SIF_POS | SIF_RANGE | SIF_PAGE;	// m_ScrollInfo.fMaskでマスクをセット.
	GetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo);	// GetScrollInfoでスクロール

	// スクロール可能になった時.
	if (m_ScrollInfo.nMax > m_ScrollInfo.nPage){	// nMaxのほうがnPageより大きい.

		// アイテムズパネルのトータルの高さを取得.
		int iTotalHeight = (int)wParam;	// wParamをintにキャストし, iTotalHeightに代入.
		m_ScrollInfo.nMax = iTotalHeight;	// m_ScrollInfo.nMaxがiTotalHeight.
		m_ScrollInfo.nPos = m_ScrollInfo.nMax;	// m_ScrollInfo.nPosはm_ScrollInfo.nMax.

		// スクロール情報を設定する.
		SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfoでm_ScrollInfoをセット.

		// アイテムズパネルの移動.
		MoveWindow(m_pWindowListItemsPanel->m_hWnd, m_pWindowListItemsPanel->m_x, -m_ScrollInfo.nPos + m_ScrollInfo.nPage, m_pWindowListItemsPanel->m_iWidth, m_pWindowListItemsPanel->m_iHeight, TRUE);	// MoveWindowで-m_ScrollInfo.nPosの位置に移動.

	}

}

// コンソールからストリームコンソールへのメッセージが送られた時.
int CStreamConsole::OnStreamCommand(WPARAM wParam, LPARAM lParam){

	// 変数の初期
	CCommand *pCommand = NULL;	// CCommandオブジェクトポインタpCommandをNULLで初期化.
	HWND hSrc = NULL;	// 送信元ウィンドウハンドルhSrcをNULLで初期化.

	// コマンドとソースを取得.
	pCommand = (CCommand *)wParam;	// wParamを(CCommand *)にキャストしてpCommandに格納.
	hSrc = (HWND)lParam;	// lParamをHWNDにキャストしてhSrcに格納.

	// コマンドの判別.
	tstring tstrCommandName = pCommand->GetCommandName();	// pCommand->GetCommandNameで取得したコマンド名をtstrCommandNameに格納.
	if (tstrCommandName == _T("hello")){	// helloコマンド.

		// OnHelloに任せる.
		OnHello(hSrc, pCommand);	// hSrc, pCommandを引数として渡して, OnHelloを呼ぶ.

	}
	else if (tstrCommandName == _T("list")){	// listコマンド.

		// OnListに任せる.
		OnList(hSrc, pCommand);	// hSrc, pCommandを引数として渡して, OnListを呼ぶ.

	}

	// 成功なら0を返す.
	return 0;	// 0を返す.

}

// "Hello, world!"の出力を要求された時.
void CStreamConsole::OnHello(HWND hSrc, CCommand *pCommand){

	// "/s"オプションがあれば, StreamConsoleに投げる.
	if (pCommand->m_vectstrCommandToken.size() > 1){	// オプションがある場合.
		if (pCommand->m_vectstrCommandToken[1] == _T("/s")){	// "/s"オプションなら.

			// インスタンスハンドルを取得.
			HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);	// GetWindowLongでhInstanceを取得.

			// アイテムの挿入.
			TCHAR tszNext[16] = {0};	// tszNextを{0}で初期化.
			_stprintf(tszNext, _T("%d"), m_iNext);	// m_iNextをtszNextに変換. 
			Insert(m_iNext, tszNext, 80, hInstance);	// Insertでm_iNext番目のアイテムを挿入.
			CWindowListItem *pItem = Get(m_iNext);	// Getでm_iNext番目を取得し, pItemに格納.

			// スタティックパネルの追加.
			CStaticPanel *pStaticPanel =  new CStaticPanel();	// CStaticPanelオブジェクトを作成, pStaticPanelに格納.
			pStaticPanel->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, pItem->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pStaticPanel->Createでウィンドウ作成.
			pStaticPanel->m_pStatic->SetText(_T("Hello, Static world!"));	// "Hello, Static world!"をセット.
			pItem->m_mapChildMap.insert(std::make_pair(_T("StaticPanel"), pStaticPanel));	// pItem->m_mapChildMap.insertで"StaticPanel"をキーとして, pStaticPanelを追加.

			// 次へ.
			m_nId++;	// m_nIdをインクリメント.
			m_iNext++;	// m_iNextをインクリメント.

			// アイテムの挿入.
			TCHAR tszNext2[16] = {0};	// tszNext2を{0}で初期化.
			_stprintf(tszNext2, _T("%d"), m_iNext);	// m_iNextをtszNext2に変換. 
			Insert(m_iNext, tszNext2, 80, hInstance);	// Insertでm_iNext番目のアイテムを挿入.
			CWindowListItem *pItem2 = Get(m_iNext);	// Getでm_iNext番目を取得し, pItem2に格納.

			// コンソールの追加.
			CConsole *pConsole = new CConsole();	// CConsoleオブジェクトを作成し, pConsoleに格納.
			pConsole->SetProcWindow(m_hWnd);	// pConsole->SetProcWindowでストリームコマンドならここに投げるようにする.
			pConsole->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, pItem2->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pConsole->Createでウィンドウ作成.
			pConsole->ShowInputForm();	// 入力フォームを出力.
			pItem2->m_mapChildMap.insert(std::make_pair(_T("Console"), pConsole));	// pItem2->m_mapChildMap.insertで"Console"をキーとして, pConsoleを追加.

			// 次へ.
			m_nId++;	// m_nIdをインクリメント.
			m_iNext++;	// m_iNextをインクリメント.

			// 終了.
			return;	// ここで終了.

		}
	}

	// 終了.
	return;	// ここで終了.

}

// ファイルリストの出力を要求された時.
void CStreamConsole::OnList(HWND hSrc, CCommand *pCommand){

	// インスタンスハンドルを取得.
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);	// GetWindowLongでhInstanceを取得.

	// アイテムの挿入.
	TCHAR tszNext[16] = {0};	// tszNextを{0}で初期化.
	_stprintf(tszNext, _T("%d"), m_iNext);	// m_iNextをtszNextに変換. 
	Insert(m_iNext, tszNext, 240, hInstance);	// Insertでm_iNext番目のアイテムを挿入.
	CWindowListItem *pItem = Get(m_iNext);	// Getでm_iNext番目を取得し, pItemに格納.

	// ファイルリストコントロールパネルの追加.
	CFileListControlPanel *pFileListControlPanel = new CFileListControlPanel();	// CFileListControlPanelオブジェクトを作成, pFileListControlPanelに格納.
	pFileListControlPanel->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, 240, pItem->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pFileListControlPanel->Createでウィンドウ作成.(高さは240固定.)
	if (pCommand->m_vectstrCommandToken.size() >= 2){	// トークンが2つ以上.
		pFileListControlPanel->ScanFile(pCommand->m_vectstrCommandToken[1]);	// pFileListControlPanel->ScanFileで第1パラメータのパスをスキャンする.
		pFileListControlPanel->ShowFileList();	// pFileListControlPanel->ShowFileListでファイルリストを表示.
	}
	pItem->m_mapChildMap.insert(std::make_pair(_T("FileListControlPanel"), pFileListControlPanel));	// pItem->m_mapChildMap.insertで"FileListControlPanel"をキーとして, pFileListControlPanelを追加.

	// 次へ.
	m_nId++;	// m_nIdをインクリメント.
	m_iNext++;	// m_iNextをインクリメント.

	// アイテムの挿入.
	TCHAR tszNext2[16] = {0};	// tszNext2を{0}で初期化.
	_stprintf(tszNext2, _T("%d"), m_iNext);	// m_iNextをtszNext2に変換. 
	Insert(m_iNext, tszNext2, 80, hInstance);	// Insertでm_iNext番目のアイテムを挿入.
	CWindowListItem *pItem2 = Get(m_iNext);	// Getでm_iNext番目を取得し, pItem2に格納.

	// コンソールの追加.
	CConsole *pConsole = new CConsole();	// CConsoleオブジェクトを作成し, pConsoleに格納.
	pConsole->SetProcWindow(m_hWnd);	// pConsole->SetProcWindowでストリームコマンドならここに投げるようにする.
	pConsole->Create(_T(""), 0, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight, pItem2->m_hWnd, (HMENU)(WM_APP + 200 + m_nId), hInstance);	// pConsole->Createでウィンドウ作成.
	pConsole->ShowInputForm();	// 入力フォームを出力.
	pItem2->m_mapChildMap.insert(std::make_pair(_T("Console"), pConsole));	// pItem2->m_mapChildMap.insertで"Console"をキーとして, pConsoleを追加.

	// 次へ.
	m_nId++;	// m_nIdをインクリメント.
	m_iNext++;	// m_iNextをインクリメント.

	// 終了.
	return;	// ここで終了.

}
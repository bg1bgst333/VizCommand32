// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// �����o�̏�����.
	m_pWindowListControl = NULL;	// m_pWindowListControl��NULL�ŏ�����.

}

// �f�X�g���N�^~CMainWindow()
CMainWindow::~CMainWindow(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CWindow::RegisterClass�œo�^.(�w�i��LTGRAY_BRUSH.)

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(���j���[���w��, �w�i�u���V�w��o�[�W����.)
BOOL CMainWindow::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// �w�i��hbrBackground.
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), NULL, hbrBackground);	// CWindow::RegisterClass�œo�^.

}


// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"CMainWindow".
	return CWindow::Create(_T("CMainWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ɃE�B���h�E�N���X��"CMainWindow"���w��.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CMainWindow::Destroy(){

	// �E�B���h�E���X�g�R���g���[���̍폜.
	if (m_pWindowListControl != NULL){	// m_pWindowListControl��NULL�łȂ����.

		// �E�B���h�E���X�g�A�C�e���̍폜.
		m_pWindowListControl->RemoveAll();	// m_pWindowListControl->RemoveAll�ŃA�C�e����S�č폜.

		// �E�B���h�E���X�g�R���g���[���̔j��.
		m_pWindowListControl->Destroy();	// m_pWindowListControl->Destroy��m_pWindowListControl�̏I�����������s.
		delete m_pWindowListControl;	// delete��m_pWindowListControl�����.
		m_pWindowListControl = NULL;	// m_pWindowListControl��NULL���Z�b�g.

	}

	// �e�E�B���h�E��Destroy���Ă�.
	CWindow::Destroy();	// CWindow::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �E�B���h�E���X�g�R���g���[���I�u�W�F�N�g�̍쐬.
	m_pWindowListControl = new CWindowListControl();	// CWindowListControl�I�u�W�F�N�g�̍쐬.

	// �E�B���h�E���X�g�R���g���[���̃E�B���h�E�쐬.
	m_pWindowListControl->Create(_T(""), 0, 0, 0, 480, 0, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pWindowListControl->Create�ō쐬.

#if 0
	// �E�B���h�E���X�g�A�C�e���̒ǉ�.
	m_pWindowListControl->Add(_T("Item0"), 320, 32, 64, 64, lpCreateStruct->hInstance);	// m_pWindowListControl->Add��"Item0"��ǉ�.
	m_pWindowListControl->Add(_T("Item1"), 32, 320, 64, 64, lpCreateStruct->hInstance);	// m_pWindowListControl->Add��"Item1"��ǉ�.

	// �E�B���h�E���X�g�A�C�e���̎擾.
	CWindowListItem *pItem0 = m_pWindowListControl->Get(0);	// 0�Ԗڂ��擾.
	CWindowListItem *pItem1 = m_pWindowListControl->Get(1);	// 1�Ԗڂ��擾.
#endif

	// �E�B���h�E���X�g�A�C�e���̒ǉ�.
	//m_pWindowListControl->Add(_T("Item0"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Add��"Item0"��ǉ�.
	//m_pWindowListControl->Add(_T("Item1"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Add��"Item1"��ǉ�.
	//m_pWindowListControl->Add(_T("Item2"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Add��"Item2"��ǉ�.
	//m_pWindowListControl->Insert(0, _T("Item-1"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insert��0�Ԗڂ�"Item-1"��}��.
	//m_pWindowListControl->Insert(1, _T("Item-0.5"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insert��1�Ԗڂ�"Item-0.5"��}��.
	//m_pWindowListControl->Insert(5, _T("Item3"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insert��2�Ԗڂ�"Item3"��}��.
	//m_pWindowListControl->Insert(0, _T("Item0"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insert��"Item0"��ǉ�.
	//m_pWindowListControl->Insert(-5, _T("Item-5"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insert��"Item-5"��ǉ�.
	//m_pWindowListControl->Insert(5, _T("Item5"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insert��"Item5"��ǉ�.
	//m_pWindowListControl->Insert(1, _T("Item-1"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insert��"Item-1"��ǉ�.
	//m_pWindowListControl->Insert(3, _T("Item3"), 80, lpCreateStruct->hInstance);	// m_pWindowListControl->Insert��"Item3"��ǉ�.

	// �E�B���h�E���X�g�A�C�e���̍폜.
	//m_pWindowListControl->Delete(3);	// m_pWindowListControl->Delete��3�Ԗڍ폜.
	//m_pWindowListControl->Delete(1);	// m_pWindowListControl->Delete��1�Ԗڍ폜.
	//m_pWindowListControl->Delete(10);	// m_pWindowListControl->Delete��10�Ԗڍ폜.
	//m_pWindowListControl->Delete(3);	// m_pWindowListControl->Delete��3�Ԗڍ폜.
	//m_pWindowListControl->Delete(-4);	// m_pWindowListControl->Delete��-4�Ԗڍ폜.

	// �����X�V�^�C�}�[���Z�b�g.
	SetTimer(hwnd, 2, 1000, NULL);	// SetTimer�ōX�V�^�C�}�[���Z�b�g.(1000�~���b==1�b)

#if 0
	// �G�f�B�b�g�R���g���[���̐���.
	// �G�f�B�b�g0.
	CEdit *pEdit0 = new CEdit();	// CEdit�I�u�W�F�N�g�𐶐�.
	pEdit0->Create(_T("Edit0"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 480, 100, pItem0->m_hWnd, (HMENU)WM_APP + 200, lpCreateStruct->hInstance);	// m_pEdit0->Create��pItem0->m_hWnd��e�Ƃ��ăE�B���h�E�쐬.
	pItem0->m_mapChildMap.insert(std::make_pair(_T("Edit0"), pEdit0));	// "Edit0"���L�[, pEdit0��l�Ƃ���, pItem0->m_mapChildMap�ɓo�^.

	// �G�f�B�b�g1.
	CEdit *pEdit1 = new CEdit();	//CEdit�I�u�W�F�N�g�𐶐�.
	pEdit1->Create(_T("Edit1"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 100, 480, pItem1->m_hWnd, (HMENU)WM_APP + 201, lpCreateStruct->hInstance);	// m_pEdit1->Create��pItem1->m_hWnd��e�Ƃ��ăE�B���h�E�쐬.
	pItem1->m_mapChildMap.insert(std::make_pair(_T("Edit1"), pEdit1));	// "Edit1"���L�[, pEdit1��l�Ƃ���, pItem1->m_mapChildMap�ɓo�^.
#endif

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CMainWindow::OnDestroy(){

	// �����o�̏I������
	//Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// �e�E�B���h�E��OnDestroy���Ă�.
	CWindow::OnDestroy();	// CWindow::OnDestroy���Ă�.

	// �I�����b�Z�[�W�̑��M.
	PostQuitMessage(0);	// PostQuitMessage�ŏI���R�[�h��0�Ƃ���WM_QUIT���b�Z�[�W�𑗐M.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CMainWindow::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E��OnSize.
	CWindow::OnSize(nType, cx, cy);	// CWindow��OnSize.

	// �E�B���h�E���X�g�R���g���[���̃T�C�Y�̓E�B���h�E�ɂ҂����荇�킹��.
	if (m_pWindowListControl != NULL){	// NULL�łȂ����.
		MoveWindow(m_pWindowListControl->m_hWnd, m_pWindowListControl->m_x, m_pWindowListControl->m_y, cx, cy, TRUE);	// MoveWindow��m_pWindowListControl->m_hWnd�̃T�C�Y��ύX.
	}

	// ��ʍX�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

}

// �^�C�}�[�C�x���g������������.
void CMainWindow::OnTimer(UINT_PTR nIDEvent){

	// �X�^�e�B�b�N�ϐ��̐錾.
	static int iCount;	// static int�̕ϐ�iCount.

	// ����X�V�^�C�}�[�̎�.
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);
	if (nIDEvent == 2){	// 2�̎�.
		if (iCount == 0){
			m_pWindowListControl->Insert(0, _T("Item0"), 80, hInstance);
		}
		else if (iCount == 1){
			m_pWindowListControl->Insert(1, _T("Item1"), 80, hInstance);
		}
		else if (iCount == 2){
			m_pWindowListControl->Insert(2, _T("Item2"), 80, hInstance);
		}
		else if (iCount == 3){
			m_pWindowListControl->Insert(3, _T("Item3"), 80, hInstance);
		}
		else if (iCount == 4){
			m_pWindowListControl->Insert(4, _T("Item4"), 80, hInstance);
		}
		else if (iCount == 5){
			//m_pWindowListControl->Delete(2);
			CWindowListItem *pItem = m_pWindowListControl->Get(1);
			MoveWindow(pItem->m_hWnd, pItem->m_x, pItem->m_y, pItem->m_iWidth, pItem->m_iHeight * 2.5, TRUE);
			CWindowListItem *pItem2 = m_pWindowListControl->Get(3);
			MoveWindow(pItem2->m_hWnd, pItem2->m_x, pItem2->m_y, pItem2->m_iWidth, pItem2->m_iHeight * 2.5, TRUE);
			//InvalidateRect(this->m_pWindowListControl->m_hWnd, NULL, TRUE);
		}
		/*
		else if (iCount == 6){
			//m_pWindowListControl->Delete(20);
		}
		else if (iCount == 7){
			//m_pWindowListControl->Delete(-10);
		}
		else if (iCount == 8){
			//m_pWindowListControl->Delete(0);
		}
		else if (iCount == 9){
			//m_pWindowListControl->Delete(0);
		}
		?*/
		else{

			// �^�C�}�[���I��.
			KillTimer(m_hWnd, 2);	// �����X�V�^�C�}�[���I��.

		}
		iCount++;	// iCount���C���N�������g.
	}

	// �����̈���쐬���ĉ�ʂ̍X�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�Ŗ����̈�쐬.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CMainWindow::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HPEN hPen = NULL;	// hPen��NULL�ŏ�����.
	HBRUSH hBrush = NULL;	// hBrush��NULL�ŏ�����.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

	// �y���ƃu���V�̐���.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0xff, 0));	// CreatePen�ŗ�(�W)�̃y�����쐬.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0x7f, 0));		// CreateSolidBrush�ŗ�(�Z)�̃u���V���쐬.

	// �y���ƃu���V�̑I��.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// �΂̃y����I��.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// �΂̃u���V��I��.

	// ��`�`��.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangle�ŋ�`��`��.
	
	// �y���ƃu���V�̕���
	SelectObject(hDC, hOldBrush);		// �Â��u���V��I��.
	SelectObject(hDC, hOldPen);		// �Â��y����I��.

	// �y���ƃu���V�̔j��.
	DeleteObject(hBrush);	// �u���V�̔j��.
	DeleteObject(hPen);	// �y���̔j��.

	// �`��I��.
	EndPaint(m_hWnd, &ps);	// EndPaint�ŕ`��I��.

}

// �E�B���h�E�������.
int CMainWindow::OnClose(){

	// �E�B���h�E�̏I������.
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// 0��Ԃ�.
	return 0;	// 0��Ԃ��ăE�B���h�E�����.

}
// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// �����o�̏�����.
	m_pWindowListControl = NULL;	// m_pWindowListControl��NULL�ŏ�����.
	m_pEdit = NULL;	// m_pEdit��NULL�ŏ�����.

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

	// �G�f�B�b�g�R���g���[���̍폜.
	if (m_pEdit != NULL){	// m_pEdit��NULL�łȂ���.
		m_pEdit->Destroy();	// m_pEdit->Destroy�Ŕj��.
		delete m_pEdit;	// delete��m_pEdit�����.
		m_pEdit = NULL;	// m_pEdit��NULL���Z�b�g.
	}

	// �E�B���h�E���X�g�A�C�e���̍폜.
	m_pWindowListControl->RemoveAll();	// m_pWindowListControl->RemoveAll�ŃA�C�e����S�č폜.

	// �E�B���h�E���X�g�R���g���[���̍폜.
	if (m_pWindowListControl != NULL){	// m_pWindowListControl��NULL�łȂ����.
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
	m_pWindowListControl->Create(_T(""), 0, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pWindowListControl->Create�ō쐬.

	// �E�B���h�E���X�g�A�C�e���̒ǉ�.
	m_pWindowListControl->Add(_T("Item0"), 320, 32, 64, 64, lpCreateStruct->hInstance);	// m_pWindowListControl->Add��"Item0"��ǉ�.
	m_pWindowListControl->Add(_T("Item1"), 32, 320, 64, 64, lpCreateStruct->hInstance);	// m_pWindowListControl->Add��"Item1"��ǉ�.

	// �}���`�r���[�A�C�e���̎擾.
	CWindowListItem *pItem0 = m_pWindowListControl->Get(0);	// 0�Ԗڂ��擾.
	
	// �G�f�B�b�g�R���g���[���̐���.
	m_pEdit = new CEdit();	// CEdit�I�u�W�F�N�g�𐶐�.
	m_pEdit->Create(_T("Edit"), WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 480, 100, pItem0->m_hWnd, (HMENU)WM_APP + 200, lpCreateStruct->hInstance);	// m_pEdit->Create��pItem0->m_hWnd��e�Ƃ��ăE�B���h�E�쐬.
 
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

	// ��ʍX�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

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
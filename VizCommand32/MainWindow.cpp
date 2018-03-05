// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "MainWindow.h"	// CMainWindow
#include "resource.h"		// ���\�[�X

// �R���X�g���N�^CMainWindow()
CMainWindow::CMainWindow() : CWindow(){

	// �����o�̏�����.
	m_pStreamConsole = NULL;	// m_pStreamConsole��NULL�ŏ�����.

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

	// �X�g���[���R���\�[���̍폜.
	if (m_pStreamConsole != NULL){	// m_pStreamConsole��NULL�łȂ����.

		// �E�B���h�E���X�g�A�C�e���̍폜.
		m_pStreamConsole->RemoveAll();	// m_pStreamConsole->RemoveAll�ŃA�C�e����S�č폜.

		// �X�g���[���R���\�[���̔j��.
		m_pStreamConsole->Destroy();	// m_pStreamConsole->Destroy��m_pStreamConsole�̏I�����������s.
		delete m_pStreamConsole;	// delete��m_pStreamConsole�����.
		m_pStreamConsole = NULL;	// m_pStreamConsole��NULL���Z�b�g.

	}

	// �e�E�B���h�E��Destroy���Ă�.
	CWindow::Destroy();	// CWindow::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �X�g���[���R���\�[���I�u�W�F�N�g�̍쐬.
	m_pStreamConsole = new CStreamConsole();	// CStreamConsole�I�u�W�F�N�g�̍쐬.

	// �X�g���[���R���\�[���̃E�B���h�E�쐬.
	m_pStreamConsole->Create(_T(""), 0, 0, 0, 480, 0, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pStreamConsole->Create�ō쐬.

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

	// �X�g���[���R���\�[���̃T�C�Y�̓E�B���h�E�ɂ҂����荇�킹��.
	if (m_pStreamConsole != NULL){	// NULL�łȂ����.
		MoveWindow(m_pStreamConsole->m_hWnd, m_pStreamConsole->m_x, m_pStreamConsole->m_y, cx, cy, TRUE);	// MoveWindow��m_pStreamConsole->m_hWnd�̃T�C�Y��ύX.
	}

}

// �^�C�}�[�C�x���g������������.
void CMainWindow::OnTimer(UINT_PTR nIDEvent){

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
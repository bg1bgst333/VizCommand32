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

	// �E�B���h�E�v���V�[�W���ɂ�CWindow::StaticWndowProc, ���j���[�͂Ȃ�(NULL)�Ƃ���.((LPCTSTR)�ŃL���X�g���Ȃ��ƃI�[�o�[���[�h���B���ɂȂ�.)
	return CWindow::RegisterClass(hInstance, _T("CMainWindow"), (LPCTSTR)NULL);	// CWindow::RegisterClass�œo�^.

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
	m_pWindowListControl->Create(_T(""), WS_BORDER, 0, 0, 640, 480, hwnd, (HMENU)(WM_APP + 1), lpCreateStruct->hInstance);	// m_pWindowListControl->Create�ō쐬.

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

// �E�B���h�E�������.
int CMainWindow::OnClose(){

	// �E�B���h�E�̏I������.
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// 0��Ԃ�.
	return 0;	// 0��Ԃ��ăE�B���h�E�����.

}
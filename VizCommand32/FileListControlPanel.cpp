// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "FileListControlPanel.h"	// CFileListControlPanel
#include <commctrl.h>	// �R�����R���g���[��

// �R���X�g���N�^CFileListControlPanel
CFileListControlPanel::CFileListControlPanel() : CListControlPanel(){

}

// �f�X�g���N�^~CFileListControlPanel
CFileListControlPanel::~CFileListControlPanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CFileListControlPanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CFileListControlPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CFileListControlPanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CFileListControlPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	return CUserControl::Create(_T("CFileListControlPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CFileListControlPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �e��OnCreate���Ă�.
	int iRet = CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreate���Ă�.

	// �q���X�g�R���g���[���̐���.
	m_pListControl = new CFileListControl();	// CFileListControl�I�u�W�F�N�g�𐶐���, �|�C���^��m_pListControl�Ɋi�[.
	m_pListControl->Create(_T(""), LVS_ICON, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pListControl->Create�Ŏq���X�g�R���g���[������.

	// ����X�V�^�C�}�[���Z�b�g.
	SetTimer(hwnd, 2, 100, NULL);	// SetTimer�ōX�V�^�C�}�[���Z�b�g.(100�~���b==0.1�b)

	// iRet��Ԃ�.
	return iRet;	// iRet��Ԃ�.

}

// �^�C�}�[�C�x���g������������.
void CFileListControlPanel::OnTimer(UINT_PTR nIDEvent){

	// �^�C�}�[���I��.
	KillTimer(m_hWnd, 2);	// ����X�V�^�C�}�[���I��.

	// �ЂƂ܂����b�Z�[�W�{�b�N�X��\��.
	MessageBox(m_hWnd, _T("CFileListControlPanel::OnTimer"), _T("VizCommand"), MB_OK);	// MessageBox��"CFileListControlPanel::OnTimer".

}
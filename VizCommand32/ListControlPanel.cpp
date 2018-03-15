// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ListControlPanel.h"	// CListControlPanel
#include <commctrl.h>	// �R�����R���g���[��

// �R���X�g���N�^CListControlPanel
CListControlPanel::CListControlPanel() : CUserControl(){

	// �����o�ϐ��̏�����.
	m_pListControl = NULL;	// m_pListControl��NULL�ŏ�����.
	m_nId = 0;	// m_nId��0�ŏ�����.

}

// �f�X�g���N�^~CListControlPanel
CListControlPanel::~CListControlPanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CListControlPanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CListControlPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CListControlPanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CListControlPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	return CUserControl::Create(_T("CListControlPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CListControlPanel::Destroy(){

	// ���X�g�R���g���[���̔j��.
	if (m_pListControl != NULL){	// m_pListControl��NULL�łȂ����.
		m_pListControl->Destroy();	// m_pListControl->Destroy�Ŕj��.
		delete m_pListControl;	// delete��m_pListControl�����.
		m_pListControl = NULL;	// m_pListControl��NULL���Z�b�g.
	}

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CListControlPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �q���X�g�R���g���[���̐���.
	m_pListControl = new CListControl();	// CListControl�I�u�W�F�N�g�𐶐���, �|�C���^��m_pListControl�Ɋi�[.
	m_pListControl->Create(_T(""), LVS_ICON, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pListControl->Create�Ŏq���X�g�R���g���[������.

	// �e��OnCreate���Ă�.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreate���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CListControlPanel::OnSize(UINT nType, int cx, int cy){

	// �e��OnSize���Ă�.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �q���X�g�R���g���[���̃��T�C�Y.
	if (m_pListControl != NULL){	// m_pListControl��NULL�łȂ���.
		MoveWindow(m_pListControl->m_hWnd, m_pListControl->m_x, m_pListControl->m_y, cx, cy, TRUE);	// MoveWindow�Ń��T�C�Y.
	}

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}

// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
void CListControlPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// �T�C�Y���o��.
	int iWidth = LOWORD(wParam);	// LOWORD��iWidth.
	int iHeight = HIWORD(wParam);	// HIWORD��iHeight.

	// �T�C�Y�Z�b�g.
	m_iWidth = iWidth;	// m_iWidth��iWidth���Z�b�g.
	m_iHeight = iHeight;	// m_iHeight��iHeight���Z�b�g.

	// ���g�̃E�B���h�E�T�C�Y�ύX.
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iHeight, TRUE);	// MoveWindow�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.

}
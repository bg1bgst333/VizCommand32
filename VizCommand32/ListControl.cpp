// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ListControl.h"	// CListControl

// �R���X�g���N�^CListControl
CListControl::CListControl() : CCustomControl(){

}

// �f�X�g���N�^~CListControl
CListControl::~CListControl(){

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CListControl::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�N���X����"SysListView32"�ȃJ�X�^���R���g���[�����쐬.
	return CCustomControl::Create(_T("SysListView32"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Create�Ń��X�g�R���g���[�����쐬.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CListControl::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(hwnd), UM_SIZECHILD, wParam, (LPARAM)hwnd);	// SendMessage��UM_SIZECHILD�𑗐M.

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return CCustomControl::OnCreate(hwnd, lpCreateStruct);	// CCustomControl::OnCreate���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CListControl::OnSize(UINT nType, int cx, int cy){

	// �e�N���X��OnSize.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSize���Ă�.

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}
// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ListControl.h"	// CListControl

// �R���X�g���N�^CListControl
CListControl::CListControl() : CCustomControl(){

	// �����o�̏�����.
	m_hImageList = NULL;	// m_hImageList��NULL�ŏ�����.

}

// �f�X�g���N�^~CListControl
CListControl::~CListControl(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CListControl::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�N���X����"SysListView32"�ȃJ�X�^���R���g���[�����쐬.
	BOOL bRet = CCustomControl::Create(_T("SysListView32"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Create�Ń��X�g�R���g���[�����쐬.

	// �C���[�W���X�g�̍쐬.
	m_hImageList = ImageList_Create(32, 32, ILC_COLOR24, 24, 0);	// ImageList_Create�ō쐬.

	// �������������s����Ԃ�.
	return bRet;	// bRet��Ԃ�.

}

// �C���[�W���X�g�̃Z�b�gSetImageList.
void CListControl::SetImageList(int nImageListType){

	// �C���[�W���X�g�̃Z�b�g.
	ListView_SetImageList(m_hWnd, m_hImageList, nImageListType);	// ListView_SetImageList�ŃC���[�W���X�g���Z�b�g.

}

// �C���[�W���X�g�ɃA�C�R����ǉ�����AddIcon.
int CListControl::AddIcon(HICON hIcon){

	// �A�C�R���̒ǉ�.
	return ImageList_AddIcon(m_hImageList, hIcon);	// ImageList_AddIcon�ŃA�C�R����ǉ�.

}

// ���X�g�R���g���[���ɃA�C�e����ǉ�InsertItem.
int CListControl::InsertItem(LPLVITEM pItem){

	// �A�C�e���̒ǉ�.
	return ListView_InsertItem(m_hWnd, pItem);	// ListView_InsertItem��pItem��ǉ�.

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

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CListControl::Destroy(){

	// �C���[�W���X�g�̔j��.
	if (m_hImageList != NULL){	// m_hImageList��NULL�łȂ���.
		ImageList_Destroy(m_hImageList);	// ImageList_Destroy�Ŕj��.
		m_hImageList = NULL;	// m_hImageList��NULL���Z�b�g.
	}

	// �e�N���X��Destroy.
	CCustomControl::Destroy();	// CCustomControl::Destroy���Ă�.

}
// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "PicturePanel.h"	// CPicturePanel

// �R���X�g���N�^CPicturePanel
CPicturePanel::CPicturePanel() : CUserControl(){

	// �����o�ϐ��̏�����.
	m_pPicture = NULL;	// m_pPicture��NULL�ŏ�����.
	m_nId = 0;	// m_nId��0�ŏ�����.

}

// �f�X�g���N�^~CPicturePanel
CPicturePanel::~CPicturePanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CPicturePanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CPicturePanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CPicturePanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CPicturePanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	return CUserControl::Create(_T("CPicturePanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CPicturePanel::Destroy(){

	// �s�N�`���[�R���g���[���̔j��.
	if (m_pPicture != NULL){	// m_pPicture��NULL�łȂ����.
		m_pPicture->Destroy();	// m_pPicture->Destroy�Ŕj��.
		delete m_pPicture;	// delete��m_pPicture�����.
		m_pPicture = NULL;	// m_pPicture��NULL���Z�b�g.
	}

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CPicturePanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �q�s�N�`���[�R���g���[���̐���.
	m_pPicture = new CPicture();	// CPicture�I�u�W�F�N�g�𐶐���, �|�C���^��m_pPicture�Ɋi�[.
	m_pPicture->Create(_T(""), 0, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pPicture->Create�Ŏq�s�N�`���[�R���g���[������.

	// �e��OnCreate���Ă�.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreate���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CPicturePanel::OnSize(UINT nType, int cx, int cy){

	// �e��OnSize���Ă�.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �q�s�N�`���[�R���g���[���̃��T�C�Y.
	if (m_pPicture != NULL){	// m_pPicture��NULL�łȂ���.
		MoveWindow(m_pPicture->m_hWnd, m_pPicture->m_x, m_pPicture->m_y, cx, cy, TRUE);	// MoveWindow�Ń��T�C�Y.
	}

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

	// �X�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

}

// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
void CPicturePanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// �T�C�Y���o��.
	int iWidth = LOWORD(wParam);	// LOWORD��iWidth.
	int iHeight = HIWORD(wParam);	// HIWORD��iHeight.

	// �T�C�Y�Z�b�g.
	m_iWidth = iWidth;	// m_iWidth��iWidth���Z�b�g.
	m_iHeight = iHeight;	// m_iHeight��iHeight���Z�b�g.

	// ���g�̃E�B���h�E�T�C�Y�ύX.
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iHeight, TRUE);	// MoveWindow�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.

}
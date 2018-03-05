// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ScalableEditPanel.h"	// CScalableEditPanel

// �R���X�g���N�^CScalableEditPanel
CScalableEditPanel::CScalableEditPanel() : CUserControl(){

	// �����o�ϐ��̏�����.
	m_pScalableEdit = NULL;	// m_pScalableEdit��NULL�ŏ�����.
	m_nId = 0;	// m_nId��0�ŏ�����.

}

// �f�X�g���N�^~CScalableEditPanel
CScalableEditPanel::~CScalableEditPanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CScalableEditPanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CScalableEditPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CScalableEditPanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CScalableEditPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	BOOL bRet = CUserControl::Create(_T("CScalableEditPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

	// ����.
	if (bRet){	// bRet��TRUE.

		// �q�X�J���u���G�f�B�b�g�R���g���[���̐���.
		m_pScalableEdit = new CScalableEdit();	// CScalableEdit�I�u�W�F�N�g�𐶐���, �|�C���^��m_pScalableEdit�Ɋi�[.
		BOOL bRet2 = m_pScalableEdit->Create(_T(""), ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, m_hWnd, m_nId + 100, hInstance);	// m_pScalableEdit->Create�Ŏq�X�J���u���G�f�B�b�g�R���g���[������.
		if (bRet2){	// bRet2��TRUE.
			// ���T�C�Y.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_pScalableEdit->m_iHeight, TRUE);	// MoveWindow��m_pScalableEdit->m_iHeight�̍����Ƀ��T�C�Y.
		}

	}

	// �߂�l��Ԃ�.
	return bRet;	// bRet��Ԃ�.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CScalableEditPanel::Destroy(){

	// �X�J���u���G�f�B�b�g�R���g���[���̔j��.
	if (m_pScalableEdit != NULL){	// m_pScalableEdit��NULL�łȂ����.
		m_pScalableEdit->Destroy();	// m_pScalableEdit->Destroy�Ŕj��.
		delete m_pScalableEdit;	// delete��m_pScalableEdit�����.
		m_pScalableEdit = NULL;	// m_pScalableEdit��NULL���Z�b�g.
	}

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CScalableEditPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �e��OnCreate���Ă�.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreate���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CScalableEditPanel::OnSize(UINT nType, int cx, int cy){

	// �e��OnSize���Ă�.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}

// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
void CScalableEditPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// �T�C�Y���o��.
	int iWidth = LOWORD(wParam);	// LOWORD��iWidth.
	int iHeight = HIWORD(wParam);	// HIWORD��iHeight.

	// �T�C�Y�Z�b�g.
	m_iWidth = iWidth;	// m_iWidth��iWidth���Z�b�g.
	m_iHeight = iHeight;	// m_iHeight��iHeight���Z�b�g.

	// ���g�̃E�B���h�E�T�C�Y�ύX.
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iHeight, TRUE);	// MoveWindow�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.

}
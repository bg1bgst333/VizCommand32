// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "EditPanel.h"	// CEditPanel

// �R���X�g���N�^CEditPanel
CEditPanel::CEditPanel() : CUserControl(){

	// �����o�ϐ��̏�����.
	m_pEdit = NULL;	// m_pEdit��NULL�ŏ�����.
	m_nId = 0;	// m_nId��0�ŏ�����.

}

// �f�X�g���N�^~CEditPanel
CEditPanel::~CEditPanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CEditPanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CEditPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CEditPanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CEditPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	return CUserControl::Create(_T("CEditPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CEditPanel::Destroy(){

	// �G�f�B�b�g�R���g���[���̔j��.
	if (m_pEdit != NULL){	// m_pEdit��NULL�łȂ����.
		m_pEdit->Destroy();	// m_pEdit->Destroy�Ŕj��.
		delete m_pEdit;	// delete��m_pEdit�����.
		m_pEdit = NULL;	// m_pEdit��NULL���Z�b�g.
	}

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CEditPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �q�G�f�B�b�g�R���g���[���̐���.
	m_pEdit = new CEdit();	// CEdit�I�u�W�F�N�g�𐶐���, �|�C���^��m_pEdit�Ɋi�[.
	m_pEdit->Create(_T(""), ES_MULTILINE | ES_WANTRETURN | ES_AUTOHSCROLL | ES_AUTOVSCROLL, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pEdit->Create�Ŏq�G�f�B�b�g�R���g���[������.

	// �e��OnCreate���Ă�.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreate���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CEditPanel::OnSize(UINT nType, int cx, int cy){

	// �e��OnSize���Ă�.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �q�G�f�B�b�g�R���g���[���̃��T�C�Y.
	if (m_pEdit != NULL){	// m_pEdit��NULL�łȂ���.
		MoveWindow(m_pEdit->m_hWnd, m_pEdit->m_x, m_pEdit->m_y, cx, cy, TRUE);	// MoveWindow�Ń��T�C�Y.
	}

}
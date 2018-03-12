// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "StaticPanel.h"	// CStaticPanel

// �R���X�g���N�^CStaticPanel
CStaticPanel::CStaticPanel() : CUserControl(){

	// �����o�ϐ��̏�����.
	m_pStatic = NULL;	// m_pStatic��NULL�ŏ�����.
	m_nId = 0;	// m_nId��0�ŏ�����.
	m_hbrBackground = NULL;	// m_hbrBackground��NULL�ŏ�����.
	m_hFont = NULL;	// m_hFont��NULL�ŏ�����.

}

// �f�X�g���N�^~CStaticPanel
CStaticPanel::~CStaticPanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CStaticPanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CStaticPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CStaticPanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CStaticPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	BOOL bRet = CUserControl::Create(_T("CStaticPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

	// �Z�΃u���V�쐬.
	m_hbrBackground = CreateSolidBrush(RGB(0x0, 0x7f, 0x0));	// CreateSolidBrush�ŔZ�΃u���V���쐬��, m_hbrBackground�Ɋi�[.

	// �t�H���g�̐���.
	m_hFont = CreateFont(32, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("�l�r ����"));	// CreateFont��"�l�r ����"�t�H���g��GDI�I�u�W�F�N�g��V�K�ɍ쐬��, hFont�Ɋi�[.(�ݒ�̓f�t�H���g�̂��̂ɂ��Ă���.)

	// Create�̖߂�l��Ԃ�.
	return bRet;	// bRet��Ԃ�.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CStaticPanel::Destroy(){

	// �t�H���g�̔j��.
	if (m_hFont != NULL){	// m_hFont��NULL�łȂ���.
		DeleteObject(m_hFont);	// DeleteObject�ō폜.
		m_hFont = NULL;	// m_hFont��NULL���Z�b�g.
	}

	// �u���V�̔j��.
	if (m_hbrBackground != NULL){	// m_hbrBackground��NULL�łȂ���.
		DeleteObject(m_hbrBackground);	// DeleteObject�ō폜.
		m_hbrBackground = NULL;	// m_hbrBackground��NULL���Z�b�g.
	}

	// �X�^�e�B�b�N�R���g���[���̔j��.
	if (m_pStatic != NULL){	// m_pStatic��NULL�łȂ����.
		m_pStatic->Destroy();	// m_pStatic->Destroy�Ŕj��.
		delete m_pStatic;	// delete��m_pStatic�����.
		m_pStatic = NULL;	// m_pStatic��NULL���Z�b�g.
	}

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CStaticPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �q�G�X�^�e�B�b�N�R���g���[���̐���.
	m_pStatic = new CStatic();	// CStatic�I�u�W�F�N�g�𐶐���, �|�C���^��m_pStatic�Ɋi�[.
	m_pStatic->Create(_T(""), SS_REALSIZECONTROL | SS_CENTER, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, hwnd, m_nId + 100, lpCreateStruct->hInstance);	// m_pStatic->Create�Ŏq�X�^�e�B�b�N�R���g���[������.

	// �e��OnCreate���Ă�.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreate���Ă�.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CStaticPanel::OnSize(UINT nType, int cx, int cy){

	// �e��OnSize���Ă�.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �q�X�^�e�B�b�N�R���g���[���̃��T�C�Y.
	if (m_pStatic != NULL){	// m_pStatic��NULL�łȂ���.
		MoveWindow(m_pStatic->m_hWnd, m_pStatic->m_x, m_pStatic->m_y, cx, cy, TRUE);	// MoveWindow�Ń��T�C�Y.
	}

}

// �q�X�^�e�B�b�N�R���g���[���̕`�掞.
HBRUSH CStaticPanel::OnCtlColorStatic(HDC hDC, HWND hStatic){

	// �w�i��Z��, �e�L�X�g�𔒂ɂ���.
	SetBkColor(hDC, RGB(0x0, 0x7f, 0x0));	// �w�i�͔Z��.
	SetTextColor(hDC, RGB(0xff, 0xff, 0xff));	// �e�L�X�g�͔�.
	SendMessage(m_pStatic->m_hWnd, WM_SETFONT, (WPARAM)m_hFont, MAKELPARAM(FALSE, 0));	// WM_SETFONT�Ńt�H���g���Z�b�g.
	return m_hbrBackground;	// m_hbrBackground��Ԃ�.

}
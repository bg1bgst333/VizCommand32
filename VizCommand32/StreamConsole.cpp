// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "StreamConsole.h"	// �X�g���[���R���\�[���N���X

// �R���X�g���N�^CStreamConsole
CStreamConsole::CStreamConsole() : CWindowListControl(){

}

// �f�X�g���N�^~CStreamConsole
CStreamConsole::~CStreamConsole(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CStreamConsole::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CStreamConsole::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CStreamConsole"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CStreamConsole::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	return CUserControl::Create(_T("CStreamConsole"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�쐬���̃n���h��OnCreate.
int CStreamConsole::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �e�E�B���h�E��OnCreate���Ă�.
	int iRet = CWindowListControl::OnCreate(hwnd, lpCreateStruct);	// CWindowListControl::OnCreate��Ԃ�.
	
	// �f�t�H���g�A�C�e���̑}��.
	Insert(0, _T("0"), 80, lpCreateStruct->hInstance);	// Insert��0�Ԗڂ̃A�C�e����}��.

	// �߂�l��Ԃ�.
	return iRet;	// iRet��Ԃ�.

}
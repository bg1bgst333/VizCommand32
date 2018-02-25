// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "WindowListItem.h"	// CWindowListItem

// �R���X�g���N�^CWindowListItem
CWindowListItem::CWindowListItem() : CUserControl(){

	// �����o�̏�����.
	m_mapChildMap.clear();	// m_mapChildMap���N���A.

}

// �f�X�g���N�^~CWindowListItem
CWindowListItem::~CWindowListItem(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CWindowListItem::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CWindowListItem::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CWindowListItem"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CWindowListItem::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	return CUserControl::Create(_T("CWindowListItem"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CWindowListItem::Destroy(){

	// �A�C�e���̈�č폜
	std::map<tstring, CWindow *>::iterator itor = m_mapChildMap.begin();	// �C�e���[�^.
	while (itor != m_mapChildMap.end()) {	// �}�b�v�̍Ō�܂�.
		if (itor->second != NULL) {	// �l��NULL�łȂ����.
			itor->second->Destroy();	// Destroy�Ŕj������.
			delete itor->second;	// ���.
			itor->second = NULL;	// NULL���Z�b�g.
		}
		itor++;	// �i��.
	}
	m_mapChildMap.clear();	// �N���A.

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CWindowListItem::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �e��OnCreate���Ă�.
	int iResult = CUserControl::OnCreate(hwnd, lpCreateStruct);	// CUserControl::OnCreate��Ԃ�.

	// �A�C�e���Y�p�l���ɍ������C������悤�ɗv��.
	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	PostMessage(GetParent(hwnd), UM_SIZECHILD, wParam, (LPARAM)hwnd);	// SendMessage��UM_SIZECHILD�𑗐M.

	// iResult��Ԃ�.
	return iResult;	// return��iResult��Ԃ�.

}

// �E�B���h�E���j�����ꂽ��.
void CWindowListItem::OnDestroy(){

	// �����o�̏I������
	//Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// �e�N���X��OnDestroy���Ă�.
	CUserControl::OnDestroy();	// CUserControl::OnDestroy���Ă�.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CWindowListItem::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HPEN hPen = NULL;	// hPen��NULL�ŏ�����.
	HBRUSH hBrush = NULL;	// hBrush��NULL�ŏ�����.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

	// �y���ƃu���V�̐���.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0xff));	// CreatePen�Ŏ�(�W)�̃y�����쐬.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0x7f, 0, 0x7f));		// CreateSolidBrush�Ŏ�(�Z)�̃u���V���쐬.

	// �y���ƃu���V�̑I��.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// ���̃y����I��.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// ���̃u���V��I��.

	// ��`�`��.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangle�ŋ�`��`��.
	
	// �E�B���h�E���̕\��.
	TextOut(hDC, 0, 0, GetText().c_str(), GetTextLength());	// TextOut�ŃE�B���h�E����`��.

	// �y���ƃu���V�̕���
	SelectObject(hDC, hOldBrush);		// �Â��u���V��I��.
	SelectObject(hDC, hOldPen);		// �Â��y����I��.

	// �y���ƃu���V�̔j��.
	DeleteObject(hBrush);	// �u���V�̔j��.
	DeleteObject(hPen);	// �y���̔j��.

	// �`��I��.
	EndPaint(m_hWnd, &ps);	// EndPaint�ŕ`��I��.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CWindowListItem::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E�̊��菈��.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}

// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
void CWindowListItem::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// �T�C�Y���o��.
	int iWidth = LOWORD(wParam);	// LOWORD��iWidth.
	int iHeight = HIWORD(wParam);	// HIWORD��iHeight.

	// �T�C�Y�Z�b�g.
	m_iWidth = iWidth;	// m_iWidth��iWidth���Z�b�g.
	m_iHeight = iHeight;	// m_iHeight��iHeight���Z�b�g.

	// ���g�̃E�B���h�E�T�C�Y�ύX.
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iHeight, TRUE);	// MoveWindow�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.

}
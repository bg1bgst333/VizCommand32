// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "WindowListItemsPanel.h"	// CWindowListItemsPanel

// �R���X�g���N�^CWindowListItemsPanel
CWindowListItemsPanel::CWindowListItemsPanel() : CUserControl(){

	// �����o�̏�����.
	m_vecWindowListItem.clear();	// m_vecWindowListItem.clear�ŃN���A.
	m_nNextId = 0;	// m_nNextId��0�ŏ�����.

}

// �f�X�g���N�^~CWindowListItemsPanel
CWindowListItemsPanel::~CWindowListItemsPanel(){

	// �����o�̏I������
	Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CWindowListItemsPanel::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(LTGRAY_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CWindowListItemsPanel::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CWindowListItemsPanel"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CWindowListItemsPanel::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	return CUserControl::Create(_T("CWindowListItemsPanel"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CWindow::Create�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CWindowListItemsPanel::Destroy(){

	// �E�B���h�E���X�g�A�C�e�����X�g�̏I������.
	m_vecWindowListItem.clear();	// m_vecWindowListItem.clear�ŃN���A.
	m_nNextId = 0;	// m_nNextId��0���Z�b�g.

	// �e�E�B���h�E��Destroy���Ă�.
	CUserControl::Destroy();	// CUserControl::Destroy���Ă�.

}

// �A�C�e���𖖔�����ǉ�����֐�Add.
void CWindowListItemsPanel::Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	// �E�B���h�E���X�g�A�C�e���̒ǉ�.
	CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItem�I�u�W�F�N�g�𐶐���, �|�C���^��pWindowListItem�Ɋi�[.
	pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, x, y, iWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Create�ŃA�C�e���쐬.
	m_vecWindowListItem.push_back(pWindowListItem);	// m_vecWindowListItem.push_back�Ŗ����ɒǉ�.
	m_nNextId++;	// m_nNextId���C���N�������g.

}

// �A�C�e���𖖔�����폜����֐�Remove.
void CWindowListItemsPanel::Remove(){

	// �E�B���h�E���X�g�A�C�e���̍폜.
	CWindowListItem *pWindowListItem = m_vecWindowListItem[m_vecWindowListItem.size() - 1];	// �����v�f���擾.
	delete pWindowListItem;	// delete��pWindowListItem�̍폜.
	m_vecWindowListItem.pop_back();	// m_vecWindowListItem.pop_back�Ń��X�g��1���炷.
	m_nNextId--;

}

// �A�C�e�����擾����֐�Get.
CWindowListItem * CWindowListItemsPanel::Get(int iIndex){

	// iIndex�Ԗڂ̗v�f��Ԃ�.
	return m_vecWindowListItem[iIndex];	// m_vecWindowListItem[iIndex]��Ԃ�.

}

// �S�ẴA�C�e�����폜����֐�RemoveAll.
void CWindowListItemsPanel::RemoveAll(){

	// �A�C�e���̐������J��Ԃ�.
	size_t n = GetSize();	// GetSize�ŃT�C�Y���擾��, n�Ɋi�[.
	for (size_t i = 0; i < n; i++){	// n�̐������J��Ԃ�.
		Remove();	// Remove�Ŗ������폜.
	}

}

// �A�C�e���̐���Ԃ��֐�GetSize.
size_t CWindowListItemsPanel::GetSize(){

	// �A�C�e���̗v�f����Ԃ�.
	return m_vecWindowListItem.size();	// m_vecWindowListItem.size�ŗv�f����Ԃ�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CWindowListItemsPanel::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// ��ɃE�B���h�E�쐬�ɐ���������̂Ƃ���.
	return 0;	// 0��Ԃ���, �E�B���h�E�쐬�ɐ��������Ƃ������ƂɂȂ�.

}

// �E�B���h�E���j�����ꂽ��.
void CWindowListItemsPanel::OnDestroy(){

	// �����o�̏I������
	//Destroy();	// Destroy�ł��̃E�B���h�E�̏I������������.

	// �e�N���X��OnDestroy���Ă�.
	CUserControl::OnDestroy();	// CUserControl::OnDestroy���Ă�.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CWindowListItemsPanel::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HPEN hPen = NULL;	// hPen��NULL�ŏ�����.
	HBRUSH hBrush = NULL;	// hBrush��NULL�ŏ�����.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

	// �y���ƃu���V�̐���.
	hPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0xff, 0, 0));	// CreatePen�Ő�(�W)�̃y�����쐬.
	hBrush = (HBRUSH)CreateSolidBrush(RGB(0x7f, 0, 0));		// CreateSolidBrush�Ő�(�Z)�̃u���V���쐬.

	// �y���ƃu���V�̑I��.
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);		// �Ԃ̃y����I��.
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);	// �Ԃ̃u���V��I��.

	// ��`�`��.
	Rectangle(hDC, 0, 0, m_iClientAreaWidth, m_iClientAreaHeight);	// Rectangle�ŋ�`��`��.
	
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
void CWindowListItemsPanel::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E�̊��菈��.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

}

// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
void CWindowListItemsPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// �T�C�Y���o��.
	int iWidth = LOWORD(wParam);	// LOWORD��iWidth.
	int iHeight = HIWORD(wParam);	// HIWORD��iHeight.
	HWND hSrc = (HWND)lParam;	// lParam��HWND�ɃL���X�g����, hSrc�Ɋi�[.

	// �E�B���h�E�}�b�v����E�B���h�E�I�u�W�F�N�g�擾.
	CWindow *pWindow = m_mapWindowMap[hSrc];	// m_mapWindowMap[hSrc]����pWindow���擾.
	
	// �E�[, ���[���擾.
	int w = pWindow->m_x + pWindow->m_iWidth;	// �擾�����E�B���h�E�̉E�[���擾.
	int h = pWindow->m_y + pWindow->m_iHeight;	// �擾�����E�B���h�E�̉��[���擾.

	// �p�l����������������g��.
	if (m_iWidth < w){	// w���傫��.
		MoveWindow(m_hWnd, m_x, m_y, w, m_iHeight, TRUE);	// MoveWindow�ŉ���w�̑傫���Ɋg��.
	}
	if (m_iHeight < h){	// h���傫��.
		MoveWindow(m_hWnd, m_x, m_y, m_iWidth, h, TRUE);	// MoveWindow�ŏc��h�̑傫���Ɋg��.
	}

}
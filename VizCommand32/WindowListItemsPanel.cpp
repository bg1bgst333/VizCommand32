// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "WindowListItemsPanel.h"	// CWindowListItemsPanel

// �R���X�g���N�^CWindowListItemsPanel
CWindowListItemsPanel::CWindowListItemsPanel() : CUserControl(){

	// �����o�̏�����.
	m_vecWindowListItem.clear();	// m_vecWindowListItem.clear�ŃN���A.
	m_nNextId = 0;	// m_nNextId��0�ŏ�����.
	m_iTotalHeight = 0;	// m_iTotalHeight��0�ŏ�����.

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

// �A�C�e���𖖔�����ǉ�����֐�Add.
void CWindowListItemsPanel::Add(LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance){

	// �E�B���h�E���X�g�A�C�e���̒ǉ�.
	CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItem�I�u�W�F�N�g�𐶐���, �|�C���^��pWindowListItem�Ɋi�[.
	pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, m_iTotalHeight, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Create�ŃA�C�e���쐬.
	m_vecWindowListItem.push_back(pWindowListItem);	// m_vecWindowListItem.push_back�Ŗ����ɒǉ�.
	m_iTotalHeight += iHeight;	// m_iTotalHeight��iHeight�𑫂�.
	m_nNextId++;	// m_nNextId���C���N�������g.

}

// �A�C�e�����w��̏ꏊ�ɑ}������֐�Insert.
void CWindowListItemsPanel::Insert(int iIndex, LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance){

	// iIndex�̒l��m_vecWindowListItem�̗v�f���ŐU�蕪����.
	int iIdx = 0;	// int�^iIdx��0�ŏ�����.
	int iInsertPosY;	// int�^iInsertPosY��0�ŏ�����.
	if (m_vecWindowListItem.size() == 0){	// �v�f����0.
		iIdx = 0;	// iIdx��0�Ƃ���.
		iInsertPosY = 0;	// iInsertPosY��0�Ƃ��Ĉ�ԏ�ɔz�u.
	}
	else{	// �v�f����1�ȏ�.
		if (iIndex < 0){	// �C���f�b�N�X�����̐�.
			iIdx = 0;	// iIdx��0�Ƃ���.
			iInsertPosY = 0;	// iInsertPosY��0�Ƃ��Ĉ�ԏ�ɔz�u.
		}
		else if (iIndex >= m_vecWindowListItem.size()){	// �C���f�b�N�X���v�f���ȏ�.
			iIdx = m_vecWindowListItem.size();	// iIdx��m_vecWindowListItem.size�̒l�Ƃ���.
			iInsertPosY = m_iTotalHeight;	// iInsertPosY��m_iTotalHeight.
		}
		else{
			iIdx = iIndex;	// iIndex�̒l����.
			iInsertPosY = m_vecWindowListItem[iIdx]->m_y;	// ���݂�iIdx�Ԗڂ�Y���W.
		}
	}

	// �I�u�W�F�N�g�쐬.
	CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItem�I�u�W�F�N�g�𐶐���, �|�C���^��pWindowListItem�Ɋi�[.
	
	// �E�B���h�E�쐬.
	pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, iInsertPosY, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Create�ŃA�C�e���쐬.

	// �x�N�^�}��.
	m_vecWindowListItem.insert(m_vecWindowListItem.begin() + iIdx, pWindowListItem);	// m_vecWindowListItem.insert��iIdx�Ԗڂ�pWindowListItem��ǉ�.

	// ���̗v�f�����炷.
	if (iIdx != m_vecWindowListItem.size()){	// �����ł͂Ȃ���.
		for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin() + iIdx + 1; itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItem��iIdx + 1�Ԗڂ���Ō�܂ŌJ��Ԃ�.
			MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*itor)->m_y + iHeight, (*itor)->m_iWidth, (*itor)->m_iHeight, TRUE);	// MoveWindow��iHeight�����炷.
		}
	}

	// ���ւ̏���.
	m_iTotalHeight += iHeight;	// m_iTotalHeight��iHeight�𑫂�.
	m_nNextId++;	// m_nNextId���C���N�������g.

	// �T�C�Y�ύX.
	if (m_hWnd != NULL){	// m_hWnd��NULL�łȂ���.
		MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iTotalHeight, TRUE);	// MoveWindow�ŃA�C�e���Y�p�l�����g��.
	}
#if 0
	// iIndex�̒l�œ����U�蕪����.
	if (iIndex == 0){	// 0�̏ꍇ.
		CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItem�I�u�W�F�N�g�𐶐���, �|�C���^��pWindowListItem�Ɋi�[.
		pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, 0, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Create�ŃA�C�e���쐬.
		m_vecWindowListItem.insert(m_vecWindowListItem.begin() + 0, pWindowListItem);	// m_vecWindowListItem.insert��0�Ԗڂ�pWindowListItem��ǉ�.
		for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin() + 1; itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItem��1�Ԗڂ���Ō�܂ŌJ��Ԃ�.
			MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*itor)->m_y + iHeight, (*itor)->m_iWidth, (*itor)->m_iHeight, TRUE);	// MoveWindow��iHeight�����炷.
		}
	}
	else if (iIndex == m_vecWindowListItem.size()){	// �x�N�^�̗v�f���Ɠ����ꍇ.(�܂��ԍŌ�.)
		CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItem�I�u�W�F�N�g�𐶐���, �|�C���^��pWindowListItem�Ɋi�[.
		pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, m_iTotalHeight, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Create�ŃA�C�e���쐬.(�}���ʒu��m_iTotalHeight.)
		m_vecWindowListItem.insert(m_vecWindowListItem.begin() + iIndex, pWindowListItem);	// m_vecWindowListItem.insert��iIndex�Ԗڂ�pWindowListItem��ǉ�.
	}
	else{	// 0�Ɨv�f���̊Ԃ̏ꍇ.
		CWindowListItem *pWindowListItem = new CWindowListItem();	// CWindowListItem�I�u�W�F�N�g�𐶐���, �|�C���^��pWindowListItem�Ɋi�[.
		pWindowListItem->Create(lpctszWindowName, WS_CHILD | WS_VISIBLE, 0, m_vecWindowListItem[iIndex]->m_y, m_iClientAreaWidth, iHeight, m_hWnd, (HMENU)(WINDOW_LIST_ITEM_ID_START + m_nNextId), hInstance);	// pWindowListItem->Create�ŃA�C�e���쐬.(�}���ʒu��m_vecWindowListItem[iIndex]->m_y.)
		m_vecWindowListItem.insert(m_vecWindowListItem.begin() + iIndex, pWindowListItem);	// m_vecWindowListItem.insert��iIndex�Ԗڂ�pWindowListItem��ǉ�.
		for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin() + iIndex + 1; itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItem��iIndex + 1�Ԗڂ���Ō�܂ŌJ��Ԃ�.
			MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*itor)->m_y + iHeight, (*itor)->m_iWidth, (*itor)->m_iHeight, TRUE);	// MoveWindow��iHeight�����炷.
		}
	}
#endif

}

// �A�C�e���𖖔�����폜����֐�Remove.
void CWindowListItemsPanel::Remove(){

	// �E�B���h�E���X�g�A�C�e���̍폜.
	CWindowListItem *pWindowListItem = m_vecWindowListItem[m_vecWindowListItem.size() - 1];	// �����v�f���擾.
	delete pWindowListItem;	// delete��pWindowListItem�̍폜.
	m_vecWindowListItem.pop_back();	// m_vecWindowListItem.pop_back�Ń��X�g��1���炷.
	m_nNextId--;

}

// �w��̏ꏊ�̃A�C�e�����폜����֐�Delete.
void CWindowListItemsPanel::Delete(int iIndex){

	// iIndex�̒l��m_vecWindowListItem�̗v�f���ŐU�蕪����.
	int iIdx = 0;	// int�^iIdx��0�ŏ�����.
	if (m_vecWindowListItem.size() == 0){	// �v�f����0�Ȃ�.
		return;	// �����ŏI��.
	}
	else if (iIndex < 0){	// iIndex�����̒l.
		iIdx = 0;	// iIdx��0�Ƃ���.
	}
	else if (iIndex > m_vecWindowListItem.size() - 1){	// iIndex���v�f�ԍ��𒴂���.
		iIdx = m_vecWindowListItem.size() - 1;	// iIdx���Ō�̗v�f�ԍ��Ƃ���.
	}
	else{	// ����ȊO.
		iIdx = iIndex;	// iIdx��iIndex�̒l�Ƃ���.
	}

	// �x�N�^����폜.
	int iHeight = 0;	// ���炷����.
	std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin() + iIdx;	// itor��iIdx�Ԗ�.
	if ((*itor) != NULL){	// NULL�łȂ���.
		iHeight = (*itor)->m_iHeight;	// iHeight��m_iHeight���Z�b�g.
		(*itor)->Destroy();	// (*itor)->Destroy�Ŕj��.
		delete (*itor);	// delete��(*itor)���폜.
		(*itor) = NULL;	// NULL���Z�b�g.
		m_vecWindowListItem.erase(itor);	// itor�̎w���v�f���폜.
		// �A�C�e�������炷.
		for (std::vector<CWindowListItem *>::iterator itor2 = m_vecWindowListItem.begin() + iIdx; itor2 != m_vecWindowListItem.end(); itor2++){	// �V����iIdx�Ԗڂ���Ō�܂ŌJ��Ԃ�.
			MoveWindow((*itor2)->m_hWnd, (*itor2)->m_x, (*itor2)->m_y - iHeight, (*itor2)->m_iWidth, (*itor2)->m_iHeight, TRUE);	// MoveWindow�ŏ�ɂ��炷.
		}
		// ���ւ̏���.
		m_iTotalHeight -= iHeight;	// m_iTotalHeight����iHeight������.
		// �T�C�Y�ύX.
		if (m_hWnd != NULL){	// m_hWnd��NULL�łȂ���.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iTotalHeight, TRUE);	// MoveWindow�ŃA�C�e���Y�p�l�����g��.
		}
	}

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

	// �e��OnCreate���Ă�.
	return CUserControl::OnCreate(hwnd, lpCreateStruct);

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

#if 0
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
#endif

	// �`��I��.
	EndPaint(m_hWnd, &ps);	// EndPaint�ŕ`��I��.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CWindowListItemsPanel::OnSize(UINT nType, int cx, int cy){

	// �e�E�B���h�E�̊��菈��.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �e�E�B���h�E���X�g�A�C�e���̕����E�ɍ��킹��.
	for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin(); itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItem�̗v�f���J��Ԃ�.
		MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*itor)->m_y, cx, (*itor)->m_iHeight, TRUE);	// ������cx�ɂ���.
	}

}

// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
void CWindowListItemsPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// �T�C�Y���o��.
	int iWidth = LOWORD(wParam);	// LOWORD��iWidth.
	int iHeight = HIWORD(wParam);	// HIWORD��iHeight.
	HWND hSrc = (HWND)lParam;	// lParam��HWND�ɃL���X�g����, hSrc�Ɋi�[.

	// �E�B���h�E�}�b�v����E�B���h�E�I�u�W�F�N�g�擾.
	CWindow *pWindow = m_mapWindowMap[hSrc];	// m_mapWindowMap[hSrc]����pWindow���擾.

#if 0	
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

	// �A�C�e���̕��̓A�C�e���Y�p�l���ɍ��킹��.
	MoveWindow(pWindow->m_hWnd, pWindow->m_x, pWindow->m_y, m_iClientAreaWidth, pWindow->m_iClientAreaHeight, TRUE);	// MoveWindow�ŉ��ɂ���.
#endif

	// �ύX���ꂽhSrc�����Ԗڂ��𒲂ׂ�.
	BOOL bHit = FALSE;	// bHit��FALSE�ŏ�����.
	m_iTotalHeight = 0;	// m_iTotalHeight��0�ɏ�����.
	for (std::vector<CWindowListItem *>::iterator itor = m_vecWindowListItem.begin(); itor != m_vecWindowListItem.end(); itor++){	// m_vecWindowListItem�̗v�f���J��Ԃ�.
		
		// hSrc�Ɠ������A�C�e����T��.
		m_iTotalHeight += (*itor)->m_iHeight;	// �����𑫂�.
		if ((*itor)->m_hWnd == hSrc){	// m_hWnd��hSrc��������.
			bHit = TRUE;	// bHit��TRUE�ɂ���.
			continue;	// ���֌�����.
		}
		if (bHit){	// bHit
			MoveWindow((*itor)->m_hWnd, (*itor)->m_x, (*(itor - 1))->m_y + (*(itor - 1))->m_iHeight, (*itor)->m_iWidth, (*itor)->m_iHeight, TRUE);
		}

	}

	// �p�l���̃T�C�Y����.
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iTotalHeight, TRUE);	// MoveWindow�ŃT�C�Y����.

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wp;	// WPARAM�^wp.
	wp = MAKEWPARAM(m_iWidth, m_iTotalHeight);	// MAKEWPARAM��wp���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wp, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}
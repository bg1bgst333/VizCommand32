// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ScalableEdit.h"	// CScalableEdit

// �R���X�g���N�^CScalableEdit
CScalableEdit::CScalableEdit() : CEdit(){

	// �����o�̏�����.
	m_iLineHeight = 0;	// �s�̍�����0�ɏ�����.
	m_iLineCount = 0;	// �s����0�ɏ�����.

}

// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
BOOL CScalableEdit::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)

	// �E�B���h�E�N���X����"Edit"�ȃJ�X�^���R���g���[�����쐬.
	BOOL bRet = CEdit::Create(lpctszWindowName, dwStyle, x, y, iWidth, iHeight, hWndParent, (HMENU)hMenu, hInstance);	// CCustomControl::Create�ŃG�f�B�b�g�R���g���[�����쐬.
	
	// �E�B���h�E�̃��T�C�Y
	MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_iLineHeight, TRUE);	// MoveWindow�ō�����1�s����m_iLineHeight�ɂ���.
	
	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;
	wParam = MAKEWPARAM(m_iWidth, m_iLineHeight);
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);
	
	// �߂�l��Ԃ�.
	return bRet;	// bRet��Ԃ�.

}

// �E�B���h�E�̍쐬���J�n���ꂽ��.
int CScalableEdit::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	// �ϐ��̐錾
	HDC hDC;		// �f�o�C�X�R���e�L�X�g�n���h��HDC�^hDC.
	HFONT hFont;	// �t�H���g�n���h��HFONT�^hFont.
	HFONT hOldFont;	// �I��O�̃t�H���g�n���h��HFONT�^hOldFont.
	TEXTMETRIC tm;	// �t�H���g��������TEXTMETRIC�\���̕ϐ�tm.

	// �e�N���X��OnCreate���Ă�.
	int iRet = CEdit::OnCreate(hwnd, lpCreateStruct);	// CEdit::OnCreate���Ă�.

	// �����̒���
	hDC = GetDC(hwnd);	// GetDC�Ńf�o�C�X�R���e�L�X�g�n���h�����擾.
	hFont = (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0);	// SendMessage��WM_GETFONT���w�肵�ăt�H���g�n���h��hFont���擾��, hFont�Ɋi�[.
	hOldFont = (HFONT)SelectObject(hDC, hFont);	// SelectObject��hFont��I��.
	GetTextMetrics(hDC, &tm);	// GetTextMetrics�Ńt�H���g�����擾��, tm�Ɋi�[.
	m_iLineHeight = tm.tmHeight;	// 1�s���̍������t�H���g�̍����ɂ���.
	SelectObject(hDC, hOldFont);	// �t�H���g�����ɖ߂�.
	ReleaseDC(hwnd, hDC);	// ReleaseDC�Ńf�o�C�X�R���e�L�X�g�������[�X.

	// �E�B���h�E�̃��T�C�Y
	//MoveWindow(hwnd, m_x, m_y, m_iWidth, m_iLineHeight, TRUE);	// MoveWindow�ō�����1�s����m_iLineHeight�ɂ���.

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	//WPARAM wParam;
	//wParam = MAKEWPARAM(m_iWidth, m_iLineHeight);
	//SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);

	// �s���̃Z�b�g.
	m_iLineCount = 1;	// 1�s���͂ł����̂�m_iLineCount��1���Z�b�g.

	// OnCreate�̖߂�l��Ԃ�.
	return iRet;	// iRet��Ԃ�.

}

// �L�[�������ꂽ��.
int CScalableEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){

	// ���^�[��, �o�b�N�X�y�[�X�̎��̓���.
	if (nChar == VK_RETURN) {		// VK_RETURN�̎�.

		// �ϐ��̐錾
		int iHeight;	// �V��������iHeight.

		// ���s������1�s���傫������.
		iHeight = m_iHeight + m_iLineHeight;	// ���݂̃E�B���h�E�̍�����1�s���̍����𑫂�.
		MoveWindow(m_hWnd, m_x, m_y, m_iWidth, iHeight, TRUE);	// MoveWindow�ō�����V����iHeight�ɂ���.
		m_iLineCount++;		// �s���𑝂₷.

		// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
		WPARAM wParam;
		wParam = MAKEWPARAM(m_iWidth, m_iHeight);
		SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);

	}
	else if (nChar == VK_BACK) {	// VK_BACK�̎�.

		// �ϐ��̐錾
		POINT pt;		// ���WPOINT�^pt.
		DWORD dwPos;	// HIWORD�͍s�̉��Ԗ�, LOWORD�̓G�f�B�b�g�{�b�N�X�̑��������ƂȂ�DWORD�^dwPos.
		WORD wRow;		// �s.
		WORD wAllLen;	// ��������.
		WORD wRowStart;	// �G�f�B�b�g�{�b�N�X��1�s�ڂ̐擪����L�����b�g�̂���s�̐擪�܂ł̕�����.
		WORD wCol;		// ��.
		int iHeight;	// �V��������iHeight.

		// �o�b�N�X�y�[�X�ōs���������珬��������.
		GetCaretPos(&pt);	// �L�����b�g�̈ʒu�����W�Ŏ擾.
		dwPos = (DWORD)SendMessage(m_hWnd, EM_CHARFROMPOS, 0, MAKELPARAM(pt.x, pt.y));	// EM_CHARFROMPOS�ō��W���s�Ɨ�ɕϊ�.
		wRow = HIWORD(dwPos);	// �s�����o��.
		wAllLen = LOWORD(dwPos);	// �������������o��.
		wRowStart = (WORD)SendMessage(m_hWnd, EM_LINEINDEX, wRow, 0);	// EM_LINEINDEX�ŃL�����b�g�s�̐擪�܂ł̕��������擾.
		wCol = wAllLen - wRowStart;	// ������������L�����b�g�s�̐擪�܂ł̕�������������, �悤�₭����ڂ����킩��.
		if (wCol == 0) {	// �񂪐擪�̏ꍇ.
			if (wRow > 0) {	// �s���擪�łȂ��ꍇ.

				// 1�s������������.
				iHeight = m_iHeight - m_iLineHeight;	// �V��������iHeight��m_iHeight����m_iLineHeight�����������̂ɂ���.
				MoveWindow(m_hWnd, m_x, m_y, m_iWidth, iHeight, TRUE);	// MoveWindow�ō�����V����iHeight�ɂ���.
				m_iLineCount--;	// m_iLineCount�����炷.

				// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
				WPARAM wParam;
				wParam = MAKEWPARAM(m_iWidth, m_iHeight);
				SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);

			}
		}

	}

	// �L�����Z�����Ȃ��̂�0��Ԃ�.
	return 0;	// return��0��Ԃ��Ɠ��͐���.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CScalableEdit::OnSize(UINT nType, int cx, int cy){

	// �e�N���X��OnSize.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSize���Ă�.

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}
// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "StreamConsoleItemsPanel.h"	// CStreamConsoleItemsPanel

// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
void CStreamConsoleItemsPanel::OnSizeChild(WPARAM wParam, LPARAM lParam){

	// �e��OnSizeChild���Ă�.
	CWindowListItemsPanel::OnSizeChild(wParam, lParam);	// CWindowListItemsPanel::OnSizeChild���Ă�.

	// ���ւ̃X�N���[���v��.
	SendMessage(GetParent(m_hWnd), UM_REQUESTSCROLLBOTTOM, m_iTotalHeight, 0);	// UM_REQUESTSCROLLBOTTOM�ŉ��ւ̃X�N���[����v������.

}
// ��d�C���N���[�h�h�~
#ifndef __STREAM_CONSOLE_ITEMS_PANEL_H__
#define __STREAM_CONSOLE_ITEMS_PANEL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "WindowListItemsPanel.h"	// CWindowListItemsPanel

// �X�g���[���R���\�[���A�C�e���Y�p�l���N���XCStreamConsoleItemsPanel
class CStreamConsoleItemsPanel : public CWindowListItemsPanel{

	// public�����o
	public:

		// public�����o�֐�
		// �����o�֐�
		virtual void OnSizeChild(WPARAM wParam, LPARAM lParam);	// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.

};

#endif
// ��d�C���N���[�h�h�~
#ifndef __EDIT_H__
#define __EDIT_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "CustomControl.h"	// CCustomControl

// �G�f�B�b�g�R���g���[���N���XCEdit
class CEdit : public CCustomControl{

	// public�����o
	public:

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CEdit();	// �R���X�g���N�^CEdit
		virtual ~CEdit();	// �f�X�g���N�^~CEdit
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		
};

#endif
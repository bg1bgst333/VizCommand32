// ��d�C���N���[�h�h�~
#ifndef __LIST_CONTROL_H__
#define __LIST_CONTROL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "CustomControl.h"	// CCustomControl

// ���X�g�R���g���[���N���XCListControl
class CListControl : public CCustomControl{

	// public�����o
	public:

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CListControl();	// �R���X�g���N�^CListControl
		virtual ~CListControl();	// �f�X�g���N�^~CListControl
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.

};

#endif
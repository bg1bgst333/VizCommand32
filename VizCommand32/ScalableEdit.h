// ��d�C���N���[�h�h�~
#ifndef __SCALABLE_EDIT_H__
#define __SCALABLE_EDIT_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Edit.h"	// CEdit

// �X�J���u���G�f�B�b�g�R���g���[���N���XCScalableEdit
class CScalableEdit : public CEdit{

	// public�����o
	public:

		// public�����o�ϐ�
		int m_iLineHeight;	// �s�̍���.
		int m_iLineCount;	// �s��.

		// public�����o����
		// �R���X�g���N�^�E�f�X�g���N�^
		CScalableEdit();	// �R���X�g���N�^CScalableEdit
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	// �L�[�������ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.

};

#endif
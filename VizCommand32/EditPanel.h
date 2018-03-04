// ��d�C���N���[�h�h�~
#ifndef __EDIT_PANEL_H__
#define __EDIT_PANEL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "UserControl.h"	// CUserControl
#include "Edit.h"	// CEdit

// �G�f�B�b�g�p�l���N���XCEditPanel
class CEditPanel : public CUserControl{

	// public�����o
	public:

		// public�����o�ϐ�
		CEdit *m_pEdit;	// CEdit�I�u�W�F�N�g�|�C���^.
		HMENU m_nId;	// HMENU�^���j���[ID.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CEditPanel();	// �R���X�g���N�^CEditPanel
		virtual ~CEditPanel();	// �f�X�g���N�^~CEditPanel
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.

};

#endif
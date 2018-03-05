// ��d�C���N���[�h�h�~
#ifndef __SCALABLE_EDIT_PANEL_H__
#define __SCALABLE_EDIT_PANEL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "UserControl.h"	// CUserControl
#include "ScalableEdit.h"	// CScalableEdit

// �X�J���u���G�f�B�b�g�p�l���N���XCScalableEditPanel
class CScalableEditPanel : public CUserControl{

	// public�����o
	public:

		// public�����o�ϐ�
		CScalableEdit *m_pScalableEdit;	// CScalableEdit�I�u�W�F�N�g�|�C���^.
		HMENU m_nId;	// HMENU�^���j���[ID.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CScalableEditPanel();	// �R���X�g���N�^CScalableEditPanel
		virtual ~CScalableEditPanel();	// �f�X�g���N�^~CScalableEditPanel
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual void OnSizeChild(WPARAM wParam, LPARAM lParam);	// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.

};

#endif
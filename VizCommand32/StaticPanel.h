// ��d�C���N���[�h�h�~
#ifndef __STATIC_PANEL_H__
#define __STATIC_PANEL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "UserControl.h"	// CUserControl
#include "Static.h"	// CStatic

// �X�^�e�B�b�N�p�l���N���X
class CStaticPanel : public CUserControl{

	// public�����o
	public:

		// public�����o�ϐ�
		CStatic *m_pStatic;	// CStatic�I�u�W�F�N�g�|�C���^.
		HMENU m_nId;	// HMENU�^���j���[ID.
		HBRUSH m_hbrBackground;	// �w�i�F�u���Vm_hbrBackground.
		HFONT m_hFont;	// �t�H���gm_hFont.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CStaticPanel();	// �R���X�g���N�^CStaticPanel
		virtual ~CStaticPanel();	// �f�X�g���N�^~CStaticPanel
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual HBRUSH OnCtlColorStatic(HDC hDC, HWND hStatic);	// �q�X�^�e�B�b�N�R���g���[���̕`�掞.

};

#endif
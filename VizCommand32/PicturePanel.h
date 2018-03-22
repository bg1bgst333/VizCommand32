// ��d�C���N���[�h�h�~
#ifndef __PICTURE_PANEL_H__
#define __PICTURE_PANEL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "UserControl.h"	// CUserControl
#include "Picture.h"	// CPicture

// �s�N�`���[�p�l���N���XCPicturePanel
class CPicturePanel : public CUserControl{

	// public�����o
	public:

		// public�����o�ϐ�
		CPicture *m_pPicture;	// CPicture�I�u�W�F�N�g�|�C���^.
		HMENU m_nId;	// HMENU�^���j���[ID.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CPicturePanel();	// �R���X�g���N�^CPicturePanel
		virtual ~CPicturePanel();	// �f�X�g���N�^~CPicturePanel
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual void OnTimer(UINT_PTR nIDEvent);	// �^�C�}�[�C�x���g������������.
		virtual void OnSizeChild(WPARAM wParam, LPARAM lParam);	// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.

};

#endif
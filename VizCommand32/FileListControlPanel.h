// ��d�C���N���[�h�h�~
#ifndef __FILE_LIST_CONTROL_PANEL_H__
#define __FILE_LIST_CONTROL_PANEL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "ListControlPanel.h"	// CListControlPanel
#include "FileListControl.h"	// CFileListControl

// �t�@�C�����X�g�R���g���[���p�l���N���XCFileListControlPanel
class CFileListControlPanel : public CListControlPanel{

	// public�����o
	public:

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CFileListControlPanel();	// �R���X�g���N�^CFileListControlPanel
		virtual ~CFileListControlPanel();	// �f�X�g���N�^~CFileListControlPanel
		// �����o�֐�
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnTimer(UINT_PTR nIDEvent);	// �^�C�}�[�C�x���g������������.

};

#endif
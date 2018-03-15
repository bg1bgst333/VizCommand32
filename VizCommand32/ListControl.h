// ��d�C���N���[�h�h�~
#ifndef __LIST_CONTROL_H__
#define __LIST_CONTROL_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "CustomControl.h"	// CCustomControl
// ����̃w�b�_
#include <commctrl.h>	// �R�����R���g���[��

// ���X�g�R���g���[���N���XCListControl
class CListControl : public CCustomControl{

	// public�����o
	public:

		// public�����o�ϐ�
		HIMAGELIST m_hImageList;	// �A�C�R���̃C���[�W���X�g�n���h��m_hImageList.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CListControl();	// �R���X�g���N�^CListControl
		virtual ~CListControl();	// �f�X�g���N�^~CListControl
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.(�E�B���h�E�N���X���ȗ��o�[�W����.)
		virtual void SetImageList(int nImageListType);	// �C���[�W���X�g�̃Z�b�gSetImageList.
		virtual int AddIcon(HICON hIcon);	// �C���[�W���X�g�ɃA�C�R����ǉ�����AddIcon.
		virtual int InsertItem(LPLVITEM pItem);	// ���X�g�R���g���[���ɃA�C�e����ǉ�InsertItem.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.

};

#endif
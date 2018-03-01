// ��d�C���N���[�h�h�~
#ifndef __WINDOW_LIST_ITEMS_PANEL_H__
#define __WINDOW_LIST_ITEMS_PANEL_H__

// �w�b�_�̃C���N���[�h
// ����̃w�b�_
#include <vector>	// std::vector
// �Ǝ��̃w�b�_
#include "UserControl.h"	// CUserControl
#include "WindowListItem.h"	// CWindowListItem

// �}�N����`
#define WINDOW_LIST_ITEM_ID_START (WM_APP + 100)	// �E�B���h�E���X�g�A�C�e����ID�̊J�n��WM_APP + 100�Ƃ���.

// �E�B���h�E���X�g�A�C�e���Y�p�l��CWindowListItemsPanel
class CWindowListItemsPanel : public CUserControl{

	// public�����o
	public:

		// public�����o�ϐ�
		std::vector<CWindowListItem *> m_vecWindowListItem;	// �E�B���h�E���X�g�A�C�e�����X�gm_vecWindowListItem.
		int m_nNextId;	// �E�B���h�E���X�g�A�C�e���̎��������o�����\�[�XID m_nNextId.
		int m_iTotalHeight;	// �E�B���h�E���X�g�S�̂̍���.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CWindowListItemsPanel();	// �R���X�g���N�^CWindowListItemsPanel
		virtual ~CWindowListItemsPanel();	// �f�X�g���N�^~CWindowListItemsPanel
		// static�����o�֐�
		static BOOL RegisterClass(HINSTANCE hInstance);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.
		static BOOL RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground);	// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
		// �����o�֐�
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);	// �E�B���h�E�쐬�֐�Create.
		virtual void Destroy();	// �E�B���h�E�̔j���ƏI�������֐�Destroy.
		virtual void Add(LPCTSTR lpctszWindowName, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance);	// �A�C�e���𖖔�����ǉ�����֐�Add.
		virtual void Add(LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance);	// �A�C�e���𖖔�����ǉ�����֐�Add.
		virtual void Insert(int iIndex, LPCTSTR lpctszWindowName, int iHeight, HINSTANCE hInstance);	// �A�C�e�����w��̏ꏊ�ɑ}������֐�Insert.
		virtual void Remove();	// �A�C�e���𖖔�����폜����֐�Remove.
		virtual void Delete(int iIndex);	// �w��̏ꏊ�̃A�C�e�����폜����֐�Delete.
		virtual CWindowListItem * Get(int iIndex);	// �A�C�e�����擾����֐�Get.
		virtual void RemoveAll();	// �S�ẴA�C�e�����폜����֐�RemoveAll.
		virtual size_t GetSize();	// �A�C�e���̐���Ԃ��֐�GetSize.
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�̍쐬���J�n���ꂽ��.
		virtual void OnDestroy();	// �E�B���h�E���j�����ꂽ��.
		virtual void OnPaint();	// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
		virtual void OnSize(UINT nType, int cx, int cy);	// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
		virtual void OnSizeChild(WPARAM wParam, LPARAM lParam);	// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.

};

#endif
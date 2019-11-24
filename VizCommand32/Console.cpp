// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Console.h"	// CConsole
#include "Command.h"	// CCommand

// �R���X�g���N�^CConsole
CConsole::CConsole() : CScalableEditPanel(){

	// �����o�̏�����.
	m_hbrBackground = NULL;	// m_hbrBackground��NULL�ŏ�����.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.
BOOL CConsole::RegisterClass(HINSTANCE hInstance){

	// �E�B���h�E�N���X�̓o�^.
	return RegisterClass(hInstance, (HBRUSH)GetStockObject(WHITE_BRUSH));	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�N���X�o�^�֐�RegisterClass.(hbrBackground�w��.)
BOOL CConsole::RegisterClass(HINSTANCE hInstance, HBRUSH hbrBackground){

	// hbrBackground���w��.
	return CUserControl::RegisterClass(hInstance, _T("CConsole"), hbrBackground);	// CUserControl::RegisterClass�œo�^.

}

// �E�B���h�E�쐬�֐�Create.
BOOL CConsole::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// �E�B���h�E�̍쐬.
	m_nId = hMenu;	// m_nId��hMenu���i�[.
	BOOL bRet = CUserControl::Create(_T("CConsole"), lpctszWindowName, dwStyle | WS_CHILD | WS_VISIBLE/* | WS_HSCROLL | WS_VSCROLL*/, x, y, iWidth, iHeight, hWndParent, m_nId, hInstance);	// CWindow::Create�ō쐬.

	// ����.
	if (bRet){	// bRet��TRUE.

		// �q�R���\�[���R�A�̐���.
		m_pScalableEdit = new CConsoleCore();	// CConsoleCore�I�u�W�F�N�g�𐶐���, �|�C���^��m_pScalableEdit�Ɋi�[.
		BOOL bRet2 = m_pScalableEdit->Create(_T(""), 0, m_x, m_y, m_iClientAreaWidth, m_iClientAreaHeight, m_hWnd, m_nId + 100, hInstance);	// m_pScalableEdit->Create�Ŏq�X�J���u���G�f�B�b�g�R���g���[������.
		if (bRet2){	// bRet2��TRUE.
			// ���T�C�Y.
			MoveWindow(m_hWnd, m_x, m_y, m_iWidth, m_pScalableEdit->m_iHeight, TRUE);	// MoveWindow��m_pScalableEdit->m_iHeight�̍����Ƀ��T�C�Y.
			// �R���\�[���R�A�̃��b�Z�[�W�̓������������ɂ���.
			if (m_pScalableEdit != NULL){	// m_pScalableEdit��NULL�łȂ����.
				// ��������E�B���h�E�̃Z�b�g.
				((CConsoleCore *)m_pScalableEdit)->SetProcWindow(m_hWnd);	// ((CConsoleCore *)m_pScalableEdit)->SetProcWindow�ŏ�������E�B���h�E�͂����ɂ���.
				// ���u���V�쐬.
				m_hbrBackground = CreateSolidBrush(RGB(0x0, 0x0, 0x0));	// CreateSolidBrush�ō��u���V���쐬��, m_hbrBackground�Ɋi�[.
				SetFocus(m_pScalableEdit->m_hWnd);	// SetFocus��m_pScalableEdit->m_hWnd�Ƀt�H�[�J�X�𓖂Ă�.
			}
		}

	}

	// �߂�l��Ԃ�.
	return bRet;	// bRet��Ԃ�.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CConsole::Destroy(){

	// �u���V�̔j��.
	if (m_hbrBackground != NULL){	// m_hbrBackground��NULL�łȂ���.
		DeleteObject(m_hbrBackground);	// DeleteObject�ō폜.
		m_hbrBackground = NULL;	// m_hbrBackground��NULl���Z�b�g.
	}

	// �e��Destroy���Ă�.
	CScalableEditPanel::Destroy();

}

// ���̓t�H�[���̏o��.
void CConsole::ShowInputForm(){
	
	// �R���\�[���R�A�̓��̓t�H�[���o�͂��Ă�.
	if (m_pScalableEdit != NULL){	// m_pScalableEdit��NULL�łȂ����.
		((CConsoleCore *)m_pScalableEdit)->ShowInputForm();	// ((CConsoleCore *)m_pScalableEdit)->ShowInputForm�œ��̓t�H�[���̏o��.
	}

}

// �R�}���h�ɑ΂��鏈�������s����E�B���h�E���Z�b�g.
void CConsole::SetProcWindow(HWND hWnd){

	// �����o�ɃZ�b�g.
	m_hProcWnd = hWnd;	// m_hProcWnd��hWnd���Z�b�g.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CConsole::OnSize(UINT nType, int cx, int cy){

	// �e��OnSize���Ă�.
	CUserControl::OnSize(nType, cx, cy);	// CUserControl::OnSize���Ă�.

	// �q�R���\�[���R�A�̃��T�C�Y.
	if (m_pScalableEdit != NULL){	// NULL�łȂ����.
		MoveWindow(m_pScalableEdit->m_hWnd, m_pScalableEdit->m_x, m_pScalableEdit->m_y, cx, cy, TRUE);	// MoveWindow�Ŏq�R���\�[���R�A�����T�C�Y.
	}

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

}

// �q�G�f�B�b�g�R���g���[���̕`�掞.
HBRUSH CConsole::OnCtlColorEdit(HDC hDC, HWND hEdit){

	// �w�i����, �e�L�X�g�𔒂ɂ���.
	SetBkColor(hDC, RGB(0x0, 0x0, 0x0));	// �w�i�͍�.
	SetTextColor(hDC, RGB(0xff, 0xff, 0xff));	// �e�L�X�g�͔�.
	return m_hbrBackground;	// m_hbrBackground��Ԃ�.

}

// ���[�U��`���b�Z�[�W������������.
void CConsole::OnUserMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){

	// switch-case���ŐU�蕪����.
	switch (uMsg) {

		// �q����e�փE�B���h�E�T�C�Y�ύX�̗v��������������.
		case UM_SIZECHILD:

			// UM_SIZECHILD�u���b�N
			{

				// OnSizeChild�ɔC����.
				OnSizeChild(wParam, lParam);	// OnSizeChild�ɔC����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// �R���\�[���R�A���烁�b�Z�[�W������ꂽ��.
		case UM_CONSOLECORECOMMAND:

			// UM_CONSOLECORECOMMAND�u���b�N
			{

				// OnConsoleCoreCommand�ɔC����.
				OnConsoleCoreCommand(wParam, lParam);	// OnConsoleCoreCommand�ɔC����.

			}

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

		// ����ȊO.
		default:

			// ����̏����֌�����.
			break;	// ������DefWindowProc�Ɍ�����.

	}

}

// �R���\�[���R�A���烁�b�Z�[�W������ꂽ��.
int CConsole::OnConsoleCoreCommand(WPARAM wParam, LPARAM lParam){

	// �ϐ��̏���
	CCommand *pCommand = NULL;	// CCommand�I�u�W�F�N�g�|�C���^pCommand��NULL�ŏ�����.
	HWND hSrc = NULL;	// ���M���E�B���h�E�n���h��hSrc��NULL�ŏ�����.

	// �R�}���h�ƃ\�[�X���擾.
	pCommand = (CCommand *)wParam;	// wParam��(CCommand *)�ɃL���X�g����pCommand�Ɋi�[.
	hSrc = (HWND)lParam;	// lParam��HWND�ɃL���X�g����hSrc�Ɋi�[.

	// �R�}���h�̔���.
	tstring tstrCommandName = pCommand->GetCommandName();	// pCommand->GetCommandName�Ŏ擾�����R�}���h����tstrCommandName�Ɋi�[.
	if (tstrCommandName == _T("hello")){	// hello�R�}���h.

		// OnHello�ɔC����.
		OnHello(hSrc, pCommand);	// hSrc, pCommand�������Ƃ��ēn����, OnHello���Ă�.

	}
	else if (tstrCommandName == _T("list")){	// list�R�}���h.

		// OnList�ɔC����.
		OnList(hSrc, pCommand);	// hSrc, pCommand�������Ƃ��ēn����, OnList���Ă�.

	}
	else if (tstrCommandName == _T("walk")){	// walk�R�}���h.

		// OnWalk�ɔC����.
		OnWalk(hSrc, pCommand);	// hSrc, pCommand�������Ƃ��ēn����, OnWalk���Ă�.

	}
	else if (tstrCommandName == _T("view")){	// view�R�}���h.

		// OnView�ɔC����.
		OnView(hSrc, pCommand);	// hSrc, pCommand�������Ƃ��ēn����, OnView���Ă�.

	}
	else {	// �R�}���h��������Ȃ�.

		// �R�}���h��������Ȃ��G���[.
		OnErrorCommandNotFound(hSrc);	// hSrc�������Ƃ��ēn����, OnErrorCommandNotFound���Ă�.

 	}

	// �����Ȃ�0��Ԃ�.
	return 0;	// 0��Ԃ�.

}

// "Hello, world!"�̏o�͂�v�����ꂽ��.
void CConsole::OnHello(HWND hSrc, CCommand *pCommand){

	// "/s"�I�v�V�����������, StreamConsole�ɓ�����.
	if (pCommand->m_vectstrCommandToken.size() > 1){	// �I�v�V����������ꍇ.
		if (pCommand->m_vectstrCommandToken[1] == _T("/s")){	// "/s"�I�v�V�����Ȃ�.

			// �X�g���[���R���\�[���ɏ����𓊂���.
			SendMessage(m_hProcWnd, UM_STREAMCOMMAND, (WPARAM)pCommand, (LPARAM)m_hWnd);	// UM_STREAMCOMMAND�ŃX�g���[���R���\�[���ɂ���ɓ�����.

			// �I��.
			return;	// �����ŏI��.

		}
	}

	// "Hello, world!"���o��.
	SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Hello, world!\r\n"), 0);	// UM_RESPONSEMESSAGE��"Hello, world!"�𑗂�.

	// ���X�|���X�I��.
	SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSE�𑗂�.

}

// �t�@�C�����X�g�̏o�͂�v�����ꂽ��.
void CConsole::OnList(HWND hSrc, CCommand *pCommand){

	// �p�X�̕⊮����.
	if (pCommand->m_vectstrCommandToken.size() == 0){	// �g�[�N��������.
		return;	// �ُ�I���Ȃ̂ł����ŏI��.
	}
	else if (pCommand->m_vectstrCommandToken.size() == 1){	// �g�[�N����1��.(�p�X���w�肳��Ă��Ȃ�.)
		tstring tstrNewCommand = pCommand->GetCommandString();	// tstrNewCommand��pCommand->GetCommandString�Ŏ擾�����R�}���h���������.
		pCommand->Clear();	// �R�}���h����������N���A.
		tstrNewCommand = tstrNewCommand + _T(" ");	// �X�y�[�X��A��.
		tstrNewCommand = tstrNewCommand + ((CConsoleCore *)m_pScalableEdit)->m_tstrCurrentPath;	// �J�����g�p�X��A��.
		pCommand->Set(tstrNewCommand);	// �R�}���h�ɃZ�b�g.
	}
	else if (pCommand->m_vectstrCommandToken.size() >= 2){	// �g�[�N����2�ȏ�.
		tstring tstrCommandName = pCommand->GetCommandName();	// �R�}���h�����擾.
		tstring tstrRelativePath = pCommand->m_vectstrCommandToken[1];	// tstrRelativePath�ɑ��΃p�X�̉\���̂���p�X���Z�b�g.
		tstring tstrFullPath = ((CConsoleCore *)m_pScalableEdit)->GetFullPath(tstrRelativePath);	// �t���p�X�ɕϊ�.
		if (tstrFullPath == _T("")){	// tstrFullPath��""�̎�.(�p�X�����݂��Ȃ���.)
			SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Error: Path not exist!\r\n"), 0);	// UM_RESPONSEMESSAGE��"Error: Path not exist!"�𑗂�.
			SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSE�𑗂�.
			return;	// �����ŏI��.
		}
		pCommand->Clear();	// �R�}���h����������N���A.
		tstring tstrNewCommand = tstrCommandName;	// tstrNewCommand��tstrCommandName���Z�b�g.
		tstrNewCommand = tstrNewCommand + _T(" ");	// �X�y�[�X��A��.
		tstrNewCommand = tstrNewCommand + tstrFullPath;	// �t���p�X��A��.
		pCommand->Set(tstrNewCommand);	// �R�}���h�ɃZ�b�g.
	}

	// �X�g���[���R���\�[���ɏ����𓊂���.
	SendMessage(m_hProcWnd, UM_STREAMCOMMAND, (WPARAM)pCommand, (LPARAM)m_hWnd);	// UM_STREAMCOMMAND�ŃX�g���[���R���\�[���ɂ���ɓ�����.

}

// �J�����g�t�H���_�̈ړ���v�����ꂽ��.
void CConsole::OnWalk(HWND hSrc, CCommand *pCommand){

	// �p�X�̕ۊǏ���.
	if (pCommand->m_vectstrCommandToken.size() == 0){	// �g�[�N��������.
		return;	// �ُ�I���Ȃ̂ł����ŏI��.
	}
	else if (pCommand->m_vectstrCommandToken.size() == 1){	// �g�[�N����1��.(�p�X���w�肳��Ă��Ȃ�.)
		
		// ���̓t�H�[���̍X�V.
		((CConsoleCore *)m_pScalableEdit)->SetCurrentPath(((CConsoleCore *)m_pScalableEdit)->GetProfilePath(((CConsoleCore *)m_pScalableEdit)->m_hWnd));	// SetCurrentPath�Ńz�[���t�H���_���Z�b�g.
		((CConsoleCore *)m_pScalableEdit)->GetInputFormString();	// GetInputFormString�œ��̓t�H�[�����擾.
		
		// ���X�|���X�I��.
		SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSE�𑗂�.

	}
	else if (pCommand->m_vectstrCommandToken.size() >= 2){	// �g�[�N����2�ȏ�.

		// ���̓t�H�[���̍X�V.
		tstring tstrRelativePath = pCommand->m_vectstrCommandToken[1];	// �w��̃p�X��tstrRelativePath�Ɋi�[.
		tstring tstrNewPath = ((CConsoleCore *)m_pScalableEdit)->GetFullPath(tstrRelativePath);	// tstrRelativePath����t���p�X���擾��, tstrNewPath�Ɋi�[.
		if (tstrNewPath == _T("")){	// ���݂��Ȃ��ꍇ��""���Ԃ�.

			// "Error: Path not exist!"���o��.
			SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Error: Path not exist!\r\n"), 0);	// UM_RESPONSEMESSAGE��"Error: Path not exist!"�𑗂�.

		}
		else{	// �p�X������ꍇ.

			// �V�����p�X���J�����g�p�X�ɂ���.
			((CConsoleCore *)m_pScalableEdit)->SetCurrentPath(tstrNewPath);	// SetCurrentPath��tstrNewPath���Z�b�g.
			((CConsoleCore *)m_pScalableEdit)->GetInputFormString();	// GetInputFormString�œ��̓t�H�[�����擾.

		}
		
		// ���X�|���X�I��.
		SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSE�𑗂�.

	}

}

// �t�@�C���̕\����v�����ꂽ��.
void CConsole::OnView(HWND hSrc, CCommand *pCommand){

	// �p�X�̑��݊m�F.
	if (pCommand->m_vectstrCommandToken.size() <= 1){	// �g�[�N��������, �܂��̓p�X���w�肳��Ă��Ȃ�.
		SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Error: No path!\r\n"), 0);	// UM_RESPONSEMESSAGE��"Error: No path!\r\n"�𑗂�.
		SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSE�𑗂�.
		return;	// �ُ�I���Ȃ̂ł����ŏI��.
	}
	else if (pCommand->m_vectstrCommandToken.size() >= 2){	// �g�[�N����2�ȏ�.
		tstring tstrCommandName = pCommand->GetCommandName();	// �R�}���h�����擾.
		tstring tstrRelativePath = pCommand->m_vectstrCommandToken[1];	// tstrRelativePath�ɑ��΃p�X�̉\���̂���p�X���Z�b�g.
		tstring tstrFullPath = ((CConsoleCore *)m_pScalableEdit)->GetFullPath(tstrRelativePath);	// �t���p�X�ɕϊ�.
		if (tstrFullPath == _T("")){	// tstrFullPath��""�̎�.(�p�X�����݂��Ȃ���.)
			SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Error: Path not exist!\r\n"), 0);	// UM_RESPONSEMESSAGE��"Error: Path not exist!"�𑗂�.
			SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSE�𑗂�.
			return;	// �����ŏI��.
		}
		pCommand->Clear();	// �R�}���h����������N���A.
		tstring tstrNewCommand = tstrCommandName;	// tstrNewCommand��tstrCommandName���Z�b�g.
		tstrNewCommand = tstrNewCommand + _T(" ");	// �X�y�[�X��A��.
		tstrNewCommand = tstrNewCommand + _T("\"");	// �_�u���N�H�[�g.
		tstrNewCommand = tstrNewCommand + tstrFullPath;	// �t���p�X��A��.
		tstrNewCommand = tstrNewCommand + _T("\"");	// �_�u���N�H�[�g.
		pCommand->Set(tstrNewCommand);	// �R�}���h�ɃZ�b�g.
	}

	// �X�g���[���R���\�[���ɏ����𓊂���.
	SendMessage(m_hProcWnd, UM_STREAMCOMMAND, (WPARAM)pCommand, (LPARAM)m_hWnd);	// UM_STREAMCOMMAND�ŃX�g���[���R���\�[���ɂ���ɓ�����.

}

// �R�}���h��������Ȃ��G���[������������.
void CConsole::OnErrorCommandNotFound(HWND hSrc){

	// "Error: Command not found!"���o��.
	SendMessage(hSrc, UM_RESPONSEMESSAGE, (WPARAM)_T("Error: Command not found!\r\n"), 0);	// UM_RESPONSEMESSAGE��"Error: Command not found!"�𑗂�.

	// ���X�|���X�I��.
	SendMessage(hSrc, UM_FINISHRESPONSE, 0, 0);	// UM_FINISHRESPONSE�𑗂�.

}
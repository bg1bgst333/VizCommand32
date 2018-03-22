// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Picture.h"	// CPicture
#include "BinaryFile.h"	// CBinaryFile

// �R���X�g���N�^CPicture
CPicture::CPicture() : CCustomControl(){

	// �����o�̏�����.
	m_hBitmap = NULL;	// m_hBitmap��NULL�ŏ�����.
	ZeroMemory(&m_Bitmap, sizeof(BITMAP));	// m_Bitmap��ZeroMemory�ŃN���A.
	m_tstrImageName.clear();	// m_tstrImageName.clear()�ŃN���A.
	m_hMemDC = NULL;	// m_hMemDC��NULL�ŏ�����.
	m_iHScrollPos = 0;	// m_iHScrollPos��0�ŏ�����.
	m_iVScrollPos = 0;	// m_iVScrollPos��0�ŏ�����.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// m_ScrollInfo��ZeroMemory�ŃN���A.
	
}

// �f�X�g���N�^~CPicture()
CPicture::~CPicture(){

	// �����o�̏I������.
	Destroy();	// Destroy���Ă�.

}

// �E�B���h�E�쐬�֐�Create(�E�B���h�E�N���X���w��o�[�W����.)
BOOL CPicture::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance){

	// CCustomControl::Create�Ő���.
	return CCustomControl::Create(_T("Static"), lpctszWindowName, dwStyle | SS_BITMAP | SS_REALSIZECONTROL | WS_HSCROLL | WS_VSCROLL, x, y, iWidth, iHeight, hWndParent, hMenu, hInstance);	// CCustomControl::Create�ŃE�B���h�E�N���X"Static"�ō쐬.

}

// �E�B���h�E�̔j���ƏI�������֐�Destroy.
void CPicture::Destroy(){

	// �r�b�g�}�b�v�̔j��.
	if (m_hBitmap != NULL){	// m_hBitmap��NULL�łȂ���.
		DeleteObject(m_hBitmap);	// m_hBitmap��DeleteObject�Ŕj��.
		m_hBitmap = NULL;	// m_hBitmap��NULL���Z�b�g.
	}
	ZeroMemory(&m_Bitmap, sizeof(BITMAP));	// m_Bitmap��ZeroMemory�ŃN���A.
	m_tstrImageName.clear();	// m_tstrImageName.clear()�ŃN���A.
	if (m_hMemDC != NULL){	// m_hMemDC��NULL�łȂ���.
		DeleteDC(m_hMemDC);	// m_hMemDC��DeleteDC�Ŕj��.
		m_hMemDC = NULL;	// m_hMemDC��NULL���Z�b�g.
	}
	m_iHScrollPos = 0;	// m_iHScrollPos��0���Z�b�g.
	m_iVScrollPos = 0;	// m_iVScrollPos��0���Z�b�g.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// m_ScrollInfo��ZeroMemory�ŃN���A.

	// �e�N���X��Destroy���Ă�.
	CCustomControl::Destroy();	// CCustomControl::Destroy���Ă�.

}

// �摜�����[�h����֐�LoadImage
BOOL CPicture::LoadImage(HINSTANCE hInstance, LPCTSTR lpctszImageName){

	// �r�b�g�}�b�v�̔j��.
	if (m_hBitmap != NULL) {	// NULL�łȂ����.
		DeleteObject(m_hBitmap);	// DeleteObject��m_hBitmap��j��.
		m_hBitmap = NULL;	// m_hBitmap��NULL���Z�b�g.
	}

	// �摜�̃��[�h.
	m_hBitmap = (HBITMAP)::LoadImage(hInstance, lpctszImageName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);	// LoadImage��m_tstrImageName�����[�h.(�Ƃ肠�����摜�t�@�C���Ƃ��ă��[�h.)
	if (m_hBitmap == NULL) {	// NULL�Ȃ玸�s.

		// �G���[����.
		m_tstrImageName = _T("");	// ���s�����̂�""���Z�b�g.

		// ���s�Ȃ̂�FALSE��Ԃ�.
		return FALSE;	// FALSE��Ԃ�.

	}

	// �����o�ɃZ�b�g.
	m_tstrImageName = lpctszImageName;	// m_tstrImageName��lpctszImageName���Z�b�g.

	// �摜���畝�ƍ������擾.
	GetObject(m_hBitmap, sizeof(BITMAP), &m_Bitmap);	// GetObject��m_hBitmap����r�b�g�}�b�v�����擾��, m_Bitmap�Ɋi�[.
	
	// �����Ȃ̂�TRUE��Ԃ�.
	return TRUE;	// TRUE��Ԃ�.

}

// �摜���Z�[�u����֐�SaveImage
BOOL CPicture::SaveImage(LPCTSTR lpctszImageName){

	// �ϐ��̏�����.
	BITMAPINFO bi = {0};	// BITMAPINFO�\���̕ϐ�bi��{0}�ŏ�����.
	LPBYTE lpBitsPixel = NULL;	// LPBYTE�^(BYTE�^�|�C���^)��lpBitsPixel��NULL�ŏ�����.
	BITMAPFILEHEADER bfh = {0};	// BITMAPFILEHEADER�\����bfh��{0}�ŏ�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	FILE *fp = NULL;	// �t�@�C���|�C���^fp��NULL�ŏ�����.

	// �r�b�g�}�b�v���̃Z�b�g.
	bi.bmiHeader.biBitCount = 24;	// �ЂƂ܂�24bit�r�b�g�}�b�v�̂ݑΉ�.
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	// BITMAPINFOHEADER�̃T�C�Y���w�肵�Ă���.
	bi.bmiHeader.biWidth = m_Bitmap.bmWidth;	// �摜��m_Bitmap.bmWidth���Z�b�g.
	bi.bmiHeader.biHeight = m_Bitmap.bmHeight;	// �摜����m_Bitmap.bmHeight���Z�b�g.
	bi.bmiHeader.biPlanes = 1;	// 1���Z�b�g.
	bi.bmiHeader.biCompression = BI_RGB;	// RGB.

	// DDB����DIB�̃s�N�Z������擾.
	hDC = GetDC(m_hWnd);	// GetDC��m_hWnd�̃f�o�C�X�R���e�L�X�ghDC���擾.
	GetDIBits(hDC, m_hBitmap, 0, m_Bitmap.bmHeight, NULL, &bi, DIB_RGB_COLORS);	// GetDIBits�Ńs�N�Z����̃T�C�Y(bi.bmiHeader.biSizeImage)���擾.
	lpBitsPixel = new BYTE[bi.bmiHeader.biSizeImage];	// �s�N�Z����p�̃������m��.
	GetDIBits(hDC, m_hBitmap, 0, m_Bitmap.bmHeight, lpBitsPixel, &bi, DIB_RGB_COLORS);	// GetDIBits�Ńs�N�Z������擾.
	ReleaseDC(m_hWnd, hDC);	// hDC�������[�X.

	// �r�b�g�}�b�v�t�@�C�����̃Z�b�g.(24bit�r�b�g�}�b�v�̏ꍇ.)
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	// �s�N�Z����ȊO�̃T�C�Y.(�܂�w�b�_�̃T�C�Y.)
	bfh.bfSize = bfh.bfOffBits + bi.bmiHeader.biSizeImage;	// �S�̂̃T�C�Y�̓w�b�_ + �s�N�Z����.
	bfh.bfType = 0x4d42;	// 0x4d42("BM")�̓r�b�g�}�b�v�ł���Ƃ����Ӗ�.
	bfh.bfReserved1 = 0;	// ������0���Z�b�g.
	bfh.bfReserved2 = 0;	// ������0���Z�b�g.

#if 1
	// �r�b�g�}�b�v�o�C�i���̃t�@�C����������.
	CBinaryFile *pBinaryFile = new CBinaryFile();	// CBinaryFile�I�u�W�F�N�g���쐬��, �|�C���^��pBinaryFile�Ɋi�[.
	pBinaryFile->Set((BYTE *)&bfh, sizeof(BITMAPFILEHEADER));	// pBinaryFile->Set��BITMAPFILEHEADER��bfh���Z�b�g.
	pBinaryFile->Write(lpctszImageName);	// pBinaryFile->Write(�t�@�C������������o�[�W����)�Ńt�@�C�����J���ď�������.
	pBinaryFile->Set((BYTE *)&bi, sizeof(BITMAPINFOHEADER));	// pBinaryFile->Set��BITMAPINFOHEADER��bi(���m�ɂ�bi.bmiHeader)���Z�b�g.
	pBinaryFile->Write();	// pBinaryFile->Write(�t�@�C���������Ȃ��o�[�W����)�ŏ�������.
	pBinaryFile->Set(lpBitsPixel, sizeof(BYTE) * bi.bmiHeader.biSizeImage);	// pBinaryFile->Set��lpBitsPixel���Z�b�g.
	pBinaryFile->Write();	// pBinaryFile->Write(�t�@�C���������Ȃ��o�[�W����)�ŏ�������.
	delete pBinaryFile;	// pBinaryFile�����.
	delete[] lpBitsPixel;	// delete[]��lpBitsPixel�����.
#else
	// �t�@�C���̏�������.
	// ���{�ꃍ�P�[���̃Z�b�g.
	setlocale(LC_ALL, "Japanese");	// setlocale��"Japanese"���Z�b�g.
	// �t�@�C�������}���`�o�C�g�ɕϊ�.
	size_t filename_len = wcstombs(NULL, lpctszImageName, _MAX_PATH);	// wcstombs�Œ���filename_len�����߂�.(filename_len��NULL�����͊܂܂�Ȃ�.)
	char *path = (char *)malloc(sizeof(char) * (filename_len + 1));	// malloc�œ��I�z����m�ۂ�, �A�h���X��path�Ɋi�[.
	wcstombs(path, lpctszImageName, _MAX_PATH);	// wcstombs��TCHAR����}���`�o�C�g�֕ϊ�.
	// �t�@�C�����J��.
	fp = fopen(path, "wb");	// �o�C�i�����[�h("wb")�ŊJ��.
	if (fp != NULL){	// fp��NULL�łȂ���.
		fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, fp);	// fwrite��bfh����������.
		fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fp);	// fwrite��bi����������.
		fwrite(lpBitsPixel, sizeof(BYTE), bi.bmiHeader.biSizeImage, fp);	// fwrite��lpBitsPixel����������.
		fclose(fp);	// fclose��fp�����.
	}
	// �������̉��.
	free(path);	// free��path�����.
	delete[] lpBitsPixel;	// delete[]��lpBitsPixel�����.
#endif

	// �����o�ɃZ�b�g.
	m_tstrImageName = lpctszImageName;	// m_tstrImageName��lpctszImageName���Z�b�g.

	// �Ƃ肠����TRUE�Ƃ���.
	return TRUE;	// TRUE��Ԃ�.

}

// �摜���Z�b�g(�\��)����֐�SetImage
void CPicture::SetImage(){

	// �ϐ��̐錾.
	HDC hDC;	// HDC�^�f�o�C�X�R���e�L�X�g�n���h��hDC.

	// �������f�o�C�X�R���e�L�X�g�̔j��.
	if (m_hMemDC != NULL) {	// NULL�łȂ����.
		DeleteDC(m_hMemDC);	// DeleteDC��m_hMemDC��j��.
		m_hMemDC = NULL;	// m_hMemDC��NULL���Z�b�g.
	}

	// �f�o�C�X�R���e�L�X�g�n���h���̎擾.
	hDC = GetDC(m_hWnd);	// GetDC��m_hWnd����f�o�C�X�R���e�L�X�g�n���h��hDC���擾.

	// �������f�o�C�X�R���e�L�X�g�̍쐬.
	m_hMemDC = CreateCompatibleDC(hDC);	// CreateCompatibleDC�ō쐬�����f�o�C�X�R���e�L�X�g�n���h����m_hMemDC�Ɋi�[.

	// �摜�̕\��.
	SendMessage(m_hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);	// SendMessage��STM_SETIMAGE�𑗐M���邱�Ƃŉ摜��\��.

	// �X�N���[���o�[�̈ʒu��������.
	m_iHScrollPos = 0;	// m_iHScrollPos��0���Z�b�g.
	m_iVScrollPos = 0;	// m_iVScrollPos��0���Z�b�g.

	// �s�N�`���[�̍ĕ`��.
	InvalidateRect(m_hWnd, NULL, TRUE);

	// �f�o�C�X�R���e�L�X�g�̉��.
	ReleaseDC(m_hWnd, hDC);	// ReleaseDC��hDC�����.

}

// �E�B���h�E�̃T�C�Y���ύX���ꂽ��.
void CPicture::OnSize(UINT nType, int cx, int cy){

	// �e��OnSize���Ă�.
	CCustomControl::OnSize(nType, cx, cy);	// CCustomControl::OnSize���Ă�.

	// UM_SIZECHILD�Ŏq�E�B���h�E�̃T�C�Y�ɍ��킹��.
	WPARAM wParam;	// WPARAM�^wParam.
	wParam = MAKEWPARAM(m_iWidth, m_iHeight);	// MAKEWPARAM��wParam���Z�b�g.
	SendMessage(GetParent(m_hWnd), UM_SIZECHILD, wParam, (LPARAM)m_hWnd);	// SendMessage��UM_SIZECHILD�𑗐M.

	// �X�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ōX�V.

}

// �E�B���h�E�̕`���v�����ꂽ���̃n���h��OnPaint.
void CPicture::OnPaint(){

	// �ϐ��̏�����.
	HDC hDC = NULL;	// hDC��NULL�ŏ�����.
	PAINTSTRUCT ps = {0};	// ps��{0}�ŏ�����.
	HBITMAP hOld = NULL;	// hOld��NULL�ŏ�����.
	int iDrawWidth;	// ���ۂ̕`�敝.
	int iDrawHeight;	// ���ۂ̕`�捂��.

	// �`��J�n.
	hDC = BeginPaint(m_hWnd, &ps);	// BeginPaint�ŕ`��J�n.

	// �r�b�g�}�b�v�̑I��.
	hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);	// SelectObject��m_hMemDC��m_hBitmap��I��.
	
	// �r�b�g�]��.
	iDrawWidth = m_iClientAreaWidth;	// �`�敝 = �s�N�`���[�R���g���[���� - �X�N���[���o�[��.
	iDrawHeight = m_iClientAreaHeight;	// �`�捂�� = �s�N�`���[�R���g���[������ - �X�N���[���o�[����.
	BitBlt(hDC, 0, 0, iDrawWidth, iDrawHeight, m_hMemDC, m_iHScrollPos, m_iVScrollPos, SRCCOPY);	// BitBlt��m_hMemDC��hDC�ɓ]��.

	// �Â��r�b�g�}�b�v���đI�����Ė߂�.
	SelectObject(m_hMemDC, hOld);	// SelectObject��hOld��I��.

	// �X�N���[���o�[�ݒ�.
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = iDrawWidth;	// �`�敝
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_Bitmap.bmWidth;	//�ő�l
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)
	// ��������.
	ZeroMemory(&m_ScrollInfo, sizeof(SCROLLINFO));	// ZeroMemory��m_ScrollInfo���N���A.
	m_ScrollInfo.cbSize = sizeof(SCROLLINFO);	// �T�C�Y
	m_ScrollInfo.fMask = SIF_PAGE | SIF_RANGE;	// �t���O
	m_ScrollInfo.nPage = iDrawHeight;	// �`�捂��
	m_ScrollInfo.nMin = 0;	// �ŏ��l
	m_ScrollInfo.nMax = m_Bitmap.bmHeight;	//�ő�l
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);	// SetScrollInfo�ŃZ�b�g.(SetImage��InvalidateRect�Ƒ�4������TRUE���Ȃ��ƃX�N���[���o�[�܂݂������ɍX�V����Ȃ�.)

	// �`��I��.
	EndPaint(m_hWnd, &ps);	// EndPaint�ŕ`��I��.

}

// ���������X�N���[���o�[�C�x���g���̃n���h��OnHScroll.
void CPicture::OnHScroll(UINT nSBCode, UINT nPos){

	// �X�N���[�����擾.
	m_ScrollInfo.fMask = SIF_POS;	// �ʒu�����ύX���[�h(���ꂪ�Ȃ���, �X�N���[���o�[�����̈ʒu�ɖ߂��Ă��܂��̂Œ���!���������O!)
	GetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo);	// �}�X�N��ݒ肵�Ă���GetScrollInfo.(����������!)

	// �X�N���[���o�[����.
	switch (nSBCode) {	// nSBCode���ƂɐU�蕪��.

		// ��ԍ�
		case SB_LEFT:

			// �ʒu���ŏ��l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// ��ԉE
		case SB_RIGHT:

			// �ʒu���ő�l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1��
		case SB_LINELEFT:

			// nPos��0�łȂ���΃f�N�������g.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1��E
		case SB_LINERIGHT:

			// nPos���ő�l-1�łȂ���΃C���N�������g.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1�y�[�W��
		case SB_PAGELEFT:

			// nPage�����炷.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1�y�[�W�E
		case SB_PAGERIGHT:

			// nPage�����₷.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBTRACK:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBPOSITION:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// ����ȊO.
		default:

			break;

	}

	// �X�N���[�����ݒ�.
	SetScrollInfo(m_hWnd, SB_HORZ, &m_ScrollInfo, TRUE);
	// �����o�ɂ��Z�b�g.
	m_iHScrollPos = m_ScrollInfo.nPos;
	// �����̈���쐬���ĉ�ʂ̍X�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�Ŗ����̈�쐬.

}

// ���������X�N���[���o�[�C�x���g���̃n���h��OnVScroll.
void CPicture::OnVScroll(UINT nSBCode, UINT nPos){

	// �X�N���[�����擾.
	m_ScrollInfo.fMask = SIF_POS;	// �ʒu�����ύX���[�h(���ꂪ�Ȃ���, �X�N���[���o�[�����̈ʒu�ɖ߂��Ă��܂��̂Œ���!���������O!)
	GetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo);	// �}�X�N��ݒ肵�Ă���GetScrollInfo.(����������!)

	// �X�N���[���o�[����.
	switch (nSBCode) {	// nSBCode���ƂɐU�蕪��.

		// ��ԏ�
		case SB_TOP:

			// �ʒu���ŏ��l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMin;
			break;

		// ��ԉ�
		case SB_BOTTOM:

			// �ʒu���ő�l��.
			m_ScrollInfo.nPos = m_ScrollInfo.nMax;
			break;

		// 1�s��
		case SB_LINEUP:

			// nPos��0�łȂ���΃f�N�������g.
			if (m_ScrollInfo.nPos > 0) {
				m_ScrollInfo.nPos--;
			}
			break;

		// 1�s��
		case SB_LINEDOWN:

			// nPos���ő�l-1�łȂ���΃C���N�������g.
			if (m_ScrollInfo.nPos < m_ScrollInfo.nMax - 1) {
				m_ScrollInfo.nPos++;
			}
			break;

		// 1�y�[�W��
		case SB_PAGEUP:

			// nPage�����炷.
			m_ScrollInfo.nPos -= m_ScrollInfo.nPage;
			break;

		// 1�y�[�W��
		case SB_PAGEDOWN:

			// nPage�����₷.
			m_ScrollInfo.nPos += m_ScrollInfo.nPage;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBTRACK:
	
			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// �܂݂��h���b�O��.
		case SB_THUMBPOSITION:

			// ������nPos���Z�b�g
			m_ScrollInfo.nPos = nPos;
			break;

		// ����ȊO.
		default:

			break;

	}

	// �X�N���[�����ݒ�.
	SetScrollInfo(m_hWnd, SB_VERT, &m_ScrollInfo, TRUE);
	// �����o�ɂ��Z�b�g.
	m_iVScrollPos = m_ScrollInfo.nPos;
	// �����̈���쐬���ĉ�ʂ̍X�V.
	InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�Ŗ����̈�쐬.

}

// �}�E�X���ړ����Ă��鎞.
void CPicture::OnMouseMove(UINT nFlags, POINT pt){

	// �}�E�X�_�E���t���O�������Ă��鎞.
	if (nFlags == MK_LBUTTON){	// ���{�^����������Ă��鎞.

		// �r�b�g�}�b�v�̑I��.
		HBITMAP hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);	// SelectObject��m_hBitmap��I��.

		// �����ꂽ�ꏊ�ɍ����_���Z�b�g.
		SetPixel(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixel�ō����_���Z�b�g.

		// �O��̏ꏊ���牟���ꂽ�ꏊ�܂ł̒�����`��.
		LineTo(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos);	// LineTo�ŉ����ꂽ�ꏊ�܂ł̒�����`��.

		// �����ꂽ�ꏊ�Ɏn�_���ړ�.
		MoveToEx(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, NULL);	// MoveToEx�Ŏn�_���ړ�.

		// �Â��r�b�g�}�b�v���đI��.
		SelectObject(m_hMemDC, hOld);	// SelectObject��hOld��I��.

		// ��ʍX�V.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ŉ�ʍX�V.

	}
	else{	// �}�E�X�_�E���t���O�������Ă��Ȃ���.

		// �}�E�X�̈ړ��ꏊ�Ɏn�_���ړ�.
		MoveToEx(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, NULL);	// MoveToEx�Ŏn�_���ړ�.

	}
}

// �}�E�X�̍��N���b�N���s��ꂽ���̃n���h��OnLButtonDown.
int CPicture::OnLButtonDown(UINT nFlags, POINT pt){

	// �}�E�X�_�E���t���O�������Ă��鎞.
	if (nFlags == MK_LBUTTON){	// ���{�^����������Ă��鎞.

		// �r�b�g�}�b�v�̑I��.
		HBITMAP hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);	// SelectObject��m_hBitmap��I��.

		// �����ꂽ�ꏊ�ɍ����_���Z�b�g.
		SetPixel(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixel�ō����_���Z�b�g.

		// �Â��r�b�g�}�b�v���đI��.
		SelectObject(m_hMemDC, hOld);	// SelectObject��hOld��I��.

		// ��ʍX�V.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ŉ�ʍX�V.

	}

	// �����Ȃ�0��Ԃ�.
	return 0;	// return��0��Ԃ�.

}

// �}�E�X�̍��{�^���������ꂽ��.
int CPicture::OnLButtonUp(UINT nFlags, POINT pt){

	// �}�E�X�_�E���t���O�������Ă��鎞.
	if (nFlags == MK_LBUTTON){	// ���{�^����������Ă��鎞.

		// �r�b�g�}�b�v�̑I��.
		HBITMAP hOld = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);	// SelectObject��m_hBitmap��I��.

		// �����ꂽ�ꏊ�ɍ����_���Z�b�g.
		SetPixel(m_hMemDC, pt.x + m_iHScrollPos, pt.y + m_iVScrollPos, RGB(0x0, 0x0, 0x0));	// SetPixel�ō����_���Z�b�g.

		// �Â��r�b�g�}�b�v���đI��.
		SelectObject(m_hMemDC, hOld);	// SelectObject��hOld��I��.

		// ��ʍX�V.
		InvalidateRect(m_hWnd, NULL, TRUE);	// InvalidateRect�ŉ�ʍX�V.

	}

	// �����Ȃ�0��Ԃ�.
	return 0;	// return��0��Ԃ�.

}
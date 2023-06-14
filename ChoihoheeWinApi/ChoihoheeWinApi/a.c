/*Chapter 3 ls ���� ��� ��ɾ�.
 ls [�ɼ�] [���ϵ�]
�ϳ� �̻��� ������ �Ӽ��� �����մϴ�.
�ɼ�:
-R ��������� Ž��
-l �� �������� ���� (ũ��� ���� �ð�)
ProcessItem �Լ��� ���� �����ڿ� ���ѵ� ǥ�õ˴ϴ� (Chapter 5 - ���� ����). */

/* �� ���α׷��� ������ �����ݴϴ�:
      1. �˻� �ڵ� �� ���͸� Ž��
      2. ���� �Ӽ�, �ð��� ������ �Ӽ�
      3. �Ϲ� ���ڿ� �Լ��� ����Ͽ� ���� ���� ��� */

      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
      /* BEGIN BOILERPLATE CODE(��ȭ���� ���� �������� �ݺ��Ǵ� �ڵ尡 ���۵˴ϴ�) */

      /*�ֿ���: ����ڰ� �Է��� �ɼǰ� ���� ��Ͽ� ���� ������ �Ӽ��� �����մϴ�.
      ��������� ���͸��� Ž���Ͽ� ���� ���͸��� �ִ� ���ϵ鵵 �����Ͽ� ������ �� �ֽ��ϴ�.
      ������ ������, ���� �� ���� �ð��� ���� �Ӽ��� ������ �� �ֽ��ϴ�.*/
#include <stdio.h>
#include <tchar.h>                                    
#include <Windows.h>
#include "EvryThng.h"

BOOL TraverseDirectory(LPCTSTR, DWORD, LPBOOL);
DWORD FileType(LPWIN32_FIND_DATA);
BOOL ProcessItem(LPWIN32_FIND_DATA, DWORD, LPBOOL);

int _tmain(int argc, LPTSTR argv[])
{
    /*�� �Լ��� ���α׷��� �������Դϴ�. ����ڰ� �Է��� �ɼǰ� ���� ��Ͽ� ����
    ������ �Ӽ��� �����մϴ�. ��������� ���͸��� Ž���Ͽ� ���� ���͸��� �ִ�
    ���ϵ鵵 �����Ͽ� ������ �� �ֽ��ϴ�.*/

    BOOL Flags[MAX_OPTIONS], ok = TRUE;
    TCHAR PathName[MAX_PATH + 1], CurrPath[MAX_PATH + 1];
    LPTSTR pSlash, pFileName;
    int i, FileIndex;

    FileIndex = Options(argc, argv, _T("Rl"), &Flags[0], &Flags[1], NULL);

    /* �˻� ������ "�θ�(parent)"�� ���� �̸� �Ǵ� ���ϵ�ī�� ǥ�������� �� �κ�����
    �����մϴ�. ���� �̸��� �����ø� �������� ���� ���� �� ���̻��Դϴ�. �θ�� �����ð�
    ���Ե� ������ ���λ��Դϴ�. �̴� ��� ��� �� �˻� ���Ͽ� ���� ����˴ϴ�.
    ������ �������� ���� ��� �˻� �������� *�� ����մϴ�. */

    GetCurrentDirectory(MAX_PATH, CurrPath); /* ���� �۾� ���͸��� ������ CurrPath�� �����մϴ�.*/
    if (argc < FileIndex + 1)
        ok = TraverseDirectory(_T("*"), MAX_OPTIONS, Flags);
    else for (i = FileIndex; i < argc; i++) {
        strcpy_s(PathName, _countof(PathName), argv[i]);

        /* ������ ��� ���� ������ �����ø� ã���ϴ�.
        ��θ� �����ϰ� �������� ���� �̸����� ����մϴ�. */

        pSlash = _tstrrchr(PathName, '\\');

        if (pSlash != NULL) {
            *pSlash = '\0';
            SetCurrentDirectory(PathName); /* ���� ��� �̸��� �����մϴ�..*/
            *pSlash = '\\'; pFileName = pSlash + 1;
        }
        else pFileName = PathName;
        ok = TraverseDirectory(pFileName, MAX_OPTIONS, Flags) && ok;
        SetCurrentDirectory(CurrPath);    /* �۾� ���丮�� �����մϴ�. */
    }


    return ok ? 0 : 1; //���̸� 0 �����̸� 1
}

static BOOL TraverseDirectory(LPCTSTR PathName, DWORD NumFlags, LPBOOL Flags)

/* �� �̸��� ���� ������ ������ Ư���� "����"�� �����ϸ� ���͸��� Ž���մϴ�.
   �� �������� ������ "����� ����� ���������� �Ӽ��� �����ϴ� ��"�Դϴ�. */

   /* PathName: Ž���� ��� ��� �Ǵ� ���� ����Դϴ�.  */
{
    HANDLE SearchHandle;
    WIN32_FIND_DATA FindData;
    BOOL Recursive = Flags[0];
    DWORD FType, iPass;
    TCHAR CurrPath[MAX_PATH + 1];

    /* ���͸� �˻� �ڵ��� ���� ��θ��� �����ϴ� ù ��° ���� �̸��� �����ɴϴ�.
    �� ���� �н��� �����մϴ�. ù ��° �н��� ������ ó���ϰ� �� ��° �н��� ���͸���
    ó���մϴ�. */

    GetCurrentDirectory(MAX_PATH, CurrPath);

    for (iPass = 1; iPass <= 2; iPass++) {
        SearchHandle = FindFirstFile(PathName, &FindData);
        if (SearchHandle == INVALID_HANDLE_VALUE) {
            ReportError(_T("Error opening Search Handle."), 0, TRUE);
            return FALSE;
        }
        /* ������ ������ �����ϴ� ������ �˻��ϱ� ���� ���͸���
           �� ���� ���͸��� ��ĵ�մϴ�. */

        do {

            /* �߰ߵ� �� ���Ͽ� ���� ���� ������ �����ɴϴ�. 1�� ��������� ��� �׸���
            �����մϴ�. 2�� ��������� ���͸� �̸��� ǥ���ϰ� ��������� ���� ���͸�
            ������ ó���մϴ�(��� �ɼ��� ������ ���). */

            FType = FileType(&FindData);
            if (iPass == 1) /* ProcessItem �Լ��� "�Ӽ��� ���"�ϴ� ����� �մϴ�. */
                ProcessItem(&FindData, MAX_OPTIONS, Flags);

            /* �� ��° �н������� ���� ���͸��� Ž���մϴ�. */

            if (FType == TYPE_DIR && iPass == 2 && Recursive) {
                _tprintf(_T("\n%s\\%s:"), CurrPath, FindData.cFileName);
                SetCurrentDirectory(FindData.cFileName);
                TraverseDirectory(_T("*"), NumFlags, Flags);
                SetCurrentDirectory(_T(".."));
            }

            /* ���� ���� �Ǵ� ���͸� �̸��� �����ɴϴ�. */

        } while (FindNextFile(SearchHandle, &FindData));

        FindClose(SearchHandle);
    }
    return TRUE;
}

static DWORD FileType(LPWIN32_FIND_DATA pFileData)

/* ���� ������ �˻� ������ �������� ��ȯ�մϴ�.
�����Ǵ� ����:
TYPE_FILE: ������ ���
TYPE_DIR: . �Ǵ� .. �̿��� ���͸��� ���
TYPE_DOT: . �Ǵ� .. ���͸��� ��� */
{
    BOOL IsDir;
    DWORD FType;
    FType = TYPE_FILE;
    IsDir = (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    if (IsDir)
        if (lstrcmp(pFileData->cFileName, _T(".")) == 0
            || lstrcmp(pFileData->cFileName, _T("..")) == 0)
            FType = TYPE_DOT;
        else FType = TYPE_DIR;
    return FType;
}
/*  END OF BOILERPLATE CODE(��ȭ���� ���� �������� �ݺ��Ǵ� �ڵ尡 �������ϴ�) */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

LPTSTR FormatSize(LPTSTR pszBuf, ULONGLONG qwFileSize)
{   // �� �Լ��� ���� ũ�⸦ ���ڿ��� ��ȯ�ϴ� ����� �մϴ�.

   /*�� �ڵ�� ���� ũ�Ⱑ 1024 ����Ʈ �̸��� ���
   ���� ũ�⸦ ����Ʈ ������ ��ȯ�Ͽ� ����մϴ�.*/
    if (qwFileSize < 1024)
        wsprintf(pszBuf, TEXT("%I64u bytes"), qwFileSize);
    /*���� ũ�Ⱑ 1024 * 1024 ����Ʈ �̸��� ���
    ���� ũ�⸦ ų�ι���Ʈ ������ ��ȯ�Ͽ� ����մϴ�.*/
    else if (qwFileSize < 1024 * 1024)
        wsprintf(pszBuf, TEXT("%I64u KB"), qwFileSize / 1024);
    /*���� ũ�Ⱑ 1024 * 1024 * 1024 ����Ʈ �̸��� ���
    ���� ũ�⸦ �ް�����Ʈ ������ ��ȯ�Ͽ� ����մϴ�.*/
    else if (qwFileSize < 1024 * 1024 * 1024)
        wsprintf(pszBuf, TEXT("%I64u MB"), qwFileSize / (1024 * 1024));
    /*���� ũ�Ⱑ �� �̻��� ��� ���� ũ�⸦ �Ⱑ����Ʈ ������ ��ȯ�Ͽ� ����մϴ�.*/
    else
        wsprintf(pszBuf, TEXT("%I64u GB"), qwFileSize / (1024 * 1024 * 1024));

    return pszBuf;   // ��ȯ�� ���ڿ��� ��ȯ
}

//�� �Լ��� ������ �Ӽ��� ����ϴ� ����� �մϴ�.
static BOOL ProcessItem(LPWIN32_FIND_DATA pFileData, DWORD dwOptions, LPBOOL pbCancel)//pbCancel �� �Ű� ������ �Լ��� ��ҵǾ����� ����
{
    static ULONGLONG totalSize = 0;
    TCHAR szFileName[MAX_PATH + 1], szSize[32], szDate[64], szTime[64];
    SYSTEMTIME stUTC, stLocal;
    ULARGE_INTEGER uliSize;

    if (pbCancel != NULL && *pbCancel)
        //pbCancel�� NULL�� �ƴϰ� *pbCancel�� ���� ��� FALSE�� ��ȯ
        return FALSE;

    if (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        //�� �ڵ�� ������ ���͸��� ��� ���͸� �̸��� ����ϰ� TRUE�� ��ȯ�մϴ�.
        _tprintf(_T("%s\n"), pFileData->cFileName);
        return TRUE;
    }

    // �� �ڵ�� ���� ũ�⸦ �����ɴϴ�.
    uliSize.LowPart = pFileData->nFileSizeLow;
    uliSize.HighPart = pFileData->nFileSizeHigh;

    //���� �̸��� ũ�⸦ ����մϴ�.
    _tprintf(_T("%s\t%s\t"), pFileData->cFileName, FormatSize(szSize, uliSize.QuadPart));

    //�� �ڵ�� ������ ������ ���� �ð��� ������ ���� �ð����� ��ȯ�ϰ� ����մϴ�.
    FileTimeToSystemTime(&pFileData->ftLastWriteTime, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
    _tprintf(_T("%02d/%02d/%d %02d:%02d %s\n"), stLocal.wMonth, stLocal.wDay,
        stLocal.wYear, stLocal.wHour % 12, stLocal.wMinute,
        stLocal.wHour < 12 ? _T("AM") : _T("PM")); ULARGE_INTEGER fileSize;

    //��� ������ �� ũ�⸦ �����ϰ� ������ ó���� ������ ����մϴ�.
    fileSize.LowPart = pFileData->nFileSizeLow;
    fileSize.HighPart = pFileData->nFileSizeHigh;
    totalSize += fileSize.QuadPart;
    _tprintf(_T("�� ũ��: %I64u ����Ʈ\n"), totalSize);
    return TRUE;
}
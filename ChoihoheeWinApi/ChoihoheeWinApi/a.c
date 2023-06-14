/*Chapter 3 ls 파일 목록 명령어.
 ls [옵션] [파일들]
하나 이상의 파일의 속성을 나열합니다.
옵션:
-R 재귀적으로 탐색
-l 긴 형식으로 나열 (크기와 수정 시간)
ProcessItem 함수에 따라 소유자와 권한도 표시됩니다 (Chapter 5 - 보안 참조). */

/* 이 프로그램은 다음을 보여줍니다:
      1. 검색 핸들 및 디렉터리 탐색
      2. 파일 속성, 시간을 포함한 속성
      3. 일반 문자열 함수를 사용하여 파일 정보 출력 */

      /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
      /* BEGIN BOILERPLATE CODE(변화없이 여러 군데에서 반복되는 코드가 시작됩니다) */

      /*주요기능: 사용자가 입력한 옵션과 파일 목록에 따라 파일의 속성을 나열합니다.
      재귀적으로 디렉터리를 탐색하여 하위 디렉터리에 있는 파일들도 포함하여 나열할 수 있습니다.
      파일의 소유자, 권한 및 수정 시간과 같은 속성을 나열할 수 있습니다.*/
#include <stdio.h>
#include <tchar.h>                                    
#include <Windows.h>
#include "EvryThng.h"

BOOL TraverseDirectory(LPCTSTR, DWORD, LPBOOL);
DWORD FileType(LPWIN32_FIND_DATA);
BOOL ProcessItem(LPWIN32_FIND_DATA, DWORD, LPBOOL);

int _tmain(int argc, LPTSTR argv[])
{
    /*이 함수는 프로그램의 시작점입니다. 사용자가 입력한 옵션과 파일 목록에 따라
    파일의 속성을 나열합니다. 재귀적으로 디렉터리를 탐색하여 하위 디렉터리에 있는
    파일들도 포함하여 나열할 수 있습니다.*/

    BOOL Flags[MAX_OPTIONS], ok = TRUE;
    TCHAR PathName[MAX_PATH + 1], CurrPath[MAX_PATH + 1];
    LPTSTR pSlash, pFileName;
    int i, FileIndex;

    FileIndex = Options(argc, argv, _T("Rl"), &Flags[0], &Flags[1], NULL);

    /* 검색 패턴을 "부모(parent)"와 파일 이름 또는 와일드카드 표현식으로 두 부분으로
    구분합니다. 파일 이름은 슬래시를 포함하지 않은 가장 긴 접미사입니다. 부모는 슬래시가
    포함된 나머지 접두사입니다. 이는 모든 명령 줄 검색 패턴에 대해 수행됩니다.
    파일이 지정되지 않은 경우 검색 패턴으로 *를 사용합니다. */

    GetCurrentDirectory(MAX_PATH, CurrPath); /* 현재 작업 디렉터리를 가져와 CurrPath에 저장합니다.*/
    if (argc < FileIndex + 1)
        ok = TraverseDirectory(_T("*"), MAX_OPTIONS, Flags);
    else for (i = FileIndex; i < argc; i++) {
        strcpy_s(PathName, _countof(PathName), argv[i]);

        /* 가능한 경우 가장 오른쪽 슬래시를 찾습니다.
        경로를 설정하고 나머지를 파일 이름으로 사용합니다. */

        pSlash = _tstrrchr(PathName, '\\');

        if (pSlash != NULL) {
            *pSlash = '\0';
            SetCurrentDirectory(PathName); /* 이제 경로 이름을 복원합니다..*/
            *pSlash = '\\'; pFileName = pSlash + 1;
        }
        else pFileName = PathName;
        ok = TraverseDirectory(pFileName, MAX_OPTIONS, Flags) && ok;
        SetCurrentDirectory(CurrPath);    /* 작업 디렉토리를 복원합니다. */
    }


    return ok ? 0 : 1; //참이면 0 거짓이면 1
}

static BOOL TraverseDirectory(LPCTSTR PathName, DWORD NumFlags, LPBOOL Flags)

/* 각 이름을 만날 때마다 구현에 특정한 "동작"을 수행하며 디렉터리를 탐색합니다.
   이 버전에서 동작은 "목록을 만들고 선택적으로 속성을 포함하는 것"입니다. */

   /* PathName: 탐색할 상대 경로 또는 절대 경로입니다.  */
{
    HANDLE SearchHandle;
    WIN32_FIND_DATA FindData;
    BOOL Recursive = Flags[0];
    DWORD FType, iPass;
    TCHAR CurrPath[MAX_PATH + 1];

    /* 디렉터리 검색 핸들을 열고 경로명을 만족하는 첫 번째 파일 이름을 가져옵니다.
    두 번의 패스를 수행합니다. 첫 번째 패스는 파일을 처리하고 두 번째 패스는 디렉터리를
    처리합니다. */

    GetCurrentDirectory(MAX_PATH, CurrPath);

    for (iPass = 1; iPass <= 2; iPass++) {
        SearchHandle = FindFirstFile(PathName, &FindData);
        if (SearchHandle == INVALID_HANDLE_VALUE) {
            ReportError(_T("Error opening Search Handle."), 0, TRUE);
            return FALSE;
        }
        /* 지정된 패턴을 만족하는 파일을 검색하기 위해 디렉터리와
           그 하위 디렉터리를 스캔합니다. */

        do {

            /* 발견된 각 파일에 대해 파일 유형을 가져옵니다. 1차 통과에서는 모든 항목을
            나열합니다. 2차 통과에서는 디렉터리 이름을 표시하고 재귀적으로 하위 디렉터리
            내용을 처리합니다(재귀 옵션이 설정된 경우). */

            FType = FileType(&FindData);
            if (iPass == 1) /* ProcessItem 함수는 "속성을 출력"하는 기능을 합니다. */
                ProcessItem(&FindData, MAX_OPTIONS, Flags);

            /* 두 번째 패스에서는 하위 디렉터리를 탐색합니다. */

            if (FType == TYPE_DIR && iPass == 2 && Recursive) {
                _tprintf(_T("\n%s\\%s:"), CurrPath, FindData.cFileName);
                SetCurrentDirectory(FindData.cFileName);
                TraverseDirectory(_T("*"), NumFlags, Flags);
                SetCurrentDirectory(_T(".."));
            }

            /* 다음 파일 또는 디렉터리 이름을 가져옵니다. */

        } while (FindNextFile(SearchHandle, &FindData));

        FindClose(SearchHandle);
    }
    return TRUE;
}

static DWORD FileType(LPWIN32_FIND_DATA pFileData)

/* 파일 유형을 검색 데이터 구조에서 반환합니다.
지원되는 유형:
TYPE_FILE: 파일인 경우
TYPE_DIR: . 또는 .. 이외의 디렉터리인 경우
TYPE_DOT: . 또는 .. 디렉터리인 경우 */
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
/*  END OF BOILERPLATE CODE(변화없이 여러 군데에서 반복되는 코드가 끝났습니다) */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

LPTSTR FormatSize(LPTSTR pszBuf, ULONGLONG qwFileSize)
{   // 이 함수는 파일 크기를 문자열로 변환하는 기능을 합니다.

   /*이 코드는 파일 크기가 1024 바이트 미만인 경우
   파일 크기를 바이트 단위로 변환하여 출력합니다.*/
    if (qwFileSize < 1024)
        wsprintf(pszBuf, TEXT("%I64u bytes"), qwFileSize);
    /*파일 크기가 1024 * 1024 바이트 미만인 경우
    파일 크기를 킬로바이트 단위로 변환하여 출력합니다.*/
    else if (qwFileSize < 1024 * 1024)
        wsprintf(pszBuf, TEXT("%I64u KB"), qwFileSize / 1024);
    /*파일 크기가 1024 * 1024 * 1024 바이트 미만인 경우
    파일 크기를 메가바이트 단위로 변환하여 출력합니다.*/
    else if (qwFileSize < 1024 * 1024 * 1024)
        wsprintf(pszBuf, TEXT("%I64u MB"), qwFileSize / (1024 * 1024));
    /*파일 크기가 그 이상인 경우 파일 크기를 기가바이트 단위로 변환하여 출력합니다.*/
    else
        wsprintf(pszBuf, TEXT("%I64u GB"), qwFileSize / (1024 * 1024 * 1024));

    return pszBuf;   // 변환된 문자열을 반환
}

//이 함수는 파일의 속성을 출력하는 기능을 합니다.
static BOOL ProcessItem(LPWIN32_FIND_DATA pFileData, DWORD dwOptions, LPBOOL pbCancel)//pbCancel 이 매개 변수는 함수가 취소되었는지 여부
{
    static ULONGLONG totalSize = 0;
    TCHAR szFileName[MAX_PATH + 1], szSize[32], szDate[64], szTime[64];
    SYSTEMTIME stUTC, stLocal;
    ULARGE_INTEGER uliSize;

    if (pbCancel != NULL && *pbCancel)
        //pbCancel이 NULL이 아니고 *pbCancel이 참인 경우 FALSE를 반환
        return FALSE;

    if (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        //이 코드는 파일이 디렉터리인 경우 디렉터리 이름을 출력하고 TRUE를 반환합니다.
        _tprintf(_T("%s\n"), pFileData->cFileName);
        return TRUE;
    }

    // 이 코드는 파일 크기를 가져옵니다.
    uliSize.LowPart = pFileData->nFileSizeLow;
    uliSize.HighPart = pFileData->nFileSizeHigh;

    //파일 이름과 크기를 출력합니다.
    _tprintf(_T("%s\t%s\t"), pFileData->cFileName, FormatSize(szSize, uliSize.QuadPart));

    //이 코드는 파일의 마지막 쓰기 시간을 가져와 로컬 시간으로 변환하고 출력합니다.
    FileTimeToSystemTime(&pFileData->ftLastWriteTime, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
    _tprintf(_T("%02d/%02d/%d %02d:%02d %s\n"), stLocal.wMonth, stLocal.wDay,
        stLocal.wYear, stLocal.wHour % 12, stLocal.wMinute,
        stLocal.wHour < 12 ? _T("AM") : _T("PM")); ULARGE_INTEGER fileSize;

    //모든 파일의 총 크기를 추적하고 파일이 처리될 때마다 출력합니다.
    fileSize.LowPart = pFileData->nFileSizeLow;
    fileSize.HighPart = pFileData->nFileSizeHigh;
    totalSize += fileSize.QuadPart;
    _tprintf(_T("총 크기: %I64u 바이트\n"), totalSize);
    return TRUE;
}
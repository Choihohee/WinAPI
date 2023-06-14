/* Chapter 2. Simple Asc2Un implementation */
#include "EvryThng.h"

#define BUF_SIZE 256

BOOL Asc2Un(LPCTSTR fIn, LPCTSTR fOut, BOOL bFailIfExists)

/* ASCII to Unicode file copy function  - Simple implementation
 *      fIn:      Source file pathname
 *      fOut:      Destination file pathname
 *      bFailIfExists:   Do not copy if the destination file already exists
 *   Behavior is modeled after CopyFile */
{
    HANDLE hIn, hOut;
    DWORD fdwOut, nIn, nOut, iCopy;
    CHAR aBuffer[BUF_SIZE] = { 0, };
    WCHAR uBuffer[BUF_SIZE];
    BOOL WriteOK = TRUE;
    int i;


    hIn = CreateFile(fIn, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hIn == INVALID_HANDLE_VALUE) return FALSE;

    fdwOut = bFailIfExists ? CREATE_NEW : CREATE_ALWAYS;

    hOut = CreateFile(fOut, GENERIC_WRITE, 0, NULL, fdwOut, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hOut == INVALID_HANDLE_VALUE) return FALSE;

    while (ReadFile(hIn, aBuffer, BUF_SIZE, &nIn, NULL) && nIn > 0 && WriteOK) {
        for (iCopy = 0; iCopy < nIn; iCopy++)
            uBuffer[iCopy] = (WCHAR)aBuffer[iCopy];

        WriteOK = WriteFile(hOut, uBuffer, 2 * nIn, &nOut, NULL);
    }
    //uBuffer를 char 포인터 p로 형변환한 후, p를 통해 메모리의 일부를 접근하      여 값을 출력
    char* p;
    p = (char*)uBuffer;

    //aBuffer 배열의 요소를 반복해 ASCII 문자로 출력
    for (i = 0; aBuffer[i] != '\0'; i++)
        printf("%c", aBuffer[i]);
    printf("\n");

    //aBuffer배열을 \\uXXXX 형식으로 16진수로 출력
    for (i = 0; aBuffer[i] != '\0'; i++)
        printf("\\u%04x", aBuffer[i]);
    printf("\n");

    //uBuffer의 메모리값을 16진수로 출력
    for (i = 0; i < 16; i++)
        printf("%x ", p[i]);
    printf("\n");

    CloseHandle(hIn);
    CloseHandle(hOut);

    return WriteOK;
}
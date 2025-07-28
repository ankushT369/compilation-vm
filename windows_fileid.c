// windows_fileid.c
#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile = CreateFileA(
        "myfile.txt",
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Error opening file: %lu\n", GetLastError());
        return 1;
    }

    BY_HANDLE_FILE_INFORMATION fileInfo;
    if (GetFileInformationByHandle(hFile, &fileInfo)) {
        unsigned long long fileID =
            ((unsigned long long)fileInfo.nFileIndexHigh << 32) |
            fileInfo.nFileIndexLow;

        printf("File ID (like inode): %llu\n", fileID);
    } else {
        printf("Error: %lu\n", GetLastError());
    }

    CloseHandle(hFile);
    return 0;
}

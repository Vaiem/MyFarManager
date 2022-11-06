﻿
#include<Windows.h>
#include<stdio.h>

extern "C" int MakeSum(int oneItem, int twoItem);

int main()
{
    HANDLE hStdout, hNewScreenBuffer;
    SMALL_RECT srctReadRect;
    SMALL_RECT srctWriteRect;
    CONSOLE_SCREEN_BUFFER_INFO screen_Buffer_info;
    CHAR_INFO* char_info;
    int size_Screen;
    COORD coordBufSize;
    COORD coordBufCoord;
    BOOL fSuccess;
   

   

    // Get a handle to the STDOUT screen buffer to copy from and
    // create a new screen buffer to copy to.

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    hNewScreenBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);                   // reserved; must be NULL
    if (hStdout == INVALID_HANDLE_VALUE ||
        hNewScreenBuffer == INVALID_HANDLE_VALUE)
    {
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
        return 1;
    }

    // Make the new screen buffer the active screen buffer.

    if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
    {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
        return 1;
    }

    if (!GetConsoleScreenBufferInfo(hNewScreenBuffer,&screen_Buffer_info))
    {
        printf("GetConsoleINfoBuffer failed - (%d)\n", GetLastError());
        return 1;
    }

    size_Screen = (int)screen_Buffer_info.dwSize.X * (int)screen_Buffer_info.dwSize.Y;
    char_info = new CHAR_INFO[size_Screen];
    memset(char_info, 0, size_Screen * sizeof(CHAR_INFO));


    char_info[0].Char.UnicodeChar = L'D';
    char_info[0].Attributes = 0x50;

    // Set the source rectangle.

    srctReadRect.Top = 0;    // top left: row 0, col 0
    srctReadRect.Left = 0;
    srctReadRect.Bottom = 1; // bot. right: row 1, col 79
    srctReadRect.Right = 79;

    // The temporary buffer size is 2 rows x 80 columns.

    coordBufSize.Y = 2;
    coordBufSize.X = 80;

    // The top left destination cell of the temporary buffer is
    // row 0, col 0.

    coordBufCoord.X = 0;
    coordBufCoord.Y = 0;

    // Copy the block from the screen buffer to the temp. buffer.

    

    // Set the destination rectangle.

    srctWriteRect.Top = 10;    // top lt: row 10, col 0
    srctWriteRect.Left = 0;
    srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79
    srctWriteRect.Right = 79;

    // Copy from the temporary buffer to the new screen buffer.

    fSuccess = WriteConsoleOutput(
        hNewScreenBuffer, // screen buffer to write to
        char_info,        // buffer to copy from
        screen_Buffer_info.dwSize,     // col-row size of chiBuffer
        coordBufCoord,    // top left src cell in chiBuffer
        &screen_Buffer_info.srWindow);  // dest. screen buffer rectangle
    if (!fSuccess)
    {
        printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
        return 1;
    }
    Sleep(5000);

    // Restore the original active screen buffer.

    if (!SetConsoleActiveScreenBuffer(hStdout))
    {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
        return 1;
    }
    
    return 0;
}




#include<Windows.h>
#include<stdio.h>

struct DataMesseng
{
    DataMesseng(short x,short y,short screenWidth, short LenghtMess) : x_pos(x), y_pos(y), screen_width(screenWidth), lenght_mess(LenghtMess)
    {}
    short x_pos;
    short y_pos;
    short screen_width;
    short lenght_mess;
};

extern "C" int MakeSum(int oneItem, int twoItem);
extern "C" void DrawConsoleHorizontal(CHAR_INFO* buffer_screen,DataMesseng pos,CHAR_INFO infoChar);

int main()
{
    HANDLE hStdout, hNewScreenBuffer;  
    CONSOLE_SCREEN_BUFFER_INFO screen_Buffer_info;
    CHAR_INFO* buffer_screen;
    int size_Screen;
    SMALL_RECT srctWriteRect;
    COORD coordBufCoord {};
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
    buffer_screen = new CHAR_INFO[size_Screen];
    memset(buffer_screen, 0, size_Screen * sizeof(CHAR_INFO));

    CHAR_INFO item;
    item.Char.UnicodeChar = L'D';
    item.Attributes = 0x50;

    srctWriteRect.Top = 10;    // top lt: row 10, col 0
    srctWriteRect.Left = 0;
    srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79
    srctWriteRect.Right = 79;


    DataMesseng pos(10, 2,screen_Buffer_info.dwSize.X,10);
    DrawConsoleHorizontal(buffer_screen, pos , item);
   

    

    // Copy the block from the screen buffer to the temp. buffer.


    // Copy from the temporary buffer to the new screen buffer.

    fSuccess = WriteConsoleOutput(
        hNewScreenBuffer, // screen buffer to write to
        buffer_screen,        // buffer to copy from
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



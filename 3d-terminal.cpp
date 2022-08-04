// 3d-terminal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h> 


// https://stackoverflow.com/questions/12900713/reducing-console-size
void SetWindow(int Width, int Height)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}




int main(){
       
    int width = 150;
    int height = 50;

    SetWindow(width, height);

    //char* screen = new char[width * height + 1];

    wchar_t* screen = new wchar_t[width * height];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    //screen[width * height] = '\0';

    float aspect_ratio = (float)width / (float)height;
    float pixel_aspect_ratio = 11.0f / 24.0f;
    
    for (int frame = 0; frame < 100000; frame++) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {

                float x = float(i) / width * 2.0f - 1.0f;
                float y = float(j) / height * 2.0f - 1.0f;

                //adapt image for screen ration and pixel ration
                x = x * aspect_ratio * pixel_aspect_ratio;

                //move the image
                x = x + cos(frame * 0.001);

                char pixel = ' ';
                if (x * x + y * y < 0.5) {
                    pixel = '#';
                }

                screen[i + j * width] = pixel;
            }
        }
        //printf(screen)
        WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
    }
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

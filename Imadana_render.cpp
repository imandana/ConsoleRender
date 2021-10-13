#include <iostream>
#include <cmath>
#include <cstdlib>

#include <Windows.h>

int row;
int column;
char* buffer;

void draw_line(int x1, int y1, int x2, int y2)
{
	int dX = abs( x2 - x1 );
	int sX = x1 < x2 ? 1 : -1;

	int dY = -abs( y2 - y1 );
	int sY = y1 < y2 ? 1 : -1;

	int err = dX + dY;

	int e2 = 0;
		while(true)
		{
			int atPos = (column* y1 ) + ( x1 + 1 );
			buffer [ atPos ] = '*';

			if( x1 == x2 && y1 == y2 )
					break;

			e2 = 2* err;
			if(e2 >= dY)
			{
				err += dY;
				x1 += sX;
			}
			if(e2 <= dX)
			{
				err += dX;
				y1 += sY;
			}
		}
}

void draw_triangle(int x1, int y1,  int x2, int y2,  int x3, int y3)
{
	draw_line(x1 ,y1 , x2 ,y2);
	draw_line(x2 , y2, x3, y3);
	draw_line(x3 , y3, x1, y1);
}

void draw_text(char* text, unsigned int size, int x, int y)
{
	int atPos = (column* y ) + ( x + 1 );
	int pos = atPos;
	for(int i =0 ; i < size; i++)
	{
		if( text[i] == '\n')
		{
			pos = pos + column - (i + 2) ;
			continue;
		}
		buffer [ pos + i] = text[i];
	}	
}
void draw_buffer_to_screen(char* buf)
{
	std::cout << buf ;
}

int main()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ), &csbi);
	column = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	row    = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	buffer = new char[ row * column ];
	memset(buffer, (int)' ', row * column);
	buffer[  (row * column) - column ] = '\0';

	int initXPos = 4;
	int initYPos = 18;
	int lengthAlas = 32;
	int tinggi = 16;
	int pucuk = -1; // 1 artinya pucuknya dibawah, -1 diatas
	draw_triangle(initXPos, initYPos, initXPos + lengthAlas , initYPos , initXPos + lengthAlas*0.5, (tinggi*pucuk) + initYPos );

	initXPos = 4;
	initYPos = 6;
	lengthAlas = 32;
	tinggi = 16;
	pucuk = 1;
	draw_triangle(initXPos, initYPos, initXPos + lengthAlas , initYPos , initXPos + lengthAlas*0.5, (tinggi*pucuk) + initYPos );

	//MUST!!!
	draw_line(1 , 1, 38, 24);
	draw_line(38, 1, 1, 24);
	//MUST

	char myText[]  = "Created by Imandana Rahimaswara\n Ohayou Gozaimasu..."; 
	draw_text(myText, strlen( myText ), 45, 10);

	draw_buffer_to_screen(buffer);
	getchar();

	delete [] buffer;
	return 0;
}

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showMousePosition(int x, int y)
{   char xStr[10]={0}, yStr[10]={0};
    itoa(x, xStr, 10);
    itoa(y, yStr, 10);
    char mousePosStr[50] = "鼠标位置：（";
	strcat(mousePosStr, xStr);
	strcat(mousePosStr, ", ");
	strcat(mousePosStr, yStr);
	strcat(mousePosStr, "）         ");
	setcolor(BLACK);
	setfont(16, 0, "consolas");
	outtextxy(30, 6, mousePosStr);
}


void run()
{   int y=100;
    PIMAGE pimg;
    
    setbkcolor(WHITE);
    setcolor(RED);
    pimg=newimage();
    getimage(pimg, "arrow.png");

    mouse_msg msg={0}; 
    for(; is_run(); delay_fps(60))
    {   while(mousemsg())
        {   msg = getmouse();
            if(msg.is_left() && msg.is_down())
            {   putimage_withalpha(NULL, pimg, msg.x, msg.y);
			    outtextxy(msg.x+30, msg.y, "鼠标左键按下！");
			}
			if(msg.is_move())
			{   showMousePosition(msg.x, msg.y); 
		    }	   
		}
	}
}

int main()
{   setinitmode(0); 
    initgraph(800, 600);
    setcaption("测试 EGE");
    run();
    closegraph();
} 

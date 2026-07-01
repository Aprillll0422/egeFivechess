#include <graphics.h>
#include <bits/stdc++.h>
using namespace std；

int chessmark;
PIMAGE black,white,button,lockpo;	//图片 
int chess[16][16]={0};		//(空白为0，黑色为1，白色为2)
mouse_msg msg={0};			//鼠标信息 
bool ifbreak=false;			//是否重玩 
int num=0;					//棋子总数 
stack <int> dropchessx;		//记录下子顺序
stack <int> dropchessy;
MUSIC drop,bgm,win,equalmu; //音乐 

//实现重玩与退出
bool click()
{
	for(;is_run();delay_fps(60))
	{
		while(mousemsg())
		{
			msg=getmouse();
			if(msg.is_down()&&msg.is_left())
			{
				//退出
				if(msg.x>=380&&msg.x<=437&&msg.y>=490&&msg.y<=525) 
				{
					
					
					return false;
					
				}
				//重玩
				else if(msg.x>=260&&msg.x<=315&&msg.y>=490&&msg.y<=525)
				{
					for(int i=0;i<16;i++)
					{
						for(int j=0;j<16;j++)
						{
							chess[i][j]=0;
						}
					 } 
					 num=0;
					cleardevice();
					return true;
				}
			}
			
			
		}
	}
		
} 

//判断是否胜利 
bool ifwin(int cek)
{
	int cnt=0;
	//横 
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			if(chess[i][j]==cek)
			{
				++cnt;
				if(cnt==5) return true;
			}
			else
			{
				cnt=0;
			}
			
		}
	}
	//竖 
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			if(chess[j][i]==cek)
			{
				++cnt;
				if(cnt==5) return true;
			}
			else
			{
				cnt=0;
			}
			
		}
	}
	//左斜
	for(int i=4;i<16;i++)
	{
		for(int r=i,c=0;r>=0;--r,++c)
		{
			if(chess[r][c]==cek)
			{
				++cnt;
				if(cnt==5) return true;
			}
			else
			{
				cnt=0;
			}
		}
		 
	}
	for(int i=11;i>0;i--)
	{
		for(int c=i,r=15;c<16;--r,++c)
		{
			if(chess[r][c]==cek)
			{
				++cnt;
				if(cnt==5) return true;
			}
			else
			{
				cnt=0;
			}
		}
		 
	}
	//右斜
	for(int i=11;i>=0;i--) 
	{
		for(int r=i,c=0;r<16;++r,++c)
		{
			if(chess[r][c]==cek)
			{
				++cnt;
				if(cnt==5) return true;
			}
			else
			{
				cnt=0;
			}
		}
	}
	for(int i=11;i>=0;i--)
	{
		for(int r=0,c=i;c<16;++c,++r)
		{
			if(chess[r][c]==cek)
			{
				++cnt;
				if(cnt==5) return true;
			}
			else
			{
				cnt=0;
			}
		}
	}
	return false;
} 


//实现退出按钮
bool out()
{
	while(mousemsg())
	{
		msg=getmouse();
		if(msg.x>=450&&msg.x<=550&&msg.y>=65&&msg.y<=108)
		{
			if(msg.is_down()&&msg.is_left())
			{
				return true;
			}
			else
			{
				break;
			}			
		}
		else break;
	}
	return false;
} 

//打印棋盘
void printchess()
{
	//棋盘 
	outtextxy(275, 0, "欢迎来到五子棋");
				
	outtextxy(75,75,"执子方：");
	switch(chessmark)
	{
		case 1:
			putimage(150,65,black);
			break;
		case 2:
			putimage(150,65,white);
			break;
	}
			
	putimage(480,65,button);
	putimage(330,65,button);
	setfont(25,0,"consolas");
	outtextxy(499,73,"退 出"); 
	outtextxy(349,73,"悔 棋");
	
	setfont(20,0,"consolas"); 
	line(50,150,650,150);
	line(50,150,50,750);
	line(50,750,650,750);
	line(650,150,650,750);
	for(int height=190,width=90;height<750,width<650;height+=40,width+=40)
	{
		line(50,height,650,height);
		line(width,150,width,750);
	}
	
	//棋子
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			if(chess[i][j]==1)
			{
				putimage(i*40+30,j*40+130,black);
			}
			else if(chess[i][j]==2)
			{
				putimage(i*40+30,j*40+130,white);
			}
		}	
	} 
} 
void run()
{
	
	black=newimage();
	getimage(black,"黑子1.png"); 	
	white=newimage();
	getimage(white,"白子1.png");
	button=newimage();
	getimage(button,"button.png");
	lockpo=newimage();
	getimage(lockpo,"lock.png");
	drop.OpenFile("C:/Users/、/Desktop/五子棋/五子棋/落子.mp3"); 
	bgm.OpenFile("C:/Users/、/Desktop/五子棋/五子棋/bgm.mp3");
	win.OpenFile("C:/Users/、/Desktop/五子棋/五子棋/win.mp3");
	equalmu.OpenFile("C:/Users/、/Desktop/五子棋/五子棋/equal.mp3");

	while(1)
	{		
		ifbreak=false;
		//绘制棋盘 
		chessmark=1;
		printchess(); 
		 
		bgm.SetVolume(0.15);
		bgm.Play(0);
		
		
		for(;is_run();delay_fps(60))
		{				
			//下棋		
			while(mousemsg())
			{											
				msg=getmouse();
				bool ifchange=false;
				if(msg.is_down()&&msg.is_left())
				{	
					//实现退出 
					if(msg.x>=480&&msg.x<=580&&msg.y>=65&&msg.y<=108)
					return;				

					//实现悔棋 
					if(msg.x>=330&&msg.x<=430&&msg.y>=65&&msg.y<=108&&!dropchessx.empty()) 
					{

						cleardevice();
						int x=dropchessx.top();
						int y=dropchessy.top();
						dropchessx.pop();
						dropchessy.pop();
						num--;
						switch(chess[x][y])
						{
							case 1:
								chessmark=1;
								break;
							case 2:
								chessmark=2;
								break;
						} 
						chess[x][y]=0;
						putimage(x*40+30,y*40+130,lockpo);						
						printchess();
											
						
					}
					
					if(30<=msg.x&&msg.x<=670&&130<=msg.y&&msg.y<=770&&chess[(msg.x-30)/40][(msg.y-130)/40]==0)
					{
						cleardevice();
						printchess();
						chess[(msg.x-30)/40][(msg.y-130)/40]=chessmark;
						if(chessmark==1)
						{
							putimage(((msg.x-30)/40)*40+30,((msg.y-130)/40)*40+130,black);
							drop.Play(150,330);
							dropchessx.push((msg.x-30)/40);	
							dropchessy.push((msg.y-130)/40);					
							++num;
						}
						else
						{
							putimage(((msg.x-30)/40)*40+30,((msg.y-130)/40)*40+130,white);
							drop.Play(150,330);
							string tmp1,tmp2;
							dropchessx.push((msg.x-30)/40);	
							dropchessy.push((msg.y-130)/40);
							++num;
						}
						ifchange=true;
								
					}
					//更换执子方 判断输赢 
					if(ifchange)
					{
						
						//判断输赢
						if(ifwin(1))
						{
							//blackwin
							PIMAGE block=newimage();
							getimage(block,"弹框.png");
							putimage(150,350,block);
							PIMAGE blockin=newimage();
							getimage(block,"弹框小.png");
							putimage(215,390,block);
							outtextxy(315,420,"黑子胜！"); 
							PIMAGE button=newimage();
							outtextxy(260,490,"       ");				
							outtextxy(260,510,"       "); 
							outtextxy(380,490,"       ");
							outtextxy(380,510,"       ");
							outtextxy(260,500," 重 玩 ");
							outtextxy(380,500," 退 出 ");
							bgm.Stop(); 
							win.Play(0,900);
							if(click())
							{
								while(!dropchessx.empty())
								{
									dropchessx.pop();
								}
								while(!dropchessy.empty())
								{
									dropchessy.pop();
								}
							
								ifbreak=true;
								break;
							}
							else
							{
								return;	
							} 
						}
						else if(ifwin(2))
						{
							//whitewin
							PIMAGE block=newimage();
							getimage(block,"弹框.png");
							putimage(150,350,block);
							PIMAGE blockin=newimage();
							getimage(block,"弹框小.png");
							putimage(215,390,block);
							outtextxy(315,420,"白子胜！"); 
							PIMAGE button=newimage();
							outtextxy(260,490,"       ");				
							outtextxy(260,510,"       "); 
							outtextxy(380,490,"       ");
							outtextxy(380,510,"       ");
							outtextxy(260,500," 重 玩 ");
							outtextxy(380,500," 退 出 ");
							bgm.Stop(); 
							win.Play(0,900);
							if(click())
							{
								while(!dropchessx.empty())
								{
									dropchessx.pop();
								}
								while(!dropchessy.empty())
								{
									dropchessy.pop();
								}
								ifbreak=true;
								break;
							}
							else
							{
								return;	
							} 
						} 
						
						else if(num==225)
						{
							//equal
							PIMAGE block=newimage();
							getimage(block,"弹框.png");
							putimage(150,350,block);
							PIMAGE blockin=newimage();
							getimage(block,"弹框小.png");
							putimage(215,390,block);
							outtextxy(315,420,"游戏结束，平局"); 
							PIMAGE button=newimage();
							outtextxy(260,490,"       ");				
							outtextxy(260,510,"       "); 
							outtextxy(380,490,"       ");
							outtextxy(380,510,"       ");
							outtextxy(260,500," 重 玩 ");
							outtextxy(380,500," 退 出 ");
							bgm.Stop(); 
							equalmu.Play(0,900);
							if(click())
							{
								while(!dropchessx.empty())
								{
									dropchessx.pop();
								}
								while(!dropchessy.empty())
								{
									dropchessy.pop();
								}
								ifbreak=true;							
							}
							else
							{
								return;	
							} 
							break;
						}
						
						//更换执子方
						
						switch(chessmark)
						{
							case 1:
								putimage(150,65,white);
								chessmark=2;
								break;
							case 2:
								putimage(150,65,black);
								chessmark=1;
								break;
						} 
						
					}
								
				}
			}
			if(ifbreak) break;
						
		}
		
	}
	
}


int main()
{
	setinitmode(0);
	initgraph(700,800);
	setcaption("五子棋");
	setbkcolor(WHITE);
	setcolor(BLACK);
	setfont(20,0,"consolas");
	run();
		
} 


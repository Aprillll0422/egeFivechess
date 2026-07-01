#include <graphics.h>
#include <ege/sys_edit.h>
#include <bits/stdc++.h>
using namespace std;
int chess[16][16]={0};
mouse_msg msg={0};
bool ifbreak=false;
int num=0;
MUSIC drop,bgm,win,equalmu; 

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


void run()
{
	PIMAGE black=newimage();
	getimage(black,"黑子1.png"); 
	PIMAGE white=newimage();
	getimage(white,"白子1.png");
	drop.OpenFile("C:/Users/、/Desktop/五子棋/落子.mp3"); 
	bgm.OpenFile("C:/Users/、/Desktop/五子棋/bgm.mp3");
	win.OpenFile("C:/Users/、/Desktop/五子棋/win.mp3");
	equalmu.OpenFile("C:/Users/、/Desktop/五子棋/equal.mp3");
	
	while(1)
	{		
		ifbreak=false;
		//绘制棋盘 
		outtextxy(200, 0, "欢迎来到五子棋(AprillllMode)");
		outtextxy(75,75,"执子方：");
		putimage(150,65,black);
		line(50,150,650,150);
		line(50,150,50,750);
		line(50,750,650,750);
		line(650,150,650,750);
		for(int height=190,width=90;height<750,width<650;height+=40,width+=40)
		{
			line(50,height,650,height);
			line(width,150,width,750);
		}
		
		bgm.SetVolume(0.15);
		bgm.Play(0);
		int chessmark=1;
		for(;is_run();delay_fps(60))
		{	
			
			//下棋(黑色为1，白色为2)		
			while(mousemsg())
			{	
							
				//outtextxy(0,0,to_string(chessmark));	
				msg=getmouse();
				bool ifchange=false;
				if(msg.is_down()&&msg.is_left())
				{
					
					//int chessx[16]={30,70,110,+40->670}
					//int chessy[16]={130,170+40->770}
					if(30<=msg.x&&msg.x<=670&&130<=msg.y&&msg.y<=770&&chess[(msg.x-30)/40][(msg.y-130)/40]==0)
					{
						chess[(msg.x-30)/40][(msg.y-130)/40]=chessmark;
						if(chessmark==1)
						{
							putimage(((msg.x-30)/40)*40+30,((msg.y-130)/40)*40+130,black);
							drop.Play(150,330);						
							++num;
						}
						else
						{
							putimage(((msg.x-30)/40)*40+30,((msg.y-130)/40)*40+130,white);
							drop.Play(150,330);
						
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
	setcaption("五子棋(AprillllMode)");
	setbkcolor(WHITE);
	setcolor(BLACK);
	setfont(20,0,"consolas");
	run();
		
} 
void inputname(int a)
{
		//基础设置 
	int TextHeight = 15;
	int place=a*TextHeight+10;
	sys_edit name;
	name.create(true);								//创建，false表示单行
	name.move(0, place);							//设置位置
	name.size(TextHeight, 5*TextHeight);			//设置尺寸，高度一般要比字的高多一点，因为输入框的边框也占一定大小。
	name.setbgcolor(WHITE);							//设置背景颜色
	name.setcolor(BLACK);							//设置文字颜色
	name.setfont(TextHeight, 0, "consolas");	//设置字体
	
	//设置输入最大长度
	int maxLen = 60;
	name.setmaxlen(maxLen);					
	name.setfocus();

	//创建输入缓存区
	int buffSize = 100;
	char strBuffer[100] = "";
	int buffLen = 0;
	for(;is_run();delay_fps(60))
	{
			bool isOutput = false;
	
		//检测到回车键弹起就标记输出
		if(kbmsg()) {
			key_msg msg = getkey();
			if ((msg.key == key_enter) && (msg.msg == key_msg_up)) {
				isOutput = true;
			}
		}
			
		//需要输出
		if (isOutput) {
			//获取输入框内容字符串
			name.gettext(buffSize, strBuffer);
			//计算字符串长度
			buffLen = strlen(strBuffer);
			name.settext("");
		}
		
		cleardevice();
		switch(a) 
		{
			case 1:
				xyprintf(0,place, "请输入先手的昵称:");
				break;
			case 2:
				xyprintf(0,place, "请输入后手的昵称:");
				break;
		
		}
		
	
		//如果缓存区有内容就输出
		if (strBuffer[0] != '\0') 
		{
			
			switch(a) 
			{
				case 1:
					xyprintf(0,place+TextHeight , "先手为：%s",strBuffer);
					
					break;
				case 2:
					xyprintf(0,place+TextHeight , "后手为：%s",strBuffer);
					
					break;
			
			}
			++a;
			continue;
							
		}
	}
	
} 

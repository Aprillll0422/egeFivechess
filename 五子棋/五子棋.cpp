#include <graphics.h>
#include <bits/stdc++.h>
using namespace std;

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
		cnt=0;
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
		cnt=0;
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
		cnt=0;
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
		cnt=0;
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
		cnt=0;
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
		cnt=0;
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

// === AI 相关 ===
//评估在(x,y)放置颜色cek的棋子可形成的连子分数
int evalPos(int x,int y,int cek)
{
	int dx[4]={1,0,1,1};
	int dy[4]={0,1,1,-1};
	int total=0;
	for(int d=0;d<4;d++)
	{
		int cnt=1;			//包含(x,y)处假设的棋子
		int opens=0;		//两端空位数
		int r=x+dx[d],c=y+dy[d];
		while(r>=0&&r<16&&c>=0&&c<16&&chess[r][c]==cek){ ++cnt; r+=dx[d]; c+=dy[d]; }
		if(r>=0&&r<16&&c>=0&&c<16&&chess[r][c]==0) ++opens;
		r=x-dx[d]; c=y-dy[d];
		while(r>=0&&r<16&&c>=0&&c<16&&chess[r][c]==cek){ ++cnt; r-=dx[d]; c-=dy[d]; }
		if(r>=0&&r<16&&c>=0&&c<16&&chess[r][c]==0) ++opens;
		int score=0;
		if(cnt>=5) score=100000;
		else if(cnt==4){ if(opens==2) score=10000; else if(opens==1) score=1000; }
		else if(cnt==3){ if(opens==2) score=1000; else if(opens==1) score=100; }
		else if(cnt==2){ if(opens==2) score=100; else if(opens==1) score=10; }
		else if(cnt==1){ if(opens==2) score=10; else if(opens==1) score=1; }
		total+=score;
	}
	return total;
}

//AI选择落子位置（后手为白子，颜色为2）
void aiMove(int &bx,int &by)
{
	bx=-1; by=-1;
	//棋盘为空则下中央
	bool any=false;
	for(int i=0;i<16&&!any;i++)
		for(int j=0;j<16&&!any;j++)
			if(chess[i][j]!=0) any=true;
	if(!any){ bx=7; by=7; return; }
	//1.AI能直接获胜
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
			if(chess[i][j]==0&&evalPos(i,j,2)>=100000){ bx=i; by=j; return; }
	//2.阻挡对手获胜
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
			if(chess[i][j]==0&&evalPos(i,j,1)>=100000){ bx=i; by=j; return; }
	//3.综合评分选择最佳位置
	int bestScore=-1;
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
			if(chess[i][j]!=0) continue;
			//只考虑已有棋子附近的空位
			bool hasNeighbor=false;
			for(int di=-2;di<=2&&!hasNeighbor;di++)
				for(int dj=-2;dj<=2&&!hasNeighbor;dj++)
				{ int ni=i+di,nj=j+dj; if(ni>=0&&ni<16&&nj>=0&&nj<16&&chess[ni][nj]!=0) hasNeighbor=true; }
			if(!hasNeighbor) continue;
			int off=evalPos(i,j,2);	//进攻分
			int def=evalPos(i,j,1);	//防守分
			int score=off*2+def;
			if(score>bestScore){ bestScore=score; bx=i; by=j; }
		}
	}
	if(bx==-1)	//兜底：任意空位
	{
		for(int i=0;i<16&&bx==-1;i++)
			for(int j=0;j<16&&bx==-1;j++)
				if(chess[i][j]==0){ bx=i; by=j; }
	}
	if(bx==-1){ bx=7; by=7; }
}

//显示结算弹框 type:1黑胜 2白胜 3平局 返回true重玩 false退出
bool showResult(int type)
{
	PIMAGE block=newimage();
	getimage(block,"弹框.png");
	putimage(150,350,block);
	getimage(block,"弹框小.png");
	putimage(215,390,block);
	if(type==1) outtextxy(315,420,"黑子胜！"); 
	else if(type==2) outtextxy(315,420,"白子胜！"); 
	else outtextxy(315,420,"游戏结束，平局"); 
	outtextxy(260,490,"       ");				
	outtextxy(260,510,"       "); 
	outtextxy(380,490,"       ");
	outtextxy(380,510,"       ");
	outtextxy(260,500," 重 玩 ");
	outtextxy(380,500," 退 出 ");
	bgm.Stop(); 
	if(type==3) equalmu.Play(0,900);
	else win.Play(0,900);
	return click();
}

//重置棋盘开始新一局
void resetBoard()
{
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
			chess[i][j]=0;
	num=0;
	while(!dropchessx.empty()) dropchessx.pop();
	while(!dropchessy.empty()) dropchessy.pop();
	cleardevice();
	chessmark=1;
	printchess();
	bgm.SetVolume(0.15);
	bgm.Play(0);
}

//落子并判断输赢/切换执子方 返回0继续 1重玩 2退出
int placeAndCheck(int x,int y)
{
	cleardevice();
	printchess();
	chess[x][y]=chessmark;
	if(chessmark==1) putimage(x*40+30,y*40+130,black);
	else putimage(x*40+30,y*40+130,white);
	drop.Play(150,330);
	dropchessx.push(x);
	dropchessy.push(y);
	++num;
	if(ifwin(chessmark))
	{
		if(showResult(chessmark)){ resetBoard(); return 1; }
		return 2;
	}
	if(num==225)
	{
		if(showResult(3)){ resetBoard(); return 1; }
		return 2;
	}
	//更换执子方
	if(chessmark==1){ chessmark=2; putimage(150,65,white); }
	else { chessmark=1; putimage(150,65,black); }
	return 0;
}

void run(bool pve)
{
	black=newimage();
	getimage(black,"黑子1.png"); 	
	white=newimage();
	getimage(white,"白子1.png");
	button=newimage();
	getimage(button,"button.png");
	lockpo=newimage();
	getimage(lockpo,"lock.png");
	drop.OpenFile("落子.mp3");
	bgm.OpenFile("bgm.mp3");
	win.OpenFile("win.mp3");
	equalmu.OpenFile("equal.mp3");

	while(1)
	{		
		ifbreak=false;
		resetBoard();
		
		for(;is_run();delay_fps(60))
		{
			//人机对战时AI(白子,后手)自动下棋
			if(pve&&chessmark==2)
			{
				delay_ms(300);
				int ax,ay;
				aiMove(ax,ay);
				int r=placeAndCheck(ax,ay);
				if(r==2) return;
				if(r==1) break;
				continue;
			}
			//下棋（人机对战时AI回合禁止玩家操作）
			while(mousemsg())
			{
				msg=getmouse();
				if(msg.is_down()&&msg.is_left())
				{
					//实现退出
				if(msg.x>=480&&msg.x<=580&&msg.y>=65&&msg.y<=108)
				{
					bgm.Stop();
					return;
				}

					//实现悔棋（人机对战时仅玩家回合可悔棋）
					if(msg.x>=330&&msg.x<=430&&msg.y>=65&&msg.y<=108&&!dropchessx.empty()&&(!pve||chessmark==1)) 
					{
						cleardevice();
						int undoCount=(pve?2:1);	//人机对战悔两步,回到玩家回合
						int lastColor=0,lx=-1,ly=-1;
						for(int u=0;u<undoCount&&!dropchessx.empty();u++)
						{
							int x=dropchessx.top();
							int y=dropchessy.top();
							dropchessx.pop();
							dropchessy.pop();
							num--;
							lastColor=chess[x][y];
							chess[x][y]=0;
							lx=x; ly=y;
						}
						if(lx>=0) putimage(lx*40+30,ly*40+130,lockpo);
						if(pve) chessmark=1; else chessmark=lastColor;
						printchess();
					}
					
					//落子（人机对战时仅玩家回合可落子）
					if(30<=msg.x&&msg.x<=670&&130<=msg.y&&msg.y<=770&&chess[(msg.x-30)/40][(msg.y-130)/40]==0&&(!pve||chessmark==1))
					{
						int x=(msg.x-30)/40,y=(msg.y-130)/40;
						int r=placeAndCheck(x,y);
						if(r==2) return;
						if(r==1){ ifbreak=true; break; }
					}
				}
			}
			if(ifbreak) break;
		}
	}
	
}

//选择页面 返回0双人 1人机 -1退出
int selectMode()
{
	cleardevice();
	setbkcolor(WHITE);
	setcolor(BLACK);
	const char* title="请选择游戏模式";
	setfont(40,0,"consolas");
	outtextxy((700-textwidth(title))/2,150,title);

	setfont(30,0,"consolas");
	const char* s1="双人对战";
	rectangle(150,300,550,400);
	outtextxy((700-textwidth(s1))/2,335,s1);

	const char* s2="人机对战";
	rectangle(150,450,550,550);
	outtextxy((700-textwidth(s2))/2,485,s2);

	setfont(25,0,"consolas");
	const char* s3="退出";
	rectangle(300,630,400,680);
	outtextxy((700-textwidth(s3))/2,642,s3);

	setfont(20,0,"consolas");
	for(;is_run();delay_fps(60))
	{
		while(mousemsg())
		{
			msg=getmouse();
			if(msg.is_down()&&msg.is_left())
			{
				if(msg.x>=150&&msg.x<=550&&msg.y>=300&&msg.y<=400) return 0;	//双人
				if(msg.x>=150&&msg.x<=550&&msg.y>=450&&msg.y<=550) return 1;	//人机
				if(msg.x>=300&&msg.x<=400&&msg.y>=630&&msg.y<=680) return -1;	//退出
			}
		}
	}
	return -1;
}


int main()
{
	setinitmode(0);
	initgraph(700,800);
	setcaption("五子棋");
	setbkcolor(WHITE);
	setcolor(BLACK);
	setfont(20,0,"consolas");
	while(1)
	{
		int mode=selectMode();
		if(mode==0) run(false);
		else if(mode==1) run(true);
		else break;
	}
	closegraph();
	return 0;	
} 

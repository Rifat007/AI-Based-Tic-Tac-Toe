# include "iGraphics.h"
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
struct bool_{
	unsigned int flMainMenu2: 1;
	unsigned int flMainMenu: 1;
	unsigned int flMainGame:1;
	unsigned int flChooseOpponent:1;
	unsigned int flBack2MainMenu: 1;
	unsigned int flBack2MainMenu1: 1;
	unsigned int flInstructions: 1;
	unsigned int flHighScore: 1;
	unsigned int flDraw: 1;
	unsigned int flAssure: 1;
	unsigned int flAssure2: 1;
	unsigned int easy:1;
	unsigned int flmode:1;
}bool_type;


//bool_type.flMainMenu2=1,bool_type.flMainMenu=0,bool_type.flMainGame=0,bool_type.flChooseOpponent=0,bool_type.flBack2MainMenu=0,bool_type.flBack2MainMenu1=0,bool_type.flInstructions=0,bool_type.flHighScore=0,bool_type.flDraw=0,bool_type.flAssure=0,bool_type.flAssure2=0;//if these variable==1 then corresponding options are selected
char press,sound;//when sound 1 sound is on else when 0 it's off.
char gameboard[16+1],turn=1;//When turn is odd first player play and when even second one plays.
char yoursign='X',oppsign='O';//your sign denotes player1's and oppsign denotes player2's sign(X and O respectively)
char selectmode;//when mode is 1 then man vs. man else when 2 man vs. computer when player one wins then 3 else when player-2 it's 4.so then no one'll be able to play.
int computermove;//defines computer's move by selecting random number%9 in man vs computer mode
//double cell_match1x,cell_match1y,cell_match2x,cell_match2y;//identifies coordinate of center of two of the 1st and 3rd of match cells
double base_x=290,base_y=150,inc=140;//indicates the coordinate of our game board and inc variable denotes the width of each cell
int youwin(void);//cheks whether first player won(using is_win function)
int opponentwin(void);//cheks whether second player or the computer won(using is_win function)
int is_win(char a);//checks which player won according to the parameter sign('X' or 'O')
void playturn1(void);//man vs. computer easy mode
void playturn2(void);//man vs. computer hard mode
int validcell(int ch);//cheks whether the choosen cell (indexed gameboard[0] to gameboard[8]) is empty or not
void init(void);//after end of the game this sets everything like before if he want to play again
void drawCross(int p,int q);// for drawing cross
void drawHorizontalLine(int a,int b);//when one player has won by placing his sign's horizontally(by row)this draws line
void drawVerticalLine(int a,int b);//when one player has won by placing his sign's vertically(by column)this draws line
void drawbakaline1(int a,int b);//when one player has won by placing his sign's diagonally(by diagonal)this draws line '\'
void drawbakaline2(int a,int b);//when one player has won by placing his sign's diagonally(by diagonal)this draws line '/'
void Drawgrid_Maingame(void);//this draws the game board or grids according to the turn and sign placed by players(according to the values of gameboard array)
void DrawBack2MainMenu(void);//this defines if a player has gone to instruction or something before playing once (because in that case we don't wanna show resume option)
void DrawChooseOpponent(void);//this function chooses opponent whether man or computer according to the click of user
void DrawInstructions(void);//this draws rules of playing if the user wants to(by identifying where user clicks his computer mouse)
void DrawMainMenu(void);//it contains New Game, Instructions, Exit options
void DrawMainMenu2(void);// it contains Resume, Instructions, New Game , Exit options
void DrawAssure(void);//it is for the surity when Exit button is pressed
void DrawAssure2(void);//it is for the surity when Exit button is pressed and return Resume mode
void DrawBack2MainMenu1(void);//this defines if a player has gone to instruction or something before playing once (because in that case we don't wanna show resume option) ,it returns Resume Button
//here functions are arranged in an order according to their prototype.[which function has prototype here before another,after main() there are original function in same order]
void sound_afterturn(void);//after giving turn this occurs sound.
void play_mode(void);//easy or hard mode.




int MAX=INT_MAX;
int MIN=INT_MIN;
int eva_score(void);
int minimax(int dep,bool max,int alpha,int beta);
int bestmove(void);

int max1(int a,int b)
{
	return (((a)>(b)) ? (a):(b));
}

int min1(int a,int b)
{
	return (((a)<(b)) ? (a):(b));
}

void iDraw()
{
	iClear();
	iShowBMP(0,0,"TicTac.bmp");
	iSetColor(255,255,255);//white
    iText(350, 50, "Press any key & press 'end' for exit",GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(999,999,999);
	iText(420,520, "Submitted by",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(420,460, "Rifat Rahman",GLUT_BITMAP_TIMES_ROMAN_24);
	if(press=='a')
	{
		if(bool_type.flMainMenu2)
		{
			//initialize();
			DrawMainMenu2();
		}
		else if(bool_type.flMainMenu) DrawMainMenu();
		else if(bool_type.flChooseOpponent) DrawChooseOpponent();
		else if(bool_type.flmode)play_mode();
		else if (bool_type.flMainGame) Drawgrid_Maingame();
		else if(bool_type.flInstructions) DrawInstructions();
		else if(bool_type.flAssure) DrawAssure();
		else if(bool_type.flAssure2) DrawAssure2();

		if(bool_type.flBack2MainMenu) DrawBack2MainMenu();
		if(bool_type.flBack2MainMenu1) DrawBack2MainMenu1();
	}
}


void iMouseMove(int mx, int my)
{

}


void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(bool_type.flBack2MainMenu)
		{
			iRectangle(base_x+100,base_y-110,40*8,40);
			if(mx>=base_x+100 && mx<=base_x+100+40*8 && my>=base_y-110 && my <= base_y-110+10*4)
			{
				bool_type.flBack2MainMenu=0;
				bool_type.flBack2MainMenu1=0;
				bool_type.flMainMenu2=1;
				bool_type.flInstructions=0;
				bool_type.flMainGame=0;
				bool_type.flChooseOpponent=0;
				bool_type.flHighScore=0;
			}
		}
		if(bool_type.flBack2MainMenu1)
		{
			iRectangle(base_x+100,base_y-110,40*8,40);
			if(mx>=base_x+100 && mx<=base_x+100+40*8 && my>=base_y-110 && my <= base_y-110+10*4)
			{
				bool_type.flBack2MainMenu1=0;
				bool_type.flBack2MainMenu=0;
				bool_type.flMainMenu=1;
				bool_type.flInstructions=0;
				bool_type.flMainGame=0;
				bool_type.flChooseOpponent=0;
				bool_type.flHighScore=0;
			}
		}
		if(bool_type.flMainMenu)
        {

			if(mx>=50*4 && mx<=50*4+50*4 && my>=98*4 && my<=98*4+17*4)
            {
                bool_type.flMainMenu=0;
                bool_type.flChooseOpponent=0;
				bool_type.flHighScore=0;
				bool_type.flmode=0;
                bool_type.flBack2MainMenu1=1;
				bool_type.flMainGame=1;
            }
            else if(mx>=50*4 && mx<=50*4+50*4 && my>=77*4 && my<=77*4+17*4)
            {
                bool_type.flMainMenu=0;
                bool_type.flInstructions=1;
                bool_type.flBack2MainMenu1=1;
            }
			else if(mx>=50*4 && mx<=50*4+50*4 && my>=56*4 && my<=56*4+17*4)
			{
				bool_type.flMainMenu=0;
                bool_type.flChooseOpponent=1;
				bool_type.flHighScore=0;
                bool_type.flBack2MainMenu1=1;
				//init();
			}
			else if(mx>=50*4 && mx<=50*4+50*4 && my>=35*4 && my<=35*4+17*4)
			{
				//exit(0);
				bool_type.flAssure2=1;
				bool_type.flMainMenu=0;
			}
        }
		else if(bool_type.flMainMenu2)
        {

			if(mx>=50*4 && mx<=50*4+50*4 && my>=98*4 && my<=98*4+17*4)
            {
                bool_type.flMainMenu=0;
				bool_type.flMainMenu2=0;
                bool_type.flChooseOpponent=1;
				bool_type.flHighScore=0;
                bool_type.flBack2MainMenu=1;
				bool_type.flMainGame=0;
            }
            else if(mx>=50*4 && mx<=50*4+50*4 && my>=77*4 && my<=77*4+17*4)
            {
                bool_type.flMainMenu2=0;
                bool_type.flInstructions=1;
                bool_type.flBack2MainMenu=1;
            }
			else if(mx>=50*4 && mx<=50*4+50*4 && my>=56*4 && my<=56*4+17*4)
			{
				//exit(0);
				bool_type.flAssure=1;
				bool_type.flMainMenu2=0;
			}
        }

		else if(bool_type.flChooseOpponent)
        {
			//iRectangle(185,325,235,50);man  vs comp
            if(mx>=185 && mx<=185+235 && my>=325 && my<=325+50)
            {
                bool_type.flmode=1;
				//bool_type.flBack2MainMenu1=0;
				//bool_type.flBack2MainMenu=1;
				bool_type.flChooseOpponent=0;

            }
			//iRectangle(185,425,235,50);
            else if(mx>=185 && mx<=185+235 && my>=425 && my<=425+50)
            {
                selectmode=1;
				bool_type.flBack2MainMenu1=1;
				bool_type.flBack2MainMenu=0;
				bool_type.flChooseOpponent=0;
                bool_type.flMainGame=1;
				init();
            }
            //val=( ((mx-73*4)*(mx-73*4))/(double)(45*4*4*45) )+( ((my-64*4)*(my-64*4))/(double)(10*10*4*4) )-1;
           // if(selectmode>0)
    //        {
    //            bool_type.flChooseOpponent=0;
    //            bool_type.flMainGame=1;
    //            //flBack2MainMenu1=1;
				//init();
    //        }
        }
		else if(bool_type.flmode)
		{
			//iRectangle(185,325,235,50);Hard
            if(mx>=185 && mx<=185+235 && my>=325 && my<=325+50)
            {
                selectmode=2;
				bool_type.easy=0;
				bool_type.flBack2MainMenu1=1;
				bool_type.flBack2MainMenu=0;
				bool_type.flMainGame=1;
				bool_type.flmode=0;
				init();
            }
			//iRectangle(185,425,235,50);
            else if(mx>=185 && mx<=185+235 && my>=425 && my<=425+50)
            {
                selectmode=2;
				bool_type.easy=1;
				bool_type.flBack2MainMenu1=1;
				bool_type.flBack2MainMenu=0;
				bool_type.flMainGame=1;
				bool_type.flmode=0;
				init();
            }
		}
		else if(bool_type.flAssure)
		{
			//iRectangle(160,475,60,30);
			if(mx>=160 && mx<=160+60 && my>=475 && my<=475+30)
			{
				exit(0);
			}
			//iRectangle(260,475,60,30);
			if(mx>=260 && mx<=260+60 && my>=475 && my<=475+30)
			{
				bool_type.flMainMenu2=1;
				bool_type.flAssure=0;
			}
		}
		else if(bool_type.flAssure2)
		{
			//iRectangle(160,475,60,30);
			if(mx>=160 && mx<=160+60 && my>=475 && my<=475+30)
			{
				exit(0);
			}
			//iRectangle(260,475,60,30);
			if(mx>=260 && mx<=260+60 && my>=475 && my<=475+30)
			{
				bool_type.flMainMenu=1;
				bool_type.flAssure2=0;
			}
		}
		else if(bool_type.flMainGame){

			if((mx>=base_x&&mx<=base_x+inc)&&(my>=base_y&&my<=base_y+inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[12]){
					gameboard[12]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[12]&&(selectmode==1)){
					gameboard[12]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+inc&&mx<=base_x+2*inc)&&(my>=base_y&&my<=base_y+inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[13]){
					gameboard[13]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[13]&&(selectmode==1)){
					gameboard[13]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+2*inc&&mx<=base_x+3*inc)&&(my>=base_y&&my<=base_y+inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[14]){
					gameboard[14]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[14]&&(selectmode==1)){
					gameboard[14]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+3*inc&&mx<=base_x+4*inc)&&(my>=base_y&&my<=base_y+inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[15]){
					gameboard[15]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[15]&&(selectmode==1)){
					gameboard[15]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}

			else if((mx>=base_x&&mx<=base_x+inc)&&(my>base_y+inc&&my<=base_y+2*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[8]){
					gameboard[8]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[8]&&(selectmode==1)){
					gameboard[8]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+inc&&mx<=base_x+2*inc)&&(my>base_y+inc&&my<=base_y+2*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[9]){
					gameboard[9]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[9]&&(selectmode==1)){
					gameboard[9]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}

			else if((mx>base_x+2*inc&&mx<=base_x+3*inc)&&(my>base_y+inc&&my<=base_y+2*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[10]){
					gameboard[10]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[10]&&(selectmode==1)){
					gameboard[10]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+3*inc&&mx<=base_x+4*inc)&&(my>base_y+inc&&my<=base_y+2*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[11]){
					gameboard[11]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[11]&&(selectmode==1)){
					gameboard[11]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}



			else if((mx>=base_x&&mx<=base_x+inc)&&(my>base_y+2*inc&&my<=base_y+3*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[4]){
					gameboard[4]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[4]&&(selectmode==1)){
					gameboard[4]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+inc&&mx<=base_x+2*inc)&&(my>base_y+2*inc&&my<=base_y+3*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[5]){
					gameboard[5]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[5]&&(selectmode==1)){
					gameboard[5]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+2*inc&&mx<=base_x+3*inc)&&(my>base_y+2*inc&&my<=base_y+3*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[6]){
					gameboard[6]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[6]&&(selectmode==1)){
					gameboard[6]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+3*inc&&mx<=base_x+4*inc)&&(my>base_y+2*inc&&my<=base_y+3*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[7]){
					gameboard[7]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[7]&&(selectmode==1)){
					gameboard[7]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}


			else if((mx>=base_x&&mx<=base_x+inc)&&(my>base_y+3*inc&&my<=base_y+4*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[0]){
					gameboard[0]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[0]&&(selectmode==1)){
					gameboard[0]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+inc&&mx<=base_x+2*inc)&&(my>base_y+3*inc&&my<=base_y+4*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[1]){
					gameboard[1]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[1]&&(selectmode==1)){
					gameboard[1]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+2*inc&&mx<=base_x+3*inc)&&(my>base_y+3*inc&&my<=base_y+4*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[2]){
					gameboard[2]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[2]&&(selectmode==1)){
					gameboard[2]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
			else if((mx>base_x+3*inc&&mx<=base_x+4*inc)&&(my>base_y+3*inc&&my<=base_y+4*inc)&&(selectmode==1||selectmode==2)){
				if((turn%2)&&!gameboard[3]){
					gameboard[3]='X';
					turn++;
					sound=1;
					sound_afterturn();
				}
				else if(!(turn%2)&&!gameboard[3]&&(selectmode==1)){
					gameboard[3]='O';
					turn++;
					sound=1;
					sound_afterturn();
				}
			}
		}
	}

}


void iKeyboard(unsigned char key)
{
	if(key >= 'a'&& key<='z')
	{
		press='a';
	}

}


void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
}

int main(void){
	bool_type.flMainMenu2=1,bool_type.flMainMenu=0,bool_type.flMainGame=0,bool_type.flChooseOpponent=0,bool_type.flBack2MainMenu=0,bool_type.flBack2MainMenu1=0,bool_type.flInstructions=0,bool_type.flHighScore=0,bool_type.flDraw=0,bool_type.flAssure=0,bool_type.flAssure2=0;//if these variable==1 then corresponding options are selected
	iSetTimer(3600,playturn1);
	iSetTimer(3600,playturn2);
	iInitialize(1000, 720, "Tic-Tac-Toe");
}
int is_win(char c)
{
	if((*gameboard==*(gameboard+1))&&(*(gameboard+2)==*(gameboard+1))&&(*(gameboard+3)==*(gameboard+2))&&(*(gameboard+1)==c)){
		return 1;
	}
	else if((*(gameboard+4)==*(gameboard+5))&&(*(gameboard+5)==*(gameboard+6))&&(*(gameboard+6)==*(gameboard+7))&&(c==*(gameboard+4))){
		return 2;
	}
	else if((*(gameboard+8)==*(gameboard+9))&&(*(gameboard+9)==*(gameboard+10))&&(*(gameboard+10)==*(gameboard+11))&&(c==*(gameboard+8))){
		return 3;
	}
	else if((*(gameboard+12)==*(gameboard+13))&&(*(gameboard+13)==*(gameboard+14))&&(*(gameboard+14)==*(gameboard+15))&&(c==*(gameboard+12))){
		return 9;
	}

	else if((*(gameboard+0)==*(gameboard+4))&&(*(gameboard+4)==*(gameboard+8))&&(*(gameboard+12)==*(gameboard+8))&&(c==*(gameboard+0))){
		return 4;
	}
	else if((*(gameboard+1)==*(gameboard+5))&&(*(gameboard+5)==*(gameboard+9))&&(*(gameboard+9)==*(gameboard+13))&&(c==*(gameboard+5))){
		return 5;
	}
	else if((*(gameboard+2)==*(gameboard+6))&&(*(gameboard+6)==*(gameboard+10))&&(*(gameboard+14)==*(gameboard+10))&&(c==*(gameboard+2))){
		return 6;
	}
	else if((*(gameboard+3)==*(gameboard+7))&&(*(gameboard+7)==*(gameboard+11))&&(*(gameboard+11)==*(gameboard+15))&&(c==*(gameboard+3))){
		return 10;
	}

	else if((*(gameboard+0)==*(gameboard+5))&&(*(gameboard+5)==*(gameboard+10))&&(*(gameboard+15)==*(gameboard+10))&&(c==*(gameboard+5))){
		return 7;
	}
	else if((*(gameboard+3)==*(gameboard+6))&&(*(gameboard+6)==*(gameboard+9))&&(*(gameboard+9)==*(gameboard+12))&&(c==*(gameboard+9))){
		return 8;
	}
	return 0;
}
int youwin(void)
{
	return is_win(yoursign);
}
int opponentwin(void)
{
	return is_win(oppsign);
}
void playturn1(void)
{
	if(selectmode==2 && bool_type.easy==1){
		if(!(turn%2)){
			do{
				computermove=(int)rand();
				computermove=computermove%16;
			 }while(!(validcell(computermove)));
			gameboard[computermove]=oppsign;
			++turn;
			sound=1;
			sound_afterturn();
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void playturn2(void)
{
	if(selectmode==2 && bool_type.easy==0){
		if(!(turn%2)){
			gameboard[bestmove()]=oppsign;
			++turn;
			sound=1;
			sound_afterturn();
		}
	}
}
void playturn21(void)
{
	if(selectmode==2 && bool_type.easy==0){
		if(!(turn%2)){
			if(turn==2){
				if(!(gameboard[4]))gameboard[4]=oppsign;
				else gameboard[0]=oppsign;
				++turn;
				return;
			}
			//checking whether computer has two adjacent cell matching
			if((gameboard[0]==oppsign)&&(gameboard[0]==gameboard[1])&&(validcell(2))){
				gameboard[2]=oppsign;
				++turn;
			}
			else if((gameboard[1]==oppsign)&&(gameboard[2]==gameboard[1])&&(validcell(0))){
				gameboard[0]=oppsign;
				++turn;
			}
			else if((gameboard[0]==oppsign)&&(gameboard[2]==gameboard[0])&&(validcell(1))){
				gameboard[1]=oppsign;
				++turn;
			}
			else if((gameboard[3]==oppsign)&&(gameboard[3]==gameboard[4])&&(validcell(5))){
				gameboard[5]=oppsign;
				++turn;
			}
			else if((gameboard[4]==oppsign)&&(gameboard[4]==gameboard[5])&&(validcell(3))){
				gameboard[3]=oppsign;
				++turn;
			}
			else if((gameboard[3]==oppsign)&&(gameboard[3]==gameboard[5])&&(validcell(4))){
				gameboard[4]=oppsign;
				++turn;
			}
			else if((gameboard[6]==oppsign)&&(gameboard[6]==gameboard[7])&&(validcell(8))){
				gameboard[8]=oppsign;
				++turn;
			}
			else if((gameboard[7]==oppsign)&&(gameboard[7]==gameboard[8])&&(validcell(6))){
				gameboard[6]=oppsign;
				++turn;
			}
			else if((gameboard[6]==oppsign)&&(gameboard[6]==gameboard[8])&&(validcell(7))){
				gameboard[7]=oppsign;
				++turn;
			}
			else if((gameboard[0]==oppsign)&&(gameboard[3]==gameboard[0])&&(validcell(6))){
				gameboard[6]=oppsign;
				++turn;
			}
			else if((gameboard[3]==oppsign)&&(gameboard[3]==gameboard[6])&&(validcell(0))){
					gameboard[0]=oppsign;
					++turn;
			}
			else if((gameboard[0]==oppsign)&&(gameboard[0]==gameboard[6])&&(validcell(3))){
					gameboard[3]=oppsign;
					++turn;
			}
			else if((gameboard[1]==oppsign)&&(gameboard[1]==gameboard[4])&&(validcell(7))){
					gameboard[7]=oppsign;
					++turn;
			}
			else if((gameboard[4]==oppsign)&&(gameboard[4]==gameboard[7])&&(validcell(1))){
					gameboard[1]=oppsign;
					++turn;
			}
			else if((gameboard[1]==oppsign)&&(gameboard[1]==gameboard[7])&&(validcell(4))){
					gameboard[4]=oppsign;
					++turn;
			}
			else if((gameboard[2]==oppsign)&&(gameboard[2]==gameboard[5])&&(validcell(8))){
					gameboard[8]=oppsign;
					++turn;
			}
			else if((gameboard[5]==oppsign)&&(gameboard[8]==gameboard[5])&&(validcell(2))){
					gameboard[2]=oppsign;
					++turn;
			}
			else if((gameboard[2]==oppsign)&&(gameboard[2]==gameboard[8])&&(validcell(5))){
					gameboard[5]=oppsign;
					++turn;
			}
			else if((gameboard[0]==oppsign)&&(gameboard[0]==gameboard[4])&&(validcell(8))){
					gameboard[8]=oppsign;
					++turn;
			}
			else if((gameboard[4]==oppsign)&&(gameboard[4]==gameboard[8])&&(validcell(0))){
					gameboard[0]=oppsign;
					++turn;
			}
			else if((gameboard[0]==oppsign)&&(gameboard[0]==gameboard[8])&&(validcell(4))){
					gameboard[4]=oppsign;
					++turn;
			}
			else if((gameboard[2]==oppsign)&&(gameboard[2]==gameboard[4])&&(validcell(6))){
					gameboard[6]=oppsign;
					++turn;
			}
			else if((gameboard[4]==oppsign)&&(gameboard[4]==gameboard[6])&&(validcell(2))){
					gameboard[2]=oppsign;
					++turn;
			}
			else if((gameboard[2]==oppsign)&&(gameboard[2]==gameboard[6])&&(validcell(4))){
					gameboard[4]=oppsign;
					++turn;
			}
			//checking here for opponent matching cells.
			else if((gameboard[0]==yoursign)&&(gameboard[0]==gameboard[1])&&(validcell(2))){
				gameboard[2]=oppsign;
				++turn;
			}
			else if((gameboard[1]==yoursign)&&(gameboard[2]==gameboard[1])&&(validcell(0))){
				gameboard[0]=oppsign;
				++turn;
			}
			else if((gameboard[0]==yoursign)&&(gameboard[2]==gameboard[0])&&(validcell(1))){
				gameboard[1]=oppsign;
				++turn;
			}
			else if((gameboard[3]==yoursign)&&(gameboard[3]==gameboard[4])&&(validcell(5))){
				gameboard[5]=oppsign;
				++turn;
			}
			else if((gameboard[4]==yoursign)&&(gameboard[4]==gameboard[5])&&(validcell(3))){
				gameboard[3]=oppsign;
				++turn;
			}
			else if((gameboard[3]==yoursign)&&(gameboard[3]==gameboard[5])&&(validcell(4))){
				gameboard[4]=oppsign;
				++turn;
			}
			else if((gameboard[6]==yoursign)&&(gameboard[6]==gameboard[7])&&(validcell(8))){
				gameboard[8]=oppsign;
				++turn;
			}
			else if((gameboard[7]==yoursign)&&(gameboard[7]==gameboard[8])&&(validcell(6))){
				gameboard[6]=oppsign;
				++turn;
			}
			else if((gameboard[6]==yoursign)&&(gameboard[6]==gameboard[8])&&(validcell(7))){
				gameboard[7]=oppsign;
				++turn;
			}
			else if((gameboard[0]==yoursign)&&(gameboard[3]==gameboard[0])&&(validcell(6))){
				gameboard[6]=oppsign;
				++turn;
			}
			else if((gameboard[3]==yoursign)&&(gameboard[3]==gameboard[6])&&(validcell(0))){
					gameboard[0]=oppsign;
					++turn;
			}
			else if((gameboard[0]==yoursign)&&(gameboard[0]==gameboard[6])&&(validcell(3))){
					gameboard[3]=oppsign;
					++turn;
			}
			else if((gameboard[1]==yoursign)&&(gameboard[1]==gameboard[4])&&(validcell(7))){
					gameboard[7]=oppsign;
					++turn;
			}
			else if((gameboard[4]==yoursign)&&(gameboard[4]==gameboard[7])&&(validcell(1))){
					gameboard[1]=oppsign;
					++turn;
			}
			else if((gameboard[1]==yoursign)&&(gameboard[1]==gameboard[7])&&(validcell(4))){
					gameboard[4]=oppsign;
					++turn;
			}
			else if((gameboard[2]==yoursign)&&(gameboard[2]==gameboard[5])&&(validcell(8))){
					gameboard[8]=oppsign;
					++turn;
			}
			else if((gameboard[5]==yoursign)&&(gameboard[8]==gameboard[5])&&(validcell(2))){
					gameboard[2]=oppsign;
					++turn;
			}
			else if((gameboard[2]==yoursign)&&(gameboard[2]==gameboard[8])&&(validcell(5))){
					gameboard[5]=oppsign;
					++turn;
			}
			else if((gameboard[0]==yoursign)&&(gameboard[0]==gameboard[4])&&(validcell(8))){
					gameboard[8]=oppsign;
					++turn;
			}
			else if((gameboard[4]==yoursign)&&(gameboard[4]==gameboard[8])&&(validcell(0))){
					gameboard[0]=oppsign;
					++turn;
			}
			else if((gameboard[0]==yoursign)&&(gameboard[0]==gameboard[8])&&(validcell(4))){
					gameboard[4]=oppsign;
					++turn;
			}
			else if((gameboard[2]==yoursign)&&(gameboard[2]==gameboard[4])&&(validcell(6))){
					gameboard[6]=oppsign;
					++turn;
			}
			else if((gameboard[4]==yoursign)&&(gameboard[4]==gameboard[6])&&(validcell(2))){
					gameboard[2]=oppsign;
					++turn;
			}
			else if((gameboard[2]==yoursign)&&(gameboard[2]==gameboard[6])&&(validcell(4))){
					gameboard[4]=oppsign;
					++turn;
			}
			else{
				do{
					computermove=(int)rand();
					computermove=computermove%16;
				}while(!(validcell(computermove)));
				gameboard[computermove]=oppsign;
				++turn;
			}
			sound=1;
			sound_afterturn();
		}
	}
}

int validcell(int ch)
{
	return !gameboard[ch];//returns nonzero if cell is empty or returns zero in it
}
void init(void)
{
	int i;
	for(i=0;i<16;i++)*(gameboard+i)=i-i;
	turn=1;
}

void drawCross(int p,int q)
{
	iSetColor(10,10,10);
	iFilledRectangle(p,q,20,20);// middle rectangle of cross

	//drawing other rectangles for cross.
	iFilledRectangle(p+20, q+20, 20,20);

	iFilledRectangle(p+20+20, q+20+20, 20, 20);

	iFilledRectangle(p+20, q-20, 20, 20);

	iFilledRectangle(p+20+20, q-20-20, 20, 20);



	iFilledRectangle(p-20,q+20,20,20);
	iFilledRectangle(p-20-20, q+20+20, 20, 20);
	iFilledRectangle(p-20,q-20, 20, 20);
	iFilledRectangle(p-20-20, q-20-20, 20,20);

}

void drawHorizontalLine(int a,int b)
{
	iSetColor(0,120,120);
	iFilledRectangle(a,b,4*inc,20);
}

void drawVerticalLine(int a,int b)
{
	iSetColor(0,120,120);
	iFilledRectangle(a,b,20,4*inc);
}

void drawbakaline1(int a,int b)
{
	int i;
	for(i=0;i<=(4*inc);i=i+10)
	{
		iSetColor(255,0,0);
		iFilledRectangle(a+i,b-i,20,20);
	}
}

void drawbakaline2(int a,int b)
{
	int i;
	for(i=0;i<=(4*inc);i=i+10)
	{
		iSetColor(255,0,0);
		iFilledRectangle(a+i,b+i,20,20);
	}
}

void Drawgrid_Maingame(void)
{
	//iShowBMP(100,100,"background.bmp");
	iSetColor(255,255,255);

	iFilledRectangle(0,0,1000,720);

	//iShowBMP(120,100,"background.bmp");
	/*iSetColor(10,10,10);
	iFilledRectangle(200,100,600,20);
	iFilledRectangle(800,100,20,520);
	iFilledRectangle(200,100,20,520);
	iFilledRectangle(200,600,600,20);*/

	iSetColor(10,10,10);
	iFilledRectangle(base_x+inc,base_y,10,4*inc);
	iFilledRectangle(base_x+2*inc,base_y,10,4*inc);
	iFilledRectangle(base_x+3*inc,base_y,10,4*inc);//extra
	iFilledRectangle(base_x,base_y+inc,4*inc,10);
	iFilledRectangle(base_x,base_y+2*inc,4*inc,10);
	iFilledRectangle(base_x,base_y+3*inc,4*inc,10);//extra

	if(gameboard[0]=='X')
	{
		drawCross(360,640);
	}
	else if(gameboard[0]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(360,640,50);
		iSetColor(255,255,255);
		iFilledCircle(360,640,40);
	}

	if(gameboard[1]=='X')
	{
		drawCross(500,640);
	}
	else if(gameboard[1]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(500,640,50);
		iSetColor(255,255,255);
		iFilledCircle(500,640,40);
	}

	if(gameboard[2]=='X')
	{
		drawCross(640,640);
	}
	else if(gameboard[2]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(640,640,50);
		iSetColor(255,255,255);
		iFilledCircle(640,640,40);
	}

	if(gameboard[3]=='X')
	{
		drawCross(780,640);
	}
	else if(gameboard[3]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(780,640,50);
		iSetColor(255,255,255);
		iFilledCircle(780,640,40);
	}


	if(gameboard[4]=='X')
	{
		drawCross(360,500);
	}
	else if(gameboard[4]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(360,500,50);
		iSetColor(255,255,255);
		iFilledCircle(360,500,40);
	}

	if(gameboard[5]=='X')
	{
		drawCross(500,500);
	}
	else if(gameboard[5]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(500,500,50);
		iSetColor(255,255,255);
		iFilledCircle(500,500,40);
	}

	if(gameboard[6]=='X')
	{
		drawCross(640,500);
	}
	else if(gameboard[6]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(640,500,50);
		iSetColor(255,255,255);
		iFilledCircle(640,500,40);
	}

	if(gameboard[7]=='X')
	{
		drawCross(780,500);
	}
	else if(gameboard[7]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(780,500,50);
		iSetColor(255,255,255);
		iFilledCircle(780,500,40);
	}




	if(gameboard[8]=='X')
	{
		drawCross(360,360);
	}
	else if(gameboard[8]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(360,360,50);
		iSetColor(255,255,255);
		iFilledCircle(360,360,40);
	}

	if(gameboard[9]=='X')
	{
		drawCross(500,360);
	}
	else if(gameboard[9]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(500,360,50);
		iSetColor(255,255,255);
		iFilledCircle(500,360,40);
	}

	if(gameboard[10]=='X')
	{
		drawCross(640,360);
	}
	else if(gameboard[10]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(640,360,50);
		iSetColor(255,255,255);
		iFilledCircle(640,360,40);
	}
	if(gameboard[11]=='X')
	{
		drawCross(780,360);
	}
	else if(gameboard[11]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(780,360,50);
		iSetColor(255,255,255);
		iFilledCircle(780,360,40);
	}




	if(gameboard[12]=='X')
	{
		drawCross(360,220);
	}
	else if(gameboard[12]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(360,220,50);
		iSetColor(255,255,255);
		iFilledCircle(360,220,40);
	}

	if(gameboard[13]=='X')
	{
		drawCross(500,220);
	}
	else if(gameboard[13]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(500,220,50);
		iSetColor(255,255,255);
		iFilledCircle(500,220,40);
	}

	if(gameboard[14]=='X')
	{
		drawCross(640,220);
	}
	else if(gameboard[14]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(640,220,50);
		iSetColor(255,255,255);
		iFilledCircle(640,220,40);
	}
	if(gameboard[15]=='X')
	{
		drawCross(780,220);
	}
	else if(gameboard[15]=='O')
	{
		iSetColor(10,10,10);
		iFilledCircle(780,220,50);
		iSetColor(255,255,255);
		iFilledCircle(780,220,40);
	}
	if((selectmode==2)||(selectmode==4))
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(youwin()==1)
		{
			drawHorizontalLine(base_x,base_y+3.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(youwin()==2)
		{
			drawHorizontalLine(base_x,base_y+2.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(youwin()==3)
		{
			drawHorizontalLine(base_x,base_y+1.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(youwin()==9)
		{
			drawHorizontalLine(base_x,base_y+0.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}


		else if(youwin()==4)
		{
			drawVerticalLine(base_x+0.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(youwin()==5)
		{
			drawVerticalLine(base_x+1.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(youwin()==6)
		{
			drawVerticalLine(base_x+2.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(youwin()==10)
		{
			drawVerticalLine(base_x+3.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}


		else if(youwin()==7)
		{
			drawbakaline1(base_x,base_y+3*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(youwin()==8)
		{
			drawbakaline2(base_x,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Congratulations...you win",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(opponentwin()==1)
		{
			drawHorizontalLine(base_x,base_y+3.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(opponentwin()==2)
		{
			drawHorizontalLine(base_x,base_y+2.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(opponentwin()==3)
		{
			drawHorizontalLine(base_x,base_y+1.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(opponentwin()==9)
		{
			drawHorizontalLine(base_x,base_y+0.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}


		else if(opponentwin()==4)
		{
			drawVerticalLine(base_x+0.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(opponentwin()==5)
		{
			drawVerticalLine(base_x+1.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(opponentwin()==6)
		{
			drawVerticalLine(base_x+2.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(opponentwin()==10)
		{
			drawVerticalLine(base_x+3.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}


		else if(opponentwin()==7)
		{
			drawbakaline1(base_x,base_y+3*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
		else if(opponentwin()==8)
		{
			drawbakaline2(base_x,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "You lost,Try Again",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}

		else if(turn==17){
			iSetColor(255,0,0);
			iText(base_x+10,base_y+3*inc+70, "Match Drawn....",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=4;
		}
	}
	else if((selectmode==1)||(selectmode==3))
	{

		if(youwin()==1)
		{
			drawHorizontalLine(base_x,base_y+3.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==2)
		{
			drawHorizontalLine(base_x,base_y+2.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==3)
		{
			drawHorizontalLine(base_x,base_y+1.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==9)
		{
			drawHorizontalLine(base_x,base_y+0.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==4)
		{
			drawVerticalLine(base_x+0.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==5)
		{
			drawVerticalLine(base_x+1.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70,"Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==6)
		{
			drawVerticalLine(base_x+2.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==10)
		{
			drawVerticalLine(base_x+3.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==7)
		{
			drawbakaline1(base_x,base_y+3*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(youwin()==8)
		{
			drawbakaline2(base_x,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-1 ('X') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==1)
		{
			drawHorizontalLine(base_x,base_y+3.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==2)
		{
			drawHorizontalLine(base_x,base_y+2.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==3)
		{
			drawHorizontalLine(base_x,base_y+1.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==9)
		{
			drawHorizontalLine(base_x,base_y+0.5*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==4)
		{
			drawVerticalLine(base_x+0.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==5)
		{
			drawVerticalLine(base_x+1.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==6)
		{
			drawVerticalLine(base_x+2.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==10)
		{
			drawVerticalLine(base_x+3.5*inc,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==7)
		{
			drawbakaline1(base_x,base_y+3*inc);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70, "Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(opponentwin()==8)
		{
			drawbakaline2(base_x,base_y);
			iSetColor(0,255,0);
			iText(base_x+10,base_y+3*inc+70,"Player-2 ('O') wins",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
		else if(turn==17){
			iSetColor(255,0,0);
			iText(base_x+10,base_y+3*inc+70, "Match Drawn....",GLUT_BITMAP_TIMES_ROMAN_24);
			selectmode=3;
		}
	}

}
void DrawBack2MainMenu(void)
{
    iSetColor(10,10,10);
    iFilledRectangle(base_x+100,base_y-110,40*8,40);
	iSetColor(255,255,255);
    iText(base_x+inc,base_y-100, "Back To Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);
}

void DrawChooseOpponent()
{
    iClear();
	iShowBMP(0,0,"tactoe.bmp");
	iSetColor(10,10,10);
	iFilledRectangle(150,127*4,300,30);

	iSetColor(200,200,200);
    //iRectangle(56*4,127*4,36*4,7*4);
    iText(155,129*4,"CHOOSE AN OPPONENT",GLUT_BITMAP_TIMES_ROMAN_24);

    iRectangle(100,200,380,400);

    iSetColor(10,10,10);
    iFilledRectangle(185,325,235,50);
    iFilledRectangle(185,425,235,50);

    iSetColor(255,255,255);
    iText(210,344,"Man Vs Computer",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(230,440,"Man Vs Man",GLUT_BITMAP_TIMES_ROMAN_24);
}






void DrawInstructions(void)
{
    iClear();
	iShowBMP(0,0,"instructions.bmp");
}

void DrawMainMenu(void)
{
	iShowBMP(0,0,"tic.bmp");
	iShowBMP(190,490,"menu.bmp");
	iSetColor(255,255,255);//white
    iRectangle(30*4,30*4,90*4,90*4);

    iSetColor(10,10,10);
    iFilledRectangle(50*4,35*4,50*4,17*4);
	iFilledRectangle(50*4,56*4,50*4,17*4);
    iFilledRectangle(50*4,77*4,50*4,17*4);
    iFilledRectangle(50*4,98*4,50*4,17*4);

	iSetColor(255,255,255);
    iText(255,105*4,"Resume",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(60*4,84*4,"Instructions",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(61*4,63*4,"New Game",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(270,42*4,"Exit",GLUT_BITMAP_TIMES_ROMAN_24);
}

void DrawMainMenu2(void)
{
	iShowBMP(0,0,"tic.bmp");
	iShowBMP(190,490,"menu.bmp");
	iSetColor(255,255,255);//white
    iRectangle(120,190,360,290);


    iSetColor(10,10,10);
	iFilledRectangle(50*4,56*4,50*4,17*4);
    iFilledRectangle(50*4,77*4,50*4,17*4);
    iFilledRectangle(50*4,98*4,50*4,17*4);

	iSetColor(255,255,255);
    iText(60*4,105*4,"New Game",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(60*4,84*4,"Instructions",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(270,63*4,"Exit",GLUT_BITMAP_TIMES_ROMAN_24);

}

void DrawAssure(void)
{
	iShowBMP(0,0,"tic.bmp");
	iSetColor(255,255,255);
    //iRectangle(56*4,127*4,36*4,7*4);
    iText(155,516,"Are you sure?",GLUT_BITMAP_TIMES_ROMAN_24);

    iRectangle(100,450,300,90);

	iSetColor(10,10,10);
	iFilledRectangle(160,475,60,30);
	iFilledRectangle(260,475,60,30);
	iSetColor(255,255,255);
	iText(165,480,"Yes",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(265,480,"No",GLUT_BITMAP_TIMES_ROMAN_24);

}

void DrawAssure2(void)
{
	iShowBMP(0,0,"tic.bmp");
	iSetColor(255,255,255);
    //iRectangle(56*4,127*4,36*4,7*4);
    iText(155,516,"Are you sure?",GLUT_BITMAP_TIMES_ROMAN_24);

    iRectangle(100,450,300,90);

	iSetColor(10,10,10);
	iFilledRectangle(160,475,60,30);
	iFilledRectangle(260,475,60,30);
	iSetColor(255,255,255);
	iText(165,480,"Yes",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(265,480,"No",GLUT_BITMAP_TIMES_ROMAN_24);
}

void DrawBack2MainMenu1(void)
{
	iSetColor(10,10,10);
    iFilledRectangle(base_x+100,base_y-110,40*8,40);
	iSetColor(255,255,255);
    iText(base_x+inc,base_y-100, "Back To Main Menu",GLUT_BITMAP_TIMES_ROMAN_24);
}
void sound_afterturn(void)
{
	if(sound){
		srand(time(NULL));
		PlaySound("Big Hit - Sound Effect",NULL,SND_ASYNC);
	}
	sound=0;
}

void play_mode(void)
{
    iClear();
	iShowBMP(0,0,"tactoe.bmp");
	iSetColor(10,10,10);
	iFilledRectangle(150,127*4,300,30);

	iSetColor(200,200,200);
    //iRectangle(56*4,127*4,36*4,7*4);
    iText(250,129*4,"Play Mode",GLUT_BITMAP_TIMES_ROMAN_24);

    iRectangle(100,200,380,400);

    iSetColor(10,10,10);
    iFilledRectangle(185,325,235,50);
    iFilledRectangle(185,425,235,50);

    iSetColor(255,255,255);
    iText(275,344,"Hard",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(275,440,"Easy",GLUT_BITMAP_TIMES_ROMAN_24);
}

bool moveLeft()
{
	for(int i=0;i<16;i++)
	{
		if(gameboard[i]==0) return true;
	}
	return false;
}

int eva_score(void)
{
	if(youwin())
	{
		return -1;
	}
	else if(opponentwin())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int minimax(int dep,bool max,int alpha,int beta)
{
	int score=eva_score();
	if(score==1) return 1;
	if(score==-1) return -1;
	if(moveLeft()==false) return 0;

	if(max)
	{
		int best=INT_MIN;
		for(int dd=0;dd<16;dd++)
		{
			if(gameboard[dd]==0)
			{
				gameboard[dd]='O';
				best=max1(best,minimax(dep+1,!max,alpha,beta));
				alpha=max1(alpha,best);
				if(alpha>=beta)
				{
					gameboard[dd]=0;
					break;
				}
				gameboard[dd]=0;
			}

		}
		return best;
	}
	else
	{
		int best=INT_MAX;
		for(int dd=0;dd<16;dd++)
		{
			if(gameboard[dd]==0)
			{
				gameboard[dd]='X';
				best=min1(best,minimax(dep+1,!max,alpha,beta));
				beta=min1(beta,best);
				if(alpha>=beta)
				{
					gameboard[dd]=0;
					break;
				}
				gameboard[dd]=0;
			}

		}
		return best;
	}
}


int bestmove(void)
{
	int bestVal=INT_MIN;
	int res=-1;
	for(int i=0;i<16;i++)
	{
		if(gameboard[i]==0)
		{
			gameboard[i]='O';
			int vall=minimax(0,false,INT_MIN,INT_MAX);
			gameboard[i]=0;
			if(vall>bestVal)
			{
				res=i;
				bestVal=vall;
			}
		}
	}
	return res;
}

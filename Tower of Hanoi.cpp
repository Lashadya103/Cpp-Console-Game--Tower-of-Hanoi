#include<iostream>
#include<conio.h>
#include<windows.h>
#include <sstream>
using namespace std;

int towers[3][5];//difine the towers as an array
int towerTop[3] = {4,-1,-1};//assing the number of disk in the each tower in the initial state.

// user defined funtions used in the game.
void instructions();
void gotoxy(int x, int y);
void drawDisks(int tower, int tileNo, int y);
void drawTower(int tower);
int isEmpty(int towerNo);
int move(int from, int to);
int validate(int from, int to);
int win();
void play();


int main(){
	while(1){
		
		//funtions used to colour the fonts and the background
		HANDLE console_menu = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_menu, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		
		system("cls");//clear the console screen
		
		gotoxy(26,2); cout<<"============================================================"<<endl;
		gotoxy(26,3); cout<<"                       TOWER OF HANOI                       "<<endl;
		gotoxy(26,4); cout<<"============================================================"<<endl<<endl;
		gotoxy(50,9);  cout<<"1. Start Game";
		gotoxy(50,11); cout<<"2. Instructions";	 
		gotoxy(50,13); cout<<"3. Quit";
		gotoxy(50,15); cout<<"Select option: ";
		
		char op = getche();//get a input from the keyboard to select the relevent option.(No need to press enter affter inputing a number like in getchar().)
		
		if(op=='1'){
			
			Beep(1000,300);// used to make sounds.
			
			play();//to strat the Game
			
		}else if(op=='2'){Beep(700,300);
			instructions();//to go to the instructin menu
		}else if(op=='3'){Beep(200,300);
			exit(0);//to exit from the game.
		}
			
	}
	return 0;
}

//function which is used to define the positions of elements in the console.
void gotoxy(int x, int y){
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD CursorPosition;
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

//function which is used to draw the disks of the tower
void drawDisks(int tower, int tileNo, int y){
	int x;
	if( tower == 1 ) x = 35;
	else if( tower == 2 ) x = 50;
	else if( tower == 3 ) x = 65;
	
	x -= tileNo;
	
	//making the disks in the tower
	for(int j=0; j<((tileNo)*2)-1; j++){
		gotoxy(x,y);
		cout<<"=";
		x++;
	}
}

//function which is used to make the tower of disks
void drawTower(int tower){
	int y = 11;
	
	gotoxy(29, 12); cout<<"-----------";
	gotoxy(44, 12); cout<<"-----------";
	gotoxy(59, 12); cout<<"-----------";
	
	gotoxy(35, 13); cout<<"1";
	gotoxy(50, 13); cout<<"2";
	gotoxy(65, 13); cout<<"3";
	
	//draw the disks of a specific tower.
	for(int i=0; i<5; i++){
		drawDisks(tower, towers[tower-1][i], y);
		y--;
	}
}

//function which is used to make the instruction menue.
void instructions(){
	
	system("cls");
	gotoxy(42, 1);cout<<"Instructions";
	gotoxy(40, 2);cout<<"----------------";
	gotoxy(25, 5);cout<<"1) Shift Disks from Tower 1 to Tower 3. ";
	gotoxy(25, 6);cout<<"2) You can not place large disk on small disk";
	gotoxy(25, 7);cout<<"3) Towers are Numbered as 1,2 and 3";
	gotoxy(15, 10);cout<<"Press any key to go back to menu";
	getch();
	Beep(200,300);
}

//function which is used to check whether a tower is empty.
int isEmpty(int towerNo){
	for(int i=0; i<5; i++)
		if( towers[towerNo][i] != 0 )
			return 0;
	return 1;
}

//function which is used to move a disk from one tower to another.
int move(int from, int to){
	if( isEmpty(from) ){
		Beep(300,500);
		return 0;
	}  
	
	if( validate(from, to) ){ 
		if( towers[from][towerTop[from]] != 0 ){
			towerTop[to]++;
			towers[to][towerTop[to]] = towers[from][towerTop[from]];
			towers[from][towerTop[from]] = 0;
			towerTop[from]--;
			Beep(1000,300);
			return 1;
		}
	}
	Beep(300,500);
	return 0;
}

//function which is used to check is it valid to move from one tower to another.
int validate(int from, int to){
	if( !isEmpty(to) ){
		 
		//check whether size of the disk 'from' tower is smaller than the size of the disk in the 'to' tower 
		if( towers[from][towerTop[from]] < towers[to][towerTop[to]] )
			return 1;
		else 
			return 0;
	}
	return 1;
}

//function which is used to pop up when the game won.
int win(){ 
	for(int i=0; i<5; i++)
		if( towers[2][i] != 5-i )
			return 0;
	return 1;
}

//function which is used play the game.
void play(){
	int from=0, to=0, tries=0;
	string str_from, str_to;
	
	HANDLE console_play = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_play, FOREGROUND_RED);
		
	for(int i=0; i<5; i++)
		towers[0][i] = 5-i;
	for(int i=0; i<5; i++)
		towers[1][i] = 0;
	for(int i=0; i<5; i++)
		towers[2][i] = 0;
	 
	while(1){
		system("cls"); 		  
		
		gotoxy(20,1); cout<<"============================================================"<<endl;
		gotoxy(20,2); cout<<"                       TOWER OF HANOI                       "<<endl;
		gotoxy(20,3); cout<<"============================================================"<<endl<<endl;
		
		drawTower(1);
		drawTower(2);
		drawTower(3);
		
		if( win() ){
			system("cls");
			
			gotoxy(20,3);cout<<"============================================================"<<endl;
			gotoxy(20,4);cout<<"                           YOU WIN                          "<<endl;
			gotoxy(20,5);cout<<"============================================================"<<endl;
			
			gotoxy(40,10);
			cout<<"You Won by "<<tries<<" No.of Tries";
			cout<<endl<<endl<<endl<<endl;
			cout<<"Press any key to go back to menu...";
			getch();
			break;
		}
		
		gotoxy(85,10);
		cout<<"No.of Tries : "<<tries;
		
		//Get the tower nubmers where a disk is moving from to.
		gotoxy(10,17);
		cout<<"From (Values: 1,2,3): ";
		cin>>str_from;
		
		stringstream int_from(str_from); //stringstream is a function in sstream to convert numbers in a char into a intger value.
		int_from >> from;
		
		gotoxy(10,18);
		cout<<"To (Values: 1,2,3): ";
		cin>>str_to;
		stringstream int_to(str_to);
		int_to >> to;
		
		//check whether input values are valid.
		if( to < 1 || to > 3 ) {
			Beep(200,500); 
			continue;
		}
		if( from < 1 || from > 3 ) {
			Beep(200,500); 
			continue;
		}
		if( from == to ) {
			Beep(200,500);
			continue;	
		} 
		
		from--;
		to--;
		
		move(from, to);
		
		
		
		//count the number of tries has done.
		tries++;
		  
	}
}

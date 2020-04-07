#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

int ary[30][30];
int ans[2000];
int RGB_table_num[1200];
int total=361,length=20;

struct RGB{
	int r,g,b,posX,posY;
}RGB_table[40],RGB_data[10000]; 


char voice_table[36][10]={" ","1","s1","2","s2","3","4","s4","5","s5","6","s6","7",
				"b1","bs1","b2","bs2","b3","b4","bs4","b5v","bs5","b6","bs6","b7","bbl",
				"bbs1","bb2","bbs2","bb3","bb4","bbs4","bb5v","bbs5"};

void ArrayInitialize(){
	int i,j;
	for(i=0;i<29;i++){
		for(j=0;j<29;j++)
			ary[i][j]=0;
	}
	for(i=0;i<=1199;i++)
		RGB_table_num[i]=0;
}


void Intput_RGB_File(){
	int a,b,c,X,Y,i=1;
	fstream table,data;
  	table.open("RGB_table.txt",ios::in);
	while(table>>a>>b>>c){
		RGB_table[i].r=a;
		RGB_table[i].g=b;
		RGB_table[i].b=c;
		i++;
	}
	i=1;
	table.close();
  	data.open("RGB.txt",ios::in);
	while(data>>X>>Y>>a>>b>>c){
		RGB_data[i].posX=X;
		RGB_data[i].posY=Y+1;
		RGB_data[i].r=a;
		RGB_data[i].g=b;
		RGB_data[i].b=c;
		i++;	
	}
	data.close();
}

int classification(int n){
	int i,min=2147483647,num=0,sum;
	for(i=1;i<=33;i++){
		if(!RGB_data[n].r&&!RGB_data[n].g&&!RGB_data[n].b){
			num=0;
			break;
		}
		sum=abs(RGB_data[n].r-RGB_table[i].r)+abs(RGB_data[n].g-RGB_table[i].g);
		sum+=abs(RGB_data[n].b-RGB_table[i].b);
		if(min>sum){
			min=sum;
			num=i;
		}
	}
	return num;
}

void intputAry(){
	int X,Y;
	for(int i=1;i<=total;i++){
		X=RGB_data[i].posX;
		Y=RGB_data[i].posY;
		ary[X][Y]=RGB_table_num[i];
	}	
}

void run(){
	int x=1,y=9,min_x=10,min_y=10,model=0,i=2;
	ans[1]=ary[x][y];
	while(x!=min_x||y!=min_y){
		switch(model){
			case 0:
				y++;
				if(ary[x][y]==0){
					y--;
					x++;	
				}
				break;
			case 1:
				x++;
				if(ary[x][y]==0){
					y--;
					x--;	
				}
				break;
			case 2:
				y--;
				if(ary[x][y]==0){
					y++;
					x--;	
				}
				break;
			case 3:
				x--;
				if(ary[x][y]==0){
					y++;
					x++;	
				}
				break;		
		}
		if(ary[x][y]==0){
			model=(model+1)%4;
		}
		else{
			ans[i]=ary[x][y];
			ary[x][y]=0;
			i++;
		}
	}
}

void Voice(){
	fstream file;
  	file.open("music.txt",ios::out);
	for(int i=1;i<=total;i++){
		if(ans[i]==0)
			break;
		else{
			printf("%-4s ",voice_table[ans[i]]);
			file<<voice_table[ans[i]]<<endl;	
		}
	}
	file.close();
}

int main()
{ 	ArrayInitialize();
	Intput_RGB_File();
	for(int i=1;i<=total;i++){
		RGB_table_num[i]=classification(i);
	}
	intputAry();
	for(int i=0;i<=length;i++){              //out moon data
		for(int j=0;j<=length;j++){
			printf("%2d ",ary[i][j]);
		}	
		cout<<endl;
	}
	cout<<endl<<endl;
	run();
	for(int i=1;i<=total;i++){              //out music route
		if(ans[i]==0)
			break;
		else
			printf("%2d ",ans[i]);
	}
	cout<<endl<<endl;
	Voice();								//out tone
	return  0;
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define HORIZONTAL_MAX 8
#define VERTICAL_MAX 8
#define BOMB 9
#define BOMB_QUANTITY 5


int generate_bomb(int data[HORIZONTAL_MAX][VERTICAL_MAX]); //座標情報生成用
int map(int data[HORIZONTAL_MAX][VERTICAL_MAX],char hide_data[HORIZONTAL_MAX][VERTICAL_MAX]); //画面表示用
int checkmap(int data[HORIZONTAL_MAX][VERTICAL_MAX],char hide_data[HORIZONTAL_MAX][VERTICAL_MAX],int dig_x,int dig_y); //map開く用
int check_finish(int data[HORIZONTAL_MAX][VERTICAL_MAX],char hide_data[HORIZONTAL_MAX][VERTICAL_MAX]);
int main(void)
{
  int data[HORIZONTAL_MAX][VERTICAL_MAX];
  char hide_data[HORIZONTAL_MAX][VERTICAL_MAX];
  int x,y;
  int flag = 0;
  
  for(x=0;x < HORIZONTAL_MAX;x++){
    for(y=0;y < VERTICAL_MAX;y++)data[x][y] = 0;
  }
  /* data[][]:爆弾の情報を管理 中身がBOMBなら爆弾が入っている */
  for(x = 0;x < HORIZONTAL_MAX;x++){
    for(y = 0;y < VERTICAL_MAX;y++){
     hide_data[x][y] = '*';
 
    }
  }

  generate_bomb(data);
  //printf("g_bomb_ok\n");
  printf("\n");
  map(data,hide_data);
  //printf("map_ok\n");

  int dig_x = 0,dig_y = 0;
  
  
  while(flag == 0){
  	printf("x\n");
  	scanf("%d",&dig_x);
  	printf("y\n");
  	scanf("%d",&dig_y);
  
  	checkmap(data,hide_data,dig_x,dig_y);
  	map(data,hide_data);
  	flag = check_finish(data,hide_data);
  }
  for(x = 0;x < HORIZONTAL_MAX;x++){
    for(y = 0;y < VERTICAL_MAX;y++){
     hide_data[x][y] = '0';
 
    }
  }
  if(flag == 1)printf("\n***Conglaturations!***\n");
  else if(flag == 2)printf("You failed sweeping...\n");
  else printf("error\n");
  map(data,hide_data);
  return 0;
}
int generate_bomb(int data[HORIZONTAL_MAX][VERTICAL_MAX])
{
  int i=0,j=0;
  int x=0,y=0;
  int bomb=BOMB_QUANTITY;
  srand((unsigned)time(NULL));
  for(;bomb > 0;bomb--){
    do{
      x = rand() % HORIZONTAL_MAX;
      y = rand() % VERTICAL_MAX;
    }while(data[x][y] == BOMB);
      data[x][y] = BOMB;    
  }

  for(x=0;x<HORIZONTAL_MAX;x++){
    for(y=0;y<VERTICAL_MAX;y++){

      if(data[x][y] == BOMB){
	for(i=-1;i<=1;i++){
	  for(j=-1;j<=1;j++){
	    
	    if(data[x+i][y+j] != BOMB && ((x+i) >= 0 && (y+j )>= 0) && ((x+i) < HORIZONTAL_MAX && (y+j) < VERTICAL_MAX))
	      data[x+i][y+j]++;

	  }
	}
      }

    }
  }
  

/*  printf("x ");
  for(x = 0;x < HORIZONTAL_MAX;x++)printf("%d ",x); //横の列番号表示
  printf("\n");
  printf("y\n");
  for(x = 0;x < HORIZONTAL_MAX;x++){
    printf("%d ",x);                                      //縦の列番号表示
    for(y = 0;y < VERTICAL_MAX;y++){

      printf("%d ",data[x][y]);
    }
    printf("\n");
  }
  */
  return 0;
}
int map(int data[HORIZONTAL_MAX][VERTICAL_MAX],char hide_data[HORIZONTAL_MAX][VERTICAL_MAX])
{
  int x = 0,y = 0;

  printf("\nx ");
  for(x = 0;x < HORIZONTAL_MAX;x++)printf("%d ",x); //横の列番号表示
  
  printf("\n");
  printf("y\n");
  for(x = 0;x < HORIZONTAL_MAX;x++){
    printf("%d ",x);                                      //縦の列番号表示
    for(y = 0;y < VERTICAL_MAX;y++){
      if(hide_data[x][y] != '*')printf("%d ",data[x][y]);
      else printf("%c ",hide_data[x][y]);
    }
    printf("\n");
  }
  return 0; 
}
int checkmap(int data[HORIZONTAL_MAX][VERTICAL_MAX],char hide_data[HORIZONTAL_MAX][VERTICAL_MAX],int dig_x,int dig_y)
{
  int i = 0,j=0;
 
    
    hide_data[dig_y][dig_x] = 0;
    if(data[dig_y][dig_x] > 0)return 0;
    
    for(i=-1;i<=1;i++){
    	for(j=-1;j<=1;j++){
    		if(data[dig_y+i][dig_x+j] < BOMB && data[dig_y+i][dig_x+j] > 0)hide_data[dig_y+i][dig_x+j] = 0;
    		if(data[dig_y+i][dig_x+j] == 0 && hide_data[dig_y+i][dig_x+j] == '*') {
    			if(dig_y+i >= 0 && dig_x+j >= 0 && dig_y+i < HORIZONTAL_MAX && dig_x+j < VERTICAL_MAX)checkmap(data,hide_data,dig_x+j,dig_y+i);
    		}
    	}
    }
  return 0;
}
int check_finish(int data[HORIZONTAL_MAX][VERTICAL_MAX],char hide_data[HORIZONTAL_MAX][VERTICAL_MAX]){
	int i,j;
	int flag=0,count=0;
	for(i=0;i<HORIZONTAL_MAX;i++){
		for(j=0;j<VERTICAL_MAX;j++){
			if(data[i][j] == BOMB && hide_data[i][j] != '*')return 2;
			if(hide_data[i][j] == '*')count++;
		}
	}
	if(count == BOMB_QUANTITY)flag = 1;
	else flag = 0;
	
	return flag;
}

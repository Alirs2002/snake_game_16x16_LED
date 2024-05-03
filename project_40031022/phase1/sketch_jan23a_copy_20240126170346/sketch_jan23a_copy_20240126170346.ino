#include <MD_MAX72xx.h>

#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::PAROLA_HW, DATA_PIN, CLK_PIN, CS_PIN);

class Snake{

  public:
    int length;
    int row_array[64];
    int col_array[64];

    Snake(){
      length = 3;
      row_array[0] = 0;
      row_array[1] = 0;
      row_array[2] = 0;

      col_array[0] = 2;
      col_array[1] = 1;
      col_array[2] = 0;

    }

    void clear_display(){
      for (int j=0;j<length;j++){

        mx.setPoint(row_array[j], col_array[j], false);


    }


    }

  void move_snake_add_length(){

    length = length+1;

    for(int i = length-1;i>0;i--){

      row_array[i] = row_array[i-1];
      col_array[i] = col_array[i-1];

    }
  }

  void move_snake(){

    for(int i = length-1;i>0;i--){

      row_array[i] = row_array[i-1];
      col_array[i] = col_array[i-1];

    }

  }

  int search_snake(int row,int col){

    for(int k = 0;k<length;k++){

      if((row==row_array[k])&&(col == col_array[k])){
        return 1;
      }

    }
    return 0;

  }

  void display_snake(){

    for (int j=0;j<length;j++){

      mx.setPoint(row_array[j], col_array[j], true);

    }



  }
};


int col;
int row;

int col_inc = 0;
int col_red = 0;
int row_inc = 0;
int row_red = 0;

int food_row = 4;
int food_col = 4;

bool start = false;
bool end = false;


Snake snake;


void clear_food(int food_row, int food_col){

  mx.setPoint(food_row, food_col, false);

}


void set_food(int food_row, int food_col){

  mx.setPoint(food_row, food_col, true);

}



void setup() {
  // put your setup code here, to run once:
  mx.begin();
  pinMode(0,INPUT_PULLUP);
  pinMode(1,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);


  snake.display_snake();
  set_food(food_row,food_col);

}


void loop() {

  if(start==true){
    snake.clear_display();
  }
  row = snake.row_array[0];
  col = snake.col_array[0];

  if((digitalRead(0)==LOW) && (col_red==0)){
    col_inc = 1;
    col_red = 0;
    row_inc = 0;
    row_red = 0;
    start = true;
  }

   if((digitalRead(1)==LOW) && (col_inc == 0)){
    col_inc = 0;
    col_red = 1;
    row_inc = 0;
    row_red = 0;
    start = true;
  }

   if((digitalRead(2)==LOW) && (row_red ==0)){
    col_inc = 0;
    col_red = 0;
    row_inc = 1;
    row_red = 0;
    start = true;
  }

   if((digitalRead(3)==LOW)&& (row_inc==0)){
    col_inc = 0;
    col_red = 0;
    row_inc = 0;
    row_red = 1;
    start = true;
  }


  col = (col+col_inc);
  col = (col-col_red);

  row = (row+row_inc);
  row = (row-row_red);




  if(start && !end){
    if(((row>7) || (row <0)) || ((col>7) || (col<0 )) ){

      end = true;


    }
    
    else if((row==food_row)&&(col==food_col)){


      clear_food(food_row,food_col);
        do{
      food_row = rand() % 8;
      food_col = rand() % 8;
        }while(snake.search_snake(food_row, food_col)==1);

      set_food(food_row,food_col);

      snake.move_snake_add_length();
      snake.col_array[0]=col;
      snake.row_array[0]=row;
      snake.display_snake();

    }else if(snake.search_snake(row, col)){

      end = true;

    }
    else{
      snake.move_snake();
      snake.row_array[0]=row;
      snake.col_array[0]=col;
      snake.display_snake();

    }

  }
  // put your main code here, to run repeatedly:
  delay(300);
}



#include <MD_MAX72xx.h>
#include <Adafruit_NeoPixel.h>

#define DIN 11

#define num_pixel  128

Adafruit_NeoPixel pixels(num_pixel, DIN, NEO_GRB + NEO_KHZ800);


class Snake{

  public:
    int length;
    int row_array[128];
    int col_array[128];

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
      for(int i =0;i<num_pixel;i++){

        pixels.setPixelColor(i,pixels.Color(150,255,0));

      }
      pixels.show();

    }


  void move_snake(){

    for(int i = length-1;i>0;i--){

      row_array[i] = row_array[i-1];
      col_array[i] = col_array[i-1];

    }

  }
    void move_snake_add_length(){

    length = length+1;

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

        if(col_array[j]<8){

         int index = (8*row_array[j])+col_array[j];
         pixels.setPixelColor(index,pixels.Color(0,150,255));


  }
  else if(col_array[j]>7){

    int index = (8*row_array[j])+(col_array[j]-8)+64;
    pixels.setPixelColor(index,pixels.Color(0,150,255));

  }

    }
    pixels.show();



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

  if(food_col<8){

    int index = (8*food_row)+food_col;
    pixels.setPixelColor(index,pixels.Color(150,255,0));


  }
  else if(col>7){

    int index = (8*food_row)+(food_col-8)+64;
    pixels.setPixelColor(index,pixels.Color(150,255,0));


  }
  pixels.show();

}


void set_food(int food_row, int food_col){

  if(food_col<8){

    int index = (8*food_row)+food_col;
    pixels.setPixelColor(index,pixels.Color(255,150,0));


  }
  else if(col>7){

    int index = (8*food_row)+(food_col-8)+64;
    pixels.setPixelColor(index,pixels.Color(255,150,0));


  }
  pixels.show();
  

}



void setup() {
  // put your setup code here, to run once:
  
  pinMode(0,INPUT_PULLUP);
  pinMode(1,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pixels.begin();
  for(int i =0;i<num_pixel;i++){

    pixels.setPixelColor(i,pixels.Color(150,255,0));

  }
  pixels.show();
  snake.display_snake();
  set_food(food_row,food_col);

}


void loop() {

  if(start==true){
    snake.clear_display();
  }

  set_food(food_row,food_col);

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
    if(((row>7) || (row <0)) || ((col>15) || (col<0 )) ){

      end = true;

    }
    
    else if((row==food_row)&&(col==food_col)){

      clear_food(food_row,food_col);
        do{
      food_row = rand() % 8;
      food_col = rand() % 16;
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
      snake.col_array[0]=col;
      snake.row_array[0]=row;
      snake.display_snake();
    }
  }
  // put your main code here, to run repeatedly:
  delay(300);
}



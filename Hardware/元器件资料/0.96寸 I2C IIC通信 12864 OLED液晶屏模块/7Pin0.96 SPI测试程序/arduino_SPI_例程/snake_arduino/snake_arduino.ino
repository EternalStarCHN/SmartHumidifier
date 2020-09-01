#include "U8glib.h"

#define RIGHT 0
#define UP    1
#define LEFT  2
#define DOWN  3

/*
 * OLED
      arduino       OLED
      D9        >     MOSI
      D10      >     SCK
      D11      >     DC
      D12      >     CS 
      D13      >     RES
SW SPI COM: 
SCK = 10, MOSI = 9 , CS = 12, A0 = 11, RES = 13
*/
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13);

int score = 0;
int level = 1;
int gamespeed = 100;
int i;
uint8_t draw_state = 0;

//组成单位，4X4像素点的方块。
const uint8_t ele[] PROGMEM = {
  0xf0, //B1111000
  0xb0, //B1011000
  0xd0, //B1101000
  0xf0, //B1111000
};

//蛇
void element(int x, int y) {
  u8g.drawBitmapP(x,y, 1,4, ele);
}

struct FOOD {
  int x;
  int y;
  int yes;  
};

FOOD food = {25, 30, 1};

struct SNAKE {
  int x[200];
  int y[200];
  int node;
  int dir;
  int lefe;
};

SNAKE snake = {{9,5}, {30,30}, 2, RIGHT, 0};

//游戏基本界面
void UI() {
  u8g.drawFrame(0,1, 102,62);   //内边界
  u8g.drawFrame(0,0, 102,64);   //外边界
  u8g.setFont(u8g_font_5x7);    //设置字体
  u8g.drawStr(104,12, "LEVEL"); //等级提示
  u8g.drawStr(104,40, "SCORE"); //分数提示
}

void printScore(int x, int y, int s) {
  u8g.setFont(u8g_font_6x10);
  u8g.setPrintPos(x, y);
  u8g.print(s);
}

void key() {
  if(LOW == digitalRead(2)) {
    snake.dir = DOWN;
  }
  if(LOW == digitalRead(3)) {
    snake.dir = RIGHT;
  }
  if(LOW == digitalRead(4)) {
    snake.dir = LEFT;
  }
  if(LOW == digitalRead(5)) {
    snake.dir = UP;
  }
}

void snakeGame() {

  switch(snake.dir) {
    case RIGHT: 
          snake.x[0] += 4;
          if(snake.x[0]>=101) {
            snake.x[0] = 1;
          } break;
    case UP: 
          snake.y[0] -= 4;
          if(snake.y[0]<=1) {
            snake.y[0] = 58;
          } break;
    case LEFT: 
          snake.x[0] -= 4;
          if(snake.x[0]<=0) {
            snake.x[0] = 97;
          } break;
    case DOWN:
          snake.y[0] += 4;
          if(snake.y[0]>=62) {
            snake.y[0] = 2;
          } break;
  }  
  
  if((snake.x[0] == food.x) && (snake.y[0] == food.y)) {
    snake.x[0] = food.x;
    snake.y[0] = food.y;
    
    snake.node++;
    food.yes = 1;
    score += 2;
    level = score/10+1;
  }

  for(i=snake.node-1;i>0;i--) {
    snake.x[i] = snake.x[i-1];
    snake.y[i] = snake.y[i-1];
  }
}

void u8g_box_frame(uint8_t a) {
  u8g.drawStr( 0, 0, "drawBox");
  u8g.drawBox(5,10,20,10);
  u8g.drawBox(10+a,15,30,7);
  u8g.drawStr( 0, 30, "drawFrame");
  u8g.drawFrame(5,10+30,20,10);
  u8g.drawFrame(10+a,15+30,30,7);
}

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}


void draw(void) {
  u8g_prepare();
  switch(draw_state >> 3) {
    case 0: u8g_box_frame(draw_state&7); break;
    //case 1: u8g_disc_circle(draw_state&7); break;
    //case 2: u8g_r_frame(draw_state&7); break;
    //case 3: u8g_string(draw_state&7); break;
    //case 4: u8g_line(draw_state&7); break;
    //case 5: u8g_triangle(draw_state&7); break;
    //case 6: u8g_ascii_1(); break;
    //case 7: u8g_ascii_2(); break;
    //case 8: u8g_extra_page(draw_state&7); break;
  }
}



void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}

void loop() {
  //u8g.firstPage();
  //u8g_box_frame(draw_state&7);

  // picture loop  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // increase the state
  draw_state++;
  if ( draw_state >= 9*8 )
    draw_state = 0;
 /* do {
    UI();

    for(i=0; i<snake.node;i++) {
      element(snake.x[i], snake.y[i]);
    }

    element(food.x, food.y);
    
    printScore(103, 62, food.x);
    printScore(116, 62, food.y);
    
    printScore(109, 22, level);
    printScore(109, 50, score);
  }while(u8g.nextPage());

  key();

  snakeGame();
  
  delay(gamespeed);*/
}

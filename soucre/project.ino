#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 
#include "LedControl.h"


int seg[10] =  {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
int sw = 0;
int a = 0; //1의자리
int b = 6; //10의자리
unsigned long oldTime = millis();
unsigned long oldTime2 = 0;
unsigned long oldTime3 = 0;
unsigned long standTime = millis();
int count;
boolean state_led1  = LOW;
unsigned long pretimee = 0;
unsigned long pretimee2 = 0;
unsigned long pretimee3 = 0;
unsigned long pretimee4 = 0;
unsigned long pretimee5 = 0;


const byte interruptPin = 18; //인터럽트 2점 핀 선언
const byte interruptPin1 = 19; //인터럽트 3점 핀 선언
const byte interruptPin2 = 20;  //인터럽트 5점 핀 선언
volatile int score = 0; // 점수
int after_score = 0; // 이후 점수
int button = 9; // 아케이드 버튼
int select1 = A8;
int select2 = A9;


const int duration = 1000;
volatile unsigned long pre_time = 0;
unsigned long cur_time = 0;
int sound_flag = 0; //사운드 선택하기 표시
int dot_flag = 0; // 도트매트릭스 선택하기 표시
int dot_flag2 = 0;
volatile int inter_flag = 0;
LedControl lc = LedControl(12, 11, 10, 3);
LedControl lc2 = LedControl(52, 50, 48, 3);
byte digits[][8] = {
  {  B00111000,  B01000100,  B01000100,  B01000100,  B01000100,  B01000100,  B01000100,  B00111000}, //0
  {  B00010000,  B00110000,  B00010000,  B00010000,  B00010000,  B00010000,  B00010000,  B00111000}, //1
  {  B00111000,  B01000100,  B00000100,  B00000100,  B00001000,  B00010000,  B00100000,  B01111100}, //2
  {  B00111000,  B01000100,  B00000100,  B00011000,  B00000100,  B00000100,  B01000100,  B00111000}, //3
  {  B00000100,  B00001100,  B00010100,  B00100100,  B01000100,  B01111100,  B00000100,  B00000100}, //4
  {  B01111100,  B01000000,  B01000000,  B01111000,  B00000100,  B00000100,  B01000100,  B00111000}, //5
  {  B00111000,  B01000100,  B01000000,  B01111000,  B01000100,  B01000100,  B01000100,  B00111000}, //6
  {  B01111100,  B00000100,  B00000100,  B00001000,  B00010000,  B00100000,  B00100000,  B00100000}, //7
  {  B00111000,  B01000100,  B01000100,  B00111000,  B01000100,  B01000100,  B01000100,  B00111000}, //8
  {  B00111000,  B01000100,  B01000100,  B01000100,  B00111100,  B00000100,  B01000100,  B00111000}, //9
  {  B00000000,  B00111100,  B01100110,  B01100110,  B01111110,  B01100110,  B01100110,  B01100110}, //A
  {  B00000000,  B01111100,  B01100110,  B01100110,  B01111100,  B01100110,  B01100110,  B01111100}, //B
  {  B00000000,  B00111100,  B01100110,  B01100000,  B01100000,  B01100000,  B01100110,  B00111100}, //C
  {  B00000000,  B01111100,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B01111100}, //D
  {  B00000000,  B01111110,  B01100000,  B01100000,  B01111100,  B01100000,  B01100000,  B01111110}, //E
  {  B00000000,  B01111110,  B01100000,  B01100000,  B01111100,  B01100000,  B01100000,  B01100000}, //F
  {  B00000000,  B00111100,  B01100110,  B01100000,  B01100000,  B01101110,  B01100110,  B00111100}, //G
  {  B00000000,  B01100110,  B01100110,  B01100110,  B01111110,  B01100110,  B01100110,  B01100110}, //H
  {  B00000000,  B00111100,  B00011000,  B00011000,  B00011000,  B00011000,  B00011000,  B00111100}, //I
  {  B00000000,  B00011110,  B00001100,  B00001100,  B00001100,  B01101100,  B01101100,  B00111000}, //J
  {  B00000000,  B01100110,  B01101100,  B01111000,  B01110000,  B01111000,  B01101100,  B01100110}, //K
  {  B00000000,  B01100000,  B01100000,  B01100000,  B01100000,  B01100000,  B01100000,  B01111110}, //L
  {  B00000000,  B01100011,  B01110111,  B01111111,  B01101011,  B01100011,  B01100011,  B01100011}, //M
  {  B00000000,  B01100011,  B01110011,  B01111011,  B01101111,  B01100111,  B01100011,  B01100011}, //N
  {  B00000000,  B00111100,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B00111100}, //O
  {  B00000000,  B01111100,  B01100110,  B01100110,  B01100110,  B01111100,  B01100000,  B01100000}, //P
  {  B00000000,  B00111100,  B01100110,  B01100110,  B01100110,  B01101110,  B00111100,  B00000110}, //Q
  {  B00000000,  B01111100,  B01100110,  B01100110,  B01111100,  B01111000,  B01101100,  B01100110}, //R
  {  B00000000,  B00111100,  B01100110,  B01100000,  B00111100,  B00000110,  B01100110,  B00111100}, //S
  {  B00000000,  B01111110,  B01011010,  B00011000,  B00011000,  B00011000,  B00011000,  B00011000}, //T
  {  B00000000,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B00111110}, //U
  {  B00000000,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B00111100,  B00011000}, //V
  {  B00000000,  B01100011,  B01100011,  B01100011,  B01101011,  B01111111,  B01110111,  B01100011}, //W
  {  B00000000,  B01100011,  B01100011,  B00110110,  B00011100,  B00110110,  B01100011,  B01100011}, //X
  {  B00000000,  B01100110,  B01100110,  B01100110,  B00111100,  B00011000,  B00011000,  B00011000}, //Y
  {  B00000000,  B01111110,  B00000110,  B00001100,  B00011000,  B00110000,  B01100000,  B01111110}  //Z
};
byte data[][8] = {
  {  B00000000,  B01111100,  B01100110,  B01100110,  B01111100,  B01111000,  B01101100,  B01100110}, // R
  {  B00000000,  B01111110,  B01100000,  B01100000,  B01111100,  B01100000,  B01100000,  B01111110}, // E
  {  B00000000,  B00111100,  B01100110,  B01100110,  B01111110,  B01100110,  B01100110,  B01100110}, // A
  {  B00000000,  B01111100,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B01111100}, // D
  {  B00000000,  B01100110,  B01100110,  B01100110,  B00111100,  B00011000,  B00011000,  B00011000},  // Y
};

byte timeout[][8] = {
  {  B00000000,  B01111110,  B01011010,  B00011000,  B00011000,  B00011000,  B00011000,  B00011000}, //T
  {  B00000000,  B00111100,  B00011000,  B00011000,  B00011000,  B00011000,  B00011000,  B00111100}, //I
  {  B00000000,  B01100011,  B01110111,  B01111111,  B01101011,  B01100011,  B01100011,  B01100011}, // m
  {  B00000000,  B01111110,  B01100000,  B01100000,  B01111100,  B01100000,  B01100000,  B01111110}, // e
  {  B00000000,  B00111100,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B00111100}, // o
  {  B00000000,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B01100110,  B00111110}, //U
  {  B00000000,  B01111110,  B01011010,  B00011000,  B00011000,  B00011000,  B00011000,  B00011000}  //T
};

char num2 = 1;


void setup() {
  Serial.begin(9600);
  
  pinMode(8, OUTPUT);  // 디지털 9번핀을 출력모드로 설정.
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), intert_2, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), intert_3, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), intert_5, FALLING);
  lc.shutdown(0, false); // 절전모드 설정 여부
  lc.shutdown(1, false);
  lc.shutdown(2, false);
  lc.setIntensity(0, 3); // 몇번째 , 밝기 조절 0~5
  lc.setIntensity(1, 3);
  lc.setIntensity(2, 3);
  lc.clearDisplay(0); // 장치 초기화
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc2.shutdown(0, false); // 절전모드 설정 여부
  lc2.shutdown(1, false);
  lc2.shutdown(2, false);
  lc2.setIntensity(0, 3); // 몇번째 , 밝기 조절 0~5
  lc2.setIntensity(1, 3);
  lc2.setIntensity(2, 3);
  lc2.clearDisplay(0); // 장치 초기화
  lc2.clearDisplay(1);
  lc2.clearDisplay(2);
  DDRF = 0xFF;
  PORTF = 0x00;
  DDRC = 0xFF;
  PORTC = 0x00;
  pinMode(select1, OUTPUT);
  pinMode(select2, OUTPUT);
  Serial.begin(9600);
}
int j = 0;
void loop() {
  unsigned long curTime = millis();


  if (curTime - standTime >= 1000)
  {
    standTime = curTime;
    if (a == 0 && b == 0)
    {
      if (num2 >= 1)
      {
        sound(3);
        num2 --;
        dot_flag = 3;
        dot_flag2 = 4;
        dot_matix();

        if (after_score < score)
        {
          
          after_score = score;
          dot_flag = 1;
          dot_flag2 = 2;
          Serial.print("qwe");
          for (int k = 0; k <= 8; k++) // 최고 기록시 정보 
          {
      //      Serial.print("ggtt");
            dot_matix();
          }       
          sound(4);
        } else
        {
          Serial.print("aa");
          dot_flag = 1;
          dot_flag2 = 1;
          dot_matix();
        }
        dot_flag = 1;
        dot_flag2 = 1;
        dot_matix();
      }

    }
    else
    {
      dot_flag = 1;
      dot_flag2 = 1;
      if ( a == 0 )
      {
        a = 9;
        b--;
      }
      else a--;
    }
  }

  if (curTime - oldTime >= 10)
  {
    sw = ~sw;
    oldTime = curTime;
    digitalWrite(select2, sw);
    digitalWrite(select1, ~sw);
    if (sw == 0)    PORTF = seg[a];
    else PORTF = seg[b];
    dot_matix();
  }

  if (curTime - oldTime2 >= 100)
  {
    oldTime2 = curTime;
    int buttonState = digitalRead(button);    //버튼 상태를 읽어들임

    if (buttonState == 0)
    {
      dot_flag = 3;
      dot_flag2 = 3;
      dot_matix();
      sound(2);
      score = 0;
      b = 6;
      a = 0;
      num2 = 1;
    }
    if (a == 0 && b == 0);


  }

  if (curTime - oldTime3 >= 500)
  {

    oldTime3 = curTime;
    if (inter_flag == 1)
    {
      sound(1);

      led(); 
      if (state_led1 == LOW) // LED 함수 2번 수행하기 위해서 (깜빡임)
      {
        inter_flag = 0;
      }
    }
  }


}


void intert_2() // Interrupt function
{
  if (a == 0 && b == 0);
  else
  {
    cur_time = millis();
    if (cur_time - pre_time >= duration) {
      score += 2;
      Serial.println(score);
      inter_flag = 1;
      pre_time = cur_time;
    }
  }

}
void intert_3() // Interrupt function
{
  if (a == 0 && b == 0);
  else
  {
    cur_time = millis();
    if (cur_time - pre_time >= duration) {
      score += 3;
      Serial.println(score);
      inter_flag = 1;
     
      pre_time = cur_time;
    }
  }

} void intert_5() // Interrupt function
{
  if (a == 0 && b == 0);
  else
  {
    cur_time = millis();
    if (cur_time - pre_time >= duration) {
      score += 5;
      Serial.println(score);
      inter_flag = 1;
      pre_time = cur_time;
    }

  }
}
void sound(int num)
{
  if (num == 1)
  {
    sound1();
  } else if (num == 2)
  {
    sound2();
  } else if (num == 3 )
  {
    sound3();
  } else if (num == 4)
  {
    sound4();
  }

}
void
sound1() // 골 넣을때 소리
{
  digitalWrite(play1,HIGH);
  digitalWrite(play1,LOW);
}
void
sound2() // 버튼 클릭시 소리
{
  digitalWrite(play2,HIGH);
  digitalWrite(play2,LOW);
}
void
sound3 () ()// 시간 초과시 소리
{
  digitalWrite(play3,HIGH);
  digitalWrite(play3,LOW);
}
void
sound4 () // 최고 기록 달성시
{
  digitalWrite(play4,HIGH);
  digitalWrite(play4,LOW);
}
void dot_matix()
{
  if (dot_flag == 1) // 숫자값 자릿수 대로 넣기
  {
    int bac, sip, il, i;
    bac = score / 100;
    sip = (score % 100) / 10;
    il =  (score % 100 % 10) / 1;


    if (dot_flag2 == 1)
    {
     // Serial.println("aa");
      lc.setRow(2, j, digits[bac][j]); //
      lc.setRow(1, j, digits[sip][j]);
      lc.setRow(0, j, digits[il][j]);
    } else
    {
   //   Serial.println(j);
      lc2.setRow(2, j, digits[bac][j]); //
      lc2.setRow(1, j, digits[sip][j]);
      lc2.setRow(0, j, digits[il][j]);
    }
    if (j == 8) j = 0;
    else j++;
  }

  else if (dot_flag == 3) // ready
  {
    int i, j, k;
    byte buffers[4 + 1][8];
    //
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 8; j++) {
        buffers[i][j] = B00000000;
      }
    }
    if (dot_flag2 == 3)
    {
      // 문자 슬라이드 처리
      for (i = 0; i < 5; i++) { // 전체 글자수 만큼 반복
        memcpy(&buffers[4], &data[i], sizeof(data[0]));
        //
        for (j = 0; j < 8; j++) { // 한 글자는 8열이므로, 글자당 8번 수행
          for (k = 0; k < 8; k++) { // 한 글자는 8행
            // 슬라이드 처리
            buffers[0][k] = (buffers[0][k] << 1) | (buffers[1][k] >> 7);
            buffers[1][k] = (buffers[1][k] << 1) | (buffers[2][k] >> 7);
            buffers[2][k] = (buffers[2][k] << 1) | (buffers[3][k] >> 7);
            buffers[3][k] = (buffers[3][k] << 1) | (buffers[4][k] >> 7);
            buffers[4][k] = (buffers[4][k] << 1);
          }
          for (k = 0; k < 8; k++) { // 슬라이드 처리후 출력
            // 출력 코드
            lc.setRow(3, k, buffers[0][k]);
            lc.setRow(2, k, buffers[1][k]);
            lc.setRow(1, k, buffers[2][k]);
            lc.setRow(0, k, buffers[3][k]);
          }
          delay(10);
        }
      }
    } else
    {
      for (i = 0; i < 7; i++) { // 전체 글자수 만큼 반복
        memcpy(&buffers[4], &timeout[i], sizeof(timeout[0]));
        //
        for (j = 0; j < 8; j++) { // 한 글자는 8열이므로, 글자당 8번 수행
          for (k = 0; k < 8; k++) { // 한 글자는 8행
            // 슬라이드 처리
            buffers[0][k] = (buffers[0][k] << 1) | (buffers[1][k] >> 7);
            buffers[1][k] = (buffers[1][k] << 1) | (buffers[2][k] >> 7);
            buffers[2][k] = (buffers[2][k] << 1) | (buffers[3][k] >> 7);
            buffers[3][k] = (buffers[3][k] << 1) | (buffers[4][k] >> 7);
            buffers[4][k] = (buffers[4][k] << 1);
          }
          for (k = 0; k < 8; k++) { // 슬라이드 처리후 출력
            // 출력 코드
            lc.setRow(3, k, buffers[0][k]);
            lc.setRow(2, k, buffers[1][k]);
            lc.setRow(1, k, buffers[2][k]);
            lc.setRow(0, k, buffers[3][k]);
          }
          delay(10);
        }
      }
    }

    delay(1000);

  }

}



void led() {

  unsigned long curTime6 = millis();

  if (curTime6 - pretimee >= 100)
  {
    pretimee = curTime6;
    if ( state_led1 == LOW)
    {
      state_led1 = HIGH;
    } else
    {
      state_led1 = LOW;
    }
    digitalWrite(30, state_led1);
    digitalWrite(32, state_led1);
    digitalWrite(34, state_led1);
    digitalWrite(36, state_led1);
  }

}

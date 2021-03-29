#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include <LiquidCrystal.h>


LiquidCrystal lcd(7,8,10,11,12,13);
#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 

int tempo = 200; // duration 옵션 값 설정 
int notes[20] = { E, E, D, C, C, D, D, E, D, C, G, G, F, E, E, D, C, D, E, C }; 


int blueTx=2;   //Tx (보내는핀 설정)
int blueRx=3;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString=""; //받는 문자열
int vibration = 0;
long Sound_signal;
long level = 0;
int piezo = 4;
long sum = 0;
int numTones = 8;
int tones[] = {C, D, E, F, G, A, B, C};
int led = 5;
int num_Measure = 128;
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mySerial.begin(9600); //블루투스 시리얼 개방
  pinMode(piezo, OUTPUT);
  pinMode(led, OUTPUT);
  lcd.begin(16, 2); 
  pinMode (A1, INPUT);
}
 
void loop() {
  //mySerial.println("ann");
  vibration = analogRead (A0);
  Serial.println(vibration);
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (A1); 
   sum = sum+Sound_signal;
  } 
  level = sum / num_Measure;
  //lcd.print("hello world");
  sum = 0;
  //Serial.println(level);
  if(vibration > 0 and level > 0){
    lcd.print("vibration: ");
    lcd.print(vibration);
    lcd.setCursor(0,2);
    lcd.print("soundlevel: ");
    lcd.print(level);
  }
  
  if (vibration > 400 and level > 100) {
    
    mySerial.println("조용히 하세요 ");
    mySerial.print("진동: ");
    mySerial.println(vibration);
    mySerial.print("소리: ");
    mySerial.println(level);
    delay(1000);
    tone(piezo, C);
    /*for (int i = 0; i < numTones; i++) {
      tone(piezo, tones[i]);
      delay(2);
      digitalWrite(led, HIGH);
    }*/
    delay(100);
    digitalWrite(led, LOW);
  } 
  //Serial.println(vibration);
  lcd.setCursor(0,0);
  lcd.clear();
  noTone(piezo);
  
  while(mySerial.available())  //mySerial에 전송된 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int 값을 char 형식으로 변환
    myString+=myChar;   //수신되는 문자를 myString에 모두 붙임 (1바이트씩 전송되는 것을 연결)
    delay(5);           //수신 문자열 끊김 방지
  }
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
    myString="";  //myString 변수값 초기화
  }
}

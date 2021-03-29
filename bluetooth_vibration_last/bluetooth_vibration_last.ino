#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
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
int vibration = 0; //진동수 변수
long Sound_signal; 
long level = 0; //소음 변수
int piezo = 4; //부저 pin 번호
long sum = 0; 
int numTones = 8;
int tones[] = {C, D, E, F, G, A, B, C};
int red = 5; //빨간 led pin 번호
int green = 6; //초록 led pin 번호
int num_Measure = 128; 



void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mySerial.begin(9600); //블루투스 시리얼 개방
  pinMode(piezo, OUTPUT); //부저 출력
  pinMode(red, OUTPUT); //led 출력
  pinMode(green, OUTPUT);
  pinMode (A1, INPUT); //소리 입력
}

void loop() {
  int cds = analogRead(A2);
  //Serial.println(cds);
  if (cds < 400){
    digitalWrite(green, HIGH);
  }
  digitalWrite(red, LOW);
  
  vibration = analogRead (A0); //진동수 입력값 받기
  for ( int i = 0 ; i <num_Measure; i ++)//128번 반복
  {  
   Sound_signal = analogRead (A1); //소음 값 입력 받기
   sum = sum+Sound_signal; //합을 추가
  } 
  level = sum / num_Measure; //평균 값 도출
  sum = 0; //합을 0으로
  //Serial.println(level);
  Serial.println(vibration); //시리얼모니터에 값을 출력
  if (vibration > 400 and level > 100) { //조건 값 설정
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    mySerial.println("조용히 하세요 "); //블루투스에 출력
    mySerial.print("진동: ");
    mySerial.println(vibration); //진동 값 출력
    mySerial.print("소리: ");
    mySerial.println(level); //소음 값 출력
    delay(1000); //1초 대기
    if (cds > 400){
      tone(piezo, C); //부저 음 내기
    }
    
    delay(100); //0.1초 대기
    
  } 
  noTone(piezo); // 부저 멈추기
}

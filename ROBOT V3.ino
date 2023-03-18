#include<math.h>

#define R_S  A2 //khai báo chân out phải cuả dò line
#define S_S  A1 //khai báo chân out giữa cuả dò line
#define L_S  A0 //khai báo chân out trái cuả dò line
#define enA 9 
#define enB 10 
#define speedMotor 180 
#define speedTurn 160

void setup() {
  pinMode(4, OUTPUT);//Set chân in1 của dc A là output
  pinMode(5, OUTPUT);//Set chân in2 của dc A là output
  pinMode(6, OUTPUT);//Set chân in1 của dc B là output
  pinMode(7, OUTPUT);//Set chân in2 của dc B là output
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);  

  pinMode(L_S, INPUT); //Set chân out trái  của dò line là input
  pinMode(S_S, INPUT);//Set chân out giữa  của dò line là input
  pinMode(R_S, INPUT);//Set chân out phải  của dò line là input

  delay(2000);//delay có nhiệm vụ dừng chương trình trong thời gian mili giây
  Serial.begin(9600); // giao tiếp Serial với baudrate 9600
}

void runMotor (int leftPWM , int rightPWM){
  analogWrite(enA,abs(leftPWM));
  analogWrite(enB,abs(rightPWM));
  digitalWrite(7,(leftPWM>0)?HIGH:LOW);
  digitalWrite(6,(leftPWM>0)?LOW:HIGH);
  digitalWrite(5,(rightPWM>0)?HIGH:LOW);
  digitalWrite(4,(rightPWM>0)?LOW:HIGH);
}
// muon xoay trai xoay phai thi chinh  speed - + la duoc nha  t quen chan cua may cai enA enB r

void line_follower(){
      if ((analogRead (L_S) < 500)&&(analogRead (S_S) > 500)&&(analogRead (R_S) < 500 )) runMotor (speedMotor ,speedMotor );// only S ->forward 
      if ((analogRead (L_S) > 500)&&(analogRead (S_S) > 500)&&(analogRead (R_S) < 500 )) runMotor (speedTurn ,-speedTurn ); // L + S ->turn left 
      if ((analogRead (L_S) > 500)&&(analogRead (S_S) < 500)&&(analogRead (R_S) < 500 )) runMotor (speedMotor ,-speedTurn );  // only L ->turn left 
      if ((analogRead (L_S) < 500)&&(analogRead (S_S) > 500)&&(analogRead (R_S) > 500 )) runMotor (-speedTurn ,speedTurn ); // R + S ->turn right 
      if ((analogRead (L_S) < 500)&&(analogRead (S_S) < 500)&&(analogRead (R_S) > 500 )) runMotor (-speedMotor ,speedTurn ); // only R ->turn right 
      if ((analogRead (L_S) > 500)&&(analogRead (S_S) > 500)&&(analogRead (R_S) > 500 )) runMotor (0,0); // all -> stop       
      if ((analogRead (L_S) < 500)&&(analogRead (S_S) < 500)&&(analogRead (R_S) < 500 )) runMotor (-speedTurn,-speedTurn); // none -> back

}
void loop(){
  // line_follower();

  Serial.print(analogRead(L_S));
  Serial.print("\t");
  Serial.print(analogRead(S_S));
  Serial.print("\t");
  Serial.println(analogRead(R_S));
  Serial.print("\t");
  // delay(500);

  // analogWrite(enA,100);
  // analogWrite(enB,100);
  // digitalWrite(5,HIGH );
  // digitalWrite(4,LOW );
  // digitalWrite(7,HIGH );
  // digitalWrite(6,LOW );

}
// vấn đề : động cơ / pin chập chờn , cần giảm tốc độ quay để k bị giật và quá line 
//cảm biến trả về đúng tín hiệu nhưng còn phải chỉnh khoảng cách giữa chúng / khoảng cách line cho hợp lý 

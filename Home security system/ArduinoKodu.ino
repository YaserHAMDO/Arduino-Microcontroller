#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#define sifreuzunlugu 4

Servo servo;  

SoftwareSerial gsm(38, 39);

Ultrasonic KapiSensoru(40, 41);
Ultrasonic OdaSensoru(42, 43);
Ultrasonic MutfakSensoru(44, 45);

int Kapi_Sensoru = 0;
int Oda_Sensoru = 0;
int Mutfak_Sensoru = 0;

char veridizisi[sifreuzunlugu]; 
char evsahibi[sifreuzunlugu] = "123"; 
char girilensifre;
byte sayac = 0;
String sifre;
bool alarimde_sureklilik = false;

const byte ROWS = 4;
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {{'1', '2', '3'},{'4', '5', '6'},{'7', '8', '9'},{'*', '0', '#'} };
byte rowPins[ROWS] = {31, 32, 33, 34};
byte colPins[COLS] = {30, 29, 28};
Keypad tustakimi = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd (27, 26, 25, 24, 23, 22);  


void setup(){
  
     lcd.begin(16,2);
     gsm.begin(9600);     
     Serial.begin(9600);
     delay(100);

     servo.attach(2); 
     servo.write(180);
      
     pinMode(35,INPUT);
     pinMode(36,INPUT);
     pinMode(37,INPUT);
     pinMode(46,INPUT);
     
     pinMode(47,OUTPUT);
    
    digitalWrite(47,LOW);
     }
     
     

void loop(){


if(digitalRead(46)==HIGH ){
  lcd.setCursor(0,0);
  lcd.print("Sifreyi giriniz:");
  
  girilensifre = tustakimi.getKey();
  if (girilensifre){
    veridizisi[sayac] = girilensifre; 
    lcd.setCursor(sayac,1); 
    lcd.print(veridizisi[sayac]); 
    sayac++; }

  if(sayac == sifreuzunlugu-1){
    lcd.clear();

    if(!strcmp(veridizisi, evsahibi)){
      lcd.print("Dogru");
      servo.write(0);
      delay(5000);
      servo.write(180); }
      
    else{
      lcd.print("Yanlis");
      delay(1000); }
      
      lcd.clear();
      veriyisil();  }


     Kapi_Sensoru = KapiSensoru.distanceRead();
     Oda_Sensoru = OdaSensoru.distanceRead();
     Mutfak_Sensoru = MutfakSensoru.distanceRead();
     
    if(Kapi_Sensoru <50){
      alarimde_sureklilik = true;
      alarim_ve_SMS("ana kapidan bir kisi girdi  ");}

    if(Oda_Sensoru <50){
      alarimde_sureklilik = true;
      alarim_ve_SMS("Oda penceresinden bir kisi girdi ");}
    
    if(Mutfak_Sensoru <50){
      alarimde_sureklilik = true;
      alarim_ve_SMS("Mutfak penceresinden bir kisi girdi ");}
     
    if(digitalRead(35)==HIGH ){
      alarim_ve_SMS("Evinizde yangin var ");}
    if(digitalRead(36)==HIGH){  
      alarim_ve_SMS("Odada gaz kacagi var ");}
    if(digitalRead(37)==HIGH){
      alarim_ve_SMS("Mutfakta gaz kacagi var ");}

      
     if(alarimde_sureklilik == false){
         digitalWrite(47,LOW);}

               }
               
               else{
                alarimde_sureklilik = false;
                digitalWrite(47,LOW);}
                
                
       
   
           delay(100);
             }



/*
    
 if (Serial.available()>0)
    switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }

  if (mySerial.available()>0)
    Serial.write(mySerial.read());   }   
    
void SendMessage(){
  gsm.println("AT+CMGF=1");
  delay(100);
  gsm.println("AT+CMGS=\"+905519557506\"\r");
  delay(100);
  gsm.println("I am SMS from GSM module");
  delay(100);
  gsm.println((char)26);
  delay(100);
  Serial.println("hello");}

void RecieveMessage(){
  gsm.println("AT+CNMI=2,2,0,0,0");
  delay(100);}
    
    */ 



void alarim_ve_SMS(String s){
  digitalWrite(47,HIGH);
  gsm.println(s);
  }

void veriyisil(){
  while(sayac !=0){
    veridizisi[sayac--] = 0; }}

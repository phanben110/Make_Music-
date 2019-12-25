#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
// need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch
int DO , re , mi, fa, son  , val ;
int f = 0 ;
int g = 0, c = 0, d = 0, e = 0, A = 0, B = 0, C = 0, D = 0, E = 0 ;
int G_T = 60 ;
int song_number = 0 ;
int LED1 = 5 ;
int LED2 = 6 ;
int LED3 = 7 ;
int LED4 = 8 ;
int LED5 = 10 ;

unsigned long time = 0;
boolean debounce1 = true ;
boolean debounce2 = true ;
boolean play_pause ;

void setup() {

  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode (A0, INPUT) ;
  pinMode (A1, INPUT) ;
  pinMode (A2, INPUT) ;
  pinMode (A3, INPUT) ;
  pinMode (A4, INPUT) ;
  pinMode (3, INPUT_PULLUP ) ;
  pinMode (2, INPUT_PULLUP ) ;
  pinMode (LED1 , OUTPUT ) ;
  pinMode (LED2 , OUTPUT ) ;
  pinMode (LED3 , OUTPUT ) ;
  pinMode (LED4 , OUTPUT ) ;
  pinMode (LED5 , OUTPUT ) ;
  tmrpcm.speakerPin = 9;

  attachInterrupt ( 0, listen_music , FALLING ) ;
  attachInterrupt ( 0, listen_music , FALLING ) ;

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");
    return;   // don't do anything more if not

  }
  else {
    Serial.println("SD ok");
    lcd.clear () ;

    lcd.print ("   WECOME TO");
    lcd.setCursor (0, 1);

    lcd.print ("   BK - MAKER");
    lcd.setCursor (0, 2) ;

    tmrpcm.play("9.wav");
    delay (4000 ) ;
  }
  //the sound file "music" will play each time the arduino powers up, or is reset

}



void loop() {


  //blink the LED manually to demonstrate music playback is independant of main loop
  /*if (tmrpcm.isPlaying() && millis() - time > 50 ) {
    digitalWrite(13, !digitalRead(13));
    time = millis();
    } else if (millis() - time > 500) {
    digitalWrite(13, !digitalRead(13));
    time = millis();
    }*/
  //  listen_music () ;


  




  DO = analogRead ( A0 ) ;
  re = analogRead ( A1 ) ;
  mi = analogRead ( A2 ) ;
  fa = analogRead ( A3 ) ;
  son = analogRead ( A4 ) ;

  A = -(f - DO )   ;
  B = -(g - re) ;
  C = -(c - mi) ;
  D = -(d - fa) ;
  E = -( e - son );

  if ( ( A > B ) && ( A > C ) && (A > D) && (A > E ) && (A >  G_T)) {
    val = 1 ;

  }
  else if ((B > A ) && ( B > C ) && ( B > D ) && ( B > E ) && ( B > G_T) ) {
    val = 2 ;
  }
  else if ((C > A  ) && ( C > B ) && ( C > D ) && ( C > E ) && ( C >  G_T ) ) {
    val = 3 ;
  }
  else if ( ( D > A ) && ( D > B ) && ( D > C ) && ( D > E ) && ( D > G_T ) ) {
    val = 4 ;
  }
  else if ( ( E > A ) && ( E > B ) && ( E > C ) && ( E > D ) && ( E > G_T )) {
    val = 5 ;
  }
  else
    val = 0 ;
  play_music () ;

  Serial.println ( val ) ;
  Serial.println (A) ;
  Serial.println (B ) ;
  Serial.println ( C) ;
  Serial.println (D) ;
  Serial.println ( E ) ;


  f = DO ;
  g = re ;
  c = mi ;
  d = fa ;
  e = son ;
  delay (400 ) ;
  digitalWrite ( LED1 , 0 ) ;
  digitalWrite ( LED2 , 0 ) ;
  digitalWrite ( LED3 , 0 ) ;
  digitalWrite ( LED4 , 0 ) ;
  digitalWrite ( LED5 , 0 ) ;

  /*  tmrpcm.play("2.wav");
    delay (4000) ;
    //tmrpcm.play("9.wav");
    //delay (4000 ) ;
    tmrpcm.play ("10.wav") ;
    delay (1000 ) ;

    tmrpcm.play ("11.wav") ;
    delay (1000 ) ;
    tmrpcm.play ("12.wav") ;
    delay (1000) ;
    tmrpcm.play ("13.wav" ) ;
    delay (1000) ;
    tmrpcm.play ("14.wav" ) ;
    delay ( 1000 ) ;
    tmrpcm.play ("15.wav") ;
    delay (1000) ;
    tmrpcm.play ("16.wav") ;
    delay ( 1000 ) ;
    tmrpcm.play ("17.wav") ;
    delay (1000 ) ;
    tmrpcm.play ("20.wav") ;
    delay (300000) ;
    tmrpcm.play ("21.wav") ;
    delay (300000) ;




    switch (val) {
      case 1:
        { tmrpcm.play("10.wav");
          break;
        }
      case 2:
        { tmrpcm.play("11.wav");
          break;
        }
      case 3:
        { tmrpcm.play("12.wav");
          break;
        }
      case 4:
        { tmrpcm.play("13.wav");
          break;
        }
      case 5:
        { tmrpcm.play("14.wav");
          break;
        }


      /*   case 4: tmrpcm.pause(); break;
        case 5: if (tmrpcm.isPlaying()) {
            Serial.println("A wav file is being played");
          } break;
        case 'S': tmrpcm.stopPlayback(); break;
        case '=': tmrpcm.volume(1); break;
        case '-': tmrpcm.volume(0); break;
        case '0': tmrpcm.quality(0); break;
        case '1': tmrpcm.quality(1); break; */
  //default: break;
  // }
}
void play_music ()
{
  switch (val) {
    case 1 : {
        digitalWrite ( LED1 , 1 ) ;
        digitalWrite ( LED5 , 0 ) ;
      
        tmrpcm.play ("11.wav") ;
        break ;
      }
    case 2 : {
        digitalWrite ( LED2 , 1 ) ;
        digitalWrite ( LED5 ,0 ) ;
        
        tmrpcm.play ("12.wav") ;
        break ;

      }
    case 3: {
        digitalWrite (LED3 , 1 ) ;
        digitalWrite ( LED5 , 0 ) ;
        
        tmrpcm.play ("13.wav") ;
        break ;
      }
    case 4: {
        digitalWrite ( LED4 , 1 ) ;
        digitalWrite ( LED5 , 0 ) ;
        
        tmrpcm.play ("14.wav") ;
        break ;
      }
    case 5: {
        digitalWrite ( LED5 , 1 );
        
        
        tmrpcm.play ("15.wav") ;
        break ;
      }
  }
}
void listen_music ()
{
  song_number ++ ;
  if  ( song_number == 6 )
  {
    song_number = 1 ;
  }
  //debounce1 = false ;
  Serial.println ("KEY PRESSED") ;
  Serial.println ("song_number=") ;
  Serial.println (song_number ) ;
  if ( song_number == 1 )
  {
    tmrpcm.play ("20.wav") ;
    lcd.clear () ;
    lcd.print ("song Number: 1") ;
    lcd.setCursor (0, 1) ; 
    lcd.print ("konhotenbai1");
    lcd.setCursor (0, 2) ;


  }
  if ( song_number == 2  )
  {
    tmrpcm.play ("21.wav");
    lcd.clear () ;
    lcd.print ("song Number: 2") ;
    lcd.setCursor (0, 1) ;
    lcd.print ("perfect");
    lcd.setCursor (0, 2) ;

  }
  if ( song_number == 3 )
  {
    tmrpcm.play ("22.wav") ;
    lcd.clear () ;
    lcd.print ("song Number: 3") ;
    lcd.setCursor (0, 1) ;
    lcd.print ("konhotenbai3");
    lcd.setCursor (0, 2) ;

  }
  if ( song_number == 4 )
  {
    tmrpcm.play ("23.wav") ;
    lcd.clear () ;
    lcd.print ("song Number: 4") ;
    lcd.setCursor (0, 1) ;
    lcd.print ("konhotenbai4");
    lcd.setCursor (0, 2) ;

  }
  if ( song_number == 5 )
  {
    tmrpcm.play ("24.wav") ;
    lcd.clear () ;
    lcd.print ("song Number: 5") ;
    lcd.setCursor (0, 1) ;
    lcd.print ("Khongnhotenbai5");
    lcd.setCursor (0, 2) ;
  }
  // if ( digitalRead (3) == LOW && debounce2 == true )
  //{
  //  tmrpcm.stopPlayback();     //  111111111111111111111111
  //debounce2 = false ;
  //}
  if ( digitalRead (2) == HIGH )
    // debounce1 = true ;
    if (digitalRead ( 3) == HIGH )
      song_number = song_number - 1 ;
      delay (1000 ) ;


}

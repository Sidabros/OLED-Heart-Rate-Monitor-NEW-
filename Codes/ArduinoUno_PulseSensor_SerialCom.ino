//LATEST SUCCESSSFULL 
//  Degiskenler

/* OLED */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
/* OLED*/

int pulsePin = 1;                 // Pulse Sensor sinyal baglanti yeri : A0
int blinkPin = 13;                // Kalp atislarini gosteren blink LED

// Buradaki degiskenler Volatile cunku Interrupt fonksiyonunda kullanilmaktadirlar
volatile int BPM;                   // Dakikada Kalp Atisini gormek icin degisken
volatile int Signal;                // Sensorden okunan analog deger
volatile int IBI = 600;             // Iki kalp atisi arasini olcmek icin gerekli degisken
volatile boolean Pulse = false;     // kalp atisinin oldugu veya olmadigi durumlari gosteren degisken
volatile boolean QS = false;        // kalp atisinin oldugu veya olmadigi durumlari gosteren degisken


unsigned short int counter=0;       // Ortalama kalp atisi bulmak icin
unsigned short int X =0;            // Ortalama BPM toplamini ifade eder
volatile unsigned short int kn = 0;      // kontrol degiskenimiz, Serial iletisimde gorsel aciklama icin


void setup(){
  
  pinMode(blinkPin,OUTPUT);         // Kalp atisini gosteren portu cikis olarak ata

//  digitalWrite(heartAttack, LOW);
//Serial.begin(115200);             // Serial baglanti hizi
  interruptSetup();                 // Interrupt alt fonksiyonunu set eder

 analogReference(DEFAULT);   // A-REF pinini sensoru besleyen kaynaga baglamak sureti ile kullanilan harici Kuantalama mekanizmasi
  // Biz arduino uzerindeki kaynaktan (5V) sensoru besledigimiz icin yukaridaki satiri comment halinde birakiyoruz.

 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.clearDisplay();
  display.display();
  delay(200);
}

void loop(){
  
 // sendDataToProcessing('S', Signal);     // Burada okunan analog degerin kuantalanmasi ile (2^10) cikan sinyal degeridir

  if (QS == true)
  {                       // Burada eger interrupt fonksiyonumuz bir kalp atisi hissederse if statement'a girilecektir
        sendDataToProcessing('B',BPM);   // Burada BPM gorulecektir        
        QS = false;                      // if statement surekli olarak dongude kalmamasi icin QS degeri degistirildi
   }
  delay(20);                             //  cihazi beklemeye al (20 ms)
}


void sendDataToProcessing(char symbol, int data ){
 if(BPM>=40)
 {
  /*  Serial.print("BPM:");                // symbol prefix tells Processing what type of data is coming  "BPM:"
    Serial.println(BPM);  */              // the data to send culminating in a carriage return "X"
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(60, 10);
    display.print(BPM);
    display.display();
 }       
}

#include <SPI.h> //SD kart modül kütüphanesi
#include <SD.h> // SD kart modül kütüphanesi
#include <DHT.h> // DHT11 sıcaklık ve nem sensörü kütüphanesi
#include <RTClib.h> // RTC kütüphanesi


#define DHTPIN 2     // dht11 sensörü hangi pine bağlı

// uncomment whatever type you're using
#define DHTTYPE DHT11   // kullandıgımız dht sensörürnün tipi


// initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);


const int chipSelect = 4; //sd kart modül hangi pine bağlı

// sd karta veri yazmak için dosya olusturuyoruz
File myFile;

// RTC kullanmak için gerekli parametre
RTC_DS1307 rtc;

void setup() {
  //dht sensörünü başlatıyoruz
  dht.begin();

  //serial monitör başlatma 
  Serial.begin(9600);
  
  // RTC nin olup olmadıgını kontrol eden fonksyon
  while(!Serial); 
    if(! rtc.begin()) {
      Serial.println("RTC modülü bulunamadı");
      while (1);
    }
    else {
      // 
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    if(! rtc.isrunning()) {
      Serial.println("RTC Modülü çalışmıyor!");
    }
    
  // setup for the SD card
  Serial.print("Sd kart yükleniyor...");

  if(!SD.begin(chipSelect)) {
    Serial.println("Yükleme Başarısız!");
    return;
  }
  Serial.println("Yükleme tamamlandı.");
    
  //open file
  myFile=SD.open("DATA.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("Dosya açıldı");
    // ölçtüğümüz verileri yazdırıyoruz
    myFile.println("Tarih,Saat,sıcaklık ºC");
  }
  myFile.close();
}

void loggingTime() {
  DateTime now = rtc.now();
  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(',');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(",");
  }
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.day(), DEC);
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  myFile.close();
  delay(1000);  
}

void loggingTemperature() {
  
  // Sıcaklık celcius cinsinden okunuyor
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  //float f = dht.readTemperature(true);
  
  // dht sensöründe herhangi bir arıza var mı kontrol ediyoruz
  if  (isnan(t) /*|| isnan(f)*/) {
    Serial.println("DHT sensöründen veri okunamadı!");
    return;
  }
  
  //debugging purposes
  Serial.print("Sıcaklık: "); 
  Serial.print(t);
  Serial.println(" *C");
  //Serial.print(f);
  //Serial.println(" *F\t"); 
  
  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("Başarıyla açıldı");
    myFile.print(t);
    myFile.println(",");
  }
  myFile.close();
}

void loop() {
  loggingTime();
  loggingTemperature();
  delay(5000);
}

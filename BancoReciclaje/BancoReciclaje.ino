#include "UbidotsEsp32Mqtt.h"

#include "HX711.h"
HX711 scale;

//#define led   34                                  //Pin GPIO34 para led
const char *UBIDOTS_TOKEN = "BBFF-ie3MYz2KJe4QXIygX8RC162mWqpFKA";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "redmi";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "8702gabo";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "balanza";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "peso"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL2 = "led";
const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

//-----------------------------------------------------------------------Celda
//const int DT = 23;                            // variable modulo celda
//const int SCK1 = 22;
//int peso=0; 

//-----------------------------------------------------------------------

unsigned long timer;
//uint8_t analogPin = 34; // Pin used to read data from GPIO34 ADC_CH6.

Ubidots ubidots(UBIDOTS_TOKEN);

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {Serial.print((char)payload[i]);}
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  timer = millis();

  //-------------------------------------------------SetupCelda
//  scale.begin(DT, SCK1);                      
//  scale.read();
//  scale.read_average(10);   // Promedio de 10 lineas
//  scale.get_value(3);   //Promedio de 3 lecturas
//  scale.get_units(3);  //Promedio de 3 lecturas menos tara
//  scale.set_scale(2649.718382);   // Valor de calibración
//  scale.tare();                   //Tara a 0
//                                 //Despues de la calibracion
//-------------------------------------------------SetupCelda
}

void loop(){
//   if (scale.is_ready()){ 
//    Serial.print("Lectura:\t"); 
//    Serial.println(scale.get_units(), 1);
          
  if (!ubidots.connected())
  { ubidots.reconnect();}
  int timeChange= ((millis()) - timer);
  if (timeChange > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    int   value=random(0,100);//(scale.get_units(), 1);
    int   value2=random(0,2);//digitalRead(led);
    Serial.println((String)VARIABLE_LABEL+" "+value);
    Serial.println((String)VARIABLE_LABEL2+" "+value2);
    ubidots.add(VARIABLE_LABEL,value); // Insert your variable Labels and the value to be sent
    ubidots.add(VARIABLE_LABEL2,value2);
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();
//  }
//  else
//     Serial.println("HX711 not found.");
} //end voidloop******************************************************************

////*****************TOMAR VARIABLES DESDE UBIDOTS
//#include "UbidotsEsp32Mqtt.h"
//
//const char *UBIDOTS_TOKEN = "";  // Put here your Ubidots TOKEN
//const char *WIFI_SSID = "";      // Put here your Wi-Fi SSID
//const char *WIFI_PASS = "";      // Put here your Wi-Fi password
//const char *DEVICE_LABEL = "";   // Replace with the device label to subscribe to
//const char *VARIABLE_LABEL = ""; // Replace with your variable label to subscribe to
//
//Ubidots ubidots(UBIDOTS_TOKEN);
//
//
//void callback(char *topic, byte *payload, unsigned int length)
//{
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  for (int i = 0; i < length; i++)
//  {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();
//}
//
//void setup()
//{
//  // put your setup code here, to run once:
//  Serial.begin(115200);
//  ubidots.setDebug(true);  // uncomment this to make debug messages available
//  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
//  ubidots.setCallback(callback);
//  ubidots.setup();
//  ubidots.reconnect();
//  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL); // Insert the dataSource and Variable's Labels
//}
//
//void loop()
//{
//  // put your main code here, to run repeatedly:
//  if (!ubidots.connected())
//  {
//    ubidots.reconnect();
//    ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL); // Insert the dataSource and Variable's Labels
//  }
//  ubidots.loop();
//}

--------------------------------------------- Balanza ALEX
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// 
//#define DT A1 
//#define SCK A0
//#define sw 9
// 
//long sample = 0;
//float val = 0;
//long count = 0;
//
//
//unsigned long readCount(void)
//{
//unsigned long Count;
//unsigned char i;
//pinMode(DT, OUTPUT);
//digitalWrite(DT,HIGH);
//digitalWrite(SCK,LOW);
//Count = 0;
//pinMode(DT, INPUT);
//
//while(digitalRead(DT));
//
//for (i= 0;i < 24;i++)
//{
//digitalWrite(SCK,HIGH);
//Count = Count << 1;
//digitalWrite(SCK,LOW);
//if(digitalRead(DT))
//Count++;
//}
//
//digitalWrite(SCK,HIGH);
//Count = Count^0x800000;
//digitalWrite(SCK,LOW);
//return(Count);
//}
//
//
//void setup()
//{
//Serial.begin(9600);
//pinMode(SCK, OUTPUT);
//pinMode(sw, INPUT_PULLUP);
//lcd.begin(16, 2);
//lcd.print(" Weight ");
//lcd.setCursor(0,1);
//lcd.print(" Measurement ");
//delay(1000);
//lcd.clear();
//calibrate();
//}
// 
//void loop()
//{
//count = readCount();
////Serial.println("Count variable: ");
////Serial.println(count);
//float w =((float(count-sample)/float(val))-2.*(float(count-sample)/float(val)))*100.;
//lcd.setCursor(0,0);
//lcd.print("Measured Weight");
//lcd.setCursor(0,1);
//lcd.print(w-222);
//lcd.print("g");
//delay(1000);
// 
//if(digitalRead(sw) == 0)
//{
//val = 0;
//sample = 0;
//w = 0;
//count = 0;//count = 0; 
//calibrate();
//}
//}
//
//void calibrate()
//{
//lcd.clear();
//lcd.print("Calibrating...");
//lcd.setCursor(0,1);
//lcd.print("Please Wait...");
//
//for(int i= 0; i< 100; i++)
//{
//count = readCount();
//sample+= count;
//}
//sample/= 100;
//lcd.clear();
//lcd.print("Put 222.024g & wait");
//count = 0;
//
//while(count < 1000)
//{
//count = readCount();
//count = sample - count;
//}
//lcd.clear();
//lcd.print("Please Wait....");
//delay(1000);
//
//for(int i = 0; i<100; i++)
//{
//count = readCount();
//val+= sample - count;
//}
////val = val/222.024;
//val = (val/222.024); // put here your calibrating weight
//lcd.clear();
//}

//////////////////////////////
/*********************


//// include the library code:
//#include <Wire.h>
//#include <Adafruit_RGBLCDShield.h>
//#include <utility/Adafruit_MCP23017.h>
//
//
//// The shield uses the I2C SCL and SDA pins. On classic Arduinos
//// this is Analog 4 and 5 so you can't use those for analogRead() anymore
//// However, you can connect other I2C sensors to the I2C bus and share
//// the I2C bus.
//Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
//
//// These #defines make it easy to set the backlight color
//#define RED     0x21
//#define YELLOW  0x23
//#define GREEN   0x22
//#define TEAL    0x26
//#define BLUE    0x24
//#define VIOLET  0x0,0xa,0x1f,0x1f,0xe,0x4,0x0
//#define WHITE   0x27
//
//byte cuerpo[8] = {
//B01110,
//B01110,
//B00100,
//B11111,
//B00100,
//B01010,
//B10001,
//B00000,
//};
//
//void setup() {
//  // Debugging output
//  Serial.begin(9600);
//  // set up the LCD's number of columns and rows: 
//  lcd.begin(16, 2);
//
//  // Print a message to the LCD. We track how long it takes since
//  // this library has been optimized a bit and we're proud of it :)
//  int time = millis();
//  lcd.print("Hello, world!");
//  time = millis() - time;
//  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
//  lcd.setBacklight(WHITE);
//}
//
//uint8_t i=0;
//void loop() {
//  // set the cursor to column 0, line 1
//  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
//  // print the number of seconds since reset:
//  lcd.print(millis()/1000);
//   lcd.setCursor(0, 7);
//   
// int count=33;
//  char ascii=0x00+33;    //Starting from 34th
//  char ascii2=(0x0,0xa,0x1f,0x1f,0xe,0x4,0x0);
//                         // Character
//  while(count!=235)
//  {
//    lcd.setCursor(0, 0);
//    lcd.print("DECIMAL = ");
//    lcd.print(count);
//    lcd.setCursor(0 , 1);
//    lcd.print("ASCII = ");
//    lcd.print(ascii);
//    lcd.setCursor(10 , 1);
//    lcd.createChar (0,cuerpo);
//    lcd.write (byte (8));
//    count++;
//    ascii++;
//    delay(500);
//    lcd.clear();
//  }
//
//   
////  uint8_t buttons = lcd.readButtons();
////
////  if (buttons) {
////    lcd.clear();
////    lcd.setCursor(0,0);
////    if (buttons & BUTTON_UP) {
////      lcd.print("UP ");
////      lcd.setBacklight(RED);
////    }
////    if (buttons & BUTTON_DOWN) {
////      lcd.print("DOWN ");
////      lcd.setBacklight(YELLOW);
////    }
////    if (buttons & BUTTON_LEFT) {
////      lcd.print("LEFT ");
////      lcd.setBacklight(GREEN);
////    }
////    if (buttons & BUTTON_RIGHT) {
////      lcd.print("RIGHT ");
////      lcd.setBacklight(TEAL);
////    }
////    if (buttons & BUTTON_SELECT) {
////      lcd.print("SELECT ");
////      lcd.setBacklight(VIOLET);
////    }
////  }
//}

//********************
#include "HX711.h"
#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
#include <Adafruit_RGBLCDShield.h>
#include <EEPROM.h>

//Define las variables globales
byte DT=36;         //GPIO36
byte CLK=39;       //GPIO39
byte modo = 34;   //GPIO34
byte tara = 35;   //GPIO35
int peso_conocido[2] = {222,234};
long escala;

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
//LiquidCrystal_I2C lcd(0x27,16,2); 
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield(); 

//Crear el objeto balanza
HX711 balanza;

//Función de Anti-debounce (Evitar el rebote del pulsador)
void anti_debounce(byte boton){
      delay(100);
      while(digitalRead(boton)); //Anti-Rebote
      delay(100);
}

//Función de calibración y ajuste
void calibration(){
  
  int i = 0,cal=1;
  long adc_lecture;
  
  // Escribimos el Mensaje en el LCD
  lcd.setCursor(2, 0);
  lcd.print("Calibracion de");
  lcd.setCursor(4, 1);
  lcd.print("Balanza");
  delay(1500);
  balanza.read();
  balanza.set_scale(); //La escala por defecto es 1
  balanza.tare(20);  //El peso actual es considerado Tara.
  
  lcd.clear();

  //Inicia el proceso de ajuste y calibración
  while(cal == 1){
    
    lcd.setCursor(1, 0);
    lcd.print("Peso Conocido:");
    lcd.setCursor(1, 1);
    lcd.print(peso_conocido[i]);
    lcd.print(" g        ");

    //Busca el peso conocido con el botón tara
    if(digitalRead(tara)){  
      anti_debounce(tara);
      i =(i>2) ? 0:i+1; //if-else en una linea
    }

    //Selecciona el peso conocido con el boton modo
    if(digitalRead(modo)){
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Ponga el Peso");
      lcd.setCursor(1, 1);
      lcd.print("y espere ...");
      delay(2000);

      //Lee el valor del HX711
      adc_lecture = balanza.get_value(100);

      //Calcula la escala con el valor leido dividido el peso conocido
      escala = adc_lecture / peso_conocido[i];

      //Guarda la escala en la EEPROM
      EEPROM.put( 0, escala );
      delay(100);
      cal = 0; //Cambia la bandera para salir del while
      lcd.clear();
    }
    
  }
}

void setup() {
  //Configura la balanza
  balanza.begin(DT, CLK);
  
  //Configura los botones
  pinMode(modo, OUTPUT);
  pinMode(tara, OUTPUT);

  // Inicializar el LCD
  //lcd.init();
  lcd.begin(16, 2);
  
  //Encender la luz de fondo.
  //lcd.backlight();
  lcd.setBacklight(0x7);

  //Lee el valor de la escala en la EEPROM
  EEPROM.get( 0, escala );

  //Pregunta si se desea entrar en calibración
  if(digitalRead(modo) && digitalRead(tara))
    calibration();

  //Mensaje inicial en el LCD
  lcd.setCursor(1, 0);
  lcd.print("Retire el Peso");
  lcd.setCursor(1, 1);
  lcd.print("y Espere");
  delay(2000);
  balanza.set_scale(escala); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Listo....");  
  delay(1000);
  lcd.clear();
}

void loop() {
  float peso;

  //Mide el peso de la balanza
  peso = balanza.get_units(10);

  //Muestra el resultado
  lcd.setCursor(1, 0);
  lcd.print("Peso: ");
  lcd.print(peso,0);
  lcd.println(" g        ");
  delay(5);

  //Botón de Tara
    if(digitalRead(tara)){  
      anti_debounce(tara);
      balanza.tare(10);  //El peso actual es considerado Tara.
    }
}

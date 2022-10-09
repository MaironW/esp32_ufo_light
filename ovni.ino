//Programa: Kit Luminária OVNI
//Autor: FILIPEFLOP
  
//-------Configurações iniciais da plataforma Blynk--------
 
#define BLYNK_PRINT Serial
  
// Insira abaixo o ID do seu template
#define BLYNK_DEVICE_NAME "UFO"
#define BLYNK_TEMPLATE_ID "TMPL6ejFgAMo"
  
// Insira abaixo o seu Auth Token
char auth[] = "oFi1Vv2wMxn8R3knG4kdvxy57CMxr-mt";
  
// Insira abaixo o nome da sua rede WiFi
char ssid[] = "Rubens";
  
// Insira abaixo a senha da sua rede WiFi
char pass[] = "10012015rubens";
 
//--------Bibliotecas utilizadas no código--------
 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
 
 
//--------Definições dos pinos--------
 
#define PIXEL_PIN1     13
#define PIXEL_PIN2     12
#define SERVO_PIN      15
 
//--------Configurações iniciais para fita e anel de LED--------
 
#define PIXEL_COUNT1  9
#define PIXEL_COUNT2  12
 
Adafruit_NeoPixel strip1(PIXEL_COUNT1, PIXEL_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(PIXEL_COUNT2, PIXEL_PIN2, NEO_GRB + NEO_KHZ800);
 
//--------Configurações iniciais do servo motor--------
 
Servo myservo;
 
//--------Definição das váriaveis globais--------
 
int switch_top = 0;
int color_top = 0;
int switch_bottom = 0;
int color_bottom = 0;
int cow_speed = 0;
int bright_top = 0;
int bright_bottom = 0;
int pos = 0;
 
//--------Setup--------
 
void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);
 
  // Inicializa o servo motor
  myservo.attach(SERVO_PIN);
  myservo.write(pos);
 
  // Inicializa a fita de LED
  strip1.begin();
  strip1.show();
  strip1.clear();
 
  // Inicializa o anel de LED
  strip2.begin();
  strip2.show();
  strip2.clear();

  // Inicializa app Blynk e conexão WIFi
  Blynk.begin(auth, ssid, pass);
}
 
//--------Loop--------
 
void loop() {
  // Atualização da plataforma Blynk
  Blynk.run();
 
  // Troca as cores da fita de LED
  if (switch_top == 0) {
    colorWipe1(strip1.Color( 0, 0, 0), 50);        // Desligado
  } else {
    switch(color_top) {
      case 1:
        colorWipe1(strip1.Color( 0, 0, 205), 50);      // Azul
        break;
      case 2:
        colorWipe1(strip1.Color( 0, 206, 209), 50);    // Ciano
        break;
      case 3:
        colorWipe1(strip1.Color( 0, 128, 0), 50);      // Verde
        break;
      case 4:
        colorWipe1(strip1.Color( 75, 0, 130), 50);     // Roxo
        break;
      case 5:
        colorWipe1(strip1.Color( 255, 105, 180), 50);  // Rosa
        break;
      case 6:
        colorWipe1(strip1.Color( 255, 0, 0), 50);      // Vermelho
        break;
      case 7:
        colorWipe1(strip1.Color( 255, 140, 0), 50);    // Laranja
        break;
      case 8:
        colorWipe1(strip1.Color( 255, 215, 0), 50);    // Amarelo
        break;
      case 9:
        theaterChase1(strip1.Color( 0, 0, 205), 50);      // Azul
        break;
      case 10:
        theaterChase1(strip1.Color( 0, 206, 209), 50);    // Ciano
        break;
      case 11:
        theaterChase1(strip1.Color( 0, 128, 0), 50);      // Verde
        break;
      case 12:
        theaterChase1(strip1.Color( 75, 0, 130), 50);     // Roxo
        break;
      case 13:
        theaterChase1(strip1.Color( 255, 105, 180), 50);  // Rosa
        break;
      case 14:
        theaterChase1(strip1.Color( 255, 0, 0), 50);      // Vermelho
        break;
      case 15:
        theaterChase1(strip1.Color( 255, 140, 0), 50);    // Laranja
        break;
      case 16:
        theaterChase1(strip1.Color( 255, 215, 0), 50);    // Amarelo
        break;
      case 17:
        rainbow1(10);
        break;    
    }
  }

  // Troca as cores do anel de LED
  if (switch_bottom == 0) {
    colorWipe2(strip2.Color( 0, 0, 0), 50);        // Desligado
  } else {
    switch(color_bottom) {
      case 1:
        colorWipe2(strip2.Color( 0, 0, 205), 50);      // Azul
        break;
      case 2:
        colorWipe2(strip2.Color( 0, 206, 209), 50);    // Ciano
        break;
      case 3:
        colorWipe2(strip2.Color( 0, 128, 0), 50);      // Verde
        break;
      case 4:
        colorWipe2(strip2.Color( 75, 0, 130), 50);     // Roxo
        break;
      case 5:
        colorWipe2(strip2.Color( 255, 105, 180), 50);  // Rosa
        break;
      case 6:
        colorWipe2(strip2.Color( 255, 0, 0), 50);      // Vermelho
        break;
      case 7:
        colorWipe2(strip2.Color( 255, 140, 0), 50);    // Laranja
        break;
      case 8:
        colorWipe2(strip2.Color( 255, 215, 0), 50);    // Amarelo
        break;
    }
  }

  // Liga e desliga o servo motor
  if (cow_speed == 0) {
    pos = 0;
    myservo.write(pos);
  } else {
    for (pos = 0; pos <= 180; pos += 1) {
      myservo.write(pos);
      delay(16-cow_speed);
    }
    for (pos = 180; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(16-cow_speed);
    }
  }
}
 
//--------Funções de controle do anel e fita de LED--------
 
void colorWipe1(uint32_t color, int wait) {
  for(int i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, color);
    strip1.show();
    delay(wait);
  }
}
 
void theaterChase1(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {
    for(int b=0; b<3; b++) {
      strip1.clear();
      for(int c=b; c<strip1.numPixels(); c += 3) {
        strip1.setPixelColor(c, color);
      }
      strip1.show();
      delay(wait);
    }
  }
}
 
void rainbow1(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip1.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip1.numPixels());
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
    }
    strip1.show();
    delay(wait);
  }
}
 
void colorWipe2(uint32_t color, int wait) {
  for(int i=0; i<strip2.numPixels(); i++) {
    strip2.setPixelColor(i, color);
    strip2.show();
    delay(wait);
  }
}
 
//--------Funções de controle dos botões do aplicativo Blynk--------

// Switch ON/OFF top LED
BLYNK_WRITE(V0) {
  switch_top = param.asInt();
}

// Switch ON/OFF bottom LED
BLYNK_WRITE(V1) {
  switch_bottom = param.asInt();
}

// Get the current color_top option
BLYNK_WRITE(V2) {
  color_top = param.asInt();
}

// Get the current color_bottom option
BLYNK_WRITE(V3) {
  color_bottom = param.asInt();
}

// Cow Speed 
BLYNK_WRITE(V4) {
  cow_speed = param.asInt();
}

// Top brigthness
BLYNK_WRITE(V5) {
  bright_top = param.asInt();
  strip1.setBrightness(bright_top);
  strip1.show();
}

// Bottom brigthness
BLYNK_WRITE(V6) {
  bright_bottom = param.asInt();
  strip2.setBrightness(bright_bottom);
  strip2.show();
}
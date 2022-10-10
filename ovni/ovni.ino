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

int color_top[] = {255, 255, 255};
int color_bottom[] = {255, 255, 255};
int mode_top = 0;
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
  colorWipe1(strip1.Color(color_top[0], color_top[1], color_top[2]), 50);

  // Inicializa o anel de LED
  strip2.begin();
  strip2.show();
  strip2.clear();
  colorWipe2(strip2.Color(color_bottom[0], color_bottom[1], color_bottom[2]), 50);

  // Inicializa app Blynk e conexão WIFi
  Blynk.begin(auth, ssid, pass);
}

//--------Loop--------

void loop() {
  // Atualização da plataforma Blynk
  Blynk.run();

  // Troca as cores da fita de LED
  switch(mode_top) {
    case 0:
      colorWipe1(strip1.Color(color_top[0], color_top[1], color_top[2]), 50);
      break;
    case 1:
      theaterChase1(strip1.Color(color_top[0], color_top[1], color_top[2]), 50);
      break;
    case 2:
      rainbow1(10);
      break;
  }

  // Troca as cores do anel de LED
  colorWipe2(strip2.Color(color_bottom[0], color_bottom[1], color_bottom[2]), 50);

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

// Get the current color_top option
BLYNK_WRITE(V0) {
  mode_top = param.asInt();
}

// Cow Speed
BLYNK_WRITE(V2) {
  cow_speed = param.asInt();
}

// Top brigthness
BLYNK_WRITE(V3) {
  bright_top = param.asInt();
  strip1.setBrightness(bright_top);
  strip1.show();
}

// Bottom brigthness
BLYNK_WRITE(V4) {
  bright_bottom = param.asInt();
  strip2.setBrightness(bright_bottom);
  strip2.show();
}

// Top RED
BLYNK_WRITE(V5) {
  color_top[0] = param.asInt();
}

// Top GREEN
BLYNK_WRITE(V6) {
  color_top[1] = param.asInt();
}

// Top BLUE
BLYNK_WRITE(V7) {
  color_top[2] = param.asInt();
}

// Bottom RED
BLYNK_WRITE(V8) {
  color_bottom[0] = param.asInt();
}

// Bottom GREEN
BLYNK_WRITE(V9) {
  color_bottom[1] = param.asInt();
}

// Bottom BLUE
BLYNK_WRITE(V10) {
  color_bottom[2] = param.asInt();
}
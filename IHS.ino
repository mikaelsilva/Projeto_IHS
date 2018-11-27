#define C1  33
#define CS1 35
#define D1  37
#define DS1 39
#define E1  41
#define F1  44
#define FS1 46
#define G1  49
#define GS1 52
#define A1  55
#define AS1 58
#define B1  62

#define C2  65
#define CS2 69
#define D2  73
#define DS2 78
#define E2  82
#define F2  87
#define FS2 93
#define G2  98
#define GS2 104
#define A2  110
#define AS2 117
#define B2  123

#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247

#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494

#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988

#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976

#define C7  2093
#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951

#define C8  4186
#define CS8 4435
#define D8  4699
#define DS8 4978

#define Oitava_1 7
#define Oitava_2 13
#define Oitava_3 18
#define Oitava_4 23
#define Oitava_5 28
#define Oitava_6 33
#define Oitava_7 38
#define Oitava_8 43

#define Nota_C 7
#define Nota_CS 13
#define Nota_D 18
#define Nota_DS 23
#define Nota_E 28
#define Nota_F 33
#define Nota_FS 38
#define Nota_G 43
#define Nota_GS 48
#define Nota_A 53
#define Nota_AS 58
#define Nota_B 63

#define Pin_Oitava_1 22
#define Pin_Oitava_2 24
#define Pin_Oitava_3 26
#define Pin_Oitava_4 28
#define Pin_Oitava_5 30
#define Pin_Oitava_6 32
#define Pin_Oitava_7 34
#define Pin_Oitava_8 36

#define Pin_Nota_C 23
#define Pin_Nota_D 25
#define Pin_Nota_E 27
#define Pin_Nota_F 29
#define Pin_Nota_G 31
#define Pin_Nota_A 33
#define Pin_Nota_B 35
#define Pin_Nota_CS 37
#define Pin_Nota_DS 39
#define Pin_Nota_FS 41
#define Pin_Nota_GS 43
#define Pin_Nota_AS 45

#define pino_trigger 50
#define pino_echo 51

#define pino_trigger2 48
#define pino_echo2 49

#include <Ultrasonic.h>



int notas[13][9]={{0,0,0,0,0,0,0,0,0},{0,A1,A2,A3,A4,A5,A6,A7,0},{0,B1,B2,B3,B4,B5,B6,B7,0},{0,C1,C2,C3,C4,C5,C6,C7,C8},{0,D1,D2,D3,D4,D5,D6,D7,D8},
                  {0,E1,E2,E3,E4,E5,E6,E7,0},{0,F1,F2,F3,F4,F5,F6,F7,0},{0,G1,G2,G3,G4,G5,G6,G7,0},{0,CS1,CS2,CS3,CS4,CS5,CS6,CS7,CS8},{0,DS1,DS2,DS3,DS4,DS5,DS6,DS7,DS8},
                  {0,FS1,FS2,FS3,FS4,FS5,FS6,FS7,0},{0,GS1,GS2,GS3,GS4,GS5,GS6,GS7,0},{0,AS1,AS2,AS3,AS4,AS5,AS6,AS7,0}};

float   linha_pino=0,coluna_pino;
int     qual_nota=0;
int     qual_oitava=0,coluna=0,linha=0;
float   distancia=0,aux=0;
 
Ultrasonic ultrasonic(pino_trigger, pino_echo);
Ultrasonic ultrasonic2(pino_trigger2, pino_echo2);

void setup() {
  Serial.begin(115200);
  pinMode(Pin_Oitava_1, OUTPUT);         
  pinMode(Pin_Oitava_2, OUTPUT); 
  pinMode(Pin_Oitava_3, OUTPUT); 
  pinMode(Pin_Oitava_4, OUTPUT); 
  pinMode(Pin_Oitava_5, OUTPUT); 
  pinMode(Pin_Oitava_6, OUTPUT); 
  pinMode(Pin_Oitava_7, OUTPUT); 
  pinMode(Pin_Oitava_8, OUTPUT); 
  
  pinMode(Pin_Nota_C, OUTPUT);
  pinMode(Pin_Nota_D, OUTPUT); 
  pinMode(Pin_Nota_E, OUTPUT); 
  pinMode(Pin_Nota_F, OUTPUT); 
  pinMode(Pin_Nota_G, OUTPUT); 
  pinMode(Pin_Nota_A, OUTPUT); 
  pinMode(Pin_Nota_B, OUTPUT); 
  
  pinMode(Pin_Nota_CS, OUTPUT);  
  pinMode(Pin_Nota_DS, OUTPUT); 
  pinMode(Pin_Nota_FS, OUTPUT); 
  pinMode(Pin_Nota_GS, OUTPUT); 
  pinMode(Pin_Nota_AS, OUTPUT); 

}

void loop() {

  if(Serial.available()){
    qual_nota = Serial.read();
  }
  
  pino(qual_nota);
  aux = ultrasonic.timing();
  distancia = ultrasonic.convert(aux, Ultrasonic::CM);
  coluna = oitava(distancia);
  
  aux = ultrasonic2.timing();
  distancia = ultrasonic2.convert(aux, Ultrasonic::CM);
  linha = nota(distancia);

  correto(qual_nota,linha,coluna);

  //Aqui seria a função que manteria o buzzer ligado somente se o buzzer for usado no arduino,
  //como iremos utilizar o buzzer da placa,não precisamos fa função do buzzer aqui, retornamos somente a frequencia
  
}



void pino(int qual_nota){
   int oitava = 0,nota = 0;
   oitava = qual_nota % 9;
   nota = qual_nota/9;

  if(oitava == 1){
    digitalWrite(Pin_Oitava_1, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Oitava_1, LOW);
  }
  else if(oitava == 2){
    digitalWrite(Pin_Oitava_2, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Oitava_2, LOW);
  }
  else if(oitava == 3){
    digitalWrite(Pin_Oitava_3, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Oitava_3, LOW);
  }
  else if(oitava == 4){
    digitalWrite(Pin_Oitava_4, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Oitava_4, LOW);
  }
  else if(oitava == 5){
    digitalWrite(Pin_Oitava_5, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Oitava_5, LOW);
  }
  else if(oitava == 6){
    digitalWrite(Pin_Oitava_6, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Oitava_6, LOW);
  }
  else if(oitava == 7){
    digitalWrite(Pin_Oitava_7, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Oitava_7, LOW);
  }
  else if(oitava == 8){
    digitalWrite(Pin_Oitava_8, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Oitava_8, LOW);
  }
  else{
    //???
  }

  //IDENTIFICANDO A LINHA
  if(nota == 1){
    digitalWrite(Pin_Nota_A, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_A, LOW);
  }
  else if(nota == 2){
    digitalWrite(Pin_Nota_B, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_B, LOW);
  }
  else if(nota == 3){
    digitalWrite(Pin_Nota_C, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_C, LOW);
  }
  else if(nota == 4){
    digitalWrite(Pin_Nota_D, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_D, LOW);
  }
  else if(nota == 5){
    digitalWrite(Pin_Nota_E, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_E, LOW);
  }
  else if(nota == 6){
    digitalWrite(Pin_Nota_F, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_F, LOW);
  } 
  else if(nota == 7){
    digitalWrite(Pin_Nota_G, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_G, LOW);
  } 
  else if(nota == 8){
    digitalWrite(Pin_Nota_CS, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_CS, LOW);
  } 
  else if(nota == 9){
    digitalWrite(Pin_Nota_DS, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_DS, LOW);
  }
  else if(nota == 10){
    digitalWrite(Pin_Nota_FS, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_FS, LOW);
  }
  else if(nota == 11){
    digitalWrite(Pin_Nota_GS, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_GS, LOW);
  } 
  else if(nota == 12){
    digitalWrite(Pin_Nota_AS, HIGH);      
    delay(100);                 
    digitalWrite(Pin_Nota_AS, LOW);
  }
  else {
    //??
  } 
}

int oitava(float distancia){
  int valor = 0;
  
  if(distancia - 2 > Oitava_1 || Oitava_1 < distancia+2){
    valor = 1;
  }
  else if(distancia - 2 > Oitava_2 || Oitava_2 < distancia+2){
    valor = 2;
  }
  else if(distancia - 2 > Oitava_3 || Oitava_3 < distancia+2){
    valor = 3;
  }
  else if(distancia - 2 > Oitava_4 || Oitava_4 < distancia+2){
    valor = 4;
  }
  else if(distancia - 2 > Oitava_5 || Oitava_5 < distancia+2){
    valor = 5;
  }
  else if(distancia - 2 > Oitava_6 || Oitava_6 < distancia+2){
    valor = 6;
  }
  else if(distancia - 2 > Oitava_7 || Oitava_7 < distancia+2){
    valor = 7;
  }
  else if(distancia - 2 > Oitava_8 || Oitava_8 < distancia+2){
    valor = 8;
  }
  else{
      valor = 0;
  }
  return valor;
}


int nota(float distancia){
  int valor = 0;

  //NATURAIS
  if(distancia - 2 < Nota_A || Nota_A < distancia + 2){
    valor = 1;
  }
  else if(distancia - 2 < Nota_B || Nota_B < distancia + 2){
    valor = 2;
  }
  else if(distancia - 2 < Nota_C || Nota_C < distancia + 2){
    valor = 3;
  }
  else if(distancia - 2 < Nota_D || Nota_D < distancia + 2){
    valor = 4;
  }
  else if(distancia - 2 < Nota_E || Nota_E < distancia + 2){
    valor = 5;
  }
  else if(distancia - 2 < Nota_F || Nota_F < distancia + 2){
    valor = 6;
  }
  else if(distancia - 2 < Nota_G || Nota_G < distancia + 2){
    valor = 7;
  }

  //SUSTENIDOS
  else if(distancia - 2 < Nota_CS || Nota_CS < distancia + 2){
    valor = 8;
  }
  else if(distancia - 2 < Nota_DS || Nota_DS < distancia + 2){
    valor = 9;
  }
  else if(distancia - 2 < Nota_FS || Nota_FS < distancia + 2){
    valor = 10;
  }
  else if(distancia - 2 < Nota_GS || Nota_GS < distancia + 2){
    valor = 11;
  }
  else if(distancia - 2 < Nota_AS || Nota_AS < distancia + 2){
    valor = 12;
  }

  //Valor invalido
  else{
    valor = 0;
  }

  
  return valor;
}

void correto(int qual_nota,int linha, int coluna){
    if(nota[linha][coluna] == (nota+qual_nota)){
    Serial.write("y");
    }
    else{
    Serial.write("n");
    }
}


#define MAX_PIN_CORTE 14
#define DELAY_COMUNIC_MULTIPLEX 200

int pin_mult_D0 = 16;
int pin_mult_D1 = 5;
int pin_mult_D2 = 4;
int pin_mult_D3 = 0;

// EXEMPLO
//D3 D2 D1 D0
// 0  0  0  1

int sinal_bin[16][4] = {0,0,0,0,  0,0,0,1,  0,0,1,0,  0,0,1,1,  0,1,0,0,  0,1,0,1,  0,1,1,0,  0,1,1,1,  1,0,0,0,  1,0,0,1,  1,0,1,0,  1,0,1,1,  1,1,0,0,  1,1,0,1,  1,1,1,0,  1,1,1,1};
int sinal_analogico[14];

void setup() {
  
  Serial.begin(9800);
  delay(10);
  pinMode(pin_mult_D0, OUTPUT);
  pinMode(pin_mult_D1, OUTPUT);
  pinMode(pin_mult_D2, OUTPUT);
  pinMode(pin_mult_D3, OUTPUT);
  delay(100);
}

void loop() {
 
  for(int i=0; i<MAX_PIN_CORTE; i++){
    // Monta a palavra binária para entrada do MOLTIPLEX
    digitalWrite(pin_mult_D0, sinal_bin[i][3]); 
    digitalWrite(pin_mult_D1, sinal_bin[i][2]); 
    digitalWrite(pin_mult_D2, sinal_bin[i][1]); 
    digitalWrite(pin_mult_D3, sinal_bin[i][0]); 

    // Delay para a resposta do MULTIPLEX
    delay(DELAY_COMUNIC_MULTIPLEX);

    // Pega resultado do piezoelétrico
    sinal_analogico[i] = analogRead(A0);  
  }

  for(int i=0; i<MAX_PIN_CORTE; i++){
    Serial.println("-> Resultado do piezo");
    Serial.print(sinal_analogico[i]);
    Serial.print(" ");
    delay(100);
  }
  Serial.println("");

  delay(500);
}

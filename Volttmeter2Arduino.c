int VSensor;
int sensorValue;
int Valor;
int VoltagePin=A1;

unsigned long tinicial;
unsigned long tiempo;
float Voltage;
/** Lazo para iniciar comuniacion serial e inicializar variables*/
void setup (){
 
  Serial.begin (9600);

 tinicial= millis ();
 tiempo=0;
 Voltage=0;
}
/** Lazo para conversion A/D y envio de datos al puerto serial  */
void loop()
{
 

  VSensor= analogRead (VoltagePin);
delay (10);
Valor = constrain (VSensor , 0 , 1023);
Voltage = ((Valor)*5)/1023.0; //restringir valores posibles 
tiempo= (millis()-tinicial);
Serial.print(tiempo);
Serial.print(',');
Serial.println (Voltage);


delay (50);

  }

/** ENCABEZADOS
*@file Voltmeter2Arduino.c
*@brief Experimento 3. IE 0624 Laboratorio de Microcontroladores. Escrito orignalmente en el IDE de Arduino
*@autor Andrés Quesada Acosta, B04927. José Pablo Martínez Hernández, B34024.
*@date 12 de octubre del 2016.
*/

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
 
/**
* @brief Lazo de medición de datos analógicos 
* @param Datos en el pin analógico del microcontrolador
* @return Resultado de la lectura de los datos
*/

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

/** ENCABEZADOS
*@file Voltmeter2.c
*@brief Experimento 3. IE 0624 Laboratorio de Microcontroladores. Escrito orignalmente en Pyton
*@autor Andr�s Quesada Acosta, B04927. Jos� Pablo Mart�nez Hern�ndez, B34024.
*@date 12 de octubre del 2016.
*/
            
/** Librerias a utilizar */

import serial #importar liberia Serial
import numpy as np # Liberia para manipular arrays
import matplotlib.pyplot as plt # importar matplotlib
import matplotlib.animation as animation
from time import time
import csv
from drawnow import *
import atexit 

/** Apertura del archivo csv */

fileCSV = open('voltaje.csv', 'w') 



/** creaci�n de objeto Serial */
arduinoData= serial.Serial('COM5',9600) 
plt.ion()
cnt=0
start_time=time()

/** Arrays para guardar datos y graficarlos con Matplotlib*/
timepoints=[]
voltaje=[]

view_time=2

/**
* @brief Lectura del puerto serial 
* @param Datos del convertidor anal�gico digital
* @return Gr�fica din�mica del comportamiento de los datos medidos
*/

fig1=plt.figure() 

plt.ylim(0,5)
plt.xlim([0,view_time])
plt.title ('Osciloscopio')
plt.grid(True)
plt.ylabel('Tension [v]')
line1,= plt.plot(voltaje)


arduinoData.flushInput()

/**
* @brief Lectura del puerto serial 
* @param Datos del convertidor anal�gico digital
* @return Lectrura de los datos 
*/

while True: #while loops that loops for ever

    while (arduinoData.inWaiting()==0): # esperar hasta que hayan datos
        pass #do nothing
        /**Lectura de lineas del puerto serial */
        
    data=arduinoData.readline() #leer linea de arduino
    dataArray=data.split(',')
    volt= float(dataArray[1])#convertir a float

/**
* @brief Creaci�n del .csv
* @param Datos le�dos por el convertidor
* @return Archivo .csv con los datos medidos
*/
    fileCSV.write(data) #escribir valores de tiempo y tension leidos del arduino en un.csv
       
    try:
        if cnt%2==0:  #tomar la mitad de los valores para generar grafica a tiempo real, se pierde resoucion pero se gana velocidad
            voltaje.append(volt)
         
                      
/** Construccion de arreglo de tiempos para graficar */
            timepoints.append(time()-start_time)
            current_time=timepoints[-1]
/**Actualizaci�n de datos para graficar */

            line1.set_xdata(timepoints)
            line1.set_ydata (voltaje)
            cnt=cnt+1
            
            
/** Definici�n de ventana de tiempo para gr�fica a tiempo real*/
            if current_time>view_time:
                plt.xlim([current_time-view_time,current_time])
        else:
            cnt=cnt+1
    except: pass
    
    
    fig1.canvas.draw()
    

/** Cerrar archivos y lectura del puerto serial */
            
fileCSV.close()
arduinoData.close()
            
           

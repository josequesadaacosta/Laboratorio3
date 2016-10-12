/** ENCABEZADOS
*@file Voltmeter2.c
*@brief Experimento 3. IE 0624 Laboratorio de Microcontroladores. Escrito en orignalmente en Pyton
*@autor Andrés Quesada Acosta, B04927. José Pablo Martínez Hernández, B34024.
*@date 13 de octubre del 2016.
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



/** creación de objeto Serial */
arduinoData= serial.Serial('COM5',9600) 
plt.ion()
cnt=0
start_time=time()

/** Arrays para guardar datos y graficarlos con Matplotlib*/
timepoints=[]
voltaje=[]

view_time=2

/**funcion para graficar datos */
fig1=plt.figure() 

plt.ylim(0,5)
plt.xlim([0,view_time])
plt.title ('Osciloscopio')
plt.grid(True)
plt.ylabel('Tension [v]')
line1,= plt.plot(voltaje)


arduinoData.flushInput()




 

   
while True: #while loops that loops for ever

    while (arduinoData.inWaiting()==0): # esperar hasta que hayan datos
        pass #do nothing
        /**Lectura de lineas del puerto serial */
        
    data=arduinoData.readline() #leer linea de arduino
    dataArray=data.split(',')
    volt= float(dataArray[1])#convertir a float
    
/** Escritura de archivo csv */
    
    fileCSV.write(data) #escribir valores de tiempo y tension leidos del arduino en un.csv
    
    
    
    try:
        if cnt%2==0:  #tomar la mitad de los valores para generar grafica a tiempo real, se pierde resoucion pero se gana velocidad
            voltaje.append(volt)
            
           
       
        
                      
/** Construccion de arreglo de tiempos para graficar */
            timepoints.append(time()-start_time)
            current_time=timepoints[-1]
/**Actualización de datos para graficar */

            line1.set_xdata(timepoints)
            line1.set_ydata (voltaje)
            cnt=cnt+1
            
            
/** Definición de ventana de tiempo para gráfica a tiempo real*/
            if current_time>view_time:
                plt.xlim([current_time-view_time,current_time])
        else:
            cnt=cnt+1
    except: pass
    
    
    fig1.canvas.draw()
    

/** Cerrar archivos y lectura del puerto serial */
            
fileCSV.close()
arduinoData.close()
            
           

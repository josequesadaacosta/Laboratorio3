function voltaje = Matlab_Arduino(numero_muestras)

% Matlab + Arduino + Serial Communications

close all;
clc;
voltaje = 0; % Vector donde se guardar�n los datos

%%% Inicializamos el Puerto Serial
delete(instrfind({'port'},{'COM4'})); 
puerto_serial = serial('COM4');
puerto_serial.BaudRate = 115200;
warning('off','MATLAB:serial:fscanf:unsuccessfulRead');

%%% Abro el puerto serial
fopen(puerto_serial);

%%% Declaro un contador del n�mero de muestras ya contadas
contador = 1;

%%% Creo una ventana para la gr�fica
figure('Name','Serial communications: Matlab + Arduino');
title('ADC Serial Communications MATLAB + ARDUINO');
xlabel('N�mero de muestras');
ylabel('Voltaje (V)');
grid on;
hold on;

%%% Lazo while para que tome las muestras que queremos

while contador<=numero_muestras
    ylim([0 5.1]);
    xlim([contador-20 contador+5]);
    valor_ADC = fscanf(puerto_serial,'%d')';
    voltaje(contador) = (valor_ADC(1)*5)/1023;
    plot(voltaje);
    drawnow
    contador = contador + 1;
end

%%% Corto la conexi�n con el puerto Serial y ellimino las variables

fclose(puerto_serial);
delete(puerto_serial);

end
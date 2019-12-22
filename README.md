# cw-arduino-beacon

Implementacion de una baliza de CW en Arduino, solo audio. Permite poner un texto que va a ser modulado en CW/Morse con un tono en un PIN del microcontrolador.

Es un proyecto simple y basico para experimentar con Arduino en el ambito de la radioaficion.

Si es lo primero que haces con Arduino, antes tenes que leer un tutorial de Arduino https://www.arduino.cc/en/Guide/HomePage y hacer los ejercicios basicos (titilar, leer un boton, etc). 


## Instrucciones

* Bajar este repositorio o el archivo `cw-arduino-beacon.ino`.
* Abrir el archivo con la IDE de Arduino (https://www.arduino.cc/en/main/software).
* Subir el programa al microcontrolador.
* Conectar un parlante piezoelectrico al PIN 13 del arduino y a algun PIN de GND (tierra).

La baliza deberia comenzar a transmitir inmediatamente y hacer pausas de un minuto entre transmisiones.


## Configurando la baliza

Si no modificamos nada, la baliza comenzara a transmitir con los parametros por defecto. Para modificar estos parametros hay que usar la IDE de arduino, editar el codigo y subirlo nuevamente al microcontrolador.

### Mensaje

El mensaje por defecto, que solo admite mayusculas y numeros, esta definido en la linea:

```c++
char MESSAGE[] = "CQ DE N0CAL";
```

Cambiando el valor entre comillas se modifica el mensaje de la baliza.

### Tono

Algunos parametros del tono se pueden cambiar en:

```c++
const int toneFreqHz = 716;       // Frecuencia del tono
const int toneDurationMs = 150;   // Duracion del tono
```

El parametro `toneFreqHz` es la frecuencia de audio del tono, expresada en Hz.

La duracion de tono mas corto se define en la variable `toneDurationMs` y esta expresada en milisegundos.

### CW

Por defecto los intervalos y espacios de CW son relativos a la duracion del tono mas corto: El espacio entre tonos es igual al el ton mas corto. El espacio entre simbolos es tres veces el tono mas corto. El espacio entre palabras es 7 veces el tono mas corto.

```c++
const int cwToneSpacingMs = toneDurationMs;          // Tiempo entre tonos (en milisengundos)
const int cwSymbolSpacingMs = cwToneSpacingMs * 3;   // Tiempo entre simbolos (en milisengundos)
const int cwWordSpacingMs = cwToneSpacingMs * 7;     // Tiempo entre palabras (en milisengundos)
```

Siempre se expresan en milisgundos:

* `cwToneSpacingMs`: Tiempo entre tonos.
* `cwSymbolSpacingMs`: Tiempo entre caracteres.
* `cwWordSpacingMs`: Tiempo entre palabras.

### Intervalo

El tiempo de espera en segundos, entre trasmision y transmision, puede ser cambiando desde:

```c++
const int SLEEP_SEC = 60;
```

## Ayuda

LU1AAT, Andres
lu1aat.andres @ gmail.com
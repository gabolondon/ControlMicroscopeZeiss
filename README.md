# Zeiss microscope OPMI S3 Control system development

![Microscope Zeiss Opmi S3](https://i.ibb.co/zmnFYpp/IMG-20201019-WA0039.jpg)

## Descripción del proyecto.

en Visión Total S.A.S. se averió un microscopio marca Zeiss, modelo opmi S3, tras una inspección se encuentran las tarjetas internas del equipo quemadas y no respondían, estas tarjetas eran de difícil obtención por lo que se acordó con la clínica realizar un proyecto de realizar el control de los motores mediante un controlador lógico, se seleccionó el STM32F103 por su tamaño reducido, alto desempeño y fiabilidad, además de tarjetas de interfaz de control de motores por PWM y de dirección.
El equipo no realizaba ninguna acción al presionar los botones del pedal y tampoco encendía la luz quirúrgica, sin embargo sí energizaba los circuitos, entonces empecé a armar el plan de acción para el proyecto teniendo en cuenta el comportamiento deseado del equipo y lo que hacía falta para que quedara funcional.
El comportamiento ideal de este microscopio es que durante las cirugías, se pueda realizar movimientos de todo el conjunto óptico por el cual se está observando los procedimientos quirúrgicos, además de tener contorl sobre el zoom, el focus y la intensidad de luz, para esto se hace uso de un pedal _(Imagen 1)_, que incluye diferentes botones para estas funciones, entonces la idea del proyecto es tomar las señales de este pedal para accionar los motores que ejecutan las tareas diseñadas.
![Imagen 1, pedal de microscopio](https://i.ibb.co/P41rrNk/foot-Pedal.png)
Para este fin se tomaron unas señales a replicar, descritas así:

- Subir y bajar Zoom, con posibilidad de cambiar la velocidad del momimiento.
- Subir y bajar focus de objetivo con posibilidad de cambiar la velocidad del momimiento.
- Encender/ apagar luz quirúrgica.
- Al presionar por más de 2.5 segundos el botón de apagado se baja la intensidad de la luz hasta el nivel mínimo de encendido.
- Al presionar por más de 2.5 segundos el botón de encendido se sube la intensidad de la luz hasta el nivel máximo de encendido.
- Movimientos de arriba, abajo, izquierda y derecha según el movimiento del joystick del pedal, que desplaza el conjunto de lentes en ejes X y Y hasta los finales de carrera como tope máximo.
- Al presionar botón de centrado, llevar el conjunto de lentes en ejex X y Y hasta el centro de sus rangos de movimiento respectivamente.
- Potenciometros de selección de velocidad de movimiento en el cuerpo del microscopio.

Se propuso reutilizar los motores del equipo y tomar las señales de los sensores finales de carrera para emular el control de posicionamiento de los lentes, el Zoom y el Focus que se realizaba originalmente desde el pedal, así como el on/off de la luz de cirugía.

## Elementos Utilizados

Para este proyecto usé una serie de dispositivos acoplados a un controlador, este es el listado:

- 2 Controladores STM32F103.
- 2 Módulos L298N de accionamiento de motores DC con control de velocidad y sentido de giro.
- 8 finales de carrera.
- 4 metros de bus de datos serial(para transportar señales).
- 2 cajas de soporte diseñadas en 3D printers.
- Conectores dupont para cables
- 1 módulo Driver Led de 36V de DC-DC a 12V.
- 1 LED 24W a 6v
- 2 potenciometros de 100K ohm.

Además se requiere de un PC con STM Flash loader software para cargar el código en los STM, además de herramientas para acceder al circuino interno del microscopio y modificarlo.

## Ejecución y pruebas

Al programar los STM32F103 se instalaron junto a los finales de carrera nuevos, reemplazando los antiguos para evitar fallas por fatiga mecánica, adicionalmente se cablean nuevamente los motores DC reemplazando cablería con años de uso, así como los Potenciometros y se isntalan nuevos cables desde la regleta de conexión del pedal hasta la tarjeta de control.
Al instalar los elementos, se procede con la conexión a la fuente de poder, que se reutilizó la fuente original Zeiss que alimentaba las tarjetas de control dañadas a 12 VDC, con esto se empezaron a hacer medidas de señales de los finales de carrera y verificar que si accionaran en la posición del brazo deseada.
Al tener las señales previas testeadas y los motores testeados, procedí a energizar el nuevo circuito para hacer testin de las señales desde el pedal sin accionamiento de motores, por lo que se desconectaron los módulos controladores de motor DC.
Con las señales ya mapeadas y correctamente conectadas a las entradas del STM32 que le corresponden, procedí a conectar las salidas del STM32 a los drivers de motor ya conectado y revisar que los movimientos de los motores se ejecuten de forma correcta.
Con muchas pruebas en caliente y con inversiones de giro de motores puesto que habían conexiones mal ejecutadas, conseguí el comportamiento esperado del sistema de control.

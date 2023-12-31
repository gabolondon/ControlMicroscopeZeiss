# Zeiss microscope OPMI S3 Control system development

## ![Microscope Zeiss Opmi S3](https://i.ibb.co/zmnFYpp/IMG-20201019-WA0039.jpg)

## Project description.

In Vision Total S.A.S. A Zeiss microscope, model opmi S3, broke down. After an inspection, the internal cards of the equipment were found burnt and did not respond. These cards were difficult to obtain, so they hooked up with the clinic carrying out a project to control the motors using a logic controller, selected the STM32F103 for its small size, high performance and reliability, as well as PWM motor control and direction interface cards.
The team did not take any action by pressing the pedal buttons and did not turn on the surgical light, however it did energize the circuits, so they began to put together the action plan for the project taking into account the desired behavior of the team and what was needed to make it functional.
The ideal behavior of this microscope is that during surgeries, you can make movements of the entire optical assembly through which surgical procedures are being observed, in addition to having control over the zoom, focus and light intensity, for this makes use of a pedal _(Image 1)_, which includes different buttons for these functions, so the idea of ​​the project is to take the signals from this pedal to activate the motors that execute the designed tasks.
![Image 1, microscope foot pedal](https://i.ibb.co/P41rrNk/foot-Pedal.png)
For this purpose, some signals were taken to be replicated, described as follows:

- Zoom up and down, with the possibility of changing the speed of the movement.
- Raise and lower target focus with the possibility of changing the speed of movement.
- Turn on/off surgical light.
- Pressing the off button for more than 2.5 seconds lowers the light intensity to the minimum on level.
- Pressing the power button for more than 2.5 seconds increases the intensity of the light to the maximum power level.
- Movements up, down, left and right according to the movement of the joystick of the pedal, which moves the set of lenses in X and Y axes up to the maximum limit stops.
- By pressing the centering button, bring the set of lenses in the X and Y axes to the center of their ranges of movement respectively.
- Movement speed selection potentiometers on the body of the microscope.

It was proposed to reuse the equipment's motors and take the signals from the limit switch sensors to emulate the control of the positioning of the lenses, the Zoom and the Focus that was originally carried out from the pedal, as well as the on/off of the light of surgery.

---

## Elements Used

For this project I used a series of devices coupled to a controller, this is the list:

- 2 STM32F103 Controllers.
- 2 L298N DC motor drive modules with speed control and direction of rotation.
- 8 career endings.
- 4 meters of serial data bus (to carry signals).
- 2 support boxes designed in 3D printers.
- Dupont connectors for cables
- 1 Cree Xlamp CXA MTG 24W LED with 12v driver.
- 2 potentiometers of 100K ohm.

In addition, a PC with STM Flash loader software is required to load the code in the STM, as well as tools to access the internal circuit of the microscope and modify it.

---

## Running and testing

When programming the STM32F103, they were installed together with the new limit switches, replacing the old ones to avoid failures due to mechanical fatigue. In addition, the DC motors were rewired, replacing wiring with years of use, as well as the Potentiometers, and new cables were installed from the power strip. pedal connection to the control card.
When installing the elements, proceed with the connection to the power source, which reused the original Zeiss source that fed the damaged control cards at 12 VDC, with this they began to measure the limit switch signals and verify than if they operated in the desired arm position.
Having tested the previous signals and tested the motors, I proceeded to energize the new circuit to test the signals from the pedal without driving motors, so the DC motor controller modules were disconnected.
With the signals already mapped and correctly connected to the corresponding STM32 inputs, I proceeded to connect the STM32 outputs to the already connected motor drivers and check that the motor movements are executed correctly.
With many hot tests and motor reversals since there were poorly executed connections, I got the expected behavior of the control system.

---

## Spanish

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

---

## Elementos Utilizados

Para este proyecto usé una serie de dispositivos acoplados a un controlador, este es el listado:

- 2 Controladores STM32F103.
- 2 Módulos L298N de accionamiento de motores DC con control de velocidad y sentido de giro.
- 8 finales de carrera.
- 4 metros de bus de datos serial(para transportar señales).
- 2 cajas de soporte diseñadas en 3D printers.
- Conectores dupont para cables
- 1 LED Cree Xlamp CXA MTG 24W con driver de 12v.
- 2 potenciometros de 100K ohm.

Además se requiere de un PC con STM Flash loader software para cargar el código en los STM, además de herramientas para acceder al circuino interno del microscopio y modificarlo.

---

## Ejecución y pruebas

Al programar los STM32F103 se instalaron junto a los finales de carrera nuevos, reemplazando los antiguos para evitar fallas por fatiga mecánica, adicionalmente se cablean nuevamente los motores DC reemplazando cablería con años de uso, así como los Potenciometros y se isntalan nuevos cables desde la regleta de conexión del pedal hasta la tarjeta de control.
Al instalar los elementos, se procede con la conexión a la fuente de poder, que se reutilizó la fuente original Zeiss que alimentaba las tarjetas de control dañadas a 12 VDC, con esto se empezaron a hacer medidas de señales de los finales de carrera y verificar que si accionaran en la posición del brazo deseada.
Al tener las señales previas testeadas y los motores testeados, procedí a energizar el nuevo circuito para hacer testin de las señales desde el pedal sin accionamiento de motores, por lo que se desconectaron los módulos controladores de motor DC.
Con las señales ya mapeadas y correctamente conectadas a las entradas del STM32 que le corresponden, procedí a conectar las salidas del STM32 a los drivers de motor ya conectado y revisar que los movimientos de los motores se ejecuten de forma correcta.
Con muchas pruebas en caliente y con inversiones de giro de motores puesto que habían conexiones mal ejecutadas, conseguí el comportamiento esperado del sistema de control.
Al comenzar a realizar pruebas con la luz LED de reemplazo a la original, se monta el LED con un disipador y un ventilador de 12v, además que se realiza en máquina 3D la carcasa para montaje en el microscopio, que contenga todos los elementos necesarios.
Al mostrar al cliente una prueba piloto y su posible costo, este prefirió dejar el projecto sólo hasta la parte del control de los motores alegando que la luz que tenía original el microscopio le servía para los procedimientos quirúrgicos.

---

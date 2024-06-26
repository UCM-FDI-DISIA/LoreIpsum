<h1 align="center"><b>HÖLLENHAUS</b></h1>
<h3 align="center"><b>LoreIpsum</b></h1>

## Índice
- [Proyecto](#Proyecto)
  - [Descripción](#descripción)
  - [Capturas](#Capturas) 
  - [Vídeo](#Video) 
  - [Página](#Pagina)
- [Presentaciones](#presentaciones)
- [Arquitectura](#Arquitectura)
- [GDD](#GDD)
  1. [Ficha técnica](#id1)
  2. [Descripción](#id2)
  3. [Ciclo de juego](#id3)
     1. [Partida genérica](#id4) 
  4. [Juego de cartas](#id5)
     1. [Habilidades](#id6)
  5. [UI](#id7)
     1. [Menús](#id8)
        1. [Inicio](#id9)
        2. [Opciones](#id10)
        3. [Pausa](#id11)
     3. [Ciudad](#id12)
     4. [Tienda](#id13)
     5. [Oficina](#id14)
     6. [Batalla](#id15)
     7. [Resolución](#id16)
  6. [Estética](#id17)
     1. [Visual](#id18)
        1. [Paleta](#id19)
        2. [Referencias](#id20)
     4. [Música](#id21)
  7. [Contenido](#id22)
     1. [Narrativa](#id23)
     2. [Cartas](#id24)
  8. [Referencias](#id25)
     1. [Mecánicas](#id26)
     2. [Artísticas](#id27)
- [QA](#QA)
  

## Proyecto
### Descripción
**HÖLLENHAUS** es un videojuego de cartas creado por *LoreIpsum* en el que tú —un fantasma en el limbo que busca un nuevo hogar en el infierno— luchas contra tu adversario por sumar la mayor cantidad de puntos en las casillas de un tablero. Te enfrentarás a diversos personajes a lo largo de la historia, ganando las almas necesarias para costearte un hogar en el infierno.
### Vídeo
[![](https://markdown-videos-api.jorgenkh.no/youtube/QCxwNdkSUNI)](https://youtu.be/1f1Kqsp9erM)
### Capturas
![Menú de inicio](/docs/GDD/images/captura00.png)
![Overworld](/docs/GDD/images/captura01.png)
![Tienda](/docs/GDD/images/captura02.png)
![Batalla](/docs/GDD/images/captura03.png)
![Oficina](/docs/GDD/images/captura04.png)
![Deckbuilding](/docs/GDD/images/captura05.png)
![Tienda](/docs/GDD/images/captura06.png)
### Página
Enlace a la [página web](https://ucm-fdi-disia.github.io/LoreIpsum/)
## Presentaciones
- **Hito 0**: [transparencias](https://docs.google.com/presentation/d/14X1H2WW96c6soYmThStQAicIRp_3ZJsN-hTsZ-rOBvw/edit?usp=drive_link) y [protocolo](https://docs.google.com/document/d/1nzUwn2zeJeuQBZWjjvqF6Tlv1n-C4KZrPEBRIF91SRE/edit?usp=sharing)
- **Hito 1**: [transparencias](https://docs.google.com/presentation/d/1n5Ko22xPMVLtqO-oFY6cvgndLT4iQ3dGm4_wTjoHPe4/edit?usp=sharing), [protocolo](https://docs.google.com/document/d/1zDPQPwhtZNLIt8iL_xZ378V7yQT1QKjliIeKrCuGFmk/edit?usp=sharing) y [guión](https://docs.google.com/document/d/1oxUlDSbENCnBTgExxYuLocpCrcsxeR2cbJSiAwpyqUE/edit?usp=sharing)
- **Hito 2**: [transparencias](https://docs.google.com/presentation/d/1RRbo9XOWkO9gCZej6tLlH4qD4hG9qMLc2hf5ba_PbnE/edit?usp=sharing), [gráficas](https://docs.google.com/spreadsheets/d/1teqh66NJ_fqeRnTNbOUWAlwWpkwhWEhiVeuGfHJ3qas/edit?usp=sharing) y [guión](https://docs.google.com/document/d/1GnP6rd4fdsNH70kAZ0Tve3oDKUXk1_WaQ3tPDaFFwzs/edit?usp=sharing)
- **Hito final**: [vídeo](https://www.youtube.com/watch?v=QCxwNdkSUNI).
## Arquitectura 
Enlace al [UML general](https://www.figma.com/file/QBQ7K1ngk58sNtPMxOUhRx/Hollenhaus-UML?type=whiteboard&node-id=0-1&t=s07Dx0HenMNke7FV-0 ).
## GDD
<p align="center">
  Paula Alemany, Nieves Alonso, Samuel García, Andrés García, Pablo Iglesias, Luis Parres, Inés Primo, Ariadna Ruiz, Paula Sierra, Cynthia Tristán, Jaime Vicente
</p>

1. ### Ficha técnica <a name="id1"></a>

| **Título:** HÖLLENHAUS | **Rating:** +12 |
|:---:|:---:|
| **Target:** Público joven con interés en juegos de cartas y/o bizarros | **Modos de juego:** 1 jugador (Modo historia), 2 jugadores (Modo VS.) |

2. ### Descripción <a name="id2"></a>
**HÖLLENHAUS** es un juego de cartas en el que el jugador —un fantasma en el limbo que busca un nuevo hogar en el infierno— lucha contra su adversario por sumar la mayor cantidad de puntos en las casillas de un tablero. El jugador se enfrentará a diversos personajes a lo largo de la historia, ganando las almas necesarias para costearse un hogar en el infierno.

3. ### Ciclo de juego <a name="id3"></a>
![Core Loop](/docs/GDD/images/image1.png)

El juego está dividido en distintos casos o niveles que se tendrán que ir resolviendo. Cada nivel culmina en un combate de cartas contra una médium a través de la cual se determinará la victoria o la derrota del caso particular. 

**Objetivo a largo plazo:** Ahorrar suficientes almas para comprar un piso en el infierno. 

**Objetivo a corto plazo:** Triunfar en la resolución del caso para el que ha sido contratado.

#### **ESTADOS EN UN CICLO DE JUEGO**
| ESTADO DE JUEGO | (0) INFORMACIÓN DEL CASO | (1) CIUDAD | (2) MÉDIUM | (3) RESOLUCIÓN | (4) FINAL DE JUEGO |
|:---:|:---:|:---:|:---:|:---:|:---:|
| | ANTICIPACIÓN | ANTICIPACIÓN | DESAFÍO | DESCARGA | 

(0) INFORMACIÓN DEL CASO

Es el comienzo del nivel. Se define el número de almas que vas a ganar si lo resuelves con éxito. Te dan la información sobre el caso y se fija objetivo: Derrotar a la médium.

(1) CIUDAD

  El jugador puede realizar las siguientes acciones:
  - [**Desplazarse por la ciudad:**](#id12) Estética implementada para acceder al resto de acciones disponibles.
  - [**Comprar cartas nuevas:**](#id13) Con el dinero  ganado de los combates menores, el jugador podrá ir a una tienda y comprar nuevas cartas para añadirlas a  su mazo.
  - [**Gestionar su mazo:**](#id14) Añadir y quitar cartas del mazo que el jugador usará en su próximo enfrentamiento.
  - [**Desafiar a un personaje:**](#id15) Enfrentamiento menor, de corta duración, contra un personaje del juego. Te puede otorgar pistas, cartas o dinero.
  - [**Desafiar a la médium:**](#id15) Pasas al estado de juego (2).

(2) MEDIUM

Enfrentamiento complejo, de larga duración (se trata del “boss” del nivel) contra la médium.

(3) RESOLUCIÓN
  -  Si el jugador pierde el enfrentamiento, vuelve al estado (1). 
  -  Ganar el enfrentamiento le proporciona cartas especiales, dinero, y almas para el objetivo final. Además, puede pasar al estado (0) o al estado (4).
     - Si no tiene suficientes almas todavía, vuelve al estado (0) con un nuevo caso.
     - Si ha conseguido el objetivo final de almas, pasa al estado (4).

(4) FINAL DE JUEGO

El jugador consigue su nuevo pisito en el infierno, o no.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;i. **Partida genérica** <a name="id4"></a>
> 1. El jugador recibe un caso de un cliente por el teléfono (lore).
> 2. El jugador se enfrenta a un personaje menor en la ciudad y obtiene una nueva carta.
> 3. El jugador se enfrenta a otro personaje menor en la ciudad y obtiene dinero.
> 4. El jugador usa el dinero que ha ganado para comprar una nueva carta en la tienda.
> 5. El jugador va a la oficina y edita su mazo si lo desea.
> 6. El jugador se enfrenta a la médium y pierde.
> 7. El jugador hace más combates menores, obtiene más dinero y nuevas cartas.
> 8. El jugador vuelve a editar su mazo para intentar ganar a la médium.
> 9. El jugador se enfrenta a la médium y gana, obtiene almas y acaba el caso. No tiene suficientes almas todavía para el piso en el infierno, vuelve a empezar otro caso para conseguir más almas.

4. ### Juego de cartas <a name="id5"></a>
![Elementos del combate básicos](/docs/GDD/images/image2.png)

El juego de cartas se desarrolla por turnos en los que los jugadores van colocando cartas en un tablero cuadriculado de dimensión variable. Cada carta que se coloque en el tablero le sumará al jugador la cantidad de puntos especificada en la carta, así como aplicar los efectos (si es que los tiene) de la carta. Estos efectos pueden variar tanto la puntuación, la posición o el efecto de otras cartas del tablero. Los efectos varían según el tipo de carta.

El objetivo del juego es **sumar más puntos que el rival** cuando acaba la partida mediante la colocación espacial de las cartas, las cuales se afectarán entre sí sumando o restando puntos.

Cada jugador tiene **4 puntos de acción** que puede utilizar en su turno para hacer distintas acciones. Las acciones principales que puede hacer el jugador son: **robar carta** del mazo, con un coste constante de 2 puntos, y **colocar una carta** en el tablero, con un coste variable según lo que indique la carta.

Todas las cartas están compuestas por tres características: **valor**, **coste** y **habilidad**. Las dos primeras son un valor numérico entero que indica la cantidad de puntos a sumar a la puntuación del jugador que la haya colocado y la cantidad de puntos a gastar de los puntos de acción, respectivamente. La habilidad de cada carta indica una acción extra que efectúa la carta al ser colocada en el tablero.

Las **habilidades** de las cartas podrán modificar los valores numéricos en distintas zonas del tablero según la especificación de la carta. Una carta podrá **aumentar** o **disminuir** el valor de puntuación que proporciona y el que proporcionan otras cartas en un área de efecto. Este área de efecto también estará especificada en la propia carta y podrá influir a las cartas **adyacentes en cruz**, a las **filas**, a las **columnas**, a las **esquinas** o al **centro** del tablero. Las cartas pueden tener coste 0, valor 0 y/o habilidad que no afecte a nada.

Finalmente, también existe la mecánica de **terreno**: una de las casillas del tablero puede tener algún tipo de modificador que afecte a las cartas que se coloquen en esa casilla, como sumar, restar, multiplicar el  valor de la carta sobre ella.

![Carta tipo y sus diferentes propiedades](/docs/GDD/images/image3.png)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;i. **Habilidades** <a name="id6"></a>

| Pictograma | Descripción | Pictograma | Descripción |
|:---:|:---:|:---:|:---:|
| ![](/docs/GDD/images/picto1.png) | Activa su efecto si se encuentra en las esquinas | ![](/docs/GDD/images/picto3.png) | Su efecto se aplica a la carta adyacente en la dirección a la que apunta |
| ![](/docs/GDD/images/picto2.png) | Activa su efecto si se encuentra en el centro | ![](/docs/GDD/images/picto4.png) | Su efecto se aplica todas las cartas en la dirección a la que apunta |
| ![](/docs/GDD/images/picto5.png) | No le afectan modificadores | ![](/docs/GDD/images/picto6.png) | Anula la habilidad de la carta adyacente en la dirección en la que apunta (ha de ir acompañada de un pictograma de flecha) |

5. ### UI <a name="id7"></a>
   1. #### Menús <a name="id8"></a>
      1. ##### Inicio <a name="id9"></a>
      Botones para modo historia, modo versus, opciones y salir.
      
      2. ##### Opciones <a name="id10"></a>
      Sliders para cambiar el volumen de los sonidos y música.
      
      3. ##### Pausa <a name="id11"></a>
      Botones para continuar la partida, guardarla, abrir las opciones y salir del juego. Se podrá guardar siempre que no se esté en mitad de un combate.
      ![](/docs/GDD/images/image7.png)

   2. #### Ciudad <a name="id12"></a>
   El jugador tiene capacidad de movimiento horizontal en la ciudad mediante point and click. Así también hay posibilidad de interactuar con el entorno. Se podrá acceder a la tienda y a la oficina clicando sus respectivas puertas.
   Por otra parte, se encontrarán NPCs, que hablarán al jugador una vez le haya clicado, y dándole la posibilidad de entrar o no en una batalla menor con este.
El movimiento por la ciudad se realizará dando clics en la calle. El personaje del jugador quedará centrado. Se podrá explorar la ciudad gracias al scroll lateral del entorno.

    ![](/docs/GDD/images/image8.png)

   3. #### Tienda <a name="id13"></a>
   Como se muestra en la imagen, el jugador podrá comprar las cartas que estén disponibles en el estante de venta. Al seleccionar una carta adquirible se te marcan las monedas que te va a costar.
   
  Por otro lado, se tiene el dinero disponible a gastar y un botón para regresar a la ciudad.

    ![](/docs/GDD/images/image9.png)

   4. #### Oficina <a name="id14"></a>
   En la sección de oficina existen dos acciones principales que el jugador puede realizar: hablar con la médium mediante un teléfono y/o administrar el mazo de cartas.

  Para acceder a la conversación con la médium, se clica en el teléfono. Informa del caso correspondiente a completar, o da acceso a repetir un caso fallido. También, en cierto punto de la partida, da opción para combatir contra ella.

  Por otra parte, para administrar el mazo, el jugador puede pulsar el cajón. Esto le mostrará el tablero con las cartas que tiene en el mazo de juego, al estilo de corcho de detective. Debajo del tablero, aparecen las cartas que tiene disponibles o que ha comprado previamente en la tienda. Estas cartas se pueden intercambiar con el mazo de juego, y así probar distintas cartas o estrategias a la hora de combatir.

  ![](/docs/GDD/images/image10.png)

   5. #### Batalla <a name="id15"></a>
   Al inicio de la batalla habrá una transición de zoom desde arriba a la mesa para que solo aparezca el tablero y mazos. 
Abajo se verá la mano y cuando se pulse sobre ella habrá una transición hacia abajo para verlas mejor.
A la derecha se verá parte del libro donde se explica lo que hace cada carta. Al hacer clic sobre una carta en su icono de habilidad, se lleva mediante una transición al libro.
Para la pausa se deshace el zoom del principio, de forma que se ven a los jugadores enteros. Al volver al juego, se deshace la transición. 
Los combates se diferencian en dos tipos: las batallas menores en la ciudad, que ocurren en la mente, y la de la pitonisa en la oficina. La decoración cambia según el tipo de enfrentamiento. Los puntos de acción están representados por velas; si se ha utilizado un número de puntos de acción, se apagan ese número de velas.
![Disposición de los elementos del menú de gestión del mazo](/docs/GDD/images/image11.png)

   6. #### Resolución <a name="id16"></a>
   Se encuentra información pertinente a la historia y la resolución de la batalla o caso correspondiente, en forma de texto en prosa o diálogo. Se encuentra un botón para continuar.
![Diagrama de menú de resolución de batalla](/docs/GDD/images/image12.png)

7. ### Estética <a name="id17"></a>
   1. **Visual** <a name="id18"></a>\
Estética referenciada en los primeros juegos en 3D, con gráficos pre-renderizados (se hace un modelo en 3D y luego se renderiza como imágenes o vídeos). Colores oscuros, desaturados y lúgubres, y una luz muy dura.
      1. **Paleta** <a name="id19"></a>\
         La paleta de colores se basa en una gama de colores sepia y unos cuantos colores para destacar determinados objetos o personajes (amarillo para objetos importantes, morado para la médium etc.).
         ![Paleta de colores](/docs/GDD/images/image13.png)
      2. **Referencias** <a name="id20"></a>
      
| Referencia | Imagen | Referencia | Imagen |
|:---:|:---:|:---:|:---:|
| Call of Cthulhu: Dark Corners of the Earth | ![](/docs/GDD/images/image14.png) | Inscryption | ![](/docs/GDD/images/image21.png) |
| Rule of Rose | ![](/docs/GDD/images/image18.png) | World Of Horror | ![](/docs/GDD/images/image23.png) |
| Paratopic | ![](/docs/GDD/images/image15.png) | De tres al cuarto | ![](/docs/GDD/images/image20.png) |
| Santerías  | ![](/docs/GDD/images/image17.png) | Lost in Vivo | ![](/docs/GDD/images/image22.png) |
| Elation for the Wonderbox 6000 | ![](/docs/GDD/images/image19.png) | Iron Lung | ![](/docs/GDD/images/image24.png) |

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ii. **Musical** <a name="id21"></a>\
   La música estará dividida en varios temas capaces de mantenerse en bucle representando las distintas fases del juego: menú, deckbuilder, ciudad/oficina/tienda y batalla. La estética general de la música será jazz tétrico y oscuro pero calmado. Un buen ejemplo sería música de ascensor pero menos feliz.

7. ### Contenido <a name="id22"></a>
   1. #### Narrativa <a name="id23"></a>
      La historia se basa en que el personaje principal —el jugador— ha muerto y para trascender al infierno debe pagar la entrada a un piso en primera línea de playa en el más allá. Para ello se apoyas en sus habilidades paranormales y monta una agencia de sustos; los clientes le contratan y usan su alma como moneda de pago, eligen una víctima y el personaje principal investigará por la ciudad qué les asusta.
![](/docs/GDD/images/image25.png)
  Una vez se está seguro de qué le da miedo, y de cómo asustar a la susodicha persona, se llama a una médium y a través de ella se materializa el ataque en forma de un duelo de cartas. Si el ataque termina bien se cobra en almas. Una vez se han resuelto todos los casos, se habrá triunfado o fracasado en el pacto inmobiliario con el demonio en función de las almas que se posean al final del juego.\
![](/docs/GDD/images/image26.png)

   2. #### Cartas <a name="id24"></a>
      Los distintos tipos de cartas varían en coste, valor y habilidad según suman/restan en horizontal, vertical o adyacentemente.

![Paleta de colores](/docs/GDD/images/image27.png)

8. ### Referencias <a name="id25"></a>
   1. #### Mecánicas <a name="id26"></a>
- [Gwent](https://www.playgwent.com/en) - CD Projekt RED (2017)
- [Marvel Snap](https://www.marvelsnap.com/) - Nuverse, Second Dinner Studios (2022)
- [Dioses! El Juego de Cartas](https://www.destripandolahistoria.com/products/dioses) - Pascu y Rodri (2023)
- [Adventure Time Card Wars](https://boardgaming.com/games/trading-card-games/adventure-time-card-wars) - Cryptozoic Entertainment (2014)
- [Inscryption](https://store.steampowered.com/app/1092790/Inscryption/) - Daniel Mullins Games (2021)
- [BeatCop](https://store.steampowered.com/app/461950/Beat_Cop/) - Pixel Crow (2017)
- [De Tres al Cuarto](https://deconstructeam.itch.io/de-tres-al-cuarto) - Deconstructeam (2022)
- [WORLD OF HORROR](https://panstasz.itch.io/world-of-horror) - Panstasz (2023)

   2. #### Artísticas <a name="id27"></a>
- [Call of Cthulhu: Dark Corners of the Earth](https://store.steampowered.com/app/22340/Call_of_Cthulhu_Dark_Corners_of_the_Earth/) - Headfirst Productions (2006)
- [Paratopic](https://store.steampowered.com/app/897030/Paratopic/) - Arbitrary Metric (2018)
- [Rule of Rose](https://en.wikipedia.org/wiki/Rule_of_Rose) - Punchline, Shirogumi (2006)
- [Elation For The Wonder Box 6000](https://store.steampowered.com/app/2154780/Elation_For_The_Wonder_Box_6000/) - Digital Tchotchkes (TBA)
- [Santerías](https://es.wikipedia.org/wiki/Santer%C3%ADa)
- [Iron Lung](https://store.steampowered.com/app/1846170/Iron_Lung/?l=spanish) - [David Szymanski](https://store.steampowered.com/developer/davidszymanski?snr=1_5_9__2000) (2022)
- [Lost in Vivo](https://store.steampowered.com/app/963710/Lost_in_Vivo/) - KIRA (2018)

## QA
1. ### Introducción <a name="id1"></a>
El día 23 de abril de 2024, realizamos un sesión de play testing, en un instituto de tres cantos IES Pintor Antonio Lopez, con el objetivo de recoger datos sobre cómo interactúan los jugadores con nuestro juego, la curva de aprendizaje, las dificultades y las reacciones a los diferentes eventos, y con ello realizar los cambios necesarios para mejorar la experiencia de juego.

2. ### Detalles del estudio <a name="id1"></a>
Dispusimos de 2 grupos de alumnos de 20-25 personas cada uno, con la duración del testeo siendo 50 minutos, edades entre los 15-18 años, que eran nuestro público objetivo. 
Para observar a los jugadores y atender sus dudas estábamos allí 9 miembros del equipo, así que pudo tener un buen seguimiento de la progresión  de los jugadores en su interacción con el juego.

En la primera sesión, les dimos a jugar el juego, tras habérselo explicado unos minutos antes en la clase ya que por un fallo de última hora, el tutorial que teníamos preparado nos falló.

En la segunda sesión, tuvimos que realizar otra vez una explicación previa tanto del lore como del gameplay del juego, y después les dimos acceso al juego. En esta sesión a diferencia de la primera, los jugadores pudieron probar también el multijugador local del juego y jugar unos contra otros.

Nuestra observación se centró principalmente en la curva de aprendizaje del juego, ver cuán sencillas o complejas eran las reglas, y que tán complicado les resultaba aprender las reglas y  ganar a la IA, así como observar si los jugadores investigaban  más por la ciudad y utilizaban la tienda y la oficina para comprar cartas y organizar su mazo respectivamente.

La IA a la que se enfrentaban los jugadores tenía siempre las mismas cartas, y el jugador era siempre el que iniciaba la partida. El jugador tenía la posibilidad de añadir y quitar cartas de su mazo en la oficina, pero no estaba disponible la opción de comprar cartas.

3. ### Resultados de la encuesta <a name="id1"></a>
_Datos sobre los encuestados:_

![](/docs/QA/ch1.png)
![](/docs/QA/ch2.png)
![](/docs/QA/ch3.png)
![](/docs/QA/ch4.png)
![](/docs/QA/ch5.png)

_Datos sobre el juego:_

![](/docs/QA/ch6.png)
![](/docs/QA/ch7.png)
![](/docs/QA/ch8.png)
![](/docs/QA/ch9.png)
![](/docs/QA/ch10.png)

4. ### Resultados observados por el equipo <a name="id1"></a>
De los datos obtenidos de los gráficos, comentarios y respuestas libres de las encuestas y nuestra propia observación durante la misma podemos concluir diferentes cosas:
- Los jugadores solían necesitar varias partidas para entender las reglas.
- La curva de aprendizaje era muy buena, en tan solo unos 10 -15 minutos la mayoría de jugadores entendían bien el juego.
- Una vez los jugadores ganaban su primera partida, seguían ganando las siguientes.
- Casi ningún jugador editó su mazo ni visitó la tienda, sin embargo aquellos que entendieron el juego con mayor rapidez sí que lo hicieron.
- De los pocos jugadores que editaron su mazo, veían muy confuso el menú de la oficina.
- Los símbolos de los efectos de las cartas eran un poco confusos al principio y los jugadores necesitaban preguntar bastante sobre su funcionamiento.
- Detección de bugs no antes vistos por nosotros.

5. ### Cambios realizados <a name="id1"></a>
Para solucionar todas estas cosas hicimos bastantes implementaciones, algunas pensadas antes del QA y otras nuevas:
- Dificultad con las reglas:
  - Implementación de un tutorial obligatorio cuando empiezas una nueva partida, el tutorial incluye:
    - Cómo funcionan los casos
    - Cómo funciona el deck-building
    - Cómo funciona la partida de cartas
    - Cómo funciona la tienda
  - Esto también ayudará a que los jugadores sepan que estas funcionalidades existen.
- Para que no ganasen siempre y se pierda dificultad se ha añadido la progresión de dificultad con los casos.
- Añadimos feedback al deckBuilding y el tutorial para evitar la confusión de la oficina.
- Añadimos una leyenda que explique la funcionalidad de cada símbolo conocido de las cartas.
- Tratamos de solucionar todos los bugs encontrados.
- Añadimos más feedback a la partida de cartas para facilitar su comprensión.

6. ### Conclusiones <a name="id1"></a>
Como conclusión podemos decir que el juego estaba funcionando como queríamos, obteniendo un feedback de parte del alumnado bastante positivo. Los alumnos se divirtieron bastante, se “picaron” con la IA y también jugando entre ellos, alguno incluso nos preguntó cómo podrían descargarlo para jugarlo cuando estuviese completo. Sin embargo le faltaba, en ese momento, trabajo de pulido para que se entendiese y contenido para que cada vez que juegues fuese diferente.

-----------
<!--
### Gráficos
...
### Resultados
...
-->






<!--
__________

Documentación
El archive README.md de la raíz del proyecto contendrá, al menos, los siguientes apartados como secciones claras:
Proyecto: nombre del equipo, del proyecto, enlace a la página pública, al release del juego y al vídeo del juego.
Presentaciones: enlaces a los material de las presentaciones.
Arquitectura: diagrama de clases y explicación general de la misma.
GDD: con:
  PEGI
  Género
  Target/audiencia esperada
  Descripción general
  Mecánicas (detalladas una a una)
  Dinámicas (tanto las generales del juego, como específicas de partes)
  Estética (criterio artístico, paleta de colores…)
  Mapas, bocetos, dibujos
  Valores de pulido, tablas…
QA: proceso explicado, gráficas y resultados de QA.
-->

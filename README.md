<h1 align="center"><b>HÖLLENHAUS</b></h1>
<h3 align="center"><b>Lore Ipsum</b></h1>

## Índice
- [Proyecto](#Proyecto)
  - [Descripción](#descripción)
  <!-- - [Capturas](#Capturas) -->
  <!-- - [Vídeo](#Video) -->
  <!-- - [Página](#Pagina) -->
- [Presentaciones](#presentaciones)
<!-- [Arquitectura](#Arquitectura) -->
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
<!-- COMENTADO PORQUE TODAVÍA NO HAY NADA
### Capturas
...
### Vídeo
...
### Página
...
-->
## Presentaciones
- [Hito 0](https://docs.google.com/presentation/d/14X1H2WW96c6soYmThStQAicIRp_3ZJsN-hTsZ-rOBvw/edit?usp=drive_link)
- Hito 1
- Hito 2
- Hito final
<!-- ## Arquitectura -->
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
> 1. El jugador recibe un caso de un cliente (lore).
> 2. El jugador se enfrenta a un personaje menor y obtiene una nueva carta.
> 3. El jugador se enfrenta a otro personaje menor y obtiene dinero.
> 4. El jugador usa el dinero que ha ganado para comprar una nueva carta.
> 5. El jugador va a la oficina y edita su mazo.
> 6. El jugador se enfrenta a la médium y pierde.
> 7. El jugador hace más combates menores y obtiene nuevas cartas y más dinero.
> 8. El jugador vuelve a editar su mazo para intentar ganar a la médium.
> 9. El jugador se enfrenta a la médium y gana, obtiene almas y acaba el caso, como no tiene suficientes almas todavía, vuelve a empezar otro caso.

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
   El jugador puede moverse en horizontal en la ciudad para ir a distintas ubicaciones con point and click disponibles como la tienda, la oficina etc, así como interactuar con ciertos NPCs para entrar en batallas menores.
    ![](/docs/GDD/images/image8.png)

   3. #### Tienda <a name="id13"></a>
   Se te muestran las cartas que puedes comprar y tu cartera. Al seleccionar una carta adquirible se te marcan las monedas que te va a costar. Botón para volver a la zona principal.
    ![](/docs/GDD/images/image9.png)

   4. #### Oficina <a name="id14"></a>
   Puedes pulsar un cajón/corcho o el teléfono. El cajón te lleva al tablero donde podrás fijar las cartas que tendrá tu mazo mientras que en la parte de abajo se te muestran todas las cartas posibles. En la parte inferior están todas las cartas y en el corcho con estilo de corcho de detective irás poniendo las cartas que quieres en tu mazo. El teléfono te lleva al diálogo con la pitonisa y al combate con ella.
  ![](/docs/GDD/images/image10.png)

   5. #### Batalla <a name="id15"></a>
   Al inicio de la batalla se hace zoom desde arriba a la mesa para que solo aparezca el tablero y mazos. 
Abajo se verá la mano y cuando se pulse sobre ella habrá una transición hacia abajo para verlas mejor.
A la derecha se verá parte del libro donde se explica lo que hace cada carta. Cuando sobre una carta haces click en el icono de la habilidad se lleva mediante transición al libro.
Para la pausa se deshace el zoom del principio y que se vea a los jugadores enteros, y para quitarla volver a hacerlo. 
Las batallas normales son batallas en la mente y la de la pitonisa en la oficina. La decoración entre ambas cambia. Para representar los puntos de acción se usarán velas que se irán apagando cuando uses cartas según su coste.
![Disposición de los elementos del menú de gestión del mazo](/docs/GDD/images/image11.png)

   6. #### Resolución <a name="id16"></a>
   Información pertinente a la historia y resolución de esa batalla/caso en forma de texto en prosa, diálogo…, y un botón para seguir.
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
   La música estará dividida en varios temas capaces de mantenerse en bucle representando las distintas fases del juego: menú, deckbuilder, ciudad/oficina/tienda y batalla. La estética general de la música será jazz tétrico y oscuro pero calmado, a lo música de ascensor pero menos feliz.

7. ### Contenido <a name="id22"></a>
   1. #### Narrativa <a name="id23"></a>
      La historia se basa en que tú, como jugador, has muerto y para trascender al infierno debes pagar la entrada a un piso en primera línea de playa en el más allá. Para ello te apoyas en tus habilidades paranormales y montas una agencia de sustos; los clientes te contratan y usan su alma como moneda de pago, eligen una víctima y tú investigas por la ciudad qué les asusta.
![](/docs/GDD/images/image25.png)
Una vez estás seguro de que sabes cómo asustar a la susodicha persona llamas a una médium y a través de ella materializas tu ataque en forma de un duelo de cartas. Si el ataque te sale bien cobras en almas. Una vez se han resuelto todos los casos, triunfas o fracasas en tu pacto inmobiliario con el demonio en función de las almas que poseas al final del juego.\
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
- [Cuaderno de bitácora](https://docs.google.com/document/d/1chs1zlM2r6k1SiD8YCIOIoj-Sr1R3oOvAWJ_08ELEhQ/edit?usp=sharing)
### Proceso
...
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

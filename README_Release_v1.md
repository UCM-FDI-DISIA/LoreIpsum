## Relase_v1
<p>
Rama para lanzar Release de Höllenhaus
</p>
<p>
En esta rama, la clase SDLUtils carga todas las texturas de diálogos que van a ser utilizadas por TextComponent.
Son muchas texturas, lo cual provoca tiempos de carga elevados al entrar al juego, además de hacer uso de apox. 1,6 Gb de memoria.
</p>
<p>
TextComponent hace uso de estas texturas ya creadas para renderizar los diálogos, asi que no necesita crear texturas nuevas para los mismos.
Esto reduce enormemente las probabilidades de encontrar un error fatal relacionado con la destrucción de texturas.
</p>
<p>
El error puede seguir ocurriendo, ya que siguen habiendo texturas creadas y destruidas durante la ejecución del programa, aunque son muy pocas en comparación con las texturas de los diálogos.
Las texturas de los diálogos son destruidas al acabar el programa, con lo que no hay memory leaks.
</p>
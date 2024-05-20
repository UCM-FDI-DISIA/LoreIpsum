## Relase_v2
<p>
Rama para lanzar Release de Höllenhaus
</p>
<p>
En esta rama, la clase TextComponent destruye el puntero a Texture correctamente, y no hemos encontrado ningún error en la lógica del programa.
Sin embargo, al ejecutar el proyecto de Visual Studio en Release, es bastante fácil que ocurra un error fatal relacionado con la destrucción de memoria dinámica de TextComponent y la clase Texture.
</p>
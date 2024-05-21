## Relase_v3
<p>
Rama para lanzar Release de Höllenhaus
</p>
<p>
En esta rama, la clase TextComponent no está destruyendo el puntero a textura cuando esta deja de utilizarse.
Esto provoca muchos memory leaks, pero evitamos un error que cancelaría el programa.
</p>
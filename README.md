# The Puppet

### Overview de las instrucciones provistas en [CG__The_Puppet.pdf](https://drive.google.com/file/d/1IyVpmkiUmeRPOFF_5HWuvTPRzHP6x5FZ/view).

Crear una marioneta 3D utilizando modelos jerárquicos y estructuras de datos.

Construir y manejar una estructura de datos jerárquica para representar la marioneta y sus transformaciones, y dibujar e iluminar la marioneta utilizando OpenGL moderno. 

Modelo jerárquico:

![Modelo jerarquico](https://i.imgur.com/whbtkc8.jpgE)

Modelo de la marioneta:

![Modelo marioneta](https://i.imgur.com/xtB7SWQ.jpg)

El proyecto consta de tres etapas: 
- **Lectura de un archivo o descripción del modelo jerárquico**: se ha omitido la lectura del modelo desde un archivo extra y se ha optado por construir el modelo directamente al llamar la función (en [main.cpp](main.cpp)) build de la clase [Model.h](Model.h) asemejando el modelo del dibujo incluido en CG__The_Puppet.pdf.
- **Despliegue**: basado en [Model.h](Model.h), se construye la marioneta y se llama en [main.cpp](main.cpp) 94.
- **Animación de las articulaciones de la marioneta**: Se ha implementado un menú con ImGui que será mejor descrito en el apartado de [Ejecución del código](#ejecución-del-código).

Se deben cumplir una serie de objetivos relacionados con la proporción de la marioneta, su configuración y la utilización de una estructura jerárquica bien diseñada. 
También se pide incluir un archivo readme o markdown con instrucciones para ejecutar el código y un video donde se describa la ejecución del proyecto en la computadora.

### Ejecución del código

1. Clonar este repositorio. Se incluyeron todas las librerías necesarias para que sea ejecutado correctamente. 

2. Correr eñ archivo [main.cpp](main.cpp) como en el vídeo.

3. **Manejo de los controles**: Para manipular la posición de la marioneta se ha incluido una interfaz con ImGui. 

![interfaz marioneta](https://i.imgur.com/8fa7e7C.jpg)

En la barra superior se encuentran los botones correspondientes a las funciones de undo, redo, reset y close. Si las pilas de movimientos para las funciones de undo o redo están vacías, los botones de undo y redo se encontrarán deshabilitados, así como si la marioneta se encuentra en su estado inicial (posición neutral), el botón de reset estará deshabilitado. 

En la barra de la izquierda (la cual puede ser arrastrada, no está fijada), se encuentran los controles para cada una de las partes de la marioneta, ordenados como en la jerarquía de la marioneta. Al hacer cñic en la parte a mover se desplegarán 3 sliders correspondientes para controlar el movimiento en xyz (pitch/yaw/roll). Se encontrará deshabilitado si el movimiento no tiene sentido. El slider limita el ángulo en el que se puede hacer el movimiento para que tenga sentido (humanamente).

![slider control](https://i.imgur.com/7v5b63K.jpg)


### Comentarios adiconales
- Las clases Camera y ShaderClass son prácticamente idénticas a las de los vídeos de Victor Gordon. Las modifiqué mínimamente para las necesidades del presente proyecto.
- La capacidad de las pilas para el undo y redo es desconocida.
- No pude implementar el control de la marioneta por teclado, en su lugar se tienen los controles de Puppet en la parte inferior de la interfaz de ImGui.


### Referencias consultadas

1. [Tutorial para window icon](https://youtu.be/So7J1dJhmZw)

2. Ángulos (límites de los movimientos) más o menos basados en 
Panero J., Zelnik M. Human Dimension and Interior Space: A Source Book of Design Reference Standards Watson-Guptill (2014) 8.9 Antrhopomorpric tables: Joint motion (p297)

3. http://www.songho.ca/opengl/gl_sphere.html

4. [Tutoriales de The Cherno](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)

5. [Tutoriales de Victor Gordan](https://www.youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-)

6. [Documentación OpenGL](https://docs.gl/)

7. [Learn OpenGL](https://learnopengl.com/)

8. https://youtu.be/VRwhNKoxUtk

9. https://www.youtube.com/watch?v=So7J1dJhmZw

10. http://www.songho.ca/opengl/gl_sphere.html ; https://stackoverflow.com/questions/52633438/sphere-mesh-in-modern-opengl ; https://stackoverflow.com/questions/43087620/draw-sphere-in-opengl-4-03

11. https://skia.googlesource.com/external/github.com/ocornut/imgui/+/refs/tags/v1.78/imgui_demo.cpp

12. https://forum.unity.com/threads/how-to-make-gui-button-disable-status.74454/

13. https://registry.khronos.org/OpenGL-Refpages/gl4/html/glEnable.xhtml

14. https://www.programcreek.com/cpp/?CodeExample=menu+main

15. https://stackoverflow.com/questions/70819078/opengl-how-to-properly-add-lighting-to-a-scene-using-the-blinn-phong-shading-m



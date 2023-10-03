# The Puppet

### Overview de las instrucciones provistas en [CG__The_Puppet.pdf](https://drive.google.com/file/d/1IyVpmkiUmeRPOFF_5HWuvTPRzHP6x5FZ/view).

Crear una marioneta 3D utilizando modelos jerárquicos y estructuras de datos.

Construir y manejar una estructura de datos jerárquica para representar la marioneta y sus transformaciones, y dibujar e iluminar la marioneta utilizando OpenGL moderno. 

Modelo jerárquico:

![Modelo jerarquico](https://i.imgur.com/whbtkc8.jpgE)

El proyecto consta de tres etapas: 
- Lectura de un archivo o descripción del modelo jerárquico: se ha omitido la lectura del modelo desde un archivo extra y se ha optado por construir el modelo directamente al llamar la función (en [main.cpp](main.cpp)) build de la clase [Model.h](Model.h)
- Despliegue.
- Animación de las articulaciones de la marioneta: Se ha implementado un menú 

Se deben cumplir una serie de objetivos relacionados con la proporción de la marioneta, su configuración y la utilización de una estructura jerárquica bien diseñada. 
También se pide incluir un archivo readme o markdown con instrucciones para ejecutar el código y un video donde se describa la ejecución del proyecto en la computadora.

### Ejecución del código



### Comentarios adiconales
- Las clases Camera y ShaderClass son prácticamente idénticas a las de los vídeos de Victor Gordon. Las modifiqué mínimamente para las necesidades del presente proyecto.
- Desconozco la capacidad de las pilas para el undo y redo.


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







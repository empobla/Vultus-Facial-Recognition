# Error handling
Manejo del proyecto y áreas a trabajar. Políticas de todos los módulos las respuestas y manejo fuera del flujo básico de eventos, que se hace. Como hacer saber en cualquier error.

En continuación se listan las partes clave donde puede haber errores.

## Equipo 1 face recognition
Se compone de tareas en donde se manejen varios. 
Argumentos: 2 constructores, un tercero donde lleguen los argumentos
Identification: una lista de cuatec. 
Checar la imagen con toda la base de datos.
Escalas.
usar las funciones facerecognition, aligment y regresar n más parecidos.
## Equipo 2 Diseño de integración 
Problemas con el docker y la funcionalidad del código. 
Problemas con los pulls y actualización del github.
cada rostro tiene una respuesta, se hacen en un arreglo de mats con los posibles que son, si matchea los demás son vacíos, dentro de las 10 imagenes que se manden es cuando se hacen los match.
Regresar varios MAT para tener otros parecidos al comparar.
creación de la verificación antes de mandarla a la GUI, referencia de la creación y destrucción facerecognition.
regresar escala original de las imagenes.
uso de lo permisivo o restrictivo dado por un usuario. 
## Equipo 3 GUI
Gui: que funcione el verify con la credencial, identify que compara con la base de datos y el tercero para agregar a una persona.
Se vea el feed de la cámara.
Devolver 10 imágenes. Devolver un entero si machea o no. 
Manda a equipo 1 la imagen.
Dentro de enroll se guardan los datos, falta la toma de fotos. 
Dentro de las primeras partes se puede aceptar manualmente.
Con verify se coloca el calculate con un botón manual.Si no se encuentra la foto de la base de dato si no existe se calcula con la comparacion empty del mat que regresaría la base de datos. 
Crash dentro de la verificacion del metodo


## Equipo 4 Face Verification (error handling)
Cargar una vez y hacer desde una función. 
Entrada de verificación: cuales son, (frame del video, ID del estudiante (sensor de la credencial). Sale ID y foto de la persona.  
Devolver un mat y un booleano a equipo 3 al gui, ver como es el devolver un mat vacío.
regresa un 1 o 0 para la identificacion al equipo 3 y saber si hubo o no un match. 
problemas en la conexión del servidor. 
 definir lo restrictivo o permisivo del sistema con el acceptance_rate. 
## Paso a paso
A través de la GUI hay 3 botones para probar el código. se pan
# Instalar el Driver de MongoCxx
## Prerequisitos
- Tener instalado 
[CMake](https://cmake.org/) 3.2 o versiones posteriores
- Compilador que soporte C++11 (gcc, clang, o Visual Studio)
- boost header (opcional)
## MacOS
#### Paso 1. Instalar el Driver de MongoC (libmongoc y libbson)
- Descargas el archivo comprimido de la version más reciente de la libreria:  `$ curl -LO https://github.com/mongodb/mongo-c-driver/releases/download/x.y.z/mongo-c-driver-1.16.2.tar.gz`
- Lo descomprimes
  `$ tar xzf mongo-c-driver-1.16.2.tar.gz`
- Te cambias al directorio descargado `$ cd mongo-c-driver-1.16.2`
- Instalas el driver
  `$ mkdir cmake-build`
  `$ cd cmake-build`
  `$ cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..`
  `$ make install`
#### Paso 2. Descargar la version más reciente del driver MongoCxx
- Puedes hacerlo vía git
`$ git clone https://github.com/mongodb/mongo-cxx-driver.git \ --branch releases/stable --depth 1`
- Te cambias a la carpeta `/build` dentro de la carpeta descargada
`$ cd mongo-cxx-driver/build`
#### Paso 3. Configurar el driver
- Configurar para que el driver MongoCxx se instale en `/usr/local`

`cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local`
#### Paso 4. Hacer Build e instalar el driver
`sudo make EP_mnmlstc_core`
`make && sudo make install`
## Listo 🤟


## Windows
Para Windows se necesita visual studio 15 2017 y boost \
*Necesitas tener el paquete en ingles de visual studio

### visual 
https://visualstudio.microsoft.com/es/vs/older-downloads/ 
tienen que elegir visual studio 2017
 
Luego al iniciar sesión con cualquier cuenta Microsoft (puede ser la del tec) eligues la versión community. 

Al instalar visual necesitamos los paquetes de c++, marcar la casilla para que se descarguen y se agreguen a nuestro visual.

(ojo: ver que dentro de detalles este el adaptador de prueba para Boost.Test, si no tienes el paquete en ingles de visual aquí mismo se puede instalar bajo la pestaña de paquetes de idioma)

Ya que tenemos visual necesitamos que se habiliten las opciones de Boost.

### Boost y drivers
A continuación están una serie de comandos que se van a escribir desde una consola de Windows, antes de comenzar recomiendo tener claro donde se va a guardar la carpeta con todos los archivos del boost, mongoc y mongocxx. Teniendo ya la carpeta con la dirección deseada necesitamos hacer los siguientes pasos:\
> git clone https://github.com/Microsoft/vcpkg.git\
> cd vcpkg\
> bootstrap-vcpkg.bat\
> vcpkg install boost:x86-windows\
> vcpkg install mongo-c-driver \
> vcpkg install mongo-cxx-driver\

checamos si están los paquetes con el siguiente comando\
> vcpkg list \

Ya que tenemos los paquetes instalados se necesita hacer que el boost este conectado con el visual studio con el siguiente comando. \
> vcpkg integrate install\

Para más información sobre el instalador de paquetes de windows: https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019  

### MongoDB
Ya tenemos los drivers pero faltan inicializar los servidores de mongo, primero necesitamos descargar Mongo Compass que es la GUI de la base de datos (parecido a MySQL). \
https://www.mongodb.com/download-center/compass (se puede cambiar la carpeta destino de donde quieres compass)

Ahora solo falta el servidor dentro de la computadora. 
https://www.mongodb.com/dr/fastdl.mongodb.org/win32/mongodb-win32-x86_64-2012plus-4.2.6-signed.msi/download  
(ojo: deseleccionar la opción de instalar compass ya que esa versión es para usar en línea y no de forma local)

Ya que tenemos los servidores necesitamos iniciar una consola y escribimos mongo para inicializar el servidor y poder editar. Como no vamos a usar la base de datos con el código podemos salir con el comando exit.  
Ahora abrimos compass y seleccionamos localhost, luego vamos al botón verde y ponemos conectar. 
 

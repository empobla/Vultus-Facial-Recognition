# Face Recognition Database

### To build:

```sh
mkdir build
cd build
cmake ..
make
./Database
```

## How to use

```c++
//Make sure to include this file
#include "src/include/DBManagerInterface.hpp"

using namespace cv;
using namespace std;

int main()
{
    //------------------ Class Cuatec ---------------------
    //Cuatec receives name(string), age(int), matricula(string),
    // image from TecId(cv::Mat) and features(cv::Mat)
    Cuatec nuevoCuatec("Sal Montesdeoca", 22, "A01025975", ImgMat, FeaturesMat);

    //Getters
    string nombre = nuevoCuatec.getNombre();
    string matricula = nuevoCuatec.getMatricula();
    int edad = nuevoCuatec.getEdad();
    Mat img = nuevoCuatec.getImg();
    Mat features = nuevoCuatec.getFeatures();

    //Setters
    nuevoCuatec.setNombre(string nuevoNombre);
    nuevoCuatec.setMatricula(string nuevoMatricula);
    nuevoCuatec.setEdad(int nuevaEdad);
    nuevoCuatec.setImg(Mat nuevaImagen);
    nuevoCuatec.setFeatures(Mat nuevoFeatures);

    //You need to instance de class once like this:
    DBManagerInterface dbManager(URI, DATABASE, COLLECTION);

    //Methods:

    //-------------------- Create ------------------------
    /*
        Create method can either receive a Cuatec object
        or receive (std::string name, int age, std::string matricula,
        cv::Mat image, cv::Mat features)
        Returns int:
            0 for failed insertion
            1 for succeed insertion
    */
    int created = dbManager.create("wicho Garcia", 22, "A01025555", M, M);
    int created = dbManager.create(nuevoCuatec);

    //-------------------- Read ------------------------
    //Prints all the data in console (JSON format)
    dbManager.readAll(); //Not recomended for bigdata

    //Returns a Cuatec object found in the DB
    Cuatec nuevoCuatec = dbManager.readOne("A01021111");

    //Returns ObjectId (string format)
    string oid = dbManager.readOid("A01025975");

    //Returns name as string
    string nombre = dbManager.readOneName("A01025975");

    //Returns age as int
    int edad = dbManager.readOneEdad("A01025975");

    //Returns features as cv::Mat
    Mat features = dbManager.readOneFeatures("A01025555");

    //Returns img as cv::Mat
    Mat img = dbManager.readOneImg("A01025555");

    //-------------------- Update ------------------------
    //Receives matricula of object to update and new name
    //Returns:
    //0 for failing at updating
    //1 for suceeding at updating
    int updated = dbManager.updateName("A01025975","Victor Coeto");

    //Receives matricula of object to update and new matricula
    //Returns:
    //0 for failing at updating
    //1 for suceeding at updating
    int updated = dbManager.updateMatricula("A01021111", "A01025986");

    //-------------------- Delete ------------------------
    //Receives matricula of object to delete
    //Returns:
    //0 for failing at deleting
    //1 for suceeding at deleting
    int result = dbManager.deleteOne("A01025975"); //falta borrar xmls guardados

    return 0;
}
```

### Authors

Víctor Adrián Coeto Gardea \
Saul Montes de Oca\
Juan Carlos Hurtado

# Instalar el Driver de MongoCxx

## Prerequisitos

- Tener instalado
  [CMake](https://cmake.org/) 3.2 o versiones posteriores
- Compilador que soporte C++11 (gcc, clang, o Visual Studio)
- boost header (opcional)

## MacOS

#### Paso 1. Instalar el Driver de MongoC (libmongoc y libbson)

- Descargas el archivo comprimido de la version más reciente de la libreria:

```sh
curl -LO https://github.com/mongodb/mongo-c-driver/releases/download/1.16.2/mongo-c-driver-1.16.2.tar.gz
```

- Lo descomprimes

```sh
tar xzf mongo-c-driver-1.16.2.tar.gz
```

- Te cambias al directorio descargado

```sh
cd mongo-c-driver-1.16.2
```

- Instalas el driver

```sh
mkdir cmake-build
cd cmake-build
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
make install
```

#### Paso 2. Descargar la version más reciente del driver MongoCxx

- Puedes hacerlo vía git

```sh
git clone https://github.com/mongodb/mongo-cxx-driver.git \ --branch releases/stable --depth 1
```

- Te cambias a la carpeta `/build` dentro de la carpeta descargada

```sh
$ cd mongo-cxx-driver/build
```

#### Paso 3. Configurar el driver

- Configurar para que el driver MongoCxx se instale en `/usr/local`

```sh
cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_INSTALL_PREFIX=/usr/local
```

#### Paso 4. Hacer Build e instalar el driver

```sh
sudo make EP_mnmlstc_core
make && sudo make install
```

### Listo 🤟

## Windows

Para Windows se necesita visual studio 15 2017 y boost \
\*Necesitas tener el paquete en ingles de visual studio

### visual

https://visualstudio.microsoft.com/es/vs/older-downloads/
tienen que elegir visual studio 2017

Luego al iniciar sesión con cualquier cuenta Microsoft (puede ser la del tec) eligues la versión community.

Al instalar visual necesitamos los paquetes de c++, marcar la casilla para que se descarguen y se agreguen a nuestro visual.

(ojo: ver que dentro de detalles este el adaptador de prueba para Boost.Test, si no tienes el paquete en ingles de visual aquí mismo se puede instalar bajo la pestaña de paquetes de idioma)

Ya que tenemos visual necesitamos que se habiliten las opciones de Boost.

### Boost y drivers

A continuación están una serie de comandos que se van a escribir desde una consola de Windows, antes de comenzar recomiendo tener claro donde se va a guardar la carpeta con todos los archivos del boost, mongoc y mongocxx. Teniendo ya la carpeta con la dirección deseada necesitamos hacer los siguientes pasos:

> git clone https://github.com/Microsoft/vcpkg.git \
> cd vcpkg\
> bootstrap-vcpkg.bat\
> vcpkg install boost:x86-windows\
> vcpkg install mongo-c-driver \
> vcpkg install mongo-cxx-driver\

checamos si están los paquetes con el siguiente comando

> vcpkg list \

Ya que tenemos los paquetes instalados se necesita hacer que el boost este conectado con el visual studio con el siguiente comando.

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

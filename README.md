# sdbuscpp-examples

Concatenator example in sdbus-c++ library [documentation](https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md).

Dependencies
------------

* `sdbus-c++` - build and install [sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp) library
* `C++17` - the library uses C++17 features.
* `libsystemd` - systemd library containing sd-bus implementation. Systemd at least v236 is needed. 
* `Cmake` - The project is built using CMake

Building
-----------------------------------

```bash
$ mkdir build
$ cd build
$ cmake ../
$ make
```
The `make` command builds all examples. If you just want to build an example, you can type `make basic_layer_server` command.

Dbus Configuration
-----------------------------------

Typical default D-Bus configuration does not allow to register services except explicitly allowed. So you should copy the `org.sdbuscpp.concatenator.conf` file in system.d to `/etc/dbus-1/system.d`.

```bash
$ sudo cp system.d/org.sdbuscpp.concatenator.conf /etc/dbus-1/system.d
```

Run Examples
-----------------------------------

* Terminal 1

```bash
$ sudo ./basic_layer_server
```

* Terminal 2

```bash
$ sudo ./basic_layer_client
```
* Examples that end with "*_server" and "*_client" do the same thing in the background. They just use diff layer of sdbus-c++ library. So you can use the basic_layer_server as a server, and xml_layer_client as a client program.

Changing .xml file
-----------------------------------

sdbus-c++ ships with the native stub generator tool called `sdbus-c++-xml2cpp`. 

The generator tool takes D-Bus XML IDL description of D-Bus interfaces on its input, and can be instructed to generate one or both of these: an adaptor header file for use on the server side, and a proxy header file for use on the client side. 

Type the `make create_server_client_glue` command to update the header files after changing xml file.

[for more details](https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md#implementing-the-concatenator-example-using-sdbus-c-generated-stubs)

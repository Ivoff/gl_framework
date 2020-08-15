# Setup
```
git clone https://github.com/Ivoff/gl_framework.git
cd gl_framework 
wget https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip -P ./vendor && cd vendor
unzip glfw-3.3.2.zip && cd glfw-3.3.2
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../../../
make 
```

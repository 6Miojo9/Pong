Remove-Item -Recurse -Force .\build\
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
.\build\Release\Pong.exe
cd ../lib/Game_Logic
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cd build
make
./test/game_logic-tests
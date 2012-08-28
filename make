gcc Drawer/SDLMGR.c Drawer/AreaMGR.c Drawer/DrawLib.c StatusHandler/StatusMGR.c Client/ClientLib.c Client/ClientDataReader.c -o client -lSDL -L lib -lSDL_draw
echo "compile client done!"
gcc StatusHandler/StatusMGR.c DataHandler/TDX/TDXReader.c testserver.c -o server
echo "compile server done!"


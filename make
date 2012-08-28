gcc Drawer/SDLMGR.c Drawer/AreaMGR.c Drawer/DrawLib.c StatusHandler/StatusMGR.c Client/ClientLib.c Client/ClientDataReader.c -o client -lSDL -L lib -lSDL_draw
gcc StatusHandler/StatusMGR.c DataHandler/GetData.c testserver.c -o server


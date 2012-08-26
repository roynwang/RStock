gcc DayData.h Drawer/SDLMGR.h Drawer/SDLMGR.c Drawer/AreaMGR.h Drawer/AreaMGR.c Drawer/DrawLib.c StatusHandler/StatusMGR.c ClientDataReader.c -o client -lSDL -L lib -lSDL_draw
gcc DayData.h StatusHandler/StatusMGR.c DataHandler/GetData.c testserver.c -o server


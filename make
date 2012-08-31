gcc Drawer/SDLMGR.c Drawer/AreaMGR.c Drawer/DrawLib.c StatusHandler/StatusMGR.c Client/ClientLib.c Client/ClientDataReader.c -o client -lSDL -L lib -lSDL_draw -lSDL_ttf
echo "compile client done!"
gcc StatusHandler/StatusMGR.c DataHandler/TDX/TDXReader.c DataHandler/Yahoo/YahooDownloader.c DataHandler/Yahoo/YahooReader.c testserver.c -o server -lcurl
echo "compile server done!"


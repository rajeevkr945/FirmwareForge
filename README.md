RGB Configurator# rgbConfigurator

refer-https://www.waveshare.com/wiki/RGB-Matrix-P3-64x64
testscript.py is the python script that runs the test-example/image-example/scrolling-text-example C program
uart-peripheral is the pybluez uart-BLE server

# RGBConfigurator

**command to run scrolling text : ** sudo ./scrolling-text-example  -led-no-hardware-pulse --led-cols=64 --led-rows=64 --led-gpio-mapping=adafruit-hat --led-chain=4 --led-limit-refresh=100 -y 40 --led-no-drop-privs  --led-slowdown-gpio=4

**command to run image-example**: sudo < absolute-path-of-the-image-file > --led-no-hardware-pulse  --led-cols=64 --led-rows=64 --led-chain=4 --led-gpio-mapping=adafruit-hat --led-limit-refresh=100  --led-no-drop-privs  --led-slowdown-gpio=4

import os
import time

# time.sleep(1)
#os.system("pkill -f 'testscript2'")
print("start_testscript")

try:
    with open("/home/admin/rpi-rgb-led-matrix/examples-api-use/switch.txt", 'w') as f:
        f.write("start")
        print('start written to file')
    print('turning on Display')
    command = " sudo ./scrolling-text-example  -led-no-hardware-pulse --led-cols=64 --led-rows=64 --led-gpio-mapping=adafruit-hat --led-chain=4 -y 40 --led-no-drop-privs  --led-slowdown-gpio=4"
    os.system(command)
    print('Display Started')
    
except Exception as e:
    print('Error:testscript1: {}'.format(e))
    
# with open("/home/admin/rpi-rgb-led-matrix/examples-api-use/switch.txt", 'w') as f:
    # f.write("start")
# print('RGB-ON')
# while(1):
    
    # command = "sudo /home/admin/rpi-rgb-led-matrix/examples-api-use/text-example --led-no-hardware-pulse --led-cols=64 --led-rows=64 --led-gpio-mapping=adafruit-hat-pwm"
    # os.system(command)
    





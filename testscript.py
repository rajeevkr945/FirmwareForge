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
    command = "sudo /home/admin/rpi-rgb-led-matrix/examples-api-use/text-example --led-no-hardware-pulse --led-cols=64 --led-rows=64 --led-gpio-mapping=adafruit-hat-pwm"
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
    





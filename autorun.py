import os
import time

flag = 1
def get_usb_device_path(device_name):
    command = f"find /dev -name '{device_name}*'"
    result = os.popen(command).read().strip()
    print(result)
    return result

usb_device_name = "sd"  # Replace with the identifier of your USB device (e.g., "sd", "sdb", etc.)

usb_device_path = get_usb_device_path(usb_device_name)



while(1):
	time.sleep(1)
	usb_device_path = get_usb_device_path(usb_device_name)
	if usb_device_path:
		os.system('feh -Z -z -F -D 3 --hide-pointer --auto-rotate -r /media')
		print(f"USB device path: {usb_device_path}")
		flag = 1
	elif usb_device_path == None and flag == 1:
		print("USB device not found.")
		flag=0
	 
		


	

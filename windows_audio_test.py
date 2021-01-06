from ahk import AHK

ahk = AHK()

print(ahk.sound_get(device_number=1, component_type='MASTER', control_type='VOLUME'))
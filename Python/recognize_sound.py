import os
import time
import wave
import serial
import pyaudio
import speech_recognition as sr

print(sr.Microphone.list_microphone_names())
num = -1
for i,x in enumerate(sr.Microphone.list_microphone_names()):
    print(i,x)
    if x == 'default': num = i

print(sr.__version__) # just to print the version not required
r = sr.Recognizer()
r.dynamic_energy_threshold = False
r.energy_threshold = 4000
print(r.pause_threshold)

my_mic = sr.Microphone(device_index=num) # my device index is 1, you have to put your device index
with my_mic as source:
    understood = False
    recognized_str_lower = ''
    while(not understood):
        os.system('espeak "Please speak your command now..." --stdout | paplay')
        r.adjust_for_ambient_noise(source)  # reduce noise
        audio = r.listen(source) #take voice input from the microphone
        recognized_str = r.recognize_google(audio) #to print voice into text
        recognized_str_lower = recognized_str.lower()
        print(recognized_str_lower) #to print voice into text
        if "fork" in recognized_str_lower or "spoon" in recognized_str_lower or "knife" in recognized_str_lower:
            understood = True
        else:
            os.system('espeak "I did not get the keywords: Spoon or Knife or Fork..." --stdout | paplay')
    # os.system('espeak "' + recognized_str_lower + '" --stdout | paplay')

    with serial.Serial('/dev/ttyUSB0', 9600, timeout=500) as ser:
        if "spoon" in recognized_str_lower:
            os.system('espeak "I am picking up spoon" --stdout | paplay')
            ser.write(bytes('S\n','utf-8'))
        elif "fork" in recognized_str_lower:
            os.system('espeak "I am picking up fork" --stdout | paplay')
            ser.write(bytes('F\n','utf-8'))
        elif "knife" in recognized_str_lower:
            os.system('espeak "I am picking up knife" --stdout | paplay')
            ser.write(bytes('K\n','utf-8'))
        time.sleep(15)
        os.system('espeak "Please take it..." --stdout | paplay')

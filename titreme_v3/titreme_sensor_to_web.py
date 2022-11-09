#read data from arduino python cod
import serial
import time

ser = serial.Serial('COM3',9600, timeout=0.1)
ser.close()
ser.open()


while True:
    #value = read_sensor_data
    data = ser.readline()
    if data:#verifi si la ligne n'est pas vide si c'est vide sa ne fait rien au cas contraire sa enregistre et sa break
        value = data.decode('utf-8')
        rows = [x for x in value.split(',')] #prend les valeur et l'enregistre dans une liste et les converti en float
        #separe la liste en differente valeur donnée par le sensor
        ID = rows[0] 
        motor_durum = rows[1]
        sicaklik = rows[2]
        gaz_degeri = rows[3]

        print(value) #affiche les valeur brute
        print(rows) #affiche les valeur enregistrer dans la liste
        print("Motor ID : " +  str(ID)) #affiche la valeur temperature enregistrer comme 1er element de la liste
        print("Motor Durumu : " +  str(motor_durum))
        print("Motor Sicakliği : " +  str(sicaklik))
        print("Gaz Degeri : " +  str(gaz_degeri))
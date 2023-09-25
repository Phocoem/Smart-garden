import serial
from datetime import datetime


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0',9600, timeout=1)
    ser.flush()
    
    while True:
        if ser.in_waiting > 0:
        
            line = ser.readline().decode('utf-8').rstrip()
            a=line.split('#')
            print(line)
            temp=float(a[0])	
            hum=float(a[1])
            soilValue=float(a[2])
            ldrValue=float(a[3])
            five=int(a[4])
            t=str(temp)
            h=str(hum)
            s=str(soilValue)
            l=str(ldrValue)
            
            now = datetime.now()

# dd/mm/YY H:M:S
            time = now.strftime("%d/%m/%Y %H:%M:%S")
            mo= "mo luc "+time
            dong="dong luc "+time
                            
            ez = open("/var/www/html/bom.txt","r")
            idi= float(ez.read())
            ez.close()
            if (five-idi==-1):
                dongmo = open("/var/www/html/dongmo.txt","a")
                dongmo.write(mo)
                dongmo.write("\n")
                dongmo.close()
            if (five-idi==1):
                dongmo = open("/var/www/html/dongmo.txt","a")
                dongmo.write(dong)
                dongmo.write("\n")
                dongmo.close()
            if (five==1 or five==2):
                bom = open("/var/www/html/bom.txt","w")
                bom.write(str(five))
                bom.close()    
            
               
            fanFile = open("/var/www/html/fanStatus.txt","r")
            command = fanFile.read()
            fanFile.close()
            
            print(temp)
            if command == 'on':
                ser.write(b"n\n")
                print(command)
            if command == 'off':
                print(command)
                ser.write(b"f\n")
            if command == 'auto':
                
                print(command)       
                if (soilValue <=30) and (ldrValue<=30):
                    ser.write(b"a\n")
                if (soilValue > 30) and (ldrValue<=30):
                    ser.write(b"b\n")
                if (soilValue <= 30) and (ldrValue>30):
                    ser.write(b"c\n")
                if (soilValue >30) and (ldrValue>30):
                    ser.write(b"d\n")
            tempFile = open("/var/www/html/data.txt","w")
            
            tempFile.write("\nNhiet do:")
            tempFile.write(t)
            tempFile.write("*C")
            tempFile.write("\nDo am khong khi:")
            tempFile.write(h)
            tempFile.write("%")
            tempFile.write("\nCuong do anh sang:")
            tempFile.write(l)
            tempFile.write("%")
            
            tempFile.write("Do am dat:")
            tempFile.write(s)
            tempFile.write("%")
            
            tempFile.close()
          
            



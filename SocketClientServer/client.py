import socket
import json

HOST = '13.250.12.60'  # The server's hostname or IP address
PORT = 65432        # The port used by the server
listfruits = '{"orange":"Qua cam", "strawberry":"Day tay", '\
             '"grape":"Nho", "durian":"Sau rieng"}'
info = '{"_id":123,"Time":11,"Temp":12,"Hum":13,"Bat":14}'
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    mylist = json.loads(listfruits)
    testingtemp = json.loads(info)
    print(mylist)
    print(mylist['durian'])
    a = "khanhne"
    s.sendall(info.encode('utf-8'))
    #s.sendall(**b**'khanhnebay')
    #s.sendall(b'{"orange":"Qua cam", "strawberry":"Day tay","grape":"Nho", "durian":"Sau rieng"}')
    data = s.recv(1024)

print('Received', data.decode())

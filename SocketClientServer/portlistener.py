import json
from pymongo import MongoClient
import socket

print ('connect successful!!')

s = socket.socket()
print ('Socket successfully created')

port = 65432


s.bind(('', port))
print ('socket binded to {0:d}'.format(port) )

s.listen(5)
print ('socket is listening')
client = MongoClient()
db = client.StorgeTempHum
coll = db.realTimeupdate
#col = coll.find_one()
#print(col)
#print (coll)

while True:  
   c, addr = s.accept()      
   print ('Got connection from', addr) 
 
  # c.send('Thank you for connecting') 
   for x in coll.find():
    print(x)
   c.close() 


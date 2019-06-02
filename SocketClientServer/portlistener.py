import json
from pymongo import MongoClient
import socket
import bson
import collections
from bson.codec_options import CodecOptions
from bson.json_util import dumps

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

"""
while True:  
   c, addr = s.accept()      
   print ('Got connection from', addr) 
 
   c.sendall('Thank you for connecting') 
   
   content = c.recv(1024)
   print(content)

   for x in coll.find():
    print(x)
   c.close() 
"""
conn, addr = s.accept()
with conn:
  print('Connected by', addr)
  while True:
     data = conn.recv(1024)
     #jsonObj = json.loads(coll.find_one())
     if not data:
        break
     print(data.decode())
     a=coll.find_one()
     #print(a)
     #b=bson.BSON.encode(a)
     datatosent = dumps(db.realTimeupdate.find_one())
     #print (dumps(db.realTimeupdate.find_one()))
     #print(datatosent.encode('utf-8'))
     #print(datatosent)
     conn.sendall(datatosent.encode('utf-8'))
    # conn.sendall(b)


# Import socket module 
import socket                
  
# Create a socket object 
s = socket.socket()          
  
# Define the port on which you want to connect 
port = 65432             
  
# connect to the server on local computer
print ("conectting...") 
s.connect(('104.43.18.254', port)) 
  
# receive data from the server
data = s.recv(1024) 
print (data)
# close the connection 
s.close()

print ("socket closed") 

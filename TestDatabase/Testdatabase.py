
import pymysql.cursors  
 
#  database.
connection = pymysql.connect(host='localhost',
                             user='root',
                             password='root',                             
                          unix_socket="/var/run/mysqld/mysqld.sock")
 
print ("connect successful!!")


from pymongo import MongoClient
import json

client = MongoClient()
db = client.Temp
collection = db.update
cursor = collection.find()
#print(cursor["Date"])
data = [[]]

for document in cursor:
	#x = json.dumps(document)
	#x = json.loads(document)
	x=[]
	x.append(document["Date"])
	x.append(document["Temp"])
	x.append(document["Hum"])
	data[0].append(x)
	#countdb =countdb + 1

print (data)
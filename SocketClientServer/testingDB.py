import json
from pymongo import MongoClient


client = MongoClient('localhost', 27017)
db = client['StorgeTemp&Hum']
collection_realTimeupdate = db['realTimeupdate']

with open('testing.json') as f:
    file_data = json.load(f)

# use collection_currency.insert(file_data) if pymongo version < 3.0
collection_realTimeupdate.insert_one(file_data)  
client.close()

from pymongo import MongoClient

client = MongoClient("mongodb://mongodb0.example.net:27019")
db = client.primer
coll = db.dataset
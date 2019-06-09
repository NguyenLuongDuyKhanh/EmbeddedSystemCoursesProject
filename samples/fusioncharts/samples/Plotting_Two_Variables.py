from django.shortcuts import render
from django.http import HttpResponse

# Include the `fusioncharts.py` file which has required functions to embed the charts in html page
from pymongo import MongoClient
import numpy as np
import json
from ..fusioncharts import FusionCharts
from ..fusioncharts import FusionTable
from ..fusioncharts import TimeSeries
import requests

# Loading Data and schema from a Static JSON String url
# The `chart` method is defined to load chart data from an JSON string.

def chart(request):

    #data = requests.get('https://s3.eu-central-1.amazonaws.com/fusion.store/ft/data/plotting-two-variable-measures-data.json').text
    client = MongoClient()
    db = client.Temp
    collection = db.update
    cursor = collection.find()
    data = []

    for document in cursor:
    	x =[]
    	x.append(document["Date"])
    	x.append(document["Temp"])
    	x.append(document["Hum"])
    	data.append(x)

    print (data)

    schema = [{
    "name": "Date",
    "type": "date",
    "format": "%-m/%d/%Y"
},
{
    "name": "Nhiệt độ (C)",
    "type": "number"
},
{
    "name": "Độ ẩm (%)",
    "type": "number"
}]

    fusionTable = FusionTable(schema, data)
    timeSeries = TimeSeries(fusionTable)

    timeSeries.AddAttribute("caption", """{ 
								text: 'Bảng thể hiện nhiệt độ và độ ẩm'
							  }""")

    timeSeries.AddAttribute("subcaption", """{ 
                                    text: 'Môn Hệ thống Nhúng nhóm Bảo - Bình - Khánh'
                                    }""")

    timeSeries.AddAttribute("yAxis", """[{
											plot: [{
											  value: 'Nhiệt độ (C)',
											  connectNullData: true
											}],
											min: '0',
											max: '10',
											title: 'Nhiệt độ (C)'  
										  }, {
											plot: [{
											  value: 'Độ ẩm (%)',
											  connectNullData: true
											}],
											min: '0',
											max: '50',
											title: 'Độ ẩm (%)'
                                        }]""");	

    # Create an object for the chart using the FusionCharts class constructor
    #fcChart = FusionCharts("timeseries", "ex1", 700, 450, "chart-1", "json", timeSeries)
    fcChart = FusionCharts("timeseries", "ex1", 700*2, 450*2, "chart-1", "json", timeSeries)

     # returning complete JavaScript and HTML code, which is used to generate chart in the browsers. 
    return  render(request, 'index.html', {'output' : fcChart.render(),'chartTitle': "Đây là Đồ án lớp thầy Hứa"})
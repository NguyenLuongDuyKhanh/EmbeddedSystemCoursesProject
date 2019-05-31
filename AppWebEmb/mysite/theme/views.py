from django.shortcuts import render

# Create your views here.
from django.template.response import TemplateResponse

# Create your views here.
def homepage(request):
    return TemplateResponse(request, 'base.html')

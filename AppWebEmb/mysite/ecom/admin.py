# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin
from .models import Type, Product

class TypeModelAdmin(admin.ModelAdmin):
    list_filter = ('active',)
    list_display = ('name', 'active', )

class ProductModelAdmin(admin.ModelAdmin):
    readonly_fields = ('image_tag',)    
    list_display = ('name', 'price', 'quantity', 'description')

admin.site.register(Type, TypeModelAdmin)
admin.site.register(Product, ProductModelAdmin)

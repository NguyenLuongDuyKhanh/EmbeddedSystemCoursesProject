# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models
from django.conf import settings
import django.utils.safestring as safestring

# Create your models here.
class Type(models.Model):
    name = models.CharField(max_length=200)
    active = models.BooleanField("Is Active", default=True)
    
    def __str__(self):
        return self.name


class Product(models.Model):
    type_id = models.ForeignKey(Type, on_delete=models.CASCADE)
    name = models.CharField("Product Name", max_length=200)
    price = models.IntegerField("Price", default=0)
    quantity = models.IntegerField("Quantity", default=0)
    image = models.ImageField(upload_to='uploads/%Y/%m/%d/')
    description = models.TextField("Description")
    
    def image_tag(self):
        if self.image:
            return safestring.mark_safe('<img src="%s%s" width="150" height="150" />' % (settings.MEDIA_URL, self.image))
        else:
            return ""

    image_tag.short_description = 'Image'
    image_tag.allow_tags = True
    
    def __str__(self):
        return self.name

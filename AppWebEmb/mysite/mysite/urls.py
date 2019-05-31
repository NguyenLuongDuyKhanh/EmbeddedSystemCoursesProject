
"""mysite URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import include, path
from theme.views import homepage #1
from django.conf.urls import url

from django.conf import settings
from django.conf.urls.static import static

from ecom.views import index, product

urlpatterns = [
    path('polls/', include('polls.urls')),
    #path('admin/', admin.site.urls),
    #path('^s',include('theme.urls')),   
    url(r'^admin/', admin.site.urls),
    url(r'^test', homepage), #3
    #url(r'^$',views.index,name='index'),
    #url(r'^product/(?P<product_id>[0-9]+)/$', views.product, name='product'),
    url(r'^$', index),
    url(r'^product/(?P<product_id>[0-9]+)/$', product),
]+ static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)

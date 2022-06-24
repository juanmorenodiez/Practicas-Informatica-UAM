from django.contrib import admin
from rango.models import Category, Page, PageAdmin
from rango.models import UserProfile


class CategoryAdmin(admin.ModelAdmin):
    prepopulated_fields = {'slug': ('name',)}


admin.site.register(Page, PageAdmin)
admin.site.register(Category, CategoryAdmin)
admin.site.register(UserProfile)

# Register your models here

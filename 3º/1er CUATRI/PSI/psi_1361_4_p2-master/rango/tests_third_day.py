# Uncomment if you want to run tests in transaction mode with a final rollback
# from django.test import TestCase
# uncomment this if you want to keep data after running tests
from unittest import TestCase

from django.test import Client
from django.urls import reverse
from populate_rango import populate
from rango.models import Category

class Chapter6FormTests(TestCase):

    def setUp(self):
        self.client = Client()
        try:
            populate()
        except ImportError:
            print('The module populate_rango does not exist')
        except NameError:
            print('The function populate() does not exist or is not correct')
        except:
            print('Something went wrong in the populate() function :-(')

        # Check forms are defined
        try:
            from forms import PageForm
            from forms import CategoryForm
            PageForm()
            CategoryForm()
        except ImportError:
            print('The module forms does not exist')
        except NameError:
            print('The class PageForm does not exist or is not correct')
        except Exception:
            print('Something else went wrong :-(')

    def get_category(self, name):
        try:
            print("name=", name)
            cat = Category.objects.get(name=name)
            print("nameCat=", cat)
        except Category.DoesNotExist:
            cat = None
        return cat

    def test_python_category_added(self):
        cat = self.get_category('Python')
        print("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", cat)
        self.client.get(reverse('rango:add_page', kwargs={'category_name_slug':cat.slug} ))
        self.assertIsNotNone(cat)

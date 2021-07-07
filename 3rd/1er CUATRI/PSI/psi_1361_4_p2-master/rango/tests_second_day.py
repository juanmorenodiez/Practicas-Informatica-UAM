# Uncomment if you want to run tests in transaction mode with a final rollback
# from django.test import TestCase
# uncomment this if you want to keep data after running tests
from unittest import TestCase

from django.test import Client
from django.urls import reverse
from populate_rango import populate
from rango.models import Category


class ModelTests(TestCase):

    def setUp(self):
        try:
            populate()
        except ImportError:
            print('The module populate_rango does not exist')
        except NameError:
            print('The function populate() does not exist or is not correct')
        except Exception:
            print('Something went wrong in the populate() function :-(')

    def get_category(self, name):
        try:
            cat = Category.objects.get(name=name)
        except Category.DoesNotExist:
            cat = None
        return cat

    def test_python_cat_added(self):
        cat = self.get_category('Python')
        self.assertIsNotNone(cat)

    def test_python_cat_with_views(self):
        cat = self.get_category('Python')
        self.assertEquals(cat.views, 128)

    def test_python_cat_with_likes(self):
        cat = self.get_category('Python')
        self.assertEquals(cat.likes, 64)


class Chapter5ViewTests(TestCase):

    def setUp(self):
        self.client = Client()
        try:
            populate()
        except ImportError:
            print('The module populate_rango does not exist')
        except NameError:
            print('The function populate() does not exist or is not correct')
        except Exception:
            print('Something went wrong in the populate() function :-(')

    def get_category(self, name):
        try:
            print("name=", name)
            cat = Category.objects.get(name=name)
            print("nameCAt=", cat)
        except Category.DoesNotExist:
            cat = None
        return cat

    def test_python_cat_added(self):
        cat = self.get_category('Python')
        self.assertIsNotNone(cat)

    def test_python_cat_with_views(self):
        cat = self.get_category('Python')
        self.assertEquals(cat.views, 128)

    def test_python_cat_with_likes(self):
        cat = self.get_category('Python')
        self.assertEquals(cat.likes, 64)

    def test_view_has_title(self):
        response = self.client.get(reverse('index'))
        # Check title used correctly
        self.assertIn(b'<title>', response.content)
        self.assertIn(b'</title>', response.content)

    # Need to add tests to:
    # check admin interface - is it configured and set up
    def test_admin_interface_page_view(self):
        from rango.admin import PageAdmin
        self.assertIn('category', PageAdmin.list_display)
        self.assertIn('url', PageAdmin.list_display)

    def test_show_category(self):
        response = self.client.get(
            reverse('rango:show_category', kwargs={'category_name_slug': 'python'}))
        self.assertIn(b'How to Think like a Computer Scientis',
                      response.content)
        response = self.client.get(
            reverse('rango:show_category',
                    kwargs={'category_name_slug': 'asdfgh'}))
        self.assertIn(b'The specified category does not exist',
                      response.content)

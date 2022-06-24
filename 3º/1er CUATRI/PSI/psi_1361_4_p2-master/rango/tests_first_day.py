from django.urls import reverse
from django.contrib.staticfiles import finders
from django.test import TestCase
from django.test import Client


class GeneralTests(TestCase):
    def test_serving_static_files(self):
        # If using static media properly result is
        # not NONE once it finds rango.jpg
        result = finders.find('images/rango.jpg')
        self.assertIsNotNone(result)


class IndexPageTests(TestCase):

    def setUp(self):
        self.client = Client()

    def test_index_contains_hello_message(self):
        # Check if there is the message 'Rango Says'
        # Chapter 4
        response = self.client.get(reverse('index'))
        self.assertIn(b'Rango says', response.content)

    def test_index_using_template(self):
        # Check the template used to render index page
        # Chapter 4
        response = self.client.get(reverse('index'))
        self.assertTemplateUsed(response, 'rango/index.html')

    def test_rango_picture_displayed(self):
        # Check if is there an image called 'rango.jpg' on the index page
        # Chapter 4
        response = self.client.get(reverse('index'))
        self.assertIn(b'img src="/static/images/rango.jpg', response.content)

    def test_index_has_title(self):
        # Check to make sure that the title tag has been used
        # And that the template contains the HTML from Chapter 4
        response = self.client.get(reverse('index'))
        self.assertIn(b'<title>', response.content)
        self.assertIn(b'</title>', response.content)


class AboutPageTests(TestCase):

    def setUp(self):
        self.client = Client()

    def test_about_contains_create_message(self):
        # Check if in the about page is there -
        # and contains the specified message
        # Exercise from Chapter 4
        response = self.client.get(reverse('rango:about'))
        self.assertIn(b'This tutorial has been put together by',
                      response.content)

    def test_about_contain_image(self):
        # Check if is there an image on the about page
        # in URL media
        # Chapter 4
        response = self.client.get(reverse('rango:about'))
        self.assertIn(b'img src="/media/', response.content)

    def test_about_using_template(self):
        #  Check the template used to render index page
        #  Exercise from Chapter 4
        import time
#        time.sleep(20)
        
        response = self.client.get(reverse('rango:about'))
        self.assertTemplateUsed(response, 'rango/about.html')

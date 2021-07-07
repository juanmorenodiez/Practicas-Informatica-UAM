# Write here any updates to this file after first release in moodle.
# modification date,    description
#jue oct 10 14:27:19 CEST 2019, add name space "rango" to reverse calls
#sat oct 12: added variable SIGIN and SIGNOUT
#########################################################################
# you may modified the following twolines
SIGNIN=b'Sign In'
SIGNUP=b'Sign Up'
###########################
# Nothing to be modified below this line
###########################
from unittest import TestCase
from django.urls import reverse
from django.contrib.auth.models import User

from rango.models import UserProfile, Page
from rango.forms import UserForm
from rango.forms import UserProfileForm
from rango.models import Category


from PIL import Image
from os.path import join
from django.conf import settings
from django.test import Client

# python ./manage.py test rango.tests.UserAuthenticationTests --keepdb
# class UserAuthenticationTests(TestCase):
from rango.tests_utils import createPicture, populate

username = "myUserName1"
passwd = "myPAssword1"
email = "kk@pp.es"
website = "http://elpais.es"
picture = "black.jpg"


class UserAuthenticationTests(TestCase):
    def setUp(self):
        self.client = Client()

    def test_index_page(self):
        """check that default page with login return 'Rango says username'
           and without login 'Rango says ... hello world'"""

        # check if user exists. if not create one
        try:
            User.objects.get(username=username)
        except User.DoesNotExist:
            user = User(username=username, email=email)
            user.set_password(passwd)
            user.save()

        # logout (just in case) -> logout redirects to index by
        # I will call it explicitely
        response = self.client.get(reverse('rango:logout'), follow=True)
        self.assertEqual(response.status_code, 200)
        response = self.client.get(reverse('index'), follow=True)

        # test message
        self.assertEqual(response.status_code, 200)  # redirection
        self.assertIn(SIGNIN, response.content)
        self.assertIn(SIGNUP, response.content)
        self.assertNotIn(b'Logout', response.content)
        self.assertNotIn(b'Add a New Category', response.content)

        # login
        loginDict = {}
        loginDict["username"] = username
        loginDict["password"] = passwd
        response = self.client.post(
            reverse('rango:login'), loginDict, follow=True)  # follow redirection
        self.assertEqual(response.status_code, 200)
        response = self.client.get(reverse('index'), follow=True)

        # test message
        self.assertIn(b'Logout', response.content)
        self.assertNotIn(b'Login', response.content)
        self.assertIn(b'Add a New Category', response.content)

    def test_add_category(self):
        # create user and login
        self.test_index_page()
        # delete category if it exists
        try:
            category = Category.objects.get(slug='testcategory')
            category.delete()
        except Category.DoesNotExist:
            pass

        catDict = {}
        catDict["name"] = 'testcategory'
        catDict["likes"] = 0
        catDict["views"] = 0
        self.client.post(reverse('rango:add_category'), catDict)
        try:
            category = Category.objects.get(slug='testcategory')
            self.assertTrue(True)
        except Category.DoesNotExist:
            self.assertTrue(False, 'No new category has been created')

    def test_add_page(self):
        # create category, user and login
        self.test_add_category()

        # delete page if it exists
        try:
            page = Page.objects.get(title='testpage')
            page.delete()
        except Page.DoesNotExist:
            pass

        # get category
        category = Category.objects.get(slug='testcategory')
        pageDict = {}
        pageDict["title"] = 'testpage'
        pageDict["category"] = category
        pageDict["views"] = 0
        pageDict["url"] = 'http://www.elpais.es'

        self.client.post(
            reverse('rango:add_page',
                    kwargs={'category_name_slug': category.slug}), pageDict)
        try:
            page = Page.objects.get(title='testpage')
            self.assertTrue(True)
        except Page.DoesNotExist:
            self.assertTrue(False, 'No new page has been created')

    def test_create_user_using_view(self):
        """  test user creation functions in views.py (no form used)"""
        # delete user if it exists
        try:
            userKK = User.objects.get(username=username)
            userKK.delete()
        except User.DoesNotExist:
            pass
        # create user self.username with password self.passwd
        # fill user form
        loginDict = {}
        loginDict["username"] = username
        loginDict["email"] = email
        loginDict["password"] = passwd
        userForm = UserForm(data=loginDict)

        # fill profile form
        profileDict = {}
        profileDict['website'] = website
        # create auxiliary black image for profileForm
        filesDict = {'picture': createPicture()}
        userProfileForm = UserProfileForm(data=profileDict, files=filesDict)

        if userForm.is_valid() and userProfileForm.is_valid():
            try:
                # Save the user's form data to the database.
                user = userForm.save()
                # Now we hash the password with the set_password method.
                # Once hashed, we can update the user object.
                user.set_password(user.password)
                user.save()
                # we need to set a user object in userprofile
                userprofile = userProfileForm.save(commit=False)
                userprofile.user = user
                userprofile.save()

            except Exception as e:
                raise Exception("Error processing form: %s" % e.message)

        self.assertTrue(userForm.is_valid())
        self.assertTrue(userProfileForm.is_valid())

        # check user name
        try:
            userKK = User.objects.get(username=username)
        except User.DoesNotExist:
            userKK = User()
        self.assertEqual(userKK.email, email)

        # check file name
        try:
            userprofileKK = UserProfile.objects.get(user=userKK)
        except User.DoesNotExist:
            userprofileKK = UserProfile()
        imageName = join(settings.MEDIA_ROOT, userprofileKK.picture.name)
        with Image.open(imageName) as im:
            width, height = im.size
        self.assertEqual(width, 200)

    def test_register_page(self):
        """  test user creation functions using web form"""
        # delete user if it exists
        try:
            userKK = User.objects.get(username=username)
            userKK.delete()
        except User.DoesNotExist:
            pass

        loginDict = {}
        loginDict["username"] = username
        loginDict["email"] = email
        loginDict["password"] = passwd
        loginDict['website'] = website
        loginDict['picture'] = createPicture()

        response = self.client.post(
            reverse('rango:register'), loginDict, follow=True)  # follow redirection
        self.assertEqual(response.status_code, 200)  # redirection
        userKK = User.objects.get(username=username)
        self.assertEqual(username, userKK.username)
        userProfileKK = UserProfile.objects.get(user=userKK)
        self.assertEqual(website, userProfileKK.website)
        imageName = join(settings.MEDIA_ROOT, userProfileKK.picture.name)
        with Image.open(imageName) as im:
            width, height = im.size
        self.assertEqual(width, 200)

    def test_category_page(self):
        """check that  category page with no login does not allow
        to add pages"""
        # check if user exists. if not create one
        try:
            User.objects.get(username=username)
        except User.DoesNotExist:
            user = User(username=username, email=email)
            user.set_password(passwd)
            user.save()

        # populate database (in case is empty)
        populate()

        # logout (in case we are logged in)
        response = self.client.get(reverse('rango:logout'), follow=True)
        self.assertEqual(response.status_code, 200)  # redirection

        # connect category/python page (no add_page available)
        # see urls.py to understand kwargs values
        # this test will work even if we cannot connect to the category page
        response = self.client.get(
            reverse('rango:show_category', kwargs={'category_name_slug': 'python'}))
        self.assertIn(b'Official Python Tutorial', response.content)
        self.assertNotIn(b'add_page', response.content)

        # login
        loginDict = {}
        loginDict["username"] = username
        loginDict["password"] = passwd
        response = self.client.post(
            reverse('rango:login'), loginDict, follow=True)  # follow redirection
        self.assertEqual(response.status_code, 200)  # redirection

        # connect category/python page (now add_page is available)
        response = self.client.get(
            reverse('rango:show_category', kwargs={'category_name_slug': 'python'}))
        self.assertIn(b'Official Python Tutorial', response.content)
        self.assertIn(b'add_page', response.content)

from PIL import Image
from io import BytesIO
from django.core.files.uploadedfile import InMemoryUploadedFile

username = "k"
passwd = "p"
email = "kk@pp.es"
website = "http://elpais.es"
picture = "black.jpg"


def populate():
    """  auxiliary function to populate database
    """
    try:
        from populate_rango import populate
        populate()
    except ImportError:
        print('The module populate_rango does not exist')
    except NameError:
        print('The function populate() does not exist or is not correct')
    except Exception:
        print('Something went wrong in the populate() function :-(')
        raise


def createPicture():
    """Auxiliary file to create a picture"""
    im = Image.new(mode='RGB', size=(200, 200))  # create a new image using PIL
    im_io = BytesIO()  # a StringIO object for saving image
    im.save(im_io, 'JPEG')  # save the image to im_io
    im_io.seek(0)  # seek to the beginning

    image = InMemoryUploadedFile(
        im_io, None, picture, 'image/jpeg', 200 * 200, None)  # im_io.len, None

    return image






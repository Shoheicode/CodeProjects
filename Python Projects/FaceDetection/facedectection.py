import cgi
from base64 import b64decode
import face_recognition

formData = cgi.FieldStorage()
face_match = 0
image= formData.getvalue("current_image")

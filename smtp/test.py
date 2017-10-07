import smtplib
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

# Load the image you want to send at bytes
img_data = open('logo.jpg', 'rb').read()

# Create a "related" message container that will hold the HTML 
# message and the image
msg = MIMEMultipart(_subtype='related')

# Create the body with HTML. Note that the image, since it is inline, is 
# referenced with the URL cid:myimage... you should take care to make
# "myimage" unique
body = MIMEText('<p>Hello <img src="cid:myimage" /></p>', _subtype='html')
msg.attach(body)

# Now create the MIME container for the image
img = MIMEImage(img_data, 'jpeg')
img.add_header('Content-Id', '<myimage>')  # angle brackets are important
msg.attach(img)

sendmail(subject, msg.as_string(), ajit, [ajittethys.vegayan], priority="high")

from qrcode import *

img = make("https://youtu.be/xvFZjo05PgG0")

img.save("qr.png", "PNG")

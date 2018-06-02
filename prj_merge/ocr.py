#-*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import argparse
import io

from google.cloud import vision
def detect_text(path):
    #path = "test.jpg"

    """Detects text in the file."""
    client = vision.ImageAnnotatorClient()

    # [START migration_text_detection]
    with io.open(path, 'rb') as image_file:
        content = image_file.read()

    image = vision.types.Image(content=content)

    response = client.text_detection(image=image)
    texts = response.text_annotations
    result = ""
    first_flag = 0
    for text in texts:
	if first_flag == 0:
		first_flag = 1
		continue
	result += text.description + '\n'
	result += str(text.bounding_poly.vertices[0].x) + '\n' + str(text.bounding_poly.vertices[0].y) + '\n'	 
	result += str(text.bounding_poly.vertices[2].x) + '\n' + str(text.bounding_poly.vertices[2].y) + '\n'
    return result
	
if __name__ == '__main__':
    detect_text('test3.jpg') # 직접 파일 같은데 있다고 가정.

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
    #print('Texts:')

    for text in texts:
        #print( '\n"{}"'.format(text.description) ) # 무슨 문자 써졌는지 표시.
        return text.description
        break

        #vertices = (['({},{})'.format(vertex.x, vertex.y) # 좌표 형식으로 분단.
                    #for vertex in text.bounding_poly.vertices])

        #print('bounds: {}'.format(','.join(vertices))) # 양 4사이드 좌표 표시.

if __name__ == '__main__':
    detect_text('test3.jpg') # 직접 파일 같은데 있다고 가정.

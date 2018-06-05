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

    #첫번째 인접 처리 구문가져오기
    parse_list = []
    for text in texts:
	parse_list = text.description.split("\n")
	break;
 
    result = ""
    first_flag = 0
    second_flag = 0
    up_flag = down_flag = 0
    list_idx = 0
    temp_up_x = temp_up_y = temp_down_x = temp_down_y = ""
    string_temp = ""
    for text in texts:
		
	# 첫 description 빼기
	if first_flag == 0:
		first_flag = 1
		continue
	# 단어 집합의 왼쪽 위 좌표 저장
	if second_flag == 0:
		temp_up_x = str(text.bounding_poly.vertices[0].x)
		temp_up_y = str(text.bounding_poly.vertices[0].y)
		second_flag = 1

	if parse_list[list_idx].find(text.description) != -1 and len(string_temp) < len(parse_list[list_idx]) :
		string_temp += text.description
		temp_down_x = str(text.bounding_poly.vertices[2].x)
		temp_down_y = str(text.bounding_poly.vertices[2].y)	
	else :
		result += parse_list[list_idx] + '\n' + temp_up_x + '\n' +  temp_up_y + '\n' +  temp_down_x + '\n' +  temp_down_y + '\n'
		string_temp = text.description
		temp_up_x = str(text.bounding_poly.vertices[0].x)
		temp_up_y = str(text.bounding_poly.vertices[0].y)
		list_idx += 1	
	#print temp_up_x +  ' ' + temp_up_y + ' ' + temp_down_x + ' ' +  temp_down_y 
    
    result += string_temp + '\n' + temp_up_x + '\n' +  temp_up_y + '\n' +  temp_down_x + '\n' +  temp_down_y + '\n'
    # end(for text)
    # print result 
    
    return result
	
if __name__ == '__main__':
    detect_text('test3.jpg') # 직접 파일 같은데 있다고 가정.

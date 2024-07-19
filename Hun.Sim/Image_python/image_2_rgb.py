from PIL import Image
 
# 이미지 파일 열기
image = Image.open("apple-98.png")  # 이미지 파일의 경로를 제공해야 합니다.
 
# 이미지가 RGB 모드가 아니라면 RGB 모드로 변환
if image.mode != 'RGB':
    image = image.convert('RGB')
 
# 이미지 크기 강제로 변환
width, height = 20, 20
image = image.resize((width, height), Image.LANCZOS)
 
# 픽셀 수 계산
pixel_count = width * height
 
# 변환된 데이터를 저장할 빈 리스트 생성
rgb565_data = []
 
# 이미지 픽셀 순회 및 RGB565로 변환
for y in range(height):
    for x in range(width):
        r, g, b = image.getpixel((x, y))
        # RGB565로 변환
        rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
        rgb565_data.append(rgb565)
 
# 변환된 데이터를 txt 파일로 저장
with open("output2.txt", "w") as file:
    file.write("const unsigned short test[{}] PROGMEM = {{\n".format(pixel_count))
    for i, data in enumerate(rgb565_data):
        if i % 16 == 0 and i != 0:
            file.write("\n")
        file.write("0x{:04X}".format(data))
        if i < len(rgb565_data) - 1:
            file.write(", ")
    file.write("\n};")
 
print("RGB565 데이터를 output.txt 파일로 저장했습니다.")
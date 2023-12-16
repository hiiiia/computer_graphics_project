import cv2

# 이미지 읽기
img = cv2.imread('snow.png', cv2.IMREAD_UNCHANGED)

# 이미지가 알파 채널을 가지고 있는지 확인
if img.shape[2] == 4:
    print("이미지에 알파값이 있습니다.")
else:
    print("이미지에 알파값이 없습니다.")

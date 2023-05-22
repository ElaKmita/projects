# TWORZENIE ZDJECIA WZORCOWEGO
import cv2 # importowanie biblioteki OpenCV

cap = cv2.VideoCapture(0)
print("Press p button to save the picture \nPress q button to quit")
while(True):
    ret,frame = cap.read() # zwraca pojedynczy obraz z kamery do zmiennej "frame"
    cv2.imshow('PHOTO',frame) # wyswietlanie przechwyconego obrazu
    if cv2.waitKey(1) & 0xFF == ord('p'): # zapisywanie zdjecia poprzez nacisniecie klawisza 'p'
        cv2.imwrite('zdjecie_wzorcowe.png',frame) # zapisywanie zdjecia wzorcowego pod nazwa 'zdjecie_wzorcowe.png'
        print("Zdjecie wzorcowe zostalo zapisane")
    if cv2.waitKey(1) & 0xFF == ord('q'): # nacisniecie klawisza "q" powoduje przerwanie i zakonczenie programu
        cv2.destroyAllWindows()
        break
cap.release()
import cv2 # importowanie biblioteki OpenCV
import numpy as np # importowanie biblioteki NumPy
from funkcja import find_contour_palette, find_element, compare_position # importowanie nowych funkcji
import pyqrcode # importowanie biblioteki ulatwiajacej prace z kodami QR
import png

    # ZDJECIE WZORCOWE
reference_img = cv2.imread('zdjecie_wzorcowe.png', 1) # wczytywanie zdecia wzorcowego

# wykrywanie konturu palety oraz odczytywanie skrajnych i srodkowych wartosci
reference_palette_contour, ref_width_palette, ref_height_palette = find_contour_palette(reference_img)

# wykrywanie konturu poszczegolnych waleczkow oraz odczytywanie skrajnych i srodkowych wartosci
ref_elem1, ref_width_elem1, ref_height_elem1 = find_element(1, reference_img, reference_palette_contour,
ref_width_palette, ref_height_palette)
ref_elem2, ref_width_elem2, ref_height_elem2 = find_element(2, reference_img, reference_palette_contour,
ref_width_palette, ref_height_palette)
ref_elem3, ref_width_elem3, ref_height_elem3 = find_element(3, reference_img, reference_palette_contour,
ref_width_palette, ref_height_palette)
ref_elem4, ref_width_elem4, ref_height_elem4 = find_element(4, reference_img, reference_palette_contour,
ref_width_palette, ref_height_palette)
reference_palette_contour = reference_palette_contour[0]

# ZDJECIE RZECZYWISTE - PRZECHWYTYWANIE OBRAZU Z KAMERY
stream = cv2.VideoCapture(0)
if not stream.isOpened():
    print("No stream :(")
    exit()
while (True):
    ret, frame = stream.read()
    if not ret: # if no frames are returned
        print("No more stream :(")
        break
    cv2.imshow("Webcam!", frame)

    # po wciśnięciu klawisza x, program sprawdza klatkę z obrazu
    if cv2.waitKey(1) == ord('x'):
        # odczytywanie kodow QR
        det = cv2.QRCodeDetector()
        val, pts, st_code = det.detectAndDecode(frame)
        print("QR:")
        print(val)
        E1_exist = bool(val[6])
        E2_exist = bool(val[7])
        E3_exist = bool(val[8])
        E4_exist = bool(val[9])
        # wyszukiwanie konturów palety i wałeczków dla poszczególnych klatek przechwytywanego obrazu
        palette_contour, width_palette, height_palette = find_contour_palette(frame)
        palette_contour = palette_contour[0]
        elem1, width_elem1, height_elem1 = find_element(1, frame, palette_contour, width_palette, height_palette)
        elem2, width_elem2, height_elem2 = find_element(2, frame, palette_contour, width_palette, height_palette)
        elem3, width_elem3, height_elem3 = find_element(3, frame, palette_contour, width_palette, height_palette)
        elem4, width_elem4, height_elem4 = find_element(4, frame, palette_contour, width_palette, height_palette)
        img_diff_1 = cv2.matchShapes(reference_palette_contour, palette_contour, cv2.CONTOURS_MATCH_I1, 0)
        # sprawdzenie czy paleta i waleczki sa ułożone prawidłowo
        tolerance = 6
        suma = compare_position(ref_width_palette, width_palette, ref_height_palette, height_palette, tolerance)
        sum_e1= compare_position(ref_width_elem1, width_elem1, ref_height_elem1, height_elem1, tolerance)
        sum_e2= compare_position(ref_width_elem2, width_elem2, ref_height_elem2, height_elem2, tolerance)
        sum_e3= compare_position(ref_width_elem3, width_elem3, ref_height_elem3, height_elem3, tolerance)
        sum_e4= compare_position(ref_width_elem4, width_elem4, ref_height_elem4, height_elem4, tolerance)

        if img_diff_1 < 0.3:
            if suma == 6:
                print("OK - Paleta prawidlowo uzlozona")
            else:
                print("ERROR - Nieprawidlowe ulozenie palety")
        else:
            print("ERROR - Nieprawidlowe ulozenie palety")
        if E1_exist:
            if sum_e1 == 6:
                print("OK - Walek prawidlowo ulozony")
            else:
                print("ERROR - Walek nieprawidlowo ulozony")
        else:
            if sum_e1 == 6:
                print("ERROR - Nie powinno byc tu walka")
            else:
                print("OK - Nie ma walka w tym miejscu")
        if E2_exist:
            if sum_e2 == 6:
                print("OK - Walek prawidlowo ulozony")
            else:
                print("ERROR - Walek nieprawidlowo ulozony")
        else:
            if sum_e2 == 6:
                print("ERROR - Nie powinno byc tu walka")
            else:
                print("OK - Nie ma walka w tym miejscu")
        if E3_exist:
            if sum_e3 == 6:
                print("OK - Walek prawidlowo ulozony")
            else:
                print("ERROR - Walek nieprawidlowo ulozony")
        else:
            if sum_e3 == 6:
                print("ERROR - Nie powinno byc tu walka")
            else:
                print("OK - Nie ma walka w tym miejscu")
        if E4_exist:
            if sum_e4 == 6:
                print("OK - Walek prawidlowo ulozony")
            else:
                print("ERROR - Walek nieprawidlowo ulozony")
        else:
            if sum_e4 == 6:
                print("ERROR - Nie powinno byc tu walka")
            else:
                print("OK - Nie ma walka w tym miejscu")
                
        if cv2.waitKey(1) == ord('q'): # nacisniecie klawisza "q" powoduje przerwanie i zakonczenie programu
            break

stream.release()
cv2.destroyAllWindows() #
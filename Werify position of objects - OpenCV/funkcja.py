import cv2
import numpy as np
import math

# Funkcja konwertująca zdjęcie do HSV
def convert_to_HSV(img):
    img = cv2.resize(img, (0,0), fx = 0.8, fy=0.8) # zmniejszenie wyświetlanego oobrazu
    img_HSV = cv2.cvtColor(img, cv2.COLOR_RGB2HSV) # zmiana modelu przestrzeni barw z RGB na HSV
    HSV_h, HSV_s, HSV_v=cv2.split(img_HSV) # wyciągnięcie poszczególnych informacji (elementów) z modelu HSV
    return(HSV_h, HSV_s, HSV_v)

# Wyznaczenie maksymalnych minimalnych i srodkowych współrzędnych wysokościowych i szerokościowych elementu
def min_mid_max(contour):
    temp = contour[0][:]
    list_dim = len(temp) # rozmiar listy
    width_list = [] # stworzenie listy składającej się z samych współrzędnych palety po szerokości
    height_list = [] # stworzenie listy składającej się z samych współrzędnych plety po wysokości
    for i in range(0, list_dim):
        temp_1 = temp[i]
        temp_2 = temp_1[0]
        width_list.append(temp_2[0]) # dodawanie do listy kolejnych współrzędnych szerokości
        height_list.append(temp_2[1]) # dodawanie do listy kolejnych współrzędnych wysokości
    min_width = min(width_list) # minimalna współrzędna palety po szerokości
    max_width = max(width_list) # maksymalna współrzędna palety po szerokości
    min_height = min(height_list) # minimalna współrzędna palety po wysokości
    max_height = max(height_list) # maksymalna współrzędna palety po wysokości
    '''
    Podzielenie palety na strefy
    Na palecie mogą znajdować się maksymalnie 4 wałeczki, dlatego dzielę pole palety na 4 równe części,
    które oznaczone są następująco:
    P1 P2
    P3 P4
    Każda ze stref jest ograniczana przez współrzęde wysokościowe i szerokościowe
    Dla każdej współrzędnej wyróżnia się 3 punkty : minimum, środek i maksimum
    '''
    mid_width = min_width + 0.5 * (max_width - min_width)
    mid_height = min_height + 0.5 * (max_height - min_height)
    width_tuple = (min_width, mid_width, max_width)
    height_tuple = (min_height, mid_height, max_height)
    return width_tuple, height_tuple

# Funkcja wyszukująca kontur palety
def find_contour_palette(img):
    HSV_h, _, _ = convert_to_HSV(img)
    blur = cv2.GaussianBlur(HSV_h, (3,3), 0) # blurowanie obrazu
    # Tworzenie obrazu binarnego
    thresh = cv2.adaptiveThreshold(blur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 205, 1)
    # Znajdowanie konturów
    contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    img_area = HSV_h.shape[0] * HSV_h.shape[1] # pole całego obrazu [jednostka: pixel^2]
    # Filtrowanie znalezionych konturów
    filtered = [] # utworzenie listy w której będą znajdowały się kontury
    for c in contours:
        # dla każdej macierzy (konkturu) zwracanego przez funkcję findContours
        # - sprawdzenie czy kontur jest na tyle duży żeby był brany pod uwagę
        if cv2.contourArea(c) < 0.3*img_area: continue
        filtered.append(c) # dodawanie nowego elementu do stworzonej listy
        filtered_contours = len(filtered)
        # tworzenie obrazu (czarny obraz, o wymiarach począkowego obrazu) na którym tworzony będzie wstępny kontur palet
    palette = np.zeros([HSV_h.shape[0], HSV_h.shape[1], 3], 'uint8')
        # img.shape[0] - wysokość obrazu (podana jako liczba pixeli),
        # img.shape[1] - szerokość obrazu (podana jako liczba pixeli)
    contour_colour = (255,255,255) # kolor którym oznaczany jest kontur
    palette_contour = 0 # utworzenie macierzy która będzie przechowywała kontur palety
    palette_area = 0
    if filtered_contours == 1:
        if img_area > cv2.contourArea(filtered[0]): # sprawdzenie czy kontur nie jest konturem całego obrazu
            palette_contour = filtered
            cv2.drawContours(palette, palette_contour, -1, contour_colour, 1) # rysowanie konturu palety
        else:
            print("Nie znaleziono konturu spełniającego podane kryteria")
    elif filtered_contours > 1:
        for c in filtered:
            area = cv2.contourArea(c)
            if area > palette_area and area < img_area:     # wybranie konturu o największym polu
                                                            # (z wykluczeniem konturu całego obrazu)
                palette_area = area
                palette_contour = [c] # przypisanie do ostatecznego konturu, konturu o największym polu
        cv2.drawContours(palette, palette_contour, -1, contour_colour, 1) # rysowanie konturu palety
    else:
        print("Nie znaleziono konturu spełniającego podane kryteria")
    cv2.imshow("Contour", palette) # wyswietlanie ostatecznego konturu palety
    width_tuple, height_tuple = min_mid_max(palette_contour)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return palette_contour, width_tuple, height_tuple


# Funkcja wyszukująca kontur elementu (wałeczka)
def find_element(part_number, img, palette_contour, width_tuple, height_tuple):
    _, HSV_s, _ = convert_to_HSV(img)
    min_width = width_tuple[0] # minimalna współrzędna palety po szerokości
    mid_width = width_tuple[1] # środkowa współrzędna palety po szerokości
    max_width = width_tuple[2] # maksymalna współrzędna palety po szerokości
    min_height = height_tuple[0] # minimalna współrzędna palety po wysokości
    mid_height = height_tuple[1] # środkowa współrzędna palety po wysokości
    max_height = height_tuple[2] # maksymalna współrzędna palety po wysokości
    # Ustawienie zakresu na którym występuje any wałeczek
    x_min = 0
    x_max = 0
    y_min = 0
    y_max = 0
    if part_number == 1:
    # dla P1 element powinien znajdować się w zakresach:
    # dla szerokości < min_width ; mid_width>
    # dla wysokości < min_height ; mid_height>
        x_min = min_width
        x_max = mid_width
        y_min = min_height
        y_max = mid_height
    elif part_number == 2:
    # dla P2 element powinien znajdować się w zakresach:
    # dla szerokości < mid_width ; max_width>
    # dla wysokości < min_height ; mid_height>
        x_min = mid_width
        x_max = max_width
        y_min = min_height
        y_max = mid_height
    elif part_number == 3:
    # dla P3 element powinien znajdować się w zakresach:
    # dla szerokości < min_width ; mid_width>
    # dla wysokości < mid_height ; max_height>
        x_min = min_width
        x_max = mid_width
        y_min = mid_height
        y_max = max_height
    elif part_number == 4:
    # dla P4 element powinien znajdować się w zakresach:
    # dla szerokości < mid_width ; max_width>
    # dla wysokości < mid_height ; max_height>
        x_min = mid_width
        x_max = max_width
        y_min = mid_height
        y_max = max_height
    else:
        print("Wprowadzono nieprawidlowy numer waleczka")
        exit()
    blur = cv2.GaussianBlur(HSV_s, (3,3), 0) # blurowanie obrazu
    # Tworzenie obrazu binarnego
    thresh = cv2.adaptiveThreshold(blur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 105, 1)
    thresh_width = thresh.shape[0]
    thresh_height = thresh.shape[1]
    for row in range (0, thresh_width):
        for col in range (0, thresh_height):
            if col > x_min and col < x_max:
                if row > y_min and row < y_max:
                    continue
                else:
                    thresh[row][col] = 0
            else:
                thresh[row][col] = 0
    # Znajdowanie konturów
    contours, _ = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    ilosc_konturow = len(contours)
    element = np.zeros([HSV_s.shape[0], HSV_s.shape[1], 3], 'uint8')
    # Filtrowanie znalezionych konturów
    filtered = [] # utworzenie listy w której będą znajdowały się
    # kontury (macierze) spełniające warunek filtracji
    for c in contours:
        if cv2.contourArea(c) < 5000: continue # dla każdego konkturu zwracanego przez funkcję findContours
        # sprawdzam czy kontur jest na tyle duży żeby był uwzględniany
        filtered.append(c) # dodawanie nowego elementu do stworzonej listy
    filtered_contours = len(filtered)
    element_contour = filtered
    cv2.drawContours(element , element_contour, -1, (0, 0, 255), 1) # rysowanie konturu palety
    cv2.imshow("ELEMENT", element) # wyswietlanie ostatecznego konturu palety
    width_tuple, height_tuple = min_mid_max(element_contour)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    element_contour = element_contour[0]
    return element_contour, width_tuple, height_tuple

def compare_position(ref_width_tuple, width_tuple, ref_height_tuple, height_tuple, tolerance):
    suma = 0
    for i in range(0,3):
        if math.isclose(ref_width_tuple[i], width_tuple[i], abs_tol=tolerance):
            suma += 1
            if math.isclose(ref_height_tuple[i], height_tuple[i], abs_tol=tolerance):
                suma += 1
    return suma
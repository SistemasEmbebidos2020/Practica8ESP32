import cv2  #pip install opencv-python
import mediapipe as mp  #pip install mediapipe
from time import sleep
import serial   #pip install pyserial
import time

# Crear una conexión serial
ser = serial.Serial('COM5', 115200)  # Reemplaza 'COM3' con el puerto correcto

# Esperar a que la conexión se establezca
time.sleep(2)

# Inicializar MediaPipe Hands
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(static_image_mode=False,
                       max_num_hands=2,
                       min_detection_confidence=0.5)

# Inicializar MediaPipe Drawing
mp_drawing = mp.solutions.drawing_utils

# Iniciar captura de video
cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        continue

    # Convertir el color de BGR a RGB
    image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Procesar la imagen y obtener las predicciones
    result = hands.process(image)

    # Dibujar los resultados
    if result.multi_hand_landmarks:
        for hand_landmarks in result.multi_hand_landmarks:
            mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

            # Obtener las coordenadas de los puntos de referencia de la mano
            landmarks_list = [landmark for landmark in hand_landmarks.landmark]

            # Comprobar si el dedo índice está arriba o abajo
            if (landmarks_list[8].y < landmarks_list[6].y) & (landmarks_list[12].y < landmarks_list[10].y):
                print("Ambos dedos arriba")
                ser.write(b'1')  # Reemplaza 'si' con tu comando
            elif (landmarks_list[8].y < landmarks_list[6].y) & (landmarks_list[12].y > landmarks_list[10].y):
                print("Indice arriba, Corazón abajo")
                ser.write(b'2')  # Reemplaza 'no' con tu comando
            elif (landmarks_list[8].y > landmarks_list[6].y) & (landmarks_list[12].y > landmarks_list[10].y):
                print("Ambos dedos abajo")
                ser.write(b'3')  # Reemplaza 'no' con tu comando
            elif (landmarks_list[8].y > landmarks_list[6].y) & (landmarks_list[12].y < landmarks_list[10].y):
                print("Indice abajo, Corazón arriba")
                ser.write(b'4')  # Reemplaza 'no' con tu comando
    # Mostrar la imagen
    cv2.imshow('MediaPipe Hands', frame)

    # Pausa
    sleep(1)

    # Salir del bucle si se presiona la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Liberar los recursos
cap.release()
cv2.destroyAllWindows()

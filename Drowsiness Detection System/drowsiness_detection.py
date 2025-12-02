
import cv2
import pickle
from imutils.video import VideoStream
import dlib
import time
import pygame
import requests

# Initialize pygame for sound
pygame.mixer.init()
alert_sound = pygame.mixer.Sound('alert.mp3')  

pick = open('model.sav','rb')
model = pickle.load(pick)
pick.close()


catagories = ['closed_eye','open_eye']


# Initialize the face detector and shape predictor
face_detector = dlib.get_frontal_face_detector()
shape_predictor = dlib.shape_predictor('shape_predictor_68_face_landmarks.dat')

# Define constants for blink detection
EYE_CLOSED_FRAMES_THRESHOLD = 5
eye_closed_frames = 0

display_label = ''


def send_post_request(url):
    headers={'Content-Type':'application/json'}
    try:
        response = requests.post(url)
        response.raise_for_status()  # Raises an HTTPError for bad responses
        print("Response Status Code:", response.status_code)
        print("Response Body:", response.text)
    except requests.exceptions.HTTPError as errh:
        print("HTTP Error:", errh)
    except requests.exceptions.ConnectionError as errc:
        print("Error Connecting:", errc)
    except requests.exceptions.Timeout as errt:
        print("Timeout Error:", errt)
    except requests.exceptions.RequestException as err:
        print("OOps: Something Else", err)

def capture_and_classify():
    global eye_closed_frames
    global display_label

    # Start the video stream
    vs = VideoStream(src=0).start() 

    # Allow the camera to warm up
    time.sleep(2.0)

    while True:
        # Capture frame-by-frame
        frame = vs.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Detect faces in the grayscale frame
        faces = face_detector(gray)

        eye_labels = []

        # Draw bounding boxes around detected faces and detect eyes
        for face in faces:
            x, y, w, h = face.left(), face.top(), face.width(), face.height()
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # Get the landmarks/parts for the face in box
            shape = shape_predictor(gray, face)

            # Extract the coordinates for the left and right eye
            left_eye_points = shape.parts()[36:42]
            right_eye_points = shape.parts()[42:48]

            for eye_points in [left_eye_points, right_eye_points]:
                eye_region = [(point.x, point.y) for point in eye_points]
                x_min = min([point[0] for point in eye_region])
                y_min = min([point[1] for point in eye_region])
                x_max = max([point[0] for point in eye_region])
                y_max = max([point[1] for point in eye_region])
                cv2.rectangle(frame, (x_min, y_min), (x_max, y_max), (255, 0, 0), 2)

                # Extract the eye region and preprocess
                eye_region_gray = gray[y_min:y_max, x_min:x_max]
                eye = cv2.resize(eye_region_gray, (50, 50)).flatten().reshape(1, -1)

                # Predict the state of the eye (open or closed)
                prediction = model.predict(eye)
                eye_labels.append(catagories[prediction[0]])

        # Determine the overall label to display
        if eye_labels.count('closed_eye') == 2:
            eye_closed_frames += 1
        else:
            eye_closed_frames = 0

        if eye_closed_frames >= EYE_CLOSED_FRAMES_THRESHOLD:
            display_label = 'closed_eye'
            if not pygame.mixer.get_busy():
                alert_sound.play()
            send_post_request('http://192.168.43.203:8001/api/detect/66636941e53814cab6b4973c')
        elif eye_labels.count('open_eye') >= 1:
            display_label = 'open_eye'

        # Display the results on the frame
        cv2.putText(frame, display_label, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255), 2)
        cv2.imshow("Frame", frame)

        # If the `q` key was pressed, break from the loop
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        if cv2.waitKey(1) & 0xFF == ord('p'):
            if pygame.mixer.get_busy():
                alert_sound.stop()       

    # Cleanup
    cv2.destroyAllWindows()
    vs.stop()

if __name__ == "__main__":
    capture_and_classify()

import sys
import serial
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QLabel
from PyQt5.QtCore import Qt, QTimer, pyqtSignal

# Configure your Arduino port and baudrate
SERIAL_PORT = '/dev/ttyUSB0'
BAUD_RATE = 115200
LONG_PRESS_DURATION = 500  # milliseconds

# Initialize serial connection
try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"✅ Serial port {SERIAL_PORT} opened successfully")
except serial.SerialException:
    ser = None
    print(f"⚠️ Could not open serial port {SERIAL_PORT}")

class LedControlUI(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("LED Control")
        self.setGeometry(500, 300, 300, 200)
        self.setStyleSheet("background-color: black;")

        self.label = QLabel("Press the button to toggle LED", self)
        self.label.setStyleSheet("color: white; font-size: 16px;")
        self.label.setAlignment(Qt.AlignCenter)

        self.button = LedControlPushButton("LED", self)
        self.button.setFixedSize(100, 100)
        self.button.setStyleSheet("""
            QPushButton {
                background-color: white;
                border-radius: 50px;
                font-size: 18px;
                font-weight: bold;
            }
            QPushButton:pressed {
                background-color: #cccccc;
            }
        """)

        layout = QVBoxLayout()
        layout.addStretch()
        layout.addWidget(self.label)
        layout.addWidget(self.button, alignment=Qt.AlignCenter)
        layout.addStretch()
        self.setLayout(layout)
        
        # Connect signals from custom button to UI methods
        self.button.short_press_signal.connect(self.handle_short_press)
        self.button.long_press_signal.connect(self.handle_long_press)

    def handle_short_press(self):
        self.label.setText("Short Press Detected! 🟢")
        print("Short Press!")
        if ser and ser.is_open:
            ser.write(b'Q')  # Q for Short Press
        else:
            print("⚠️ Serial not connected")

    def handle_long_press(self):
        self.label.setText("Long Press Detected! 🔴")
        print("Long Press!")
        if ser and ser.is_open:
            ser.write(b'L')  # L for Long Press
        else:
            print("⚠️ Serial not connected")

class LedControlPushButton(QPushButton):
    """
    A custom QPushButton that can detect short and long presses.
    """
    # Define custom signals here
    short_press_signal = pyqtSignal()
    long_press_signal = pyqtSignal()

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.timer = QTimer()
        self.timer.setInterval(LONG_PRESS_DURATION)
        self.timer.setSingleShot(True)
        self.timer.timeout.connect(self.on_long_press)
        self.is_long_press = False

    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.is_long_press = False
            self.timer.start()
            super().mousePressEvent(event) # Call original method for visual feedback

    def mouseReleaseEvent(self, event):
        if event.button() == Qt.LeftButton:
            if self.timer.isActive():
                self.timer.stop()
                if not self.is_long_press:
                    self.short_press_signal.emit() # Emit the short press signal
            super().mouseReleaseEvent(event) # Call original method for visual feedback

    def on_long_press(self):
        self.is_long_press = True
        self.long_press_signal.emit() # Emit the long press signal

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = LedControlUI()
    window.show()
    sys.exit(app.exec_())
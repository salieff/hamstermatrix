import serial
import pyaudio
import wave
import time


class Hamster:
    IDLE = 0
    WAIT_READY = 1
    WAIT_FORWARD = 2
    WAIT_TIME = 3
    WAIT_BYE = 4
    FINISHED = 5

    def __init__(self):
        self.state = self.IDLE
        self.portaudio_interface = None
        self.portaudio_stream = None
        self.portaudio_frames = list()

        self.serial_port = serial.Serial()
        self.serial_port.port = '/dev/ttyUSB0'
        self.serial_port.baudrate = 115200
        self.serial_port.rts = 0
        self.serial_port.dtr = 0

        self.current_click_code = 0
        self.reverse_code = False
        self.record_time = 0
        self.forward_counter = 0
        self.start_time = 0
        self.motor_voltages = list()

    def start(self, click_code, reverse_code=False, record_time=20):
        self.state = self.WAIT_READY
        self.current_click_code = click_code
        self.reverse_code = reverse_code
        self.record_time = record_time

        self.open_uart()
        self.open_audio()

        while self.state != self.FINISHED:
            self.process_uart()
            self.process_audio()

        self.close_uart()
        self.close_audio()

        self.write_motor_voltage()
        self.write_audio()

    def open_uart(self):
        self.motor_voltages = list()
        self.serial_port.open()

    def process_uart(self):
        if self.state == self.WAIT_TIME and time.time() - self.start_time >= self.record_time:
            self.start_time = time.time()
            self.state = self.WAIT_BYE
            self.serial_port.write(b'STOP\n')
            return

        if self.state == self.WAIT_BYE and time.time() - self.start_time >= 3:
            self.state = self.FINISHED
            return

        if self.serial_port.in_waiting <= 0:
            return

        line = self.serial_port.readline().decode('utf-8')

        motor_voltage = None
        if line.startswith('[[HMSTRMTRX]] MOTOR '):
            motor_voltage = int(line[20:])
            self.motor_voltages.append({'voltage': motor_voltage, 'trigger': 0})

        if line.startswith('[[HMSTRMTRX]] TRIGGERS '):
            trigger_value = int(line[23:24]) * int(line[25:]) * 1000 + 1000
            self.motor_voltages[-1]['trigger'] = trigger_value if self.motor_voltages else self.motor_voltages.append({'voltage': 0, 'trigger': trigger_value})

        if self.state == self.WAIT_READY and line == '[[HMSTRMTRX]] READY\r\n':
            self.forward_counter = 0
            self.state = self.WAIT_FORWARD
            self.serial_port.write(b'START\n')
            return

        if self.state == self.WAIT_FORWARD and motor_voltage is not None:
            if motor_voltage <= 0:
                self.forward_counter = 0
                return

            self.forward_counter += 1
            if self.forward_counter >= 10:
                self.send_click_code()
                self.start_time = time.time()
                self.state = self.WAIT_TIME
                return

    def send_click_code(self):
        if self.reverse_code:
            self.serial_port.write(b'REVTRIGGER %a\n' % self.current_click_code)
        else:
            self.serial_port.write(b'TRIGGER %a\n' % self.current_click_code)

    def close_uart(self):
        self.serial_port.close()

    def write_motor_voltage(self):
        with open(Hamster.motor_file_name(self.current_click_code, self.reverse_code), 'w') as file:
            file.write('\n'.join(str(item['voltage']) + ' ' + str(item['trigger']) for item in self.motor_voltages))

    def open_audio(self):
        self.portaudio_interface = pyaudio.PyAudio()
        self.portaudio_stream = self.portaudio_interface.open(
            format=pyaudio.paInt16,
            channels=1,
            rate=44100,
            frames_per_buffer=1024,
            input=True
        )
        self.portaudio_frames = list()

    def process_audio(self):
        data = self.portaudio_stream.read(1024)
        self.portaudio_frames.append(data)

    def close_audio(self):
        self.portaudio_stream.stop_stream()
        self.portaudio_stream.close()
        self.portaudio_interface.terminate()

    def write_audio(self):
        wave_file = wave.open(Hamster.audio_file_name(self.current_click_code, self.reverse_code), 'wb')
        wave_file.setnchannels(1)
        wave_file.setsampwidth(self.portaudio_interface.get_sample_size(pyaudio.paInt16))
        wave_file.setframerate(44100)
        wave_file.writeframes(b''.join(self.portaudio_frames))
        wave_file.close()

    @staticmethod
    def audio_file_name(click_code, reverse_code=False):
        return f'report/{click_code:03d}' + ('R' if reverse_code else 'F') + '-hamster-sound.wav'

    @staticmethod
    def motor_file_name(click_code, reverse_code=False):
        return f'report/{click_code:03d}' + ('R' if reverse_code else 'F') + '-hamster-motor.log'
